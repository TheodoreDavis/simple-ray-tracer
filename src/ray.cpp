#include <inc/ray.h>

std::ostream& operator<<(std::ostream& out, const ray &rhs) {
	
    out << "{ori=" << rhs.origin_ << "], dir=" << rhs.direction_;
	return out;
}

const v3 ray::eval(const float t) { return (origin_ + t * direction_); }