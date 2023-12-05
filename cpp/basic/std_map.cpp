#include "std_map.h"

#include <map>
#include <unordered_map>

#include "assert.h"

using std::map;

template <typename First, typename Second>
bool compareExistValueInMap(const std::map<First, Second>& mapFirst2Second, const First& first, const Second& second)
{
    auto iter = mapFirst2Second.find(first);
    if (iter == mapFirst2Second.end())
        return false;
    return (second == iter->second);
}

TEST(std_map, access)
{
    map<int, int> mapInt2Int = {{1, 11}, {2, 22}};

    int first = 1;

    // 1 map::find()访问
    auto iter = mapInt2Int.find(first);
    if (iter != mapInt2Int.end())
        assert(iter->second == 11);

    // 2 map::operator[]访问
    mapInt2Int[3] = 33;
    {
        /*
         * "非只读的operator[]"一定会修改map的second，不存在key时会插入一个新的
         * 两种写法："mapInt2Int[first] = second;" 和 "if (auto iter = mapInt2Int.find(first); iter == mapInt2Int.end())
         * mapInt2Int[first] = second;" 后者不会强制插入key，只有存在key时才更新value，避免不必要键值对
         */
        mapInt2Int[2] = -22;
        assert(compareExistValueInMap(mapInt2Int, 2, -22));
    }
    assert(compareExistValueInMap(mapInt2Int, 1, 11));

    // operator[]访问不存在的first，会返回默认构造的second
    assert(mapInt2Int[0] == 0);

    map<std::string, std::string> mapStr2Int = {{"a", "aa"}, {"b", "bb"}};
    assert(mapStr2Int["not exist"] == "");

    {
        map<int, AccessStdMapTest> mapInt2Object = {{1, AccessStdMapTest()}, {2, AccessStdMapTest()}};
        std::cout << ">>> get not exist value in mapInt2Object:" << std::endl;
        const AccessStdMapTest& object = mapInt2Object[0]; // 调用默认构造函数
    }
    {
        map<int, AccessStdMapTest*> mapInt2Pointer = {{1, new AccessStdMapTest}, {2, new AccessStdMapTest}};
        std::cout << ">>> get not exist value in mapInt2Pointer:" << std::endl;
        AccessStdMapTest*& pObject = mapInt2Pointer[0];
        assert(pObject == nullptr);
    }
    {
        map<int, AccessStdMapTestPtr> mapInt2Ptr = {{1, std::make_shared<AccessStdMapTest>()},
                                                    {2, std::make_shared<AccessStdMapTest>()}};
        std::cout << ">>> get not exist value in mapInt2Ptr:" << std::endl;
        const AccessStdMapTestPtr& pObject = mapInt2Ptr[0];
        assert(pObject == nullptr);
        assert(pObject.get() == nullptr);
    }

    // 2 map::at访问
    mapInt2Int = {{1, 11}, {2, 22}};
    int second = mapInt2Int.at(1);
    assert(second == 11);
#if 0
	mapInt2Int.at(0); // _Xout_of_range("invalid map<K, T> key");
#endif
}

TEST(std_map, emplace)
{
    std::map<int, std::unique_ptr<std::string>> my_map;
    my_map.emplace(1, std::make_unique<std::string>("good"));
    my_map[1] = std::make_unique<std::string>("leak");

    map<int, int> mapInt2Int = {{1, 11}, {2, 22}};
    auto          size       = mapInt2Int.size();

    // emplace已存在的元素
    auto [iter, inserted] = mapInt2Int.emplace(1, -1);
    assert(!inserted);
    assert(iter->second == 11);
    assert(mapInt2Int.size() == size);

    // emplace不存在的元素
    auto [iter2, inserted2] = mapInt2Int.emplace(3, 33);
    assert(inserted2);
    assert(iter2->second == 33);
    assert(mapInt2Int.size() == size + 1);

    // 参数一：给容器提供一个插入位置的建议，并不一定会被容器采纳，取决于key
    auto iter3 = mapInt2Int.emplace_hint(mapInt2Int.begin(), 10, 1000);
}

TEST(std_map, try_emplace)
{
    // 若容器中已存在等价于 k 的关键，则不做任何事。否则行为类似 emplace
    std::map<std::string, std::string> mapStr2Str;
    mapStr2Str.try_emplace("a", "a");
    mapStr2Str.try_emplace("b", "abcd");
    mapStr2Str.try_emplace("c", 3, 'c'); // <"c", "ccc">
    mapStr2Str.try_emplace("c", "Won't be inserted");

    assert(mapStr2Str.size() == 3);
}

TEST(std_map, insert_or_assign)
{
    std::map<std::string, std::string> mapStr2Str;
    mapStr2Str.insert_or_assign("a", "a");
    mapStr2Str.insert_or_assign("b", "b");
    mapStr2Str.insert_or_assign("c", "c");
    mapStr2Str.insert_or_assign("c", "cc");

    assert(mapStr2Str.size() == 3);

    auto iter = mapStr2Str.find("c");
    if (iter != mapStr2Str.end())
        assert(iter->second == "cc");
}
