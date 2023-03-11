#ifndef STD_MAP_H
#define STD_MAP_H
#include <memory>

class AccessStdMapTest
{
	int m_int;
public:
	int value() const { return m_int; }
	void value(int val) { m_int = val; }

	AccessStdMapTest()
	{
		m_int = 100;
		std::cout << "AccessStdMapTest() m_int = " << m_int << std::endl;
	}
	AccessStdMapTest(int i)
	{
		m_int = i;
		std::cout << "AccessStdMapTest(int i) m_int = " << m_int << std::endl;
	}
	AccessStdMapTest(const AccessStdMapTest& other)
	{
		m_int = other.m_int;
		std::cout << "AccessStdMapTest(const AccessStdMapTest& other) m_int = " << m_int << std::endl;
	}
	AccessStdMapTest& operator=(const AccessStdMapTest& other)
	{
		if (this != &other)
			m_int = other.m_int;
		std::cout << "AccessStdMapTest& operator =(const AccessStdMapTest& other) m_int = " << m_int << std::endl;
		return *this;
	}

	// 移动构造
	explicit AccessStdMapTest(AccessStdMapTest&& other) noexcept
	{
		m_int = other.m_int; // attach
		other.m_int = 0; // detach
		std::cout << "AccessStdMapTest(AccessStdMapTest&& other) m_int = " << m_int << std::endl;
	}

	// 移动赋值运算符
	AccessStdMapTest& operator=(AccessStdMapTest&& other)
	{
		if (this != &other)
		{
			m_int = other.m_int;
			other.m_int = 0;
		}
		std::cout << "AccessStdMapTest& operator =(AccessStdMapTest&& other) m_int = " << m_int << std::endl;
		return *this;
	}

	~AccessStdMapTest()
	{
		std::cout << "~AccessStdMapTest() m_int = " << m_int << std::endl;
	}
};
using AccessStdMapTestPtr = std::shared_ptr<AccessStdMapTest>;

#endif // !STD_MAP_H
