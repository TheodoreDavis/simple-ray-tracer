#include <iostream>

#include <inc/triangle.h>

int main(int argc, char *argv[]) {
	
	triangle tri = triangle(v3(1.0, 1.0, 0.0), v3(7.0, 7.0, 0), v3(4.0, 4.0, 0.0));
	std::cout << "--- TESTING SHAPE COLOR ---" << std::endl;
	v3 color = tri.getColor();
	std::cout << "color=[" << color << "] :: " << (CMPFLOAT_EQUAL(v3.r(), 1.0) && CMPFLOAT_EQUAL(v3.g(), 0.4) && CMPFLOAT_EQUAL(v3.b(), 0.4)) ? "PASSED" : "FAILED" << std::endl;
	
	std::cout << "--- TESTING RAY INTERSECTIONS ---" << std::endl;
	
}