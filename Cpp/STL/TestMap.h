#pragma once




class TestMapObject
{
public:
	TestMapObject(int i) : m_i(i)
	{
		std::cout << "TestMapObject(int i)" << std::endl;
	}
	~TestMapObject()
	{
		std::cout << "~TestMapObject() m_i = " << m_i << std::endl;
	}

private:
	int m_i;
};
typedef std::shared_ptr<TestMapObject> TestMapObjectPtr;