#include <iostream>

#include <inc/triangle.h>

int main(int argc, char *argv[]) {
	
	triangle tri = triangle(v3(1, 1, 2), v3(7, 7, 2), v3(4, 4, 2)); //triangle to test
	v3 o = v3(1, 1, 0); //origin of rays cast
	v3 d = v3(1, 1, 2); // direction to cast the rays in
	std::string testStatus_fail = "FAILED"; //test result to print for failed test
	std::string testStatus_pass = "PASSED"; //test result to print for passed test
	std::string testStatus_result = "";
	
	std::cout << "--- TESTING SHAPE COLOR ---" << std::endl;
	v3 color = tri.getColor();
	testStatus_result = (CMPFLOAT_EQUAL(color.r(), 1.0) && CMPFLOAT_EQUAL(color.g(), 0.4) && CMPFLOAT_EQUAL(color.b(), 0.4)) ? testStatus_pass : testStatus_fail;
	std::cout << "color=[" << color << "] :: " << testStatus_result << std::endl;
	
	std::cout << "--- TESTING RAY INTERSECTIONS ---" << std::endl;
	int intersections = tri.rayIntersections(o, d);
	testStatus_result = intersections == 1 ? testStatus_pass : testStatus_fail;
	std::cout << "direction=[" << d << "] :: " << testStatus_result << std::endl;
	
	//TODO
	/*
	std::cout << "--- TESTING RAY INTERSECTION POINT ---" << std::endl;
	v3 intersection = tri.rayIntersectionPoint(o, d);
	*/
}