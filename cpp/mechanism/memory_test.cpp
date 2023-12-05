#include "memory_test.h"

#ifdef USING_MEMORY_MANAGEMENT

class Name
{
    int _i;

public:
    Name(int i) : _i(i) {}
};

TEST(memory, operator_new_delete)
{
    int* p1 = new int;
    delete p1;

    int* p2 = new int[10]; // guaranteed to call the replacement in C++11
    delete[] p2;

    auto name = new Name(1);
    delete name;

    auto pName = std::make_shared<Name>(100);
    pName      = nullptr;
}

#endif // USING_MEMORY_MANAGEMENT