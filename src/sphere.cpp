#include <inc/sphere.h>

std::ostream& operator<<(std::ostream& out, const sphere &rhs) {
	
    out << "center={" << rhs.center_.x() <<
        ", " << rhs.center_.y() <<
        ", " << rhs.center_.z() <<
        "} radius=" << rhs.radius_;
	return out;
}

bool const sphere::rayIntersections(const ray &casted, hitRecord& rec) {
	
	ray r = casted;
    v3 temp = r.ori() - center_;
    
    //find a,b,c for quadratic -- a is always 1 since dir is a unit vector
    float b = 2 * r.dir().dotProduct(temp);
    float c = temp.magnitudeSquared() - radius_ * radius_;
    float res = b * b - 4 * c;
    
    // no real roots
    if (CMPFLOAT_LESS(res, 0.0f))
        return false;

    // 1 real root
    if (CMPFLOAT_EQUAL(res, 0.0f)) {
        rec.t() = -b / 2.0;
    } else {
        float t1 = (-b + sqrt(res)) / 2.0;
        float t2 = (-b - sqrt(res)) / 2.0;

        // The t with the smaller length is the first intersection
        rec.t() = CMPFLOAT_LESS(abs(t1), abs(t2)) ? t1 : t2;
    }

    rec.point() = r.ori() + rec.t() * r.dir();
    rec.getMaterial() = material_;

    rec.normal() = rec.point() - center_;
    rec.normal().normalize();
    //rec.normal() += rec.point(); // Not sure if this normal needs to be rebased

    return true;
}