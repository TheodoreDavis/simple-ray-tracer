#include <inc/sphere.h>

int const sphere::rayIntersections(const v3& ori, const v3& dir) {
    v3 o = ori, d = dir;
    v3 temp = o - center_;
    
    //find a,b,c for quadratic -- a is always 1 since dir is a unit vector
    float a = d.magnitudeSquared();
    float b = 2 * d.dotProduct(temp);
    float c = temp.magnitudeSquared() - radius_ * radius_;
    float res = b * b - 4 * a * c;
    
    // no real roots
    if (CMPFLOAT_LESS(res, 0.0f))
        return 0;

    // 1 real root
    if (CMPFLOAT_EQUAL(res, 0.0f))
        return 1;

    // 2 real roots
    return 2;
    
}

v3 const sphere::rayIntersectionPoint(const v3& ori, const v3& dir) {
    v3 o = ori, d = dir;
    v3 temp = o - center_;
    
    //find a,b,c for quadratic -- a is always 1 since dir is a unit vector
    float a = d.magnitudeSquared();
    float b = 2 * d.dotProduct(temp);
    float c = temp.magnitudeSquared() - radius_ * radius_;
    float res = b * b - 4 * a * c;

    // no real roots - should never be true!
    if (CMPFLOAT_LESS(res, 0.0f))
        return ori;

    // 1 real root
    if (CMPFLOAT_EQUAL(res, 0.0f))
        return (o + (-b / (2 * a)) * d);

    // 2 real roots return the close point to ori
    float t1 = (-b + sqrt(res)) / 2 / a;
    float t2 = (-b - sqrt(res)) / 2 / a;
    v3 p1 = t1 * d;
    v3 p2 = t2 * d;

    if(CMPFLOAT_LESS(p1.magnitudeSquared(), p2.magnitudeSquared()))
        return o + p1;
    return o + p2;
}

v3 const sphere::intersectionNormal(const v3& point) {
    
    // Probably don't need
    float x = point.x() - center_.x();
    float y = point.y() - center_.y();
    float z = point.z() - center_.z();
    if(CMPFLOAT_NEQUAL(x*x + y*y + z*z, radius_*radius_))
        return v3(0,0,0); //error

    v3 p = point;
    return (p - center_);

}