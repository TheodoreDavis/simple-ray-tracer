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
            material_ = Material(v3(0.392, 0.584, 0.929));
        }

        sphere(v3 center, float radius, Material material) {
            center_ = center;
            radius_ = radius;
            material_ = material;
        }

        friend std::ostream& operator<<(std::ostream& out, const sphere& rhs);

        bool const rayIntersections(const ray &casted, hitRecord& rec);
};
#endif