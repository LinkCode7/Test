#ifndef CPP11_BASIC_H
#define CPP11_BASIC_H
//#include <vector>
#include <type_traits>
#include <unordered_map>
#include <iostream>

class MyIntClass
{
public:
	int m_int;
	MyIntClass() :m_int(0) { std::cout << "MyIntClass()" << std::endl; }
	MyIntClass(int i) :m_int(i) { std::cout << "MyIntClass(int i)" << std::endl; }
	MyIntClass(const MyIntClass& other) :m_int(other.m_int) { std::cout << "MyIntClass(const MyIntClass & other)" << std::endl; }
	MyIntClass(MyIntClass&& other) :m_int(other.m_int) { std::cout << "MyIntClass(MyIntClass && other)" << std::endl; }

	MyIntClass& operator=(const MyIntClass& other)
	{
		m_int = other.m_int;
		std::cout << "MyIntClass& operator=(const MyIntClass & other)" << std::endl;
		return *this;  // 支持连等：a = b = c;
	}
	MyIntClass& operator=(MyIntClass&& other) noexcept
	{
		m_int = other.m_int;
		//other.m_int = 0;
		std::cout << "MyIntClass& operator=(MyIntClass && other) noexcept" << std::endl;
		return *this;
	}

	// other
	bool operator==(const MyIntClass& other) const { // 作为unordered_map.key要实现
		std::cout << ">>> bool operator==(const MyIntClass& other) const" << std::endl;
		return m_int == other.m_int;
	}
	bool operator!=(const MyIntClass& other) const {
		std::cout << ">>> bool operator!=(const MyIntClass& other) const" << std::endl;
		return m_int != other.m_int;
	}
	bool operator<(const MyIntClass& other) const {
		std::cout << ">>> bool operator<(const MyIntClass& other) const" << std::endl;
		return m_int < other.m_int;
	}
};

struct my_hash_code {
	size_t operator()(const MyIntClass& id) const { return std::hash<unsigned int>()(id.m_int) ^ std::hash<unsigned int>()(id.m_int); }
};

class TestCpp11Class
{
	std::vector<MyIntClass> m_arr;
	std::unordered_map<MyIntClass, std::vector<MyIntClass>, my_hash_code> m_mapInt2Array;

public:
	std::vector<MyIntClass> getArray() {
		std::cout << "--->getArray()" << std::endl;
		return m_arr;
	}
	std::vector<MyIntClass>* getArrayPoint() {
		std::cout << "--->getArrayPoint()" << std::endl;
		return &m_arr;
	}
	std::vector<MyIntClass>& getArrayReference() {
		std::cout << "--->getArrayReference()" << std::endl;
		return m_arr;
	}

	std::unordered_map<MyIntClass, std::vector<MyIntClass>, my_hash_code> getMap() {
		std::cout << "--->getMap()" << std::endl;
		return m_mapInt2Array;
	}
	std::unordered_map<MyIntClass, std::vector<MyIntClass>, my_hash_code>* getMapPoint() {
		std::cout << "--->getMapPoint()" << std::endl;
		return &m_mapInt2Array;
	}
	std::unordered_map<MyIntClass, std::vector<MyIntClass>, my_hash_code>& getMapReference() {
		std::cout << "--->getMapReference()" << std::endl;
		return m_mapInt2Array;
	}

	void initArray();
	void initMap();
};

#endif
