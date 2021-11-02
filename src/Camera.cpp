#include <inc/Camera.h>

std::ostream& operator<<(std::ostream& out, const Camera &rhs) {
	out << "{position=" << rhs.pos() << ", lookat=" << rhs.lookat() << ", horizontal=" << rhs.hor() << ", vertical=" << rhs.vert() << ", upperleft=" << rhs.ul() << ", fov=" << rhs.fov() << ", ar=" << rhs.ar() <<  "}";
	return out;
}

const Ray Camera::get_ray(const uint32_t y, const uint32_t x) {

	float y_norm = (((float)y) / height_) + FLOAT_RAND_RANGE(0.0005, 0.0005);
	float x_norm = (((float)x) / width_) + FLOAT_RAND_RANGE(-0.0005, 0.0005);

	V3 dir = upperleft_ + x_norm * horizontal_ - y_norm * vertical_ + position_;
	Ray r = Ray(position_, dir);
	return (const Ray)r;
}
