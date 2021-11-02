#ifndef _CAMERA_
#define _CAMERA_

#include <cmath>
#include <cstdint>

#include <inc/V3.h>
#include <inc/Ray.h>

class Camera {
	private:
		uint32_t height_;
		uint32_t width_;
		V3 position_;
		V3 lookat_;
		V3 horizontal_;
		V3 vertical_;
		V3 upperleft_;
		float fieldofview_;
		float aspectratio_;
	public:
		/*
			constructors
		*/
		Camera(uint32_t h, uint32_t w) {
			V3 pos = V3(0, 0, 0);
			V3 lookat = V3(0, 0, 1); // direction to look at (Center of the viewing plane)
			V3 up = V3(0, 1, 0); // "up" direction (The 'roll' the camera)
			float fov = 210.0; // field-of-view (in degrees)
			float ar = ((float)w) / h; // aspect ratio

			this->height_ = h;
			this->width_ = w;

			V3 z = (lookat - pos).unitVector(); //dir to center of view plane
			V3 y = up.unitVector(); //dir of up
			V3 x = (z.crossProduct(y)); //angle between z and y
			float theta = fov * M_PI_2 / 180.0; // half the viewing angle in radians

			this->position_ = pos;
			this->lookat_ = lookat;
			this->vertical_ = -2 * tan(theta) * y; 
			this->horizontal_ = 2 * tan(theta) * ar * x;
			this->upperleft_ = this->position_ + z + (this->vertical_ / 2) - (this->horizontal_ / 2);
			this->fieldofview_ = fov;
			this->aspectratio_ = ar;
		}
		Camera(uint32_t h, uint32_t w, V3 pos, V3 lookat, V3 up) {
			float fov = 210.0; // field-of-view (in degrees)
			float ar = ((float)w) / h; // aspect ratio

			this->height_ = h;
			this->width_ = w;

			V3 z = (lookat - pos).unitVector();
			V3 y = up.unitVector();
			V3 x = z.crossProduct(y);
			float theta = (fov * (M_PI / 180.0)) / 2;

			this->position_ = pos;
			this->lookat_ = lookat;
			this->vertical_ = -2 * tan(theta) * y;
			this->horizontal_ = 2 * tan(theta) * ar * x;
			this->upperleft_ = this->position_ + z + (this->vertical_ / 2) - (this->horizontal_ / 2);
			this->fieldofview_ = fov;
			this->aspectratio_ = ar;
		}
		Camera(uint32_t h, uint32_t w, V3 pos, V3 lookat, V3 up, float fov, float ar) {
			this->height_ = h;
			this->width_ = w;

			V3 z = (lookat - pos).unitVector();
			V3 y = up.unitVector();
			V3 x = z.crossProduct(y);
			float theta = (fov * (M_PI / 180.0)) / 2;

			this->position_ = pos;
			this->lookat_ = lookat;
			this->vertical_ = -2 * tan(theta) * y;
			this->horizontal_ = 2 * tan(theta) * ar * x;
			this->upperleft_ = this->position_ + z + (this->vertical_ / 2) - (this->horizontal_ / 2);
			this->fieldofview_ = fov;
			this->aspectratio_ = ar;
		}

		/*
			accessors
		*/
		uint32_t h() const { return this->height_; }
		uint32_t& h() { return this->height_; }
		uint32_t w() const { return this->width_; }
		uint32_t& w() { return this->width_; }
		V3 pos() const { return this->position_; }
		V3& pos() { return this->position_; }
		V3 lookat() const { return this->lookat_; }
		V3& lookat() { return this->lookat_; }
		V3 hor() const { return this->horizontal_; }
		V3& hor() { return this->horizontal_; }
		V3 vert() const { return this->vertical_; }
		V3& vert() { return this->vertical_; }
		V3 ul() const { return this->upperleft_; }
		V3& ul() { return this->upperleft_; }
		float fov() const { return this->fieldofview_; }
		float& fov() { return this->fieldofview_; }
		float ar() const { return this->aspectratio_; }
		float& ar() { return this->aspectratio_; }

		/*
			i/o functions
		*/
		friend std::ostream& operator<<(std::ostream& out, const Camera &rhs);

		/*
			utility functions
		*/
		const Ray get_ray(const uint32_t y, const uint32_t x);
};

#endif
