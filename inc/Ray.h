#ifndef _RAY_
#define _RAY_

#include <inc/V3.h>

class Ray {
	private:
		V3 origin_;
		V3 direction_;
		float intensity_;
		float currIoR_;
	public:
		/*
			constructors
		*/
		Ray() {
			this->origin_ = V3(0, 0, 0);
			this->direction_ = V3(0, 0, 1);
			this->intensity_ = 1.0f;
		}
		Ray(V3 origin, V3 direction) {

			this->origin_ = origin;
			this->direction_ = direction;
			this->intensity_ = 1.0f;
		}
		Ray(V3 origin, V3 direction, float intensity) {

			this->origin_ = origin;
			this->direction_ = direction;
			this->intensity_ = intensity;
		}

		/*
			accessors
		*/
		V3 ori() const { return this->origin_; }
		V3& ori() { return this->origin_; }
		V3 dir() const { return this->direction_; }
		V3& dir() { return this->direction_; }
		float intensity() const { return this->intensity_; }
		float& intensity() { return this->intensity_; }
		float currIoR() const { return this->currIoR_; }
		float& currIoR() { return this->currIoR_; }

		/*
			i/o functions
		*/
		friend std::ostream& operator<<(std::ostream& out, const Ray &rhs);

		/*
			utility functions
		*/
		const V3 eval(const float t);
};

#endif
