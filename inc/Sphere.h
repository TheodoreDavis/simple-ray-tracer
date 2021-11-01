#ifndef _SPHERE_
#define _SPHERE_

#include <inc/Shape.h>

class Sphere : public Shape {
    private:
        V3 center_;
        float radius_;

    public:
        Sphere(V3 center) {
            center_ = center;
            radius_ = 1.0;
            material_ = new Diffuse(V3(0.392, 0.584, 0.929));
        }
        
        Sphere(V3 center, float radius) {
            center_ = center;
            radius_ = radius;
            material_ = new Diffuse(V3(0.392, 0.584, 0.929));
        }

        Sphere(V3 center, float radius, Material* material) {
            center_ = center;
            radius_ = radius;
            material_ = material;
        }

        ~Sphere() {
            delete material_;
        }

        friend std::ostream& operator<<(std::ostream& out, const Sphere& rhs);

        bool const rayIntersections(const Ray &casted, HitRecord& rec);
};
#endif
