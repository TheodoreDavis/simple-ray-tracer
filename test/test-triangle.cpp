#include <iostream>

#include <inc/triangle.h>

void printResult(ray r, hitRecord rec, bool result_intersection, bool result_point);

int main(int argc, char *argv[]) {
	
	
	triangle tri = triangle(v3(1, 1, 1), v3(5, 3, 1), v3(3, 5, 1)); //triangle to test
	
	std::cout << "TRIANGLE: " << tri << std::endl;
	
	ray r; //ray to cast with point origin and direction
	hitRecord rec; //hitrecord 
	std::string testStatus_result = "";
	bool intersected = 0; //if ray hit triangle
	
//	std::cout << std::endl;
//	std::cout << "--- TESTING SHAPE COLOR ---" << std::endl;
//	material mat = tri.getMaterial();
//	testStatus_result = (FLOAT_EQUAL(color.r(), 1.0) && FLOAT_EQUAL(color.g(), 0.4) && FLOAT_EQUAL(color.b(), 0.4)) ? "PASSED" : "FAILED";
//	std::cout << "color=[" << color << "] :: " << testStatus_result << std::endl;
	
	std::cout << std::endl;
	std::cout << "--- TESTING RAY INTERSECTIONS ---" << std::endl;
	r = ray(v3(0, 0, 0), v3(3, 3, 1));
	intersected = tri.rayIntersections(r, rec);
	printResult(r, rec, intersected, (rec.point() == v3(3.0f, 3.0f, 1.0f)));
	
	r = ray(v3(2, 2, 0), v3(4, 3, 2));
	intersected = tri.rayIntersections(r, rec);
	printResult(r, rec, intersected, (rec.point() == v3(4.0f, 3.5, 1.0f)));
		
	r = ray(v3(0, 0, 0), v3(3, 1, 2));
	intersected = tri.rayIntersections(r, rec);
	printResult(r, rec, !intersected, (rec.point() == v3(4.0f, 3.5, 1.0f)));
	
	r = ray(v3(2, 2, 0), v3(4, 3, -2));
	intersected = tri.rayIntersections(r, rec);
	printResult(r, rec, !intersected, (rec.point() == v3(4.0f, 3.5, 1.0f)));
	
	return 0;
}

void printResult(ray r, hitRecord rec, bool result_intersection, bool result_point) {
	
	std::string testStatus_intersection = result_intersection ? "PASSED" : "FAILED";
	std::string testStatus_point = result_point ? "PASSED" : "FAILED";
	std::cout << "origin=" << r.ori() << ", direction=" << r.dir() << ", point=" << rec.point() 
		<< " :: Intersection [" << testStatus_intersection 
		<< "] - Point [" << testStatus_point << "]" 
		<< std::endl;
	
	return;
}