#include <inc/triangle.h>

const v3 triangle::get_bary(const v3 &p) {
	
	float norm2_r = 1/norm_.dotProduct(norm_);
	
	return v3(	norm_.dotProduct((c_ - p).crossProduct(p - b_)) * norm2_r,
				norm_.dotProduct((a_ - p).crossProduct(p - c_)) * norm2_r,
				norm_.dotProduct((b_ - p).crossProduct(p - a_)) * norm2_r);
}

const int triangle::rayIntersections(const v3 &ori, const v3 &dir) {
	
	//TODO
	return 0;
}
const v3 triangle::rayIntersectionPoint(const v3& ori, const v3& dir) {
	
	//TODO
	return v3(0.0, 0.0, 0.0);
}
const v3 triangle::intersectionNormal(const v3& point) {
	
	//TODO
	return v3(0.0, 0.0, 0.0);
}