#pragma once
#include "my_vector.h"

// 宏控制，拷贝和构造，放在private下是不允许拷贝和构造
#define COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&);    \
    TypeName& operator=(const TypeName&)

// 宏控制，操作符new和delete，放在private下是不允许堆上实例化
#define OPERATOR_NEW_DELETE(TypeName) \
    void* operator new(size_t size);  \
    void  operator delete(void* ptr)

class SimpleObject
{
private:
    COPY_AND_ASSIGN(SimpleObject);
    OPERATOR_NEW_DELETE(SimpleObject);

public:
    SimpleObject() { m_i = 0; }
    ~SimpleObject() {}

private:
    int m_i;
};

class DeepCloneItemTest
{
public:
    DeepCloneItemTest()                               = default;
    DeepCloneItemTest(const DeepCloneItemTest& other) = default;

    DeepCloneItemTest(int id) : m_id(id) {}

    int m_id = 0;
};
using TestDeepCloneItemSp = std::shared_ptr<DeepCloneItemTest>;

class EnableCopyTest
{
public:
    EnableCopyTest()                            = default;
    EnableCopyTest(const EnableCopyTest& other) = default;

    EnableCopyTest(const std::string str) : m_str(str) {}
    ~EnableCopyTest() {}

    void print();

    int              m_int    = 1001;
    std::string      m_str    = "string";
    std::vector<int> m_arrInt = {1, 2, 3}; // 值拷贝

    std::vector<DeepCloneItemTest*>  m_arrPointer = {new DeepCloneItemTest(1), new DeepCloneItemTest(2)};
    std::vector<TestDeepCloneItemSp> m_arrPtr     = {std::make_shared<DeepCloneItemTest>(10), std::make_shared<DeepCloneItemTest>(20)};
};

class DisableCopyClassTest
{
public:
    DisableCopyClassTest()                                  = delete;
    DisableCopyClassTest(const DisableCopyClassTest& other) = delete;

    DisableCopyClassTest(const std::string str) : m_str(str) {}

    void print();

    std::string m_str = "string";
};

//
class CopyContainerTest
{
    std::string   m_str    = "string";
    MyVector<int> m_arrInt = {1, 2, 3};

public:
    CopyContainerTest()                               = default;
    CopyContainerTest(const CopyContainerTest& other) = default;

    CopyContainerTest(const std::string str) : m_str(str) {}

    MyVector<int> get();
};

class ConstructWithSmartPtr
{
    int m_int;

public:
    ConstructWithSmartPtr() : m_int(1) {}
    ConstructWithSmartPtr(const ConstructWithSmartPtr& other) : m_int(other.m_int) {}

    int get() { return m_int; }
};

class ReturnObjectTest
{
    ConstructWithSmartPtr m_obj;

public:
    ConstructWithSmartPtr getObject() { return m_obj; }
};

class TestPointObject
{
public:
    TestPointObject() { std::cout << "TestPointObject()" << std::endl; }
    TestPointObject(int i) { std::cout << "TestPointObject(int i)" << std::endl; }
    TestPointObject(const TestPointObject& other) { std::cout << "TestPointObject(const TestPointObject& other)" << std::endl; }
    TestPointObject& operator=(const TestPointObject& other)
    {
        std::cout << "TestPointObject& operator =(const TestPointObject& other)" << std::endl;
        return *this;
    }
    explicit TestPointObject(TestPointObject&& other) noexcept { std::cout << "TestPointObject(TestPointObject&& other)" << std::endl; }
    TestPointObject& operator=(TestPointObject&& other)
    {
        std::cout << "TestPointObject& operator =(TestPointObject&& other)" << std::endl;
        return *this;
    }
    ~TestPointObject() { std::cout << "~TestPointObject()" << std::endl; }
};

class TestLineObject
{
    TestPointObject begin_;
    TestPointObject end_;

public:
    TestLineObject(const TestPointObject& begin, const TestPointObject& end) : begin_(begin), end_(end) {}
    // TestLineObject(const TestPointObject& begin, const TestPointObject& end) : begin_(std::move(begin)), end_(std::move(end)) {}
};

class TestCppConstruct
{
    int _1 = 0;
    int _2 = 0;
    int _3 = 0;

public:
    TestCppConstruct() {}

    TestCppConstruct(int i1, int i2, int i3) : _1(i1), _2(i2), _3(i3) {}
    TestCppConstruct(TestCppConstruct const& other) : _1(other._1), _2(other._2), _3(other._3) {}
    // void operator=(TestCppConstruct const& other) { TestCppConstruct(other); } // 此时为什么需要默认构造函数?
};