#pragma once
#include <memory>

void testCppOperator();
void testCompareSharedPtr();
void testSortPointer();


class MyObject
{
public:
	MyObject() : value_(10001) { std::cout << "MyObject()" << std::endl; }
	explicit MyObject(int value) : value_(value) { std::cout << "explicit MyObject(int value)" << std::endl; }
	MyObject(double value) : value_(static_cast<int>(value)) { std::cout << "explicit MyObject(double value)" << std::endl; }

	MyObject(const MyObject& other)
	{
		std::cout << "MyObject(const MyObject& other)" << std::endl;
		value_ = other.value_;
	}

	MyObject& operator=(const MyObject& rhs)
	{
		std::cout << "MyObject& operator=(const MyObject& rhs)" << std::endl;
		if (this == &rhs) return *this;

		this->value_ = rhs.value_;
		return *this;
	}

	//bool operator<(const MyObject& oth) { return value_ < oth.value_; } // 对智能指针无效

	int value_;
};
typedef std::shared_ptr<MyObject> MyObjectPtr;






class Read
{
public:

	Read() {}

	operator std::string()
	{
		std::string strVal("std::string case");
		return strVal;
	}
	operator long()
	{
		return 100;
	}
	operator bool()
	{
		return false;
	}

	operator int()
	{
		return 10;
	}
};