#include <inc/triangle.h>

std::ostream& operator<<(std::ostream& out, const triangle &rhs) {
	
    out << "{a=" << rhs.a_ << "], b=" << rhs.b_ << ", c=" << rhs.c_ << ", norm=" << rhs.norm_;
	return out;
}

const v3 triangle::get_bary(v3 p) {
	
	float norm2_r = 1/norm_.dotProduct(norm_);
	
	return v3(	norm_.dotProduct(((v3)(c_ - p)).crossProduct(p - b_)) * norm2_r,
				norm_.dotProduct(((v3)(a_ - p)).crossProduct(p - c_)) * norm2_r,
				norm_.dotProduct(((v3)(b_ - p)).crossProduct(p - a_)) * norm2_r);
}

const bool triangle::rayIntersections(const ray &casted, hitRecord& rec) {
	
	ray r = casted;
	
	/*
		find point where ray intersects plane triangle is on (if it does at all)
	*/
	float dot_nd = norm_.dotProduct(r.dir());
	if (CMPFLOAT_EQUAL(dot_nd, 0.0f)) { return 0; } //ray is parallel to triangle plane, so intersection not possible
	float t = ((v3)(a_ - r.ori())).dotProduct(norm_) / dot_nd; //ray parmaeter to get the point where the ray intersects the plane
	v3 p = r.eval(t); //evaulate ray at t
	
	/*
		run test to see of point lies on the triangle.
		if it does, then the ray intersected the triangle
	*/
	v3 b = triangle::get_bary(p); //get barycentric coordinate of that point
	if (CMPFLOAT_EGREATER(b.x(), 0.0f) && CMPFLOAT_EGREATER(b.y(), 0.0f) && CMPFLOAT_EGREATER(b.z(), 0.0f)) {
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