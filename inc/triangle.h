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
		triangle(v3 a, v3 b, v3 c) {
			this->a_ = a;
			this->b_ = b;
			this->c_ = c;
			this->color_ = v3(1.0f, 0.4f, 0.4f);  //pastel red
			
			norm_ = (b - a).crossProduct(c - a);
		}
		triangle(v3 a,v3 b, v3 c, v3 color) {
			this->a_ = a;
			this->b_ = b;
			this->c_ = c;
			this->color_ = color;
			
			norm_ = (b - a).crossProduct(c - a);
		}
		
		/*
			i/o functions
		*/
		friend std::ostream& operator<<(std::ostream& out, const triangle &rhs);
		
		/*
			utility functions
		*/
		const v3 get_bary(v3 p);
		/*
			implementation of shape virtual functions
		*/
		const int rayIntersections(const v3& ori, const v3& dir);
		const v3 rayIntersectionPoint(const v3& ori, const v3& dir);
		const v3 intersectionNormal(const v3& point);
};

#endif