#pragma once

constexpr int fibonacci(int index)
{
	return (index == 1 || index == 2) ? 1 : fibonacci(index - 1) + fibonacci(index - 2);
}



#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif
constexpr double Angle2Radian(double angle)
{
	return (angle / 180.0 * PI);
}

constexpr double Radian2Angle(double radian)
{
	return (radian / PI * 180.0);
}



template<typename T>
auto print_type_info(const T& t)
{
	if constexpr (std::is_integral<T>::value)
	{
		return t + 1;
	}
	else
	{
		return t + 0.001;
	}
}
