#include "pch.h"
#include "function.h"




TEST(c_function, standar)
{
	const char* src = "hello";
	char* des = new char[strlen(src)];
	my_strcpy(des, src);
}
