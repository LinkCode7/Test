#include "pch.h"
#include "assert.h"

using std::cout;
using std::endl;

void getWidths(int count, float widths[])
{
	if (!widths)
		return;

	// logic...
	float* arrWidths = new float[count];
	for (auto i = 0; i < count; ++i)
		arrWidths[i] = 0.1;

	// out
	float* cursor = widths;
	for (auto i = 0; i < count; ++i)
		*cursor++ = arrWidths[i];

	delete[] arrWidths;
}

TEST(floating, increase)
{
	float value1 = 0;
	getWidths(1, &value1);

	float value2[3] = {};
	getWidths(3, value2);
}

TEST(std_atoi, atoi_case)
{
	assert(std::atoi("") == 0);
	assert(std::atoi(" ") == 0);
	assert(std::atoi("a") == 0);
	assert(std::atoi("+") == 0);
	assert(std::atoi("*") == 0);
	assert(std::atoi("@") == 0);
	assert(std::atoi(".") == 0);

	assert(std::atoi("0") == 0);
	assert(std::atoi("0.0") == 0);
	assert(std::atoi("0.1") == 0);
	assert(std::atoi("0.01") == 0);
	assert(std::atoi("3.14") == 3);

	assert(std::atoi("-1") == -1);
	assert(std::atoi("-0.1") == 0);
	assert(std::atoi("-0.01") == 0);
	assert(std::atoi("-3.14") == -3);
}
