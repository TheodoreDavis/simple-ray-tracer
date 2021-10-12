#include <inc/Sphere.h>

std::ostream& operator<<(std::ostream& out, const Sphere &rhs) {
	
    out << "center={" << rhs.center_.x() <<
        ", " << rhs.center_.y() <<
        ", " << rhs.center_.z() <<
        "} radius=" << rhs.radius_;
	return out;
}

bool const Sphere::rayIntersections(const Ray &casted, HitRecord& rec) {
	
	Ray r = casted;
    V3 temp = r.ori() - center_;
    
    //find a,b,c for quadratic -- a is always 1 since dir is a unit vector
    float b = 2 * r.dir().dotProduct(temp);
    float c = temp.magnitudeSquared() - radius_ * radius_;
    float res = b * b - 4 * c;
    
    // no real roots
    if (FLOAT_LESS(res, 0.0f))
        return false;

    // 1 real root
    if (FLOAT_EQUAL(res, 0.0f)) {
        rec.t() = -b / 2.0;
    } else {
        float t1 = (-b + sqrt(res)) / 2.0;
        float t2 = (-b - sqrt(res)) / 2.0;

        // Find the smaller t that is > 0
        if(FLOAT_GREATER(t1, 0.005) && FLOAT_GREATER(t2, 0.005))
            rec.t() = FLOAT_LESS(t1, t2) ? t1 : t2;
        else if(FLOAT_GREATER(t1, 0.005))
            rec.t() = t1;
        else if(FLOAT_GREATER(t2, 0.005))
            rec.t() = t2;
        else
            return false; // Only happens if origin is next to the surface of the sphere and shoots a ray away from center
    }

    rec.point() = r.ori() + rec.t() * r.dir();
    rec.getMaterial() = material_;

    rec.normal() = rec.point() - center_;
    rec.normal().normalize();

    return true;
}