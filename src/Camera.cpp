#include <inc/Camera.h>

std::ostream& operator<<(std::ostream& out, const Camera &rhs) {
	out << "{position=" << rhs.position_ << ", horizontal=" << rhs.horizontal_ << ", vertical=" << rhs.vertical_ << ", upperleft=" << rhs.upperleft_ << "}";
	return out;
}

const Ray Camera::get_ray(const uint32_t y, const uint32_t x) {

	float y_norm = (((float)y) / height_) + FLOAT_RAND_RANGE(-0.5, 0.5);
	float x_norm = (((float)x) / width_) + FLOAT_RAND_RANGE(-0.5, 0.5);

	V3 dir = upperleft_ + (x_norm * horizontal_) - (y_norm * vertical_) - position_;
	Ray r = Ray(position_, dir);
	return (const Ray)r;
}
