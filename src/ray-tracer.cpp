#include <inc/Sphere.h>
#include <inc/Triangle.h>
#include <inc/ShapeList.h>
#include <inc/Image.h>
#include <inc/HitRecord.h>

#include <iostream>
#include <vector>
#include <cmath>

#define MAX_DEPTH 1
#define BG_COLOR V3(0.22,0.724,0.22)

V3 getColor(const Ray& r, const Shapelist& shapes, int depth);
V3 specularAlgo(const Ray& in, const V3& norm, const V3& point, const float intensity, const Shapelist& shapes, int depth);

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
    shapes.add(new Sphere(V3(0,0,4), 2));
    shapes.add(new Sphere(V3(4,0,4.5), 1.0, Material(0.8, V3(.9,.2,.3))));
    shapes.add(new Sphere(V3(0,1004,4), 1000, Material(0.3, V3(0.7,0.7,0.7))));
    shapes.add(new Sphere(V3(0,-1004,4), 1000, Material(V3(0.2,0.2,0.2))));

    // Image data
    uint32_t height = 600, width = 800;
    float unitHeight = 3, unitWidth = 4;
    V3 **image = new V3*[height];
	
    for(uint32_t y = 0; y < height; y++) {
        image[y] = new V3[width];
        for(uint32_t x = 0; x < width; x++) {
            // Grab dir for the pixel
            V3 dir = V3(plane.x() - unitWidth / 2 + unitWidth * (x + 1) / width,
                        plane.y() + unitHeight / 2 - unitHeight * (y + 1) / height,
                        plane.z() - origin.z()).unitVector();
			
            Ray cast = Ray(origin, dir, 1.0);
            image[y][x] = getColor(cast, shapes, 0);
        }
    }
	
	image_write_rgb("./out/output", image, height, width);
	
	for(uint32_t y = 0; y < height; y++) { delete[] image[y]; }
    delete[] image;

	return 0;
}

V3 getColor(const Ray& r, const Shapelist& shapes, int depth) {
    V3 color = V3(0,0,0);

    // Ray doesn't have enough strength to return the light
    if(CMPFLOAT_ELESS(r.intensity(), 0.0) || depth >= MAX_DEPTH)
        return color;

    HitRecord hit;

    if(shapes.intersectionAtRay(r, hit)) {

        // Look at specular
        if(CMPFLOAT_NEQUAL(hit.getMaterial().specular(), 0.0)) {
            color += specularAlgo(r, hit.normal(), hit.point(), hit.getMaterial().specular(), shapes, depth + 1);
        }

        // Look at ...

        // Look at glass

        // Look at absorbtion
        if(CMPFLOAT_NEQUAL(hit.getMaterial().absorb(), 0.0)) {
            color += hit.getMaterial().absorb() * hit.getMaterial().color();
        }

    } else {
        color = r.intensity() * BG_COLOR;
    }

    return r.intensity() * color;
}

V3 specularAlgo(const Ray& in, const V3& norm, const V3& point, const float intensity, const Shapelist& shapes, int depth) {
    V3 outDir = in.dir() - 2 * in.dir().dotProduct(norm) * norm;
    
    // Temp debugging :) -- should be 1.
    // std::cout << outDir.magnitudeSquared() << std::endl;

    Ray out = Ray(point, outDir, intensity);
    return getColor(out, shapes, depth);
}