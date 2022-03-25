#pragma once
#include <math.h>



class Fibonacci
{
	int a, b, c;
	std::vector<double> m_store;

public:

	void generate(double);
	double getValueByIndex(double n);
	void print(std::string separator);
};