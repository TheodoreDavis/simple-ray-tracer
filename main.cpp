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

#define MAX_DEPTH 20
#define ANTI_ALIASING 4
//#define BG_COLOR V3(0.39,0.58,0.92)
#define BG_COLOR V3(0.95,0.5,0.3)

V3 getColor(const Ray& r, const Shapelist& shapes, int depth);

V3 pointInUnitCircle(const V3& center, float limit = 1.0f);

int main(int argc, char *argv[]) {

		// Image data
		uint32_t height = 750, width = 1000;
		V3 **image = new V3*[height];

    //Add shapes into our space
    Shapelist shapes = Shapelist();
    shapes.add(new Sphere(V3(0,0,6), 1.0, new Diffuse(V3(.4, .5, .8))));
    shapes.add(new Sphere(V3(2,0,6), 1.0, new Specular(0.01, V3(.4, .8, .4))));
    shapes.add(new Sphere(V3(-1,0.2,3), 1.0, new Glass(1.33, V3(1, 1, 1))));
    shapes.add(new Sphere(V3(0,5,5), 1.0, new Emitter(1, V3(1, 1, 1)))); //light
    shapes.add(new Triangle(V3(-100,-1,100), V3(100,-1,100), V3(0,-1,-100), new Diffuse(V3(.8,.5,.4)))); // floor

		// scene Camera(image_height, image_width, position, dir_lookat, dir_up, fov, ar)
		Camera camera = Camera(height, width, V3(0,0,0.5), V3(0,0,1), V3(0,1,0), 210, width/height);
		std::cout << camera << std::endl;

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

								Ray cast = camera.get_ray(y, x);
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
