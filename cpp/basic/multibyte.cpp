#include "multibyte.h"
// #include "assert.h"

#include <cassert>
#include <clocale>
#include <cstring>
#include <cuchar>
#include <cwchar>
#include <iomanip>
#include <iostream>

TEST(multibyte, u32string)
{
    std::setlocale(LC_ALL, "en_US.utf8");

    std::string str = u8"z\u00df\u6c34\U0001F34C"; // 或 u8"zß水🍌"

    std::cout << "Processing " << str.size() << " bytes: [ " << std::showbase;
    for (unsigned char c : str)
        std::cout << std::hex << +c << ' ';
    std::cout << "]\n";

    std::mbstate_t state{}; // 零初始化为初始状态
    char32_t       c32;
    const char *   ptr = str.c_str(), *end = str.c_str() + str.size() + 1;

    while (std::size_t rc = std::mbrtoc32(&c32, ptr, end - ptr, &state))
    {
        std::cout << "Next UTF-32 char: " << std::hex << c32 << " obtained from ";
        assert(rc != (std::size_t)-3); // no surrogates in UTF-32
        if (rc <= ((std::size_t)-1) / 2)
        {
            std::cout << std::dec << rc << " bytes [ ";
            for (std::size_t n = 0; n < rc; ++n)
                std::cout << std::hex << +(unsigned char)ptr[n] << ' ';
            std::cout << "]\n";
            ptr += rc;
        }
        else
            break;
    }

    std::cout << std::dec;

    std::string    strUtf8 = "123";
    std::u32string strU32(strUtf8.begin(), strUtf8.end()); // U"..."
    std::cout << strU32.c_str() << std::endl;
}
