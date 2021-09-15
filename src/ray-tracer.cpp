#include <inc/sphere.h>
#include <inc/image.h>

#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
    // TODO if need user imput
    // if(argc < 2) {
    //     std::cout << " An example use of this program is as follows:" << std::endl;
    //     std::cout << "./ray-tracer" << std::endl;
    // }

    // Origin of all the rays
    v3 origin = v3(0,0,0);

    // View plane of pixels
    v3 plane = v3(0,0,1);

    v3 backgroundColor = v3(0.724,0.724,0.724);

    //Add shapes into our space
    //std::vector<shape> shapes;
    //shapes.push_back(sphere(v3(0,0,2), 1.0));
    sphere s = sphere(v3(0,0,4), 1.0); // Change sphere location here!

    // Image data
    uint32_t height = 300, width = 400;
    float unitHeight = 1.5, unitWidth = 2;
    v3 **image = new v3*[height];
    

    for(uint32_t y = 0; y < height; y++) {
        image[y] = new v3[width];

        for(uint32_t x = 0; x < width; x++) {
            v3 dir = v3(plane.x() - unitWidth / 2 + unitWidth * (x + 1) / width,
                        plane.y() + unitHeight / 2 - unitHeight * (y + 1) / height,
                        plane.z() - origin.z());
            // for(auto s : shapes) {
            //     //TODO check if more than 1 shape has an intersection

            // }
            if(s.rayIntersections(origin, dir) > 0) {
                image[y][x] = s.getColor();
            } else {
                image[y][x] = backgroundColor;
            }
        }
    }
	
	image_write_rgb("./out/img", image, height, width);
	
	return 0;
}