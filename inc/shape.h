/**
 * Class for defining all common public functions that shapes should have for our Ray tracer.
 */
#ifndef _SHAPE_
#define _SHAPE_

#include <inc/Ray.h>
#include <inc/Material.h>
#include <inc/hitRecord.h>
#include <inc/cmpfloat.h>

class Shape {
    protected:
        Material material_;

    public:
        Shape() {}

        Material getMaterial() const {return material_;}
        Material& getMaterial() {return material_;}

        /** 
         * Returns the number of intersections that a Ray casted 
         * from a point-origin with direction has with this object.
         * @param Ray A Ray with a point in 3 dimensional space and a direction.
         * @return The number of intersections.
         */
        virtual bool const rayIntersections(const Ray &casted, HitRecord& rec) = 0;
};

#endif
