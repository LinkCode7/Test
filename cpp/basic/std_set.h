#ifndef SED_SET_H
#define SED_SET_H
#include <string>
#include <memory>
#include <iostream>

class TestFunctionObjectOfSet;
using TestFunctionObjectOfSetPtr = std::shared_ptr<TestFunctionObjectOfSet>;

class TestFunctionObjectOfSet
{
	std::string m_str;
public:
	TestFunctionObjectOfSet(const std::string& str) : m_str(str) {}

	std::string name() const { return m_str; }
	void name(const std::string& str) { m_str = str; }

	// 不依赖operator==
	bool operator==(const TestFunctionObjectOfSet&) const = delete;
	bool operator==(const TestFunctionObjectOfSetPtr&) const = delete;

	size_t operator()() const
	{
		std::cout << "size_t operator()()" << std::endl;
		return std::hash<std::string>()(m_str);
	}

	bool operator<(const TestFunctionObjectOfSet& right) const {
		std::cout << "bool operator<(const TestFunctionObjectOfSet& right) const" << std::endl;
		return m_str < right.m_str;
	}

	// 这里必须写friend（error C2804: 二进制“operator <”的参数太多），且不能写const（error C2270: “<”: 非成员函数上不允许修饰符）
	friend bool operator<(const TestFunctionObjectOfSetPtr& left, const TestFunctionObjectOfSetPtr& right) {
		std::cout << "friend bool operator<(const TestFunctionObjectOfSetPtr& left, const TestFunctionObjectOfSetPtr& right)" << std::endl;
		return left->m_str < right->m_str;
	}
	bool operator<(const TestFunctionObjectOfSetPtr& right) const {
		std::cout << "It's not called" << std::endl;
		return m_str < right->m_str;
	}
};

struct TestFunctionObjectOfSetCompare
{
	bool operator()(const TestFunctionObjectOfSet& left, const TestFunctionObjectOfSet& right) const
	{
		std::cout << ">>> bool operator()(const TestFunctionObjectOfSet& left, const TestFunctionObjectOfSet& right) const" << std::endl;
		return left.name() < right.name();
	}
};

struct TestFunctionObjectOfSetPtrCompare
{
	bool operator()(const TestFunctionObjectOfSetPtr& left, const TestFunctionObjectOfSetPtr& right) const
	{
		std::cout << ">>> bool operator()(const TestFunctionObjectOfSetPtr& left, const TestFunctionObjectOfSetPtr& right) const" << std::endl;
		return left->name() < right->name();
	}
};



class TestFunctionObjectOfUnorderedSet;
using TestFunctionObjectOfUnorderedSetPtr = std::shared_ptr<TestFunctionObjectOfUnorderedSet>;

class TestFunctionObjectOfUnorderedSet
{
	std::string m_name;
	std::string m_adress;
public:
	TestFunctionObjectOfUnorderedSet(const std::string& name, const std::string& adress) : m_name(name), m_adress(adress) {}

	std::string name() const { return m_name; }
	void name(const std::string& str) { m_name = str; }

	std::string adress() const { return m_adress; }
	void adress(const std::string& str) { m_adress = str; }

#if 1
	// 依赖operator==
	bool operator==(const TestFunctionObjectOfUnorderedSet& other) const
	{
		std::cout << "bool operator==(const TestFunctionObjectOfUnorderedSet& other) const" << std::endl;
		return m_name == other.m_name && m_adress == other.m_adress;
	}
	bool operator==(const TestFunctionObjectOfUnorderedSetPtr& other) const = delete;
#endif


	size_t operator()(const TestFunctionObjectOfUnorderedSet& item) const
	{
		std::cout << "size_t operator()(const TestFunctionObjectOfUnorderedSet& item) const" << std::endl;
		return std::hash<std::string>()(item.m_name) ^ std::hash<std::string>()(item.m_adress);
		return std::hash<std::string>()(item.m_name);
	}
};

struct TestFunctionObjectOfUnorderedSetCompare
{
	size_t operator()(const TestFunctionObjectOfUnorderedSet& item) const
	{
		std::cout << ">>> size_t operator()(const TestFunctionObjectOfUnorderedSet& item) const" << std::endl;
		return std::hash<std::string>()(item.name()) ^ std::hash<std::string>()(item.adress());
	}
};

struct TestFunctionObjectOfUnorderedSetPtrCompare
{
	size_t operator()(const TestFunctionObjectOfUnorderedSetPtr& item) const
	{
		std::cout << ">>> size_t operator()(const TestFunctionObjectOfUnorderedSetPtr& item) const" << std::endl;
		return std::hash<std::string>()(item->name()) ^ std::hash<std::string>()(item->adress());
	}
};

#endif
