#include <inc/sphere.h>
#include <inc/triangle.h>
#include <inc/shapeList.h>
#include <inc/image.h>
#include <inc/hitRecord.h>

#include <iostream>
#include <vector>
#include <cmath>

#define MAX_DEPTH 1
#define BG_COLOR v3(0.22,0.724,0.22)

v3 getColor(const ray& r, const shapelist& shapes, int depth);
v3 specularAlgo(const ray& in, const v3& norm, const v3& point, const float intensity, const shapelist& shapes, int depth);

int main(int argc, char *argv[]) {
    // TODO if need user imput
    // if(argc < 2) {
    //     std::cout << " An example use of this program is as follows:" << std::endl;
    //     std::cout << "./ray-tracer" << std::endl;
    // }

    // Origin of all the rays
    v3 origin = v3(0,0,0);

    // Point light in the space
    //v3 pLight = v3(-2,2,1);

    // View plane of pixels
    v3 plane = v3(0,0,1);

    //Add shapes into our space
    //std::vector<shape> shapes;
    //shapes.push_back(sphere(v3(0,0,2), 1.0));
    shapelist shapes = shapelist();
	//shapes.add(new triangle(v3(-0.25f,-0.25f,0.5f), v3(-0.0f,-0.25f,0.5f), v3(-0.0f,0.0f,0.5f), material(v3(0.0,255.0,0.0))));
    shapes.add(new sphere(v3(0,0,4), 2));
    shapes.add(new sphere(v3(4,0,4.5), 1.0, Material(0.8, v3(.9,.2,.3))));
    shapes.add(new sphere(v3(0,1004,4), 1000, Material(0.3, v3(0.7,0.7,0.7))));
    shapes.add(new sphere(v3(0,-1004,4), 1000, Material(v3(0.2,0.2,0.2))));

    // Image data
    uint32_t height = 600, width = 800;
    float unitHeight = 3, unitWidth = 4;
    v3 **image = new v3*[height];
	
    for(uint32_t y = 0; y < height; y++) {
        image[y] = new v3[width];
        for(uint32_t x = 0; x < width; x++) {
            // Grab dir for the pixel
            v3 dir = v3(plane.x() - unitWidth / 2 + unitWidth * (x + 1) / width,
                        plane.y() + unitHeight / 2 - unitHeight * (y + 1) / height,
                        plane.z() - origin.z()).unitVector();
			
            ray cast = ray(origin, dir, 1.0);
            image[y][x] = getColor(cast, shapes, 0);
        }
    }
	
	image_write_rgb("./out/output", image, height, width);
	
	for(uint32_t y = 0; y < height; y++) { delete[] image[y]; }
    delete[] image;

	return 0;
}

v3 getColor(const ray& r, const shapelist& shapes, int depth) {
    v3 color = v3(0,0,0);

    // Ray doesn't have enough strength to return the light
    if(CMPFLOAT_ELESS(r.intensity(), 0.0) || depth >= MAX_DEPTH)
        return color;

    hitRecord hit;

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

v3 specularAlgo(const ray& in, const v3& norm, const v3& point, const float intensity, const shapelist& shapes, int depth) {
    v3 outDir = in.dir() - 2 * in.dir().dotProduct(norm) * norm;
    
    // Temp debugging :) -- should be 1.
    // std::cout << outDir.magnitudeSquared() << std::endl;

    ray out = ray(point, outDir, intensity);
    return getColor(out, shapes, depth);
}