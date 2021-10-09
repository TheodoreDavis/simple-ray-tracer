#include <inc/Sphere.h>
#include <inc/Triangle.h>
#include <inc/ShapeList.h>
#include <inc/Image.h>
#include <inc/HitRecord.h>

#include <iostream>
#include <vector>
#include <cmath>

#define MAX_DEPTH 6
#define ANTI_ALIASING 4
#define BG_COLOR V3(0.22,0.424,0.62)

V3 getColor(const Ray& r, const Shapelist& shapes, float currIndex, int depth);
V3 specularAlgo(const Ray& in, const V3& norm, const V3& point, const float intensity, const float currIndex, const Shapelist& shapes, int depth);
V3 glassAlgo(const Ray& in, const V3& norm, const V3& point, const float intensity, const float indexMat1, const float indexMat2, const Shapelist& shapes, int depth);

int main(int argc, char *argv[]) {
    // TODO if need user imput
    // if(argc < 2) {
    //     std::cout << " An example use of this program is as follows:" << std::endl;
    //     std::cout << "./ray-tracer" << std::endl;
    // }

    // Origin of all the rays
    V3 origin = V3(0,0,0);

    // Point light in the space
    //V3 pLight = V3(-2,2,1);

    // View plane of pixels
    V3 plane = V3(0,0,1);

    //Add shapes into our space
    //std::vector<shape> shapes;
    //shapes.push_back(Sphere(V3(0,0,2), 1.0));
    Shapelist shapes = Shapelist();
	//shapes.add(new Triangle(V3(-0.25f,-0.25f,0.5f), V3(-0.0f,-0.25f,0.5f), V3(-0.0f,0.0f,0.5f), material(V3(0.0,255.0,0.0))));
    shapes.add(new Sphere(V3(0.3,0,7), .4, Material(.2, 0, .0, .8, 1.6, V3(.7, .2, .7))));
    shapes.add(new Sphere(V3(0,0,4), 2, Material(0, 0, 1.0, 0, 1.3, V3(0.392, 0.584, 0.929))));
    shapes.add(new Sphere(V3(4,0,4.5), 1.0, Material(0.99, V3(.9,.9,.9))));
    shapes.add(new Sphere(V3(0,1004,4), 1000, Material(0.3, V3(0.7,0.7,0.7))));
    shapes.add(new Sphere(V3(0,-1004,4), 1000, Material(V3(0.2,0.2,0.2))));

    // Image data
    uint32_t height = 3000, width = 4000;
    float unitHeight = 3, unitWidth = 4;
    float hHeight = unitHeight / 2.0, hWidth = unitWidth / 2.0;
    float iHeight = 1.0 / height, iWidth = 1.0 / width;

    V3 **image = new V3*[height];
	
    float prog = 0;
    for(uint32_t y = 0; y < height; y++) {
        image[y] = new V3[width];

        float cur = (float) y / (float) height;
        if(CMPFLOAT_EGREATER(cur - prog, 0.01)) {
            prog += cur;
            std::cout << cur << "%" << std::endl; // Progress updates every 1%
        }
        for(uint32_t x = 0; x < width; x++) {
            // Grab dir for the pixel
            V3 color = V3(0,0,0);
            for(int i=0; i < ANTI_ALIASING; i++) {
                V3 dir = V3(plane.x() - hWidth + unitWidth * (x + 1) * iWidth + FLOAT_RAND * iWidth,
                        plane.y() + hHeight - unitHeight * (y + 1) * iHeight - FLOAT_RAND * iHeight,
                        plane.z() - origin.z()).unitVector();
			
                Ray cast = Ray(origin, dir, 1.0);
                color += getColor(cast, shapes, 1.0, 0);
            }
            image[y][x] = color / ANTI_ALIASING;
        }
    }
	
	image_write_rgb("./out/output", image, height, width);
	
	for(uint32_t y = 0; y < height; y++) { delete[] image[y]; }
    delete[] image;

	return 0;
}

V3 getColor(const Ray& r, const Shapelist& shapes, float currIndex, int depth) {
    V3 color = V3(0,0,0);

    // Ray doesn't have enough strength to return the light
    if(CMPFLOAT_ELESS(r.intensity(), 0.0) || depth >= MAX_DEPTH)
        return color;

    HitRecord hit;

    if(shapes.intersectionAtRay(r, hit)) {

        // Look at specular
        if(CMPFLOAT_NEQUAL(hit.getMaterial().specular(), 0.0)) {
            color += specularAlgo(r, hit.normal(), hit.point(), hit.getMaterial().specular(), currIndex, shapes, depth + 1);
        }

        // Look at ...

        // Look at glass
        if(CMPFLOAT_NEQUAL(hit.getMaterial().glass(), 0.0)) {
            // Exiting object into air
            if(CMPFLOAT_EQUAL(currIndex, hit.getMaterial().indexOfReflection()))
                color += glassAlgo(r, -hit.normal(), hit.point(), hit.getMaterial().glass(), currIndex, 1.0, shapes, depth + 1);
            else
                color += glassAlgo(r, hit.normal(), hit.point(), hit.getMaterial().glass(), currIndex, hit.getMaterial().indexOfReflection(), shapes, depth + 1);
        }

        // Look at absorbtion
        if(CMPFLOAT_NEQUAL(hit.getMaterial().absorb(), 0.0)) {
            color += hit.getMaterial().absorb() * hit.getMaterial().color();
        }

    } else {
        color = BG_COLOR;
    }

    return r.intensity() * color;
}

V3 specularAlgo(const Ray& in, const V3& norm, const V3& point, const float intensity, const float currIndex, const Shapelist& shapes, int depth) {
    V3 outDir = in.dir() - 2 * in.dir().dotProduct(norm) * norm;
    Ray out = Ray(point, outDir, intensity);
    return getColor(out, shapes, currIndex, depth);
}

V3 glassAlgo(const Ray& in, const V3& norm, const V3& point, const float intensity, const float indexMat1, const float indexMat2, const Shapelist& shapes, int depth) {
    float cosTheta = norm.dotProduct(-in.dir());
    float sinTheta = sqrt(1.0 - cosTheta * cosTheta);
    float ratio = indexMat1 / indexMat2;

    // Schlick's approximation
    float temp = (1 - ratio) / (1 + ratio);
    temp *= temp;
    temp = temp + (1.0 - temp) * pow((1.0-cosTheta), 5);
    bool schlick = CMPFLOAT_LESS(FLOAT_RAND, temp);

    // Reflect if TIR or Schlicks
    if(CMPFLOAT_GREATER(ratio * sinTheta, 1.0) || schlick)
        return specularAlgo(in, norm, point, intensity, indexMat1, shapes, depth);

    V3 tperp = ratio * (in.dir() + cosTheta * norm);
    V3 t = tperp - sqrt(1.0 - tperp.magnitudeSquared()) * norm;
    Ray out = Ray(point, t, intensity);
    return getColor(out, shapes, indexMat2, depth);
}