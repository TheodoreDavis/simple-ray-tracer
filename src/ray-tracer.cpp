#include <inc/sphere.h>
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

    v3 backgroundColor = v3(0.824,0.824,0.824);

    //Add shapes into our space
    //std::vector<shape> shapes;
    //shapes.push_back(sphere(v3(0,0,2), 1.0));
    sphere s = sphere(v3(0,0,2), 1.0);

    // Image data
    int height = 400, width = 533;
    float unitHeight = 1.5, unitWidth = 2;
    v3 image[width][height];

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            v3 dir = v3(plane.x() - unitWidth / 2 + unitWidth * (x + 1) / width,
                        plane.y() + unitHeight / 2 - unitHeight * (y + 1) / height,
                        plane.z() - origin.z());
            // for(auto s : shapes) {
            //     //TODO check if more than 1 shape has an intersection

            // }
            if(s.rayIntersections(origin, dir) > 0)
                image[x][y] = s.getColor();
            else
                image[x][y] = backgroundColor;
        }
    }

    

}