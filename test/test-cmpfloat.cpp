#include <iostream>
#include <string>

#include <inc/cmpfloat.h>

void print_result(float a, float b, bool result, std::string str_result);

int main(int argc, char *argv[]) {

	float a = 5.0f;
	float b = 5.0f;
	bool result = 0;
	std::string str_testResult;
	
	//test equality
	std::cout << "--- TESTING CMP EQUAL ---" << std::endl;
	result = CMPFLOAT_EQUAL(a, b);
	print_result(a, b, result, result ? "PASSED" : "FAILED");
	a = 3.0f;
	b = 2.0f;
	result = CMPFLOAT_EQUAL(a, b);
	print_result(a, b, result, !result ? "PASSED" : "FAILED");
	
	//test inequality
	std::cout << "--- TESTING CMP NEQUAL ---" << std::endl;
	result = CMPFLOAT_NEQUAL(a, b);
	print_result(a, b, result, result ? "PASSED" : "FAILED");
	a = 5.0f;
	b = 5.0f;
	result = CMPFLOAT_NEQUAL(a, b);
	print_result(a, b, result, !result ? "PASSED" : "FAILED");
	
	//test greater-than
	std::cout << "--- TESTING CMP GREATER ---" << std::endl;
	result = CMPFLOAT_GREATER(a, b);
	print_result(a, b, result, !result ? "PASSED" : "FAILED");
	b = 4.0f;
	result = CMPFLOAT_GREATER(a, b);
	print_result(a, b, result, result ? "PASSED" : "FAILED");
	b = 6.0f;
	result = CMPFLOAT_GREATER(a, b);
	print_result(a, b, result, !result ? "PASSED" : "FAILED");
	
	//test less-than
	std::cout << "--- TESTING CMP LESS ---" << std::endl;
	result = CMPFLOAT_LESS(a, b);
	print_result(a, b, result, result ? "PASSED" : "FAILED");
	b = 4.0f;
	result = CMPFLOAT_LESS(a, b);
	print_result(a, b, result, !result ? "PASSED" : "FAILED");
	b = 5.0f;
	result = CMPFLOAT_LESS(a, b);
	print_result(a, b, result, !result ? "PASSED" : "FAILED");
	
	//test greater-or-equal-to
	std::cout << "--- TESTING CMP GREATER-OR-EQUAL ---" << std::endl;
	result = CMPFLOAT_EGREATER(a, b);
	print_result(a, b, result, result ? "PASSED" : "FAILED");
	b = 4.0f;
	result = CMPFLOAT_EGREATER(a, b);
	print_result(a, b, result, result ? "PASSED" : "FAILED");
	b = 6.0f;
	result = CMPFLOAT_EGREATER(a, b);
	print_result(a, b, result, !result ? "PASSED" : "FAILED");
	
	//test lesser-or-equal-to
	std::cout << "--- TESTING CMP LESSER-OR-EQUAL ---" << std::endl;
	result = CMPFLOAT_ELESS(a, b);
	print_result(a, b, result, result ? "PASSED" : "FAILED");
	b = 4.0f;
	result = CMPFLOAT_ELESS(a, b);
	print_result(a, b, result, !result ? "PASSED" : "FAILED");
	b = 5.0f;
	result = CMPFLOAT_ELESS(a, b);
	print_result(a, b, result, result ? "PASSED" : "FAILED");
	
	return 0;
}

void print_result(float a, float b, bool result, std::string str_result) {
	
	std::cout << "a=[" << a << "], b=[" << b << "] :: test result=[" << result << "] :: test [" << str_result << "]" << std::endl;
	return;
}