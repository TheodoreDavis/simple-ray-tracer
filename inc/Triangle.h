#ifndef _TRIANGLE_
#define _TRIANGLE_

#include <inc/Shape.h>

class Triangle : public Shape {
	private:
		V3 a_;
		V3 b_;
		V3 c_;
		V3 norm_;
	public:
		/*
			constructors
		*/
		Triangle(V3 a, V3 b, V3 c) {
			this->a_ = a;
			this->b_ = b;
			this->c_ = c;
			this->material_ = new Diffuse(V3(1.0f, 0.4f, 0.4f));  //color is pastel red

			this->norm_ = ((V3)(b - a)).crossProduct(c - a);
		}

		Triangle(V3 a, V3 b, V3 c, Material* mat) {
			this->a_ = a;
			this->b_ = b;
			this->c_ = c;
			this->material_ = mat;

			this->norm_ = ((V3)(b - a)).crossProduct(c - a);
		}

		~Triangle() {
			delete material_;
		}

		/*
			i/o functions
		*/
		friend std::ostream& operator<<(std::ostream& out, const Triangle &rhs);

		/*
			utility functions
		*/
		const V3 get_bary(V3 p);
		/*
			implementation of shape virtual functions
		*/
		bool const rayIntersections(const Ray &casted, HitRecord& rec);
};

#endif
