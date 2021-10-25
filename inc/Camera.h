#ifndef _CAMERA_
#define _CAMERA_

#include <cmath>
#include <cstdint>

#include <inc/V3.h>
#include <inc/Ray.h>

class Camera {
	private:
		V3 position_;
		V3 horizontal_;
		V3 vertical_;
		V3 upperleft_;
	public:
		/*
			constructors
		*/
		Camera() {
			V3 pos = V3(0, 0, 0);
			V3 lookat = V3(0, 0, 1); // direction to look at
			V3 up = V3(0, 1, 0); // "up" direction
			float fov = 210.0; // field-of-view (in degrees)
			float ar = 1.0; // aspect ratio

			V3 z = (lookat - pos).unitVector();
			V3 y = up.unitVector();
			V3 x = z.crossProduct(y);
			float theta = (fov * M_PI) / (180 * 2);

			this->position_ = pos;
			this->vertical_ = 2 * tan(theta) * y;
			this->horizontal_ = 2 * tan(theta) * ar * x;
			this->upperleft_ = this->position_ + z + this->vertical_ / 2 - this->horizontal_ / 2;
		}
		Camera(V3 pos, V3 lookat, V3 up) {
			const float fov = 210.0; // field-of-view (in degrees)
			const float ar = 1.0; // aspect ratio

			V3 z = (lookat - pos).unitVector();
			V3 y = up.unitVector();
			V3 x = z.crossProduct(y);
			float theta = (fov * M_PI) / (180 * 2);

			this->position_ = pos;
			this->vertical_ = 2 * tan(theta) * y;
			this->horizontal_ = 2 * tan(theta) * ar * x;
			this->upperleft_ = this->position_ + z + this->vertical_ / 2 - this->horizontal_ / 2;
		}
		Camera(V3 pos, V3 lookat, V3 up, float fov, float ar) {
			V3 z = (lookat - pos).unitVector();
			V3 y = up.unitVector();
			V3 x = z.crossProduct(y);
			float theta = (fov * M_PI) / (180 * 2);

			this->position_ = pos;
			this->vertical_ = 2 * tan(theta) * y;
			this->horizontal_ = 2 * tan(theta) * ar * x;
			this->upperleft_ = this->position_ + z + this->vertical_ / 2 - this->horizontal_ / 2;
		}

		/*
			accessors
		*/
		V3 pos() const { return this->position_; }
		V3& pos() { return this->position_; }
		V3 hor() const { return this->horizontal_; }
		V3& hor() { return this->horizontal_; }
		V3 vert() const { return this->vertical_; }
		V3& vert() { return this->vertical_; }
		V3 ul() const { return this->upperleft_; }
		V3& ul() { return this->upperleft_; }

		/*
			i/o functions
		*/
		friend std::ostream& operator<<(std::ostream& out, const Camera &rhs);

		/*
			utility functions
		*/
		const V3 eval(const Ray ray, const float t, const uint32_t y, const uint32_t x);
};

#endif
