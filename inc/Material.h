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

        virtual ~Material() {}

        V3 color() const { return color_; }
		V3& color() { return color_; }

        virtual bool new_ray(const Ray &in, const HitRecord &r, V3 &color, Ray &out) const = 0;
        virtual V3 emit(const HitRecord &r) const {
            return V3(0,0,0);
        }
};

class Emitter : public Material {
    private:
        float brightness_;
    public:
        Emitter(float f, const V3& c) : Material(c), brightness_(f) {}

        bool new_ray(const Ray &in, const HitRecord &r, V3 &color, Ray &out) const {
            return false;
        }

        V3 emit(const HitRecord &r) const {
            return brightness_ * this->color();
        }
};

class Diffuse : public Material {
    public:
        Diffuse(const V3& c) : Material(c) {}

        bool new_ray(const Ray &in, const HitRecord &r, V3 &color, Ray &out) const {
            color = this->color();
            V3 dir = r.normal() + V3::pointInUnitCircle();
            dir.normalize();
            out = Ray(r.point(), dir);
            return true;
        }
};

class Specular : public Material {
    private:
        float fuzz_;
    public:
        Specular(float f, const V3& c) : Material(c), fuzz_(f) {}

        bool new_ray(const Ray &in, const HitRecord &r, V3 &color, Ray &out) const {
            color = this->color();
            V3 dir = in.dir().reflect(r.normal()) + fuzz_ * V3::pointInUnitCircle();
            dir.normalize();
            out.ori() = r.point();
            out.dir() = dir;
            return out.dir().dotProduct(r.normal()) > 0;
        }
};

class Glass : public Material {
    private:
        float index_;
    public:
        Glass( float f, const V3& c) : Material(c), index_(f) {}

        bool new_ray(const Ray &in, const HitRecord &r, V3 &color, Ray &out) const {
            color = this->color();

            // Check if we're hiting a material with the same index of refraction
            // Assuming we're exiting the shape if the index are the same
            V3 normal = r.normal();
            float index = index_;
            if(FLOAT_EQUAL(in.currIoR(), index)) {
                normal *= -1;
                index = 1.0f;
            }

            float cosTheta = normal.dotProduct(-in.dir());
            float sinTheta = sqrt(1.0 - cosTheta * cosTheta);
            float ratio = in.currIoR() / index;

            // Schlick's approximation
            float temp = (1 - ratio) / (1 + ratio);
            temp *= temp; 
            temp = temp + (1.0 - temp) * pow((1.0-cosTheta), 5);
            bool schlick = FLOAT_LESS(FLOAT_RAND, temp);

            // Check if material acts specular
            if(FLOAT_GREATER(sinTheta * ratio, 1.0f) || schlick) {
                return Specular(0, this->color()).new_ray(in, r, color, out);
            }
            
            // Calculate new dir
            V3 tperp = ratio * (in.dir() + cosTheta * normal);
            V3 dir = tperp - sqrt(1.0 - tperp.magnitudeSquared()) * normal;
            dir.normalize();

            out.ori() = r.point();
            out.dir() = dir;
            out.currIoR() = index;
            return true;
        }
};
#endif
