#include <inc/Triangle.h>

std::ostream& operator<<(std::ostream& out, const Triangle &rhs) {

    out << "{a=" << rhs.a_ << "], b=" << rhs.b_ << ", c=" << rhs.c_ << ", norm=" << rhs.norm_;
	return out;
}

const V3 Triangle::get_bary(V3 p) {

	float norm2_r = 1/norm_.dotProduct(norm_);

	return V3(	norm_.dotProduct(((V3)(c_ - p)).crossProduct(p - b_)) * norm2_r,
				norm_.dotProduct(((V3)(a_ - p)).crossProduct(p - c_)) * norm2_r,
				norm_.dotProduct(((V3)(b_ - p)).crossProduct(p - a_)) * norm2_r);
}

const bool Triangle::rayIntersections(const Ray &casted, HitRecord& rec) {

	Ray r = casted;

	/*
		find point where ray intersects plane triangle is on (if it does at all)
	*/
	float dot_nd = norm_.dotProduct(r.dir());
	if (FLOAT_EQUAL(dot_nd, 0.0f)) { return 0; } //ray is parallel to triangle plane, so intersection not possible
	float t = ((V3)(a_ - r.ori())).dotProduct(norm_) / dot_nd; //ray parmaeter to get the point where the ray intersects the plane
	V3 p = r.eval(t); //evaulate ray at t

	/*
		run test to see of point lies on the triangle.
		if it does, then the ray intersected the triangle
	*/
	V3 b = Triangle::get_bary(p); //get barycentric coordinate of that point
	if (FLOAT_EGREATER(b.x(), 0.0f) && FLOAT_EGREATER(b.y(), 0.0f) && FLOAT_EGREATER(b.z(), 0.0f)) {
		//if b is in triangle, ray hit

		//populate hit-record
		rec.t() = t;
		rec.point() = p;
		rec.getMaterial() = material_;
		rec.normal() = norm_;
		rec.normal().normalize();

		//return true
		return 1;
	}

	return 0;
}
