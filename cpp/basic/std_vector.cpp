#include <algorithm>
#include <cassert>
#include <vector>

class TestVectorResize
{
    int value_;

public:
    TestVectorResize(int value) : value_(value) { std::cout << "TestVectorResize(int value)" << std::endl; }
    TestVectorResize(TestVectorResize&& other) : value_(other.value_)
    {
        std::cout << "TestVectorResize(TestVectorResize &&other)" << std::endl;
    }
    TestVectorResize(const TestVectorResize& other) : value_(other.value_)
    {
        std::cout << "TestVectorResize(const TestVectorResize& other)" << std::endl;
    }
    ~TestVectorResize() { std::cout << "~TestVectorResize()" << std::endl; }
};

// 重置元素大小
TEST(std_vector, resize)
{
    std::vector<int> arr1{1, 2, 3, 4, 5};
    arr1.resize(10, -1); // 1,2,3,4,5,-1,-1,-1,-1,-1

    std::vector<int> arr2{1, 2, 3, 4, 5};
    arr2.resize(10); // 默认构造填充：1,2,3,4,5,0,0,0,0,0

    std::vector<int*> arr3{new int(1), new int(2), new int(3), new int(4), new int(5)};
    arr3.resize(7); // 1,2,3,4,5,nullptr,nullptr
    std::for_each(arr3.begin(), arr3.end(), [](int* pointer) { delete pointer; });

    // 新值比旧值小，缩容、析构尾部元素
    std::vector<TestVectorResize> arr4{1, 2, 3, 4, 5};
    auto                          capacity4 = arr4.capacity();

    // 注意这里析构了三次、构造了一次
    std::cout << ">> arr4.resize():" << std::endl;
    arr4.resize(3, -1); // 1,2,3
    assert(arr4.size() == 3);

    assert(arr4.capacity() == capacity4);
}

// 扩容
TEST(std_vector, reserve)
{
    // 新值比旧值大，扩容、元素不变
    std::vector<int> arr1{1, 2, 3, 4, 5};
    auto             capacity1 = arr1.capacity(); // 不同编译器实现不同：vc++是1.5倍、g++2倍
    arr1.reserve(10);                             // 1,2,3,4,5
    assert(arr1.size() == 5);
    assert(arr1.capacity() == 10);

    // 新值比旧值小，不做任何处理
    std::vector<TestVectorResize> arr3{1, 2, 3, 4, 5};
    auto                          size3     = arr3.size();
    auto                          capacity3 = arr3.capacity();
    arr3.reserve(3);
    assert(arr3.size() == size3);
    assert(arr3.capacity() == capacity3);
}
