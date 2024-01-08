#include "std_function.h"

TEST(std_function, func_init)
{
    std::function<int()> fun = []() { return 100; };

    TestFunction obj(fun);

    if (obj.valid())
        std::cout << obj.result() << std::endl;
}
