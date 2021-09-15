#ifndef _TRIANGLE_
#define _TRIANGLE_

#include <inc/shape.h>

class triangle : public shape {
	private:
		v3 a_;
		v3 b_;
		v3 c_;
		v3 norm_;
	public:
		/*
			constructors
		*/
		triangle(const v3 &a, const v3 &b, const v3 &c) {
			this->a_ = a;
			this->b_ = b;
			this->c_ = c;
			this->color_ = v3(1.0, 0.4, 0.4);  //pastel red
			
			norm_ = ((v3)b - (v3)a).crossProduct((v3)c - (v3)a);
		}
		triangle(const v3 &a, const v3 &b, const v3 &c, const v3 &color) {
			this->a_ = a;
			this->b_ = b;
			this->c_ = c;
			this->color_ = color;
			
			norm_ = ((v3)b - (v3)a).crossProduct((v3)c - (v3)a);
		}
		/*
			utility functions
		*/
		const v3 get_bary(const v3 &p);
		/*
			implementation of shape virtual functions
		*/
		const int rayIntersections(const v3& ori, const v3& dir);
		const v3 rayIntersectionPoint(const v3& ori, const v3& dir);
		const v3 intersectionNormal(const v3& point);
};

#endif