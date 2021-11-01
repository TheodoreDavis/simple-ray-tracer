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

#define MAX_DEPTH 16
#define ANTI_ALIASING 4
#define BG_COLOR V3(0.8,0.8,0.8)
#define ff 0.3f

V3 getColor(const Ray& r, const Shapelist& shapes, float currIndex, int depth);

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
    //shapes.add(new Triangle(V3(-200, 5, 100), V3(200, 5, 100), V3(0, 5, -100), Material(Property::Specular, 0.7, V3(0.0,0.7,0.0)))); //green specular reflective triangle celing
    //shapes.add(new Sphere(V3(0,0,4), 1.0, Material(Property::Diffuse, V3(.4, .5, .8)))); //blue perfectly diffuse sphere
    // shapes.add(new Sphere(V3(-2,0,3.9), 1.0, Material(Property::Diffuse, V3(.7, .2, .7)))); //magenta perfectly diffuse sphere
    // shapes.add(new Sphere(V3(-1,0,1.9), 1, Material(Property::Glass, 1.3, V3(.7, .7, .7)))); //glass sphere: index of refrection = 1.4
    // //shapes.add(new Triangle(V3(-1.5, 0.4, 1.9), V3(1.5, 0.3, 1.9), V3(0, 1.4, 1.9), Material(Property::Glass, 1.0, V3(0.9, 0.9, 0.9)))); // glass triangle: index of refraction = 1.4
    // shapes.add(new Sphere(V3(-3,3,4), 1.0, Material(Property::Specular, 0.9, V3(.9,.9,.9)))); //fuzzy specular sphere
    // shapes.add(new Sphere(V3(2,0,5.5), 1.0, Material(Property::Light, V3(1,1,1)))); //white light sphere
    // shapes.add(new Triangle(V3(-200, -1, 100), V3(200, -1, 100), V3(0, -1, -100), Material(Property::Diffuse, V3(1.0, 0.4, 0.4)))); //red perfectly diffuse triangle floor
    shapes.add(new Sphere(V3(0,0,4), 1.0, new Diffuse(V3(.4, .5, .8))));

    // Image data
    uint32_t height = 750, width = 1000;
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
    // Ray doesn't have enough strength to return the light
    if(depth >= MAX_DEPTH)
        return V3(0,0,0);

    HitRecord hit;
    V3 color;
    Ray out;
    if(shapes.intersectionAtRay(r, hit)) {
        if (hit.material()->new_ray(r, hit, color, out)) {
            return color * getColor(out, shapes, currIndex, depth + 1);
        } else {
            return hit.material()->emit(hit);
        }
    }

    // if(shapes.intersectionAtRay(r, hit)) {
    //     V3 color = hit.material().color();
    //     V3 rcolor;

    //     // Look at diffuse
    //     if(hit.material().property() == Property::Diffuse) { rcolor = diffuseAlgo(color, r, hit, currIndex, shapes, depth + 1); }

    //     // Look at specular
    //     if(hit.material().property() == Property::Specular) { rcolor = specularAlgo(color, r, hit, currIndex, shapes, depth + 1); }

    //     // Look at glass
    //     if(hit.material().property() == Property::Glass) {
    //         // Exiting object into air
    //         if(FLOAT_EQUAL(currIndex, hit.material().indexOfReflection()))
    //             rcolor = glassAlgo(color, r, true, hit, currIndex, 1.0, shapes, depth + 1);
    //         else
    //             rcolor = glassAlgo(color, r, false, hit, currIndex, hit.material().indexOfReflection(), shapes, depth + 1);
    //     }

	// 	// Look at light
	// 	if(hit.material().property() == Property::Light) { return lightAlgo(color, r, hit, currIndex, shapes, depth + 1); }

    //     return color * rcolor;
    // }
	return BG_COLOR;
}

// V3 diffuseAlgo(V3& color, const Ray& in, const HitRecord& hit, const float currIndex, const Shapelist& shapes, int depth) {
//     // physically correct lambertian's are actually easy!

//     // create unit sphere centered at point of intersection + unit_normal
//     V3 sCenter = hit.point() + hit.normal();
//     // find a point p0 that's a uniformally distributed point inside the sphere
//     // -- find a point p0 inside the boinding cube (cube with side length 2) of the sphere and check if it's in the sphere
//     V3 p0 = pointInUnitCircle(sCenter, hit.material().effect());

//     V3 dir = (hit.point() + hit.normal()) + (p0 - hit.normal()).unitVector();
//     Ray out = Ray(hit.point(), dir);
//     return getColor(color, out, shapes, currIndex, depth);
// }

// V3 specularAlgo(V3& color, const Ray& in, const HitRecord& hit, const float currIndex, const Shapelist& shapes, int depth) {
//     V3 outDir = in.dir() - 2 * in.dir().dotProduct(hit.normal()) * hit.normal();
//     outDir += hit.material().fuzz() * pointInUnitCircle(V3(0,0,0));
//     outDir.normalize();
//     Ray out = Ray(hit.point(), outDir);
//     return getColor(color, out, shapes, currIndex, depth);
// }

// V3 glassAlgo(V3& color, const Ray& in, bool flag, const HitRecord& hit, const float indexMat1, const float indexMat2, const Shapelist& shapes, int depth) {
//     HitRecord alt_hit = hit;

//     // Ray is escaping shape, thus normal is facing the wrong way
//     if(flag)
//         alt_hit.normal() = -alt_hit.normal();

//     float cosTheta = alt_hit.normal().dotProduct(-in.dir());
//     float sinTheta = sqrt(1.0 - cosTheta * cosTheta);
//     float ratio = indexMat1 / indexMat2;

//     // Schlick's approximation
//     float temp = (1 - ratio) / (1 + ratio);
//     temp *= temp;
//     temp = temp + (1.0 - temp) * pow((1.0-cosTheta), 5);
//     bool schlick = FLOAT_LESS(FLOAT_RAND, temp);

//     // Reflect if TIR or Schlicks
//     if(FLOAT_GREATER(ratio * sinTheta, 1.0) || schlick)
//     	return specularAlgo(color, in, alt_hit, indexMat1, shapes, depth);

//     V3 tperp = ratio * (in.dir() + cosTheta * alt_hit.normal());
//     V3 t = tperp - sqrt(1.0 - tperp.magnitudeSquared()) * alt_hit.normal();
//     Ray out = Ray(hit.point(), t);
//     return getColor(color, out, shapes, indexMat2, depth);
// }

// V3 lightAlgo(V3& color, const Ray& in, const HitRecord& hit, const float currIndex, const Shapelist& shapes, int depth) {
//     return hit.material().color();
// }
