#include <inc/sphere.h>
#include <inc/triangle.h>
#include <inc/shapeList.h>
#include <inc/image.h>
#include <inc/hitRecord.h>

#include <iostream>
#include <vector>
#include <cmath>

int main(int argc, char *argv[]) {
    // TODO if need user imput
    // if(argc < 2) {
    //     std::cout << " An example use of this program is as follows:" << std::endl;
    //     std::cout << "./ray-tracer" << std::endl;
    // }

    // Origin of all the rays
    v3 origin = v3(0,0,0);

    // Point light in the space
    v3 pLight = v3(-2,2,1);

    // View plane of pixels
    v3 plane = v3(0,0,1);

    v3 backgroundColor = v3(0.724,0.724,0.724);

    //Add shapes into our space
    //std::vector<shape> shapes;
    //shapes.push_back(sphere(v3(0,0,2), 1.0));
    shapelist shapes = shapelist();
    triangle t = triangle(v3(-0.5f,-0.5f,3.0f), v3(-0.5f,0.0f,3.0f), v3(0.0f,-0.5f,3.0f));
    shapes.add(new sphere(v3(0,0,4), 2.0));
    shapes.add(new sphere(v3(.5,0,2.5), 1.0, material(v3(0.7,0.0,0.0))));

    // Image data
    uint32_t height = 300, width = 400;
    float unitHeight = 1.5, unitWidth = 2;
    v3 **image = new v3*[height];
    

    for(uint32_t y = 0; y < height; y++) {
        image[y] = new v3[width];
        for(uint32_t x = 0; x < width; x++) {
            // Grab dir for the pixel
            hitRecord rec;
            v3 dir = v3(plane.x() - unitWidth / 2 + unitWidth * (x + 1) / width,
                        plane.y() + unitHeight / 2 - unitHeight * (y + 1) / height,
                        plane.z() - origin.z()).unitVector();

            if(shapes.intersectionAtRay(origin, dir, rec)) {
                v3 r = pLight - rec.point();
                float theta = acos(r.dotProduct(rec.normal()) / r.magnitude());
                float intensity = (M_PI - theta) * M_1_PI;

                image[y][x] = intensity * rec.getMaterial().color();
            } else {
                image[y][x] = backgroundColor;
            }
        }
    }
	
	image_write_rgb("./out/output", image, height, width);
	
    delete image;

	return 0;
}