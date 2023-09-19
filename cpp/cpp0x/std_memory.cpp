#include "std_memory.h"

void test_string_view()
{
    constexpr std::string_view unicode[]{"▀▄─", "▄▀─", "▀─▄", "▄─▀"};

    for (int y{}, p{}; y != 6; ++y, p = ((p + 1) % 4))
    {
        for (int x{}; x != 16; ++x)
            std::cout << unicode[p];
        std::cout << '\n';
    }
}

// std::string_view保存了一段连续缓冲区的引用，注意引用临时对象后会产生未定义行为
TEST(memory, string_view)
{
    // test_string_view();

    std::string line("int _value;");

    auto size = line.size();
    if (line[size - 1] != ';')
        return;

    auto pos = line.find(' ');
    if (pos == std::string::npos)
        return;

    std::string      name  = line.substr(pos + 1, (size - 1) - (pos + 1));
    std::string_view name2 = line.substr(pos + 1, (size - 1) - (pos + 1)); // 引用临时对象

    auto ss = name2.size();

    std::cout << "name:" << name << std::endl;
    std::cout << "name2:" << name2 << std::endl;
}
