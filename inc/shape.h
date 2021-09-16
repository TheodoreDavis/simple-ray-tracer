/**
 * Class for defining all common public functions that shapes should have for our ray tracer.
 */
#ifndef _SHAPE_
#define _SHAPE_

#include <inc/ray.h>
#include <inc/material.h>
#include <inc/hitRecord.h>
#include <inc/cmpfloat.h>

class shape {
    protected:
        material material_;

    public:
        shape() {  }

        material getMaterial() const {return material_;}
        material& getMaterial() {return material_;}

        /** 
         * Returns the number of intersections that a ray casted 
         * from a point-origin with direction has with this object.
         * @param ray A ray with a point in 3 dimensional space and a direction.
         * @return The number of intersections.
         */
        virtual bool const rayIntersections(const ray &casted, hitRecord& rec) = 0;
};

#endif
