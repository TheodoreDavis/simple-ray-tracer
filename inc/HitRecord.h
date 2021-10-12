#ifndef _HITRECORD_
#define _HITRECORD_

#include <inc/V3.h>
#include <inc/Material.h>

/**
 * Class to cotain information about a hittable after checking if a ray has it one
 */
class HitRecord {
    private:
        float t_;
        V3 point_;
        V3 normal_;
        Material material_;
    public:
        HitRecord() {}

        HitRecord(float t, const V3& point, const V3& normal) {
            t_ = t;
            point_ = point;
            normal_ = normal;
            material_ = Material();
        }

        HitRecord(float t, const V3& point, const V3& normal, const Material& material) {
            t_ = t;
            point_ = point;
            normal_ = normal;
            material_ = material;
        }

        float t() const {return t_;}
        float& t() {return t_;}

        V3 point() const {return point_;}
        V3& point() {return point_;}

        V3 normal() const {return normal_;}
        V3& normal() {return normal_;}

        Material material() const {return material_;}
        Material& material() {return material_;}

        HitRecord& operator=(HitRecord rhs) {
            t_ = rhs.t_;
            point_ = rhs.point_;
            normal_ = rhs.normal_;
            material_ = rhs.material_;
            return *this;
        }
};

#endif
