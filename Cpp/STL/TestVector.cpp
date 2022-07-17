#include "pch.h"
#include "TestVector.h"

#pragma warning(disable:4267)


using namespace std;


Point::Point()
{
	m_i = 0;
	++g_iConstructCount;
	std::cout << "Point()" << std::endl;
}

Point::Point(const Point& oth)
{
	m_i = oth.m_i;
	std::cout << "Point(const Point& oth)" << std::endl;
}

Point::Point(Point&& oth)noexcept
{
	m_i = oth.m_i;
	//oth.m_i = nullptr;
	std::cout << "Point(const Point&& oth)" << std::endl;
}

Point& Point::operator=(const Point& oth)
{
	m_i = oth.m_i;
	std::cout << "Point::operator=(const Point& oth)" << std::endl;
	return *this;
}

Point& Point::operator=(Point&& oth)noexcept
{
	m_i = oth.m_i;
	//oth.m_i = nullptr;
	std::cout << "Point::operator=(const Point&& oth)" << std::endl;
	return *this;
}

Point::~Point()
{
	++g_iDestructCount;
	std::cout << "~Point()" << std::endl;
}

void TestVectorBase();
void PrintVectorLength(const std::vector<Point>& vec);
void TestVectorPush();
void TestMemoryGrowth();
void TestMoveSemantic();
void TestCapacity();
void TestResize();


#include <assert.h>
template<class T>
void RemoveAt(std::vector<T>& vec, int index)
{
	assert(index >= 0 && index < static_cast<int>(vec.size()));

	vec.erase((vec.rbegin() + (vec.size() - index)).base());
}

TEST(TestVector, Base)
{
	TestVectorBase();
	//TestVectorPush();
	//TestMemoryGrowth();

	TestMoveSemantic();

	TestResize();
	TestCapacity();


	vector<int> vec = {1,2,3,4,5,6};

	//RemoveAt(vec, 2);
	for(int i = 0; i < 6; ++i)
		RemoveAt(vec, vec.size()-1);
}






void PrintVectorLength(const std::vector<Point>& vec)
{
	cout << "-------------------------------- size = " << vec.size() << endl;
	cout << "-------------------------------- capacity = " << vec.capacity() << endl;
}

void TestVectorPush()
{
	std::vector<Point> vecPt;

	PrintVectorLength(vecPt);
	cout << endl << endl << endl;

	int iCount = 100;
	for (int i = 0; i < iCount; ++i)
	{
		vecPt.push_back(Point());
		PrintVectorLength(vecPt);
		cout << endl;
	}

	std::vector<Point>::iterator iter = vecPt.begin();
	for (; iter != vecPt.end(); ++iter)
	{
		Point pt = *iter;
		//const Point& pt = *iter;
	}

	cout << endl << endl << endl;

	cout << "g_iConstructCount = " << g_iConstructCount << endl;
	cout << "g_iDestructCount = " << g_iDestructCount << endl;
}

void TestMemoryGrowth()
{
	// 内存增长方式：new = old * 1.5
	// 1,2,3,4,6,9,13,19,28,42,63,94,141,211,316,474,711,1066
	vector<int> vec;

	unsigned int iLastCapacity = vec.capacity();

	for (auto i = 0; i < 1000; ++i)
	{
		vec.push_back(1);

		// 容量发生改变时输出
		if (vec.capacity() != iLastCapacity)
		{
			iLastCapacity = vec.capacity();
			cout << vec.capacity() << endl;
		}
	}
}

Point GetPointObject()
{
	return Point();
}

void _PrintPoint(const Point& pt)
{
	cout << "PrintPoint(const Point& pt)" << endl;
}

void _PrintPoint(Point&& pt)
{
	cout << "PrintPoint(Point&& pt)" << endl;
}

void PrintPoint(Point&& pt)
{
	_PrintPoint(pt);

	// 当参数是绑定到一个右值时，就将参数转换成一个右值
	_PrintPoint(std::forward<Point>(pt));
}

void TestMoveSemantic()
{
	Point pt = GetPointObject();

	Point pt1 = std::move(pt);

	PrintPoint(std::move(pt1));
}

void TestCapacity()
{
	using namespace std;
	vector<ConstructCount> vec;
	cout << "vector::capacity() = " << vec.capacity() << endl;

	// reserve是直接扩充到已经确定的大小，可以减少多次开辟和释放空间、多次拷贝数据的问题，
	// reserve只是保证vector中的空间大小（capacity）最少达到参数所指定的大小n
	vec.reserve(3);
	cout << "vector::capacity() = " << vec.capacity() << endl;

	// resize改变逻辑长度，物理长度不够时补足内存，物理长度超过时不扣减物理长度
	vec.resize(4);
	cout << "vector::capacity() = " << vec.capacity() << endl;

	ConstructCount object(5);
	vec.resize(10, object);
	cout << "vector::capacity() = " << vec.capacity() << endl;
	auto oo = vec[4];

	vec.resize(0); // setLogicLength(0);
	cout << "vector::capacity() = " << vec.capacity() << endl;


	std::vector<int> arr;
	for (int i = 0; i < 50; ++i)
		arr.emplace_back(i);

	cout << "arr.size = " << arr.size() << " | arr.capacity = " << arr.capacity() << endl;
	arr.shrink_to_fit(); // 如果物理长度大于逻辑长度，使物理长度等于逻辑长度（减少内存占用）
	cout << "arr.size = " << arr.size() << " | arr.capacity = " << arr.capacity() << endl;
}

// resize(count,)改变元素个数，count大于vector.size时，尾部追加，调用构造；小于时，从尾部开始删元素，物理长度不变，等于setLogicLength
// reserve(new_cap)物理长度，new_cap大于vector.size才有效，等于setPhysicalLength
void TestResize()
{
	std::vector<int> arr = { 1,2,3,4,5 };
	cout << "arr.size = " << arr.size() << " | arr.capacity = " << arr.capacity() << endl;

//#define TEST_RESIZE_GREATER

#ifdef TEST_RESIZE_GREATER
	arr.resize(6);
#else
	arr.resize(3);
#endif
	for (const auto& value : arr)
		cout << value << ",";
	cout << endl << "arr.size = " << arr.size() << " | arr.capacity = " << arr.capacity() << endl;


	cout << endl << endl;

	std::vector<int> arr2 = { 1,2,3,4,5 };
	cout << "arr2.size = " << arr2.size() << " | arr2.capacity = " << arr2.capacity() << endl;

#define TEST_RESERVE_GREATER

#ifdef TEST_RESERVE_GREATER
	arr2.reserve(6);
#else
	arr2.reserve(3);
#endif
	for (const auto& value : arr2)
		cout << value << ",";
	cout << endl << "arr2.size = " << arr2.size() << " | arr2.capacity = " << arr2.capacity() << endl;
}

void TestVectorBase()
{
	vector<ConstructCount> vec;
	vec.reserve(100);
	vec.push_back(ConstructCount(1));
	vec.push_back(ConstructCount(2));

	// operator =
	cout << endl;
	vector<ConstructCount> vec2;
	vec2.reserve(100);
	vec2 = vec;
	cout << endl << "&vec[0]:" << &vec[0] << ", &vec2[0]:" << &vec2[0] << endl;
}