#ifndef _SPHERE_
#define _SPHERE_

#include <inc/shape.h>

class sphere : public shape {
    private:
        v3 center_;
        float radius_;

    public:
        sphere(v3 center, float radius) {
            center_ = center;
            radius_ = radius;
            material_ = material(v3(0.392, 0.584, 0.929));
        }

        sphere(v3 center, float radius, material material) {
            center_ = center;
            radius_ = radius;
            material_ = material;
        }

        bool const rayIntersections(const ray &casted, hitRecord& rec);
};
#endif