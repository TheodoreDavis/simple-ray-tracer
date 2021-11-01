#ifndef _MATERIAL_
#define _MATERIAL_

#include "inc/V3.h"
#include "inc/Ray.h"
#include "inc/HitRecord.h"

/**
 * Class for holding light and color information of a shape
 *
 * The following data members:
 * specular_ diffuse_ glass_ absorb_
 * should have a sum of 1
 */
class Material {
    private:
        V3 color_;
    public:
        Material() {
            color_ = V3(0.7,0.7,0);
        }

        Material(const V3 color) {
            color_ = color;
        }

        virtual ~Material() = 0;

        virtual bool new_ray(const Ray &in, const HitRecord &r, V3 &color, Ray &out) const = 0;
        virtual V3 emit(const HitRecord &r) const {
            return V3(0,0,0);
        }
};

class Diffuse : public Material {
    public:
        ~Diffuse() {}

        Diffuse(const V3& c) : Material(c) {}

        bool new_ray(const Ray &in, const HitRecord &r, V3 &color, Ray &out) const {
            V3 dir = r.normal() + V3::pointInUnitCircle();
            out = Ray(r.point(), dir);
            return true;
        }
};

class Specular : public Material {
    private:
        float fuzz_;
    public:
        ~Specular() {}

        Specular(const V3& c, float f) : Material(c), fuzz_(f) {}

        bool new_ray(const Ray &in, const HitRecord &r, V3 &color, Ray &out) const {
            V3 dir = r.normal() + V3::pointInUnitCircle();
            out = Ray(r.point(), dir);
            return true;
        }
};
#endif
