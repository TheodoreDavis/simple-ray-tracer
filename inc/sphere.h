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
            color_ = v3(0.392, 0.584, 0.929);
        }

        sphere(v3 center, float radius, v3 color) {
            center_ = center;
            radius_ = radius;
            color_ = color;
        }

        int const rayIntersections(const v3& ori, const v3& dir);
        v3 const rayIntersectionPoint(const v3& ori, const v3& dir);
        v3 const intersectionNormal(const v3& point);
};
#endif