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
			this->material_ = Material(v3(1.0f, 0.4f, 0.4f));  //color is pastel red
			
			this->norm_ = ((v3)(b - a)).crossProduct(c - a);
		}
		triangle(v3 a, v3 b, v3 c, Material mat) {
			this->a_ = a;
			this->b_ = b;
			this->c_ = c;
			this->material_ = mat;
			
			this->norm_ = ((v3)(b - a)).crossProduct(c - a);
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
		const bool rayIntersections(const ray &casted, hitRecord& rec);
};

#endif