#ifndef _HITRECORD_
#define _HITRECORD_

#include <inc/v3.h>
#include <inc/material.h>


/**
 * Class to cotain information about a hittable after checking if a ray has it one
 */
class hitRecord {
    private:
        float t_;
        v3 point_;
        v3 normal_;
        material material_;
    public:
        hitRecord() {}
        
        hitRecord(float t, const v3& point, const v3& normal) {
            t_ = t;
            point_ = point;
            normal_ = normal;
            material_ = material();
        }
        
        hitRecord(float t, const v3& point, const v3& normal, const material& material) {
            t_ = t;
            point_ = point;
            normal_ = normal;
            material_ = material;
        }

        float t() const {return t_;}
        float& t() {return t_;}

        v3 point() const {return point_;}
        v3& point() {return point_;}

        v3 normal() const {return normal_;}
        v3& normal() {return normal_;}

        material getMaterial() const {return material_;}
        material& getMaterial() {return material_;}
};

#endif
