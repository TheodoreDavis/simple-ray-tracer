/**
 * Class for defining all common public functions that shapes should have for our ray tracer.
 */
#ifndef _SHAPE_
#define _SHAPE_

#include <inc/v3.h>
#include <inc/cmpfloat.h>

class shape {
    protected:
        v3 color_;

    public:
        shape() {}

        v3 getColor() const {return color_;}
        v3& getColor() {return color_;}

        /** 
         * Returns the number of intersections that a ray casted 
         * from ori with direction dir has with this object.
         * @param ori A point in 3 dimensional space.
         * @param dir A unit vector of a direction.
         * @return The number of intersections.
         */
        virtual int const rayIntersections(const v3& ori, const v3& dir) = 0;

        /**
         * Returns the point that the ray intersects this shape.
         * In the case that there are multiple intersections,
         * this returns the closest one to @param ori.
         * @param ori A point in 3 dimensional space.
         * @param dir A unit vector of a direction.
         * @return A point in 3 dimensional space.
         */
        virtual v3 const rayIntersectionPoint(const v3& ori, const v3& dir) = 0;

        /**
         * Returns a unit vector in the direction of
         * the normal of the surface of the shape
         * at the first intersection of the ray casted
         * from ori with direction dir
         * @param point A point on the surface of the shape
         * @return The normal vector of the shape at @param point 
         */
        virtual v3 const intersectionNormal(const v3& point) = 0;

};

#endif
