#include <iostream>
#include <iomanip>
#include <vector>

#include <cmath>
#include <ctime>

#include <inc/Sphere.h>
#include <inc/Triangle.h>
#include <inc/ShapeList.h>
#include <inc/HitRecord.h>
#include <inc/Camera.h>
#include <inc/image.h>

#define MAX_DEPTH 50
#define ANTI_ALIASING 15
//#define BG_COLOR V3(0.39,0.58,0.92)
#define BG_COLOR V3(0.95,0.5,0.3)
#define ff 0.3f

V3 getColor(const Ray& r, const Shapelist& shapes, int depth);

V3 pointInUnitCircle(const V3& center, float limit = 1.0f);

int main(int argc, char *argv[]) {
    // TODO if need user input
    // if(argc < 2) {
    //     std::cout << " An example use of this program is as follows:" << std::endl;
    //     std::cout << "./ray-tracer" << std::endl;
    // }

	// scene Camera
	//Camera camera = Camera();

    // Origin of all the rays
    V3 origin = V3(0,0,0);

    // Point light in the space
    //V3 pLight = V3(-2,2,1);

    // View plane of pixels
    V3 plane = V3(0,0,1);

    //Add shapes into our space
    Shapelist shapes = Shapelist();
    shapes.add(new Sphere(V3(0,0,6), 1.0, new Diffuse(V3(.4, .5, .8))));
    shapes.add(new Sphere(V3(2,0,6), 1.0, new Specular(0.01, V3(.4, .8, .4))));
    shapes.add(new Sphere(V3(-1,0,3), 1.0, new Glass(1.33, V3(.8, .3, .8))));
    shapes.add(new Sphere(V3(0,5,5), 1.0, new Emitter(1, V3(1, 1, 1)))); //light
    //shapes.add(new Triangle(V3(-100,50,100), V3(100,50,100), V3(0,50,-100), new Specular(0.7, V3(.8, .8, .4)))); //fuzzy relfective ceiling
    shapes.add(new Triangle(V3(-100,-1,100), V3(100,-1,100), V3(0,-1,-100), new Diffuse(V3(.8,.5,.4)))); // floor

    // Image data
    uint32_t height = 750, width = 1000;
    float unitHeight = 3, unitWidth = 4;
    float hHeight = unitHeight / 2.0, hWidth = unitWidth / 2.0; 
    float iHeight = 1.0 / height, iWidth = 1.0 / width;

    V3 **image = new V3*[height];

    // init rand seed
    //srand(time(NULL));
    srand(7);

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
            if(x == 450 && y == 375)
                std::cout << "hi" << std::endl;
            for(int i=0; i < ANTI_ALIASING; i++) {
                V3 dir = V3(plane.x() - hWidth + unitWidth * (x + 1) * iWidth + FLOAT_RAND * iWidth,
                        plane.y() + hHeight - unitHeight * (y + 1) * iHeight - FLOAT_RAND * iHeight,
                        plane.z() - origin.z()).unitVector();

                Ray cast = Ray(origin, dir);
                color += getColor(cast, shapes, 0);
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

V3 getColor(const Ray& r, const Shapelist& shapes, int depth) {
    // Ray doesn't have enough strength to return the light
    if(depth >= MAX_DEPTH)
        return V3(0,0,0);

    HitRecord hit;
    V3 color;
    Ray out;
    if(shapes.intersectionAtRay(r, hit)) {
        if ((*hit.material())->new_ray(r, hit, color, out)) {
            return color * getColor(out, shapes, depth + 1);
        } else {
            return (*hit.material())->emit(hit);
        }
    }
	return BG_COLOR;
}
