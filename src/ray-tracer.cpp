#include <inc/Sphere.h>
#include <inc/Triangle.h>
#include <inc/ShapeList.h>
#include <inc/Image.h>
#include <inc/HitRecord.h>

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <ctime>

#define MAX_DEPTH 6
#define ANTI_ALIASING 4
#define BG_COLOR V3(0.22,0.424,0.62)

V3 getColor(const Ray& r, const Shapelist& shapes, float currIndex, int depth);

V3 diffuseAlgo(const Ray& in, const V3& norm, const V3& point, const float intensity, const float currIndex, const Shapelist& shapes, int depth);
V3 specularAlgo(const Ray& in, const V3& norm, const V3& point, const float intensity, const float currIndex, const Shapelist& shapes, int depth);
V3 glassAlgo(const Ray& in, const V3& norm, const V3& point, const float intensity, const float indexMat1, const float indexMat2, const Shapelist& shapes, int depth);

int main(int argc, char *argv[]) {
    // TODO if need user input
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
    Shapelist shapes = Shapelist();
    shapes.add(new Triangle(V3(-7.3, 5, 0), V3(7.3, 5, 0), V3(0, 2, 15), Material(0.8, V3(0,1.0,0)))); //specular reflective triangle celing
    shapes.add(new Sphere(V3(0.3,-3,7), 1.0, Material(0.0, 0.5, 0.0, 0.5, 1.0, V3(.7, .2, .7)))); //perfectly diffuse sphere
    shapes.add(new Sphere(V3(4,0,4.5), 1.0, Material(0.99, V3(.9,.9,.9)))); //specular reflective diffuse sphere
    shapes.add(new Triangle(V3(-7.3, -5, 0), V3(7.3, -5, 0), V3(0, -2, 15), Material(0.0, 0.5, 0.0, 0.5, 1.0, V3(1.0, 0.4, 0.4)))); //perfectly diffuse triangle floor

    // Image data
    uint32_t height = 3000, width = 4000;
    float unitHeight = 3, unitWidth = 4;
    float hHeight = unitHeight / 2.0, hWidth = unitWidth / 2.0;
    float iHeight = 1.0 / height, iWidth = 1.0 / width;

    V3 **image = new V3*[height];

    // init rand seed
    srand(time(NULL));

    float progPrev = 0;
    for(uint32_t y = 0; y < height; y++) {
        image[y] = new V3[width];

        // print rendering progress
        float progCurr = (float) y / (float) height;
        if (FLOAT_EQUAL(progPrev, 0.0)) { progPrev = progCurr; }
        if(FLOAT_EGREATER(progCurr - progPrev, 0.01)) {
            printf("image %3d%% - %d/%d lines - rendered\n", (int)(progCurr * 100), y, height);
            progPrev = progCurr;
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
    printf("image %3d%% - %d/%d lines - rendered\n", 100, height, height);

	  image_write_rgb("./out/output", image, height, width);

    std::cout << "image wrote to file" << std::endl;

    //TODO - free shape memory

    // free image memory
	  for(uint32_t y = 0; y < height; y++) { delete[] image[y]; }
    delete[] image;

    return 0;
}

V3 getColor(const Ray& r, const Shapelist& shapes, float currIndex, int depth) {
    V3 color = V3(0,0,0);

    // Ray doesn't have enough strength to return the light
    if(FLOAT_ELESS(r.intensity(), 0.0) || depth >= MAX_DEPTH)
        return color;

    HitRecord hit;

    if(shapes.intersectionAtRay(r, hit)) {

        // Look at diffuse
        if(FLOAT_NEQUAL(hit.getMaterial().diffuse(), 0.0)) {
            color += diffuseAlgo(r, hit.normal(), hit.point(), hit.getMaterial().diffuse(), currIndex, shapes, depth + 1);
        }

        // Look at specular
        if(FLOAT_NEQUAL(hit.getMaterial().specular(), 0.0)) {
            color += specularAlgo(r, hit.normal(), hit.point(), hit.getMaterial().specular(), currIndex, shapes, depth + 1);
        }

        // Look at glass
        if(FLOAT_NEQUAL(hit.getMaterial().glass(), 0.0)) {
            // Exiting object into air
            if(FLOAT_EQUAL(currIndex, hit.getMaterial().indexOfReflection()))
                color += glassAlgo(r, -hit.normal(), hit.point(), hit.getMaterial().glass(), currIndex, 1.0, shapes, depth + 1);
            else
                color += glassAlgo(r, hit.normal(), hit.point(), hit.getMaterial().glass(), currIndex, hit.getMaterial().indexOfReflection(), shapes, depth + 1);
        }

        // Look at absorbtion
        if(FLOAT_NEQUAL(hit.getMaterial().absorb(), 0.0)) {
            color += hit.getMaterial().absorb() * hit.getMaterial().color();
        }

    } else {
        color = BG_COLOR;
    }

    return r.intensity() * color;
}

V3 diffuseAlgo(const Ray& in, const V3& norm, const V3& point, const float intensity, const float currIndex, const Shapelist& shapes, int depth) {
    // physically correct lambertian's are actually easy!
    V3 n = norm.unitVector();
    V3 p = point;

    // create unit sphere centered at point of intersection + unit_normal
    V3 sCenter = p + n;
    // find a point p0 that's a uniformally distributed point inside the sphere
    // -- find a point p0 inside the boinding cube (cube with side length 2) of the sphere and check if it's in the sphere
    V3 p0;
    do {
        p0.x() = (sCenter.x() + FLOAT_RAND*2)-1;
        p0.y() = (sCenter.y() + FLOAT_RAND*2)-1;
        p0.z() = (sCenter.z() + FLOAT_RAND*2)-1;
    }   while(FLOAT_GREATER(FLOAT_SQUARE(sCenter.x()-p0.x()) + FLOAT_SQUARE(sCenter.y()-p0.y()) + FLOAT_SQUARE(sCenter.z()-p0.z()), 1.0));

    Ray out = Ray(p, (V3)(p + n) + (p0 - n).unitVector(), intensity);
    return getColor(out, shapes, currIndex, depth);
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
    bool schlick = FLOAT_LESS(FLOAT_RAND, temp);

    // Reflect if TIR or Schlicks
    if(FLOAT_GREATER(ratio * sinTheta, 1.0) || schlick)
        return specularAlgo(in, norm, point, intensity, indexMat1, shapes, depth);

    V3 tperp = ratio * (in.dir() + cosTheta * norm);
    V3 t = tperp - sqrt(1.0 - tperp.magnitudeSquared()) * norm;
    Ray out = Ray(point, t, intensity);
    return getColor(out, shapes, indexMat2, depth);
}
