#pragma once





int g_iConstructCount = 0;
int g_iDestructCount = 0;

class Point
{
public:
	Point();

	Point(const Point& oth);

	Point(Point&& oth)noexcept;

	Point& operator=(const Point& oth);

	Point& operator=(Point&& oth)noexcept;

	~Point();

private:
	int m_i;
};

class ConstructCount
{
public:
	ConstructCount()
	{
		std::cout << "ConstructCount()" << std::endl;
	}
	ConstructCount(int value)
	{
		value_ = value;
		std::cout << "ConstructCount(int value)" << std::endl;
	}
	ConstructCount(const ConstructCount& oth)
	{
		value_ = oth.value_;
		std::cout << "ConstructCount(const ConstructCount& oth)" << std::endl;
	}
	~ConstructCount()
	{
		std::cout << "~ConstructCount()" << std::endl;
	}

	int value_;
};