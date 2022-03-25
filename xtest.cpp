#include "pch.h"
//#include "xtest.h" // xtest.h在预编译头中包含了，这里再包含的话会重复
#include "windows.h"


xtest::_Test::_Test(const std::string &n1, const std::string& n2) :test_case_name(n1), test_name(n2) {}
void Output(const char* str, long color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | color);
	std::cout << str;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void xtest::OutputRed(const char* str)
{
	Output(str, FOREGROUND_RED);
}
void xtest::OutputGreen(const char* str)
{
	Output(str, FOREGROUND_GREEN);
}



void xtest::UnitTest::Run()
{
	OutputGreen("[==========] Start Test...");
	std::cout << std::endl;
	for (auto it = begin(all_tests12); it != end(all_tests12); ++it)
	{
		OutputGreen("[ RUN      ] ");
		std::cout << (*it)->test_case_name << "." << (*it)->test_name << std::endl;
		(*it)->testBody();
		std::cout << std::endl;
	}
}











TEST(Test, test1)
{
	ASSERT_EQ(1, 1);
	ASSERT_EQ(1, 2);
	ASSERT_EQ(2, 3);
}

TEST(Test, test2)
{
	EXPECT_EQ(1, 1);
	EXPECT_EQ(1, 2);
	EXPECT_EQ(2, 3);
}