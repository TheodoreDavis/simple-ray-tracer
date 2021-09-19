/**
 * Class for defining all common public functions that shapes should have for our ray tracer.
 */
#ifndef _SHAPE_
#define _SHAPE_

#include <inc/v3.h>
#include <inc/material.h>
#include <inc/hitRecord.h>
#include <inc/cmpfloat.h>

class shape {
    protected:
        material material_;

    public:
        shape() {}

        material getMaterial() const {return material_;}
        material& getMaterial() {return material_;}

        /** 
         * Returns the number of intersections that a ray casted 
         * from ori with direction dir has with this object.
         * @param ori A point in 3 dimensional space.
         * @param dir A unit vector of a direction.
         * @return The number of intersections.
         */
        virtual bool const rayIntersections(const v3& ori, const v3& dir, hitRecord& rec) = 0;

};

#endif
