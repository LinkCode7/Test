#include "unordered_container.h"

#include <unordered_map>
#include <unordered_set>

void test_unordered_container()
{
    repeat_element();
}

void repeat_element()
{
    std::unordered_map<int, int> hash_map;
    std::unordered_map<int, int> hash_map1;
    hash_map1[1] = 1;
    hash_map1[1] = 11;

    for (const auto& item : hash_map1)
    {
        std::cout << item.first << "," << item.second << std::endl;
    }

    std::cout << std::endl << std::endl;

    std::unordered_map<int, int> hash_map2;
    hash_map2.insert(std::make_pair(2, 2));
    hash_map2.insert(std::make_pair(2, 22));

    for (const auto& item : hash_map2)
    {
        std::cout << item.first << "," << item.second << std::endl;
    }
}