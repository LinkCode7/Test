#ifndef CPP_OBJECT_TEST_H
#define CPP_OBJECT_TEST_H

class CppObjectTest
{
	int* m_pNumber;
public:
	int number() const { return *m_pNumber; }
	void number(int value) { *m_pNumber = value; }

	CppObjectTest()
	{
		m_pNumber = new int(100);
		std::cout << "CppObjectTest() *m_pNumber = " << *m_pNumber << std::endl;
	}
	CppObjectTest(int i)
	{
		m_pNumber = new int(i);
		std::cout << "CppObjectTest(int i) *m_pNumber = " << *m_pNumber << std::endl;
	}
	CppObjectTest(const CppObjectTest& other)
	{
		m_pNumber = new int(*other.m_pNumber);
		std::cout << "CppObjectTest(const CppObjectTest& other) *m_pNumber = " << *m_pNumber << std::endl;
	}
	CppObjectTest& operator=(const CppObjectTest& other)
	{
		if (this != &other)
		{
			delete m_pNumber;
			m_pNumber = new int(*other.m_pNumber);
		}
		std::cout << "CppObjectTest& operator =(const CppObjectTest& other) *m_pNumber = " << *m_pNumber << std::endl;
		return *this;
	}

	// 移动构造
	explicit CppObjectTest(CppObjectTest&& other) noexcept
	{
		m_pNumber = other.m_pNumber; // attach
		other.m_pNumber = nullptr; // detach
		std::cout << "CppObjectTest(CppObjectTest&& other) *m_pNumber = " << *m_pNumber << std::endl;
	}

	// 移动赋值运算符
	CppObjectTest& operator=(CppObjectTest&& other)
	{
		if (this != &other)
		{
			m_pNumber = other.m_pNumber;
			other.m_pNumber = nullptr;
		}
		std::cout << "CppObjectTest& operator =(CppObjectTest&& other) *m_pNumber = " << *m_pNumber << std::endl;
		return *this;
	}

	~CppObjectTest()
	{
		if (m_pNumber)
			std::cout << "~CppObjectTest() *m_pNumber = " << *m_pNumber << std::endl;
		else
			std::cout << "~CppObjectTest() *m_pNumber = " << "null" << std::endl; // std::move(this)
		delete m_pNumber;
	}
};
using CppObjectTestPtr = std::shared_ptr<CppObjectTest>;

#endif // !#define CPP_OBJECT_TEST_H

