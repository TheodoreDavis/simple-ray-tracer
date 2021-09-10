#include <inc/cmpfloat.h>
#include <iostream>
#include <string>

void print_result(float a, float b, bool result, std::string str_result);

int main() {

	float a = 5.0f;
	float b = 5.0f;
	
	std::string str_testResult;
	
	//test equality
	std::cout << "--- TESTING CMP EQUAL ---" << std::endl;
	
	str_testResult = CMPFLOAT_EQUAL(a, b) == 1 ? "PASSED" : "FAILED";
	print_result(a, b, 1, str_testResult);
	a = 3.0f;
	b = 2.0f;
	str_testResult = CMPFLOAT_EQUAL(a, b) == 0 ? "PASSED" : "FAILED";
	print_result(a, b, 0, str_testResult);
	
	//test inequality
	std::cout << "--- TESTING CMP NEQUAL ---" << std::endl;
	str_testResult = CMPFLOAT_NEQUAL(a, b) == 1 ? "PASSED" : "FAILED";
	print_result(a, b, 1, str_testResult);
	a = 5.0f;
	b = 5.0f;
	str_testResult = CMPFLOAT_NEQUAL(a, b) == 0 ? "PASSED" : "FAILED";
	print_result(a, b, 0, str_testResult);
	
	//test greater-than
	std::cout << "--- TESTING CMP GREATER ---" << std::endl;
	str_testResult = CMPFLOAT_GREATER(a, b) == 0 ? "PASSED" : "FAILED";
	print_result(a, b, 0, str_testResult);
	b = 4.0f;
	str_testResult = CMPFLOAT_GREATER(a, b) == 1 ? "PASSED" : "FAILED";
	print_result(a, b, 1, str_testResult);
	b = 6.0f;
	str_testResult = CMPFLOAT_GREATER(a, b) == 0 ? "PASSED" : "FAILED";
	print_result(a, b, 0, str_testResult);
	
	//test less-than
	std::cout << "--- TESTING CMP LESS ---" << std::endl;
	str_testResult = CMPFLOAT_LESS(a, b) == 1 ? "PASSED" : "FAILED";
	print_result(a, b, 1, str_testResult);
	b = 4.0f;
	str_testResult = CMPFLOAT_LESS(a, b) == 0 ? "PASSED" : "FAILED";
	print_result(a, b, 0, str_testResult);
	b = 5.0f;
	str_testResult = CMPFLOAT_LESS(a, b) == 0 ? "PASSED" : "FAILED";
	print_result(a, b, 0, str_testResult);
	
	//test greater-or-equal-to
	std::cout << "--- TESTING CMP GREATER-OR-EQUAL ---" << std::endl;
	str_testResult = CMPFLOAT_EGREATER(a, b) == 1 ? "PASSED" : "FAILED";
	print_result(a, b, 1, str_testResult);
	b = 4.0f;
	str_testResult = CMPFLOAT_EGREATER(a, b) == 1 ? "PASSED" : "FAILED";
	print_result(a, b, 1, str_testResult);
	b = 6.0f;
	str_testResult = CMPFLOAT_EGREATER(a, b) == 0 ? "PASSED" : "FAILED";
	print_result(a, b, 0, str_testResult);
	
	//test lesser-or-equal-to
	std::cout << "--- TESTING CMP LESSER-OR-EQUAL ---" << std::endl;
	str_testResult = CMPFLOAT_ELESS(a, b) == 1 ? "PASSED" : "FAILED";
	print_result(a, b, 1, str_testResult);
	b = 4.0f;
	str_testResult = CMPFLOAT_ELESS(a, b) == 0 ? "PASSED" : "FAILED";
	print_result(a, b, 0, str_testResult);
	b = 5.0f;
	str_testResult = CMPFLOAT_ELESS(a, b) == 1 ? "PASSED" : "FAILED";
	print_result(a, b, 1, str_testResult);
}

void print_result(float a, float b, bool result, std::string str_result) {
	
	std::cout << "a=[" << a << "], b=[" << b << "] :: result=[" << result << "] :: test [" << str_result << "]" << std::endl;
	return;
}