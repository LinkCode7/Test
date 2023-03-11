#include "pch.h"
#include "std_move.h"
//#include "std_bind.h"

#include <utility> // std::move

using namespace std;

template <class T>
void ShrinkToFit(vector<T>& arr) { vector<T>(arr).swap(arr); }

TEST(std_move, test_container)
{
#define _USE_SMART_POINTER

#ifdef _USE_SMART_POINTER
#define TEST_MOVE_OBJECT TestMoveObjectPtr
#else
#define TEST_MOVE_OBJECT TestMoveObject
#endif

	{
		std::vector<TEST_MOVE_OBJECT> arr;
		// set physical length
		arr.reserve(1000);

#ifdef _USE_SMART_POINTER
		arr.push_back(std::make_shared<TestMoveObject>());
		std::cout << "-------------------------------------------" << std::endl;
		arr.push_back(std::make_shared<TestMoveObject>(2));
		//TestMoveObject p1 = TestMoveObject(1001);
#else
		arr.push_back(TestMoveObject());
		std::cout << "-------------------------------------------" << std::endl;
		arr.push_back(TestMoveObject(2));
#endif

		std::cout << "-------------------------------------------" << std::endl;

		map<int, std::vector<TEST_MOVE_OBJECT>> mapp;
		mapp.insert(make_pair(1, arr));
		mapp[1] = arr;
		std::cout << "-------------------------------------------" << std::endl;

		int value = -1;
		for (const auto& item : mapp)
		{
			// 拷贝构造（不使用智能指针）
			std::vector<TEST_MOVE_OBJECT> con = item.second;
			const auto& container = item.second;
			//value = item.second[0].m_pNumber;
		}
	}

#undef TEST_MOVE_OBJECT
}

// 标准库的例子
TEST(std_move, standard_example)
{
	// std::move是将对象的状态或者所有权从一个对象转移到另一个对象，
	// 因为没有内存的搬迁/拷贝，所以可以提高利用效率，改善性能

	std::string str = "hello world";
	std::vector<std::string> v;
	// 将使用 push_back(const T&), 即产生拷贝行为
	v.push_back(str);
	std::cout << "str : [" << str << "]" << std::endl;
	// 将使用 push_back(const T&&), 不会出现拷贝行为
	// 而整个字符串会被移动到 vector 中，所以有时候 std::move 会用来减少拷贝出现的开销
	v.push_back(std::move(str));
	std::cout << "str : [" << str << "]" << std::endl;

	_test_move2();
}

void _test_move2()
{
	TestMoveObject object(1001);
	std::cout << ">>> before move : " << object.m_pNumber << std::endl;
	{
		std::vector<TestMoveObject> arr;
		arr.reserve(1000);
		arr.emplace_back(object);
		arr.emplace_back(std::move(object));
	}

	std::cout << ">>> after move : " << object.m_pNumber << std::endl;
}

TEST(std_move, move_and_swap)
{
	std::vector<int> arr; // = { 1, 2, 3, 4, 5 };
	arr.push_back(0);
	arr.push_back(1);
	arr.push_back(2);
	arr.push_back(3);
	arr.push_back(4);

	std::cout << "size : " << arr.size() << ", capacity : " << arr.capacity() << std::endl;
	ShrinkToFit(arr);
	std::cout << "size : " << arr.size() << ", capacity : " << arr.capacity() << std::endl;
}

// 利用移动语义实现高性能的swap函数
template<typename T>
void _Swap(T& lhs, T& rhs)
{
	// 如果a、b是可移动的，则直接转移资源的所有权
	// 如果是不可移动的，则通过复制来交换两个对象
	T temp(std::move(lhs));
	lhs = std::move(rhs);
	rhs = std::move(temp);
}

TEST(std_move, test_container2)
{
	std::vector<TestMoveObjectPtr> vec;
	vec.reserve(1000);
	vec.push_back(std::make_shared<TestMoveObject>());
	vec.push_back(std::make_shared<TestMoveObject>());

	// map的second是个容器
	map<int, std::vector<TestMoveObjectPtr>> mapp;
	mapp.insert(make_pair(1, vec));
	mapp[1] = vec;

	auto sp = std::make_shared<TestMoveObject>(9);
	std::vector<TestMoveObjectPtr> container;

	auto iter = mapp.find(1);
	if (iter == mapp.end())
	{
		container.push_back(sp);
		mapp[2] = container;
	}
	else
	{
		//container = iter->second;
		//container.push_back(sp);
		iter->second.push_back(sp);
	}
}

TEST(std_move, return_vector)
{
	std::vector<int> vec = get_vector();
}

void test_forward()
{
}

TEST(std_move, rvalue)
{
	{
		std::vector<TestMoveObject> arr = { 10,20,30 };

		RValueReferencesTest object;
		object.setOfReference(arr);
	}

	{
		std::vector<TestMoveObject> arr = { 1,2,3 };

		RValueReferencesTest object;
		object.setOfRValue(std::move(arr));
	}
}



void foo(const TestMoveObject& n)
{
	// 一次默认构造、一次拷贝构造、一次析构
	{
		// 在对象上 const 调用时， std::move 返回对象的副本，该副本可能不是开发人员的意图。
		// 代码分析名称： NO_MOVE_OP_ON_CONST
		const TestMoveObject local1 = std::move(n); // C26478 reported here
	}

	// 没有发生构造
	{
		const TestMoveObject& local2 = std::move(n);
	}
}
template <typename T>
void bar(T t) {};
TEST(std_move, move_const_value)
{
	// 不要对常量变量使用 std::move
	TestMoveObject object;
	foo(object);

	const TestMoveObject cobject;
	bar(std::move(cobject)); // C26478 reported here
}











// 已知A公司的图形库中有一个矩形类如下，它实现了宽、高的Get/Set方法，请用面向对象的思想依次回答如下问题，考虑使用封装、继承、多态、接口等，形式不限，尽你所能！
// 1.请写一个正方形类(Square)，同样实现其宽、高的Get/Set方法（正方形是特殊的矩形）
// 2.现在需要将矩形、正方形显示出来：请为这些类声明一个绘制方法(不要纠结实现，原型为：void Draw();)
// 3.现在需要将A公司的图形绘制在B公司的设备环境上，请为B公司申明这些类的绘制方法，比如：void DrawRectangle(const Rectangle& rectangle);
class Rectangle
{
public:
	virtual void SetHeight(int iHeight) { m_iHeight = iHeight; }
	virtual void SetWidth(int iWidth) { m_iWidth = iWidth; }

	virtual int GetHeight() { return m_iHeight; }
	virtual int GetWidth() { return m_iWidth; }


private:
	int m_iHeight;
	int m_iWidth;
};



// 本题主要考察面向对象思想，扩展：面向接口编程思想
// 1.1 Square继承Rectangle，这种是最常见的错误：public继承中应严格遵守is-a的关系
// 1.2 Square单独写一个类，较好方法

// 2.1 为每个类实现一个Draw函数，不利于维护、扩展
// 2.2 实现一个基类（Entity或Geometry或Shape）,基类提供需函数，子类实现虚函数
// 2.3 实现接口

// 3.1 逐个实现：void DrawRectangle(const Rectangle& rectangle); void DrawSquare(const Square& square); 无法扩展业务，不现实的实现
// 3.2 void DrawShape(const Shape& shape) { shape.Draw(); }
// 3.3 实现接口