#include "operator.h"

void testOperator1()
{
    std::string strResult = Read();
    long        result    = Read();
    bool        isTrue    = Read();

    testCppOperator();
    testCompareSharedPtr();
    testSortPointer();
}

void testCppOperator()
{
    MyObject object1;
    MyObject object2(10);
    MyObject object3(3.14);

    MyObject object4(object1);
    MyObject object5 = object2;
    object5          = object1; // operator=
    object5          = 0.5;     // MyObject(double value),operator=
}

void testCompareSharedPtr()
{
    MyObjectPtr p1 = std::make_shared<MyObject>(1);
    MyObjectPtr p3 = std::make_shared<MyObject>(3);
    MyObjectPtr p2 = std::make_shared<MyObject>(2);

    std::vector<MyObjectPtr> arrObject = {p1, p3, p2};

    std::sort(arrObject.begin(), arrObject.end(), [&](const MyObjectPtr& left, const MyObjectPtr& right) {
        return left->value_ < right->value_; // 自动推导返回值类型
    });
}

void testSortPointer()
{
}