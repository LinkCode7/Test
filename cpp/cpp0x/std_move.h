#pragma once

void _test_move2();
void test_forward();

// std::move本身不移动对象，二是返回一个右值型别 -> make a moveable object
// std::forward并不转发

// 移动语义：https://www.cnblogs.com/5iedu/p/11318729.html

class TestMoveObject
{
public:
	int* m_pNumber;
	TestMoveObject()
	{
		m_pNumber = new int(100);
		std::cout << "TestMoveObject() *m_pNumber = " << *m_pNumber << std::endl;
	}
	TestMoveObject(int i)
	{
		m_pNumber = new int(i);
		std::cout << "TestMoveObject(int i) *m_pNumber = " << *m_pNumber << std::endl;
	}
	TestMoveObject(const TestMoveObject& other)
	{
		m_pNumber = new int(*other.m_pNumber);
		std::cout << "TestMoveObject(const TestMoveObject& other) *m_pNumber = " << *m_pNumber << std::endl;
	}
	TestMoveObject& operator=(const TestMoveObject& other)
	{
		if (this != &other)
		{
			delete m_pNumber;
			m_pNumber = new int(*other.m_pNumber);
		}
		std::cout << "TestMoveObject& operator =(const TestMoveObject& other) *m_pNumber = " << *m_pNumber << std::endl;
		return *this;
	}

	// 移动构造
	explicit TestMoveObject(TestMoveObject&& other) noexcept
	{
		m_pNumber = other.m_pNumber; // attach
		other.m_pNumber = nullptr; // detach
		std::cout << "TestMoveObject(TestMoveObject&& other) *m_pNumber = " << *m_pNumber << std::endl;
	}

	// 移动赋值运算符
	TestMoveObject& operator=(TestMoveObject&& other)
	{
		if (this != &other)
		{
			m_pNumber = other.m_pNumber;
			other.m_pNumber = nullptr;
		}
		std::cout << "TestMoveObject& operator =(TestMoveObject&& other) *m_pNumber = " << *m_pNumber << std::endl;
		return *this;
	}

	~TestMoveObject()
	{
		if (m_pNumber)
			std::cout << "~TestMoveObject() *m_pNumber = " << *m_pNumber << std::endl;
		else
			std::cout << "~TestMoveObject() *m_pNumber = " << "null" << std::endl;
		delete m_pNumber;
	}
};
typedef std::shared_ptr<TestMoveObject> TestMoveObjectPtr;

class RValueReferencesTest
{
	std::vector<TestMoveObject> m_array;
public:
	// 以右值引用传递
	void setOfReference(const std::vector<TestMoveObject>& arr)
	{
		m_array = arr;
	}
	void setOfRValue(std::vector<TestMoveObject>&& arr)
	{
		// vector&&,std::exchange(m_array, arr);
		//m_array = static_cast<std::vector<TestMoveObject>&&>(arr); // 移动构造
		//m_array = std::forward<std::vector<TestMoveObject>&&>(arr); // 移动构造

		m_array = arr; // msvc-ISO C++17：会执行拷贝构造
	}
};

std::vector<int> get_vector()
{
	// 此处的左值temp会被进行此隐式右值转换，等价于static_cast<std::vector<int> &&>(temp)
	std::vector<int> temp = { 1, 2, 3, 4 };
	return temp;
}
