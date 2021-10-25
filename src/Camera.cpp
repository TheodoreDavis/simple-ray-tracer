#include <inc/Camera.h>

std::ostream& operator<<(std::ostream& out, const Camera &rhs) {
	out << "{position=" << rhs.position_ << ", horizontal=" << rhs.horizontal_ << ", vertical=" << rhs.vertical_ << ", upperleft=" << rhs.upperleft_ << "}";
	return out;
}

const V3 Camera::eval(const Ray ray, const float t, const uint32_t y, const uint32_t x) {
	V3 r = ray.ori() + t * (upperleft_ + x * horizontal_ - y * vertical_ - position_);
	return (const V3)r;
}
