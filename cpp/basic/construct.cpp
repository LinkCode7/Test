#include "construct.h"

using std::cout;
using std::endl;

TEST(Construct, CppClass)
{
    SimpleObject so;

    // error C2248 : “SimpleObject::operator new” : 无法访问 private 成员
    // SimpleObject* pSimpleObject = new SimpleObject;

    TestCppConstruct object1(1, 1, 1);
    TestCppConstruct object2(2, 2, 2);
    // object1 = object2;
}

TEST(Construct, DeepClone)
{
    EnableCopyTest object1("object1");
    object1.print();

    EnableCopyTest object2(object1);
    object2.print();

    EnableCopyTest object3 = object1;
    object3.print();

    // 此时不能在析构函数中释放
    for (auto& item : object1.m_arrPointer)
        delete item;

#ifdef TEST_COPY_CONSTRUCT_BUT_DISABLE
    DisableCopyClassTest disable1("disable1");
    DisableCopyClassTest disable2(disable1);  // error C2280: 尝试引用已删除的函数
    DisableCopyClassTest disable3 = disable1; // error C2280: 尝试引用已删除的函数
#endif
}

void EnableCopyTest::print()
{
    cout << endl
         << this << " >> "
         << " m_str: " << m_str << " m_int: " << m_int;
    cout << " m_arrInt: ";
    for (const auto& item : m_arrInt)
        cout << item << ", ";

    cout << endl << " m_arrPointer: ";
    for (const auto& item : m_arrPointer)
        cout << item << ", ";
    cout << " m_arrPtr: ";
    for (const auto& item : m_arrPtr)
        cout << item << ", "; // .get()

    cout << endl;
}

void DisableCopyClassTest::print()
{
    cout << endl
         << this << " >> "
         << " m_str: " << m_str << endl;
}

TEST(Construct, CopyContainer)
{
    MyVector<int> arr = {1};
}

TEST(Construct, make_shared)
{
    auto ptr = std::make_shared<ConstructWithSmartPtr>();

    ConstructWithSmartPtr* pointer = ptr.get();
    auto                   ptr2    = std::make_shared<ConstructWithSmartPtr>(*pointer);
    // auto ptr3 = std::make_shared<ConstructWithSmartPtr>(ptr); // error C2664
    auto ptr3 = std::make_shared<ConstructWithSmartPtr>(*ptr);
}

TEST(Construct, ReturnObject)
{
    ReturnObjectTest test;
    auto             result = test.getObject().get();
}

TEST(Construct, RedundantCopy)
{
    // 判断是否为易销毁类型
    bool trivially = std::is_trivially_destructible<TestPointObject>::value;
    assert(!trivially);
    {
        TestPointObject begin;
        TestPointObject end;
        TestLineObject  line(begin, end);
    }
}