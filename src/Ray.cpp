#include <inc/Ray.h>

std::ostream& operator<<(std::ostream& out, const Ray &rhs) {
    out << "{ori=" << rhs.origin_ << ", dir=" << rhs.direction_ << "}";
	return out;
}

const V3 Ray::eval(const float t) { return (origin_ + t * direction_); }
