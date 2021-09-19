#include <iostream>

#include <inc/triangle.h>

void printResult_intersection(v3 o, v3 d, bool result);

int main(int argc, char *argv[]) {
	
	
	triangle tri = triangle(v3(1, 1, 1), v3(5, 3, 1), v3(3, 5, 1)); //triangle to test
	
	std::cout << "TRIANGLE: " << tri << std::endl << std::endl;
	
	v3 o; //origin of rays cast
	v3 d; // direction to cast the rays in
	std::string testStatus_result = "";
	int intersections = 0; //number of ray intersections per triangle
	v3 p; //point where ray intersected triangle
	
	std::cout << "--- TESTING SHAPE COLOR ---" << std::endl;
	v3 color = tri.getColor();
	testStatus_result = (CMPFLOAT_EQUAL(color.r(), 1.0) && CMPFLOAT_EQUAL(color.g(), 0.4) && CMPFLOAT_EQUAL(color.b(), 0.4)) ? "PASSED" : "FAILED";
	std::cout << "color=[" << color << "] :: " << testStatus_result << std::endl;
	
	std::cout << std::endl;
	std::cout << "--- TESTING RAY INTERSECTIONS ---" << std::endl;
	o = v3(0, 0, 0);
	d = v3(3, 3, 1);
	intersections = tri.rayIntersections(o, d);
	printResult_intersection(o, d, intersections > 0);
	
	o = v3(2, 2, 0);
	d = v3(4, 3, 2);
	intersections = tri.rayIntersections(o, d);
	printResult_intersection(o, d, intersections > 0);

	o = v3(0, 0, 0);
	d = v3(3, 1, 2);
	intersections = tri.rayIntersections(o, d);
	printResult_intersection(o, d, intersections < 1);
	
	o = v3(2, 2, 0);
	d = v3(4, 3, -2);
	intersections = tri.rayIntersections(o, d);
	printResult_intersection(o, d, intersections < 1);

	std::cout << std::endl;
	std::cout << "--- TESTING RAY INTERSECTION POINT ---" << std::endl;
	o = v3(0, 0, 0);
	d = v3(3, 3, 1);
	p = tri.rayIntersectionPoint(o, d);
	printResult_intersection(o, d, p == v3(3, 3, 1));
	
	o = v3(2, 2, 0);
	d = v3(4, 3, 2);
	p = tri.rayIntersectionPoint(o, d);
	printResult_intersection(o, d, p == v3(4, 3.5, 1));
	
	o = v3(0, 0, 0);
	d = v3(4, 3, 0);
	p = tri.rayIntersectionPoint(o, d);
	printResult_intersection(o, d, p == o);
	
	return 0;
}

void printResult_intersection(v3 o, v3 d, bool result) {
	
	std::string testStatus = result ? "PASSED" : "FAILED";
	std::cout << "origin=[" << o << "], direction=[" << d << "] :: " << testStatus << std::endl;
	
	return;
}