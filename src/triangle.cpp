#include <inc/triangle.h>

std::ostream& operator<<(std::ostream& out, const triangle &rhs) {
	
    out << "{a=" << rhs.a_ << "], b=" << rhs.b_ << ", c=" << rhs.c_ << ", norm=" << rhs.norm_;
	return out;
}

const v3 triangle::get_bary(v3 p) {
	
	float norm2_r = 1/norm_.dotProduct(norm_);
	
	return v3(	norm_.dotProduct((c_ - p).crossProduct(p - b_)) * norm2_r,
				norm_.dotProduct((a_ - p).crossProduct(p - c_)) * norm2_r,
				norm_.dotProduct((b_ - p).crossProduct(p - a_)) * norm2_r);
}

const int triangle::rayIntersections(const v3 &ori, const v3 &dir) {
	
	v3 o = ori;
	
	/*
		find point where ray intersects plane triangle is on (if it does at all)
	*/
	v3 p = triangle::rayIntersectionPoint(ori, dir);
	if (p == o) { return 0; } //ray is parallel to triangle plane, so intersection not possible
	
	/*
		run test to see of point lies on the triangle.
		if it does, then the ray intersected the triangle
	*/
	v3 b = triangle::get_bary(p); //get barycentric coordinate of that point
	if (CMPFLOAT_EGREATER(b.x(), 0.0f) && CMPFLOAT_EGREATER(b.y(), 0.0f) && CMPFLOAT_EGREATER(b.z(), 0.0f)) { return 1; }
	return 0;
}
const v3 triangle::rayIntersectionPoint(const v3& ori, const v3& dir) {
	
	v3 o = ori;
	v3 d = dir;
	
	float dot_nd = norm_.dotProduct(d);
	if (CMPFLOAT_EQUAL(dot_nd, 0.0f)) { return ori; } //ray is parallel to triangle plane, so intersection not possible
	float t = (a_ - o).dotProduct(norm_) / dot_nd; //ray parmaeter to get the point where the ray intersects the plane
	
	return o + (t * d);
}
const v3 triangle::intersectionNormal(const v3& point) {
	
	//TODO?
	return norm_;
}