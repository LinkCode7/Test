#include "std_set.h"

#include <bitset>
#include <set>
#include <unordered_set>

#include "assert.h"

using namespace std;

TEST(std_set, insert_result)
{
    set<int> digits;
    auto     result = digits.insert(100);
    ASSERT_EQ(result.second, true);
    // CompileTimeTypeDiagnosis<decltype(result)> object;
    // CompileTimeTypeDiagnosis<std::pair<std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<int>>>,bool>>

    result = digits.insert(100);
    ASSERT_EQ(result.second, false);
}

TEST(std_set, key_compare_object)
{
    set<TestFunctionObjectOfSet> setObject;
    setObject.emplace(TestFunctionObjectOfSet("b"));
    setObject.emplace(TestFunctionObjectOfSet("a"));
    setObject.emplace(TestFunctionObjectOfSet("c"));

    // 修改元素
    for (auto& item : setObject)
    {
        if (item.name() == "c")
            const_cast<TestFunctionObjectOfSet&>(item).name(std::string("d"));
    }

    // 新增元素
    bool bInsert = setObject.emplace(TestFunctionObjectOfSet("a")).second; // 相同元素
    assert(bInsert == false);
    setObject.emplace(TestFunctionObjectOfSet("p"));
    setObject.emplace(TestFunctionObjectOfSet("o"));
    setObject.emplace(TestFunctionObjectOfSet("i"));
    setObject.emplace(TestFunctionObjectOfSet("u"));

    // 删除第一个元素
    std::cout << std::endl;
    auto iter = setObject.begin();
    for (; iter != setObject.end();)
    {
        iter = setObject.erase(iter);
    }
}

TEST(std_set, key_compare)
{
    // set存普通对象
    set<TestFunctionObjectOfSet> setObject;
    setObject.emplace(TestFunctionObjectOfSet("b"));
    setObject.emplace(TestFunctionObjectOfSet("a"));
    setObject.emplace(TestFunctionObjectOfSet("c"));

    set<TestFunctionObjectOfSet, TestFunctionObjectOfSetCompare> setObject2;
    setObject2.emplace(TestFunctionObjectOfSet("y"));
    setObject2.emplace(TestFunctionObjectOfSet("x"));
    setObject2.emplace(TestFunctionObjectOfSet("z"));

    // set存智能指针
    set<TestFunctionObjectOfSetPtr> setObjectPtr;
    setObjectPtr.emplace(std::make_shared<TestFunctionObjectOfSet>("b"));
    setObjectPtr.emplace(std::make_shared<TestFunctionObjectOfSet>("a"));
    setObjectPtr.emplace(std::make_shared<TestFunctionObjectOfSet>("c"));

    set<TestFunctionObjectOfSetPtr, TestFunctionObjectOfSetPtrCompare> setObjectPtr2;
    setObjectPtr2.emplace(std::make_shared<TestFunctionObjectOfSet>("y"));
    setObjectPtr2.emplace(std::make_shared<TestFunctionObjectOfSet>("x"));
    setObjectPtr2.emplace(std::make_shared<TestFunctionObjectOfSet>("z"));
}

TEST(std_set, key_compare_ptr)
{
    set<TestFunctionObjectOfSetPtr> setObjectPtr;
    setObjectPtr.emplace(std::make_shared<TestFunctionObjectOfSet>("b"));
    setObjectPtr.emplace(std::make_shared<TestFunctionObjectOfSet>("a"));
    setObjectPtr.emplace(std::make_shared<TestFunctionObjectOfSet>("c"));

    // 修改元素
    for (auto& item : setObjectPtr)
    {
        if (item->name() == "c")
            const_cast<TestFunctionObjectOfSet&>(*item).name(std::string("d"));
    }

    // 新增元素
    bool bInsert = setObjectPtr.emplace(std::make_shared<TestFunctionObjectOfSet>("a")).second; // 相同元素
    assert(bInsert == false);
    setObjectPtr.emplace(std::make_shared<TestFunctionObjectOfSet>("p"));
    setObjectPtr.emplace(std::make_shared<TestFunctionObjectOfSet>("o"));
    setObjectPtr.emplace(std::make_shared<TestFunctionObjectOfSet>("i"));
    setObjectPtr.emplace(std::make_shared<TestFunctionObjectOfSet>("u"));

    // 查找元素
    auto temp    = std::make_shared<TestFunctionObjectOfSet>("a");
    auto theFind = setObjectPtr.find(temp);
    assert(theFind != setObjectPtr.end());

    int* pElement = reinterpret_cast<int*>(&**theFind);
    int* pTemp    = reinterpret_cast<int*>(&*temp);
    assert(*pElement != *pTemp); // find返回的是容器内元素的地址，不是参数地址

    // 最后，删除元素
    std::cout << std::endl;
    auto iter = setObjectPtr.begin();
    for (; iter != setObjectPtr.end();)
    {
        iter = setObjectPtr.erase(iter);
    }
}

TEST(std_unordered_set, key_compare)
{
    // unordered_set<TestFunctionObjectOfUnorderedSet> setObject;
    // setObject.emplace(TestFunctionObjectOfUnorderedSet("b", "2"));
    // setObject.emplace(TestFunctionObjectOfUnorderedSet("a", "1"));
    // setObject.emplace(TestFunctionObjectOfUnorderedSet("c", "3"));

    unordered_set<TestFunctionObjectOfUnorderedSet, TestFunctionObjectOfUnorderedSetCompare> setObject2;
    setObject2.emplace(TestFunctionObjectOfUnorderedSet("b", "2"));
    setObject2.emplace(TestFunctionObjectOfUnorderedSet("a", "1"));
    setObject2.emplace(TestFunctionObjectOfUnorderedSet("c", "3"));

    unordered_set<TestFunctionObjectOfUnorderedSetPtr, TestFunctionObjectOfUnorderedSetPtrCompare> setObjectPtr;
    setObjectPtr.emplace(std::make_shared<TestFunctionObjectOfUnorderedSet>("b", "2"));
    setObjectPtr.emplace(std::make_shared<TestFunctionObjectOfUnorderedSet>("a", "1"));
    setObjectPtr.emplace(std::make_shared<TestFunctionObjectOfUnorderedSet>("c", "3"));
}

enum GeometryTag
{
    ePoint = 0,
    eSegment,
    eLineString,
    eArc,
    eCircle,
    eGeometryCount
};

TEST(std_bitset, normal)
{
    // 数组实现
    std::bitset<eGeometryCount + 1> bits;

    bits[ePoint] = true;

    auto str  = bits.to_string();
    auto size = bits.count();

    auto count = bits.count();
    bool is    = bits.any();

    bits[ePoint] = false;
    assert(bits[ePoint] == false);

    std::cout << bits << std::endl;
}

TEST(std_bitset, cppreference)
{
    typedef std::size_t length_t, position_t; // the hints

    // constructors:
    constexpr std::bitset<4> b1;
    constexpr std::bitset<4> b2{0xA};                                         // == 0B1010
    std::bitset<4>           b3{"0011"};                                      // can also be constexpr since C++23
    std::bitset<8>           b4{"ABBA", length_t(4), /*0:*/ 'A', /*1:*/ 'B'}; // == 0B0000'0110

    // bitsets can be printed out to a stream:
    std::cout << "b1:" << b1 << "; b2:" << b2 << "; b3:" << b3 << "; b4:" << b4 << '\n';

    // bitset supports bitwise operations:
    b3 |= 0b0100;
    assert(b3 == 0b0111);
    b3 &= 0b0011;
    assert(b3 == 0b0011);
    b3 ^= std::bitset<4>{0b1100};
    assert(b3 == 0b1111);

    // operations on the whole set:
    b3.reset();
    assert(b3 == 0);
    b3.set();
    assert(b3 == 0b1111);
    assert(b3.all() && b3.any() && !b3.none());
    b3.flip();
    assert(b3 == 0);

    // operations on individual bits:
    b3.set(position_t(1), true);
    assert(b3 == 0b0010);
    b3.set(position_t(1), false);
    assert(b3 == 0);
    b3.flip(position_t(2));
    assert(b3 == 0b0100);
    b3.reset(position_t(2));
    assert(b3 == 0);

    // subscript operator[] is supported:
    b3[2] = true;
    assert(true == b3[2]);

    // other operations:
    assert(b3.count() == 1);
    assert(b3.size() == 4);
    assert(b3.to_ullong() == 0b0100ULL);
    assert(b3.to_string() == "0100");
}

TEST(std_hash, string_int)
{
    size_t str = std::hash<std::string>()("");
    assert(str == 14695981039346656037);

    size_t str_a = std::hash<std::string>()("a");
    assert(str_a == 12638187200555641996);

    size_t str_b = std::hash<std::string>()("b");
    assert(str_b == 12638190499090526629);

    size_t str_0 = std::hash<std::string>()("0");
    assert(str_0 == 12638135523509116079);

    size_t str_1 = std::hash<std::string>()("1");
    assert(str_1 == 12638134423997487868);

    // int
    size_t int0 = std::hash<int>()(0);
    assert(int0 == 5558979605539197941);

    size_t int1 = std::hash<int>()(1);
    assert(int1 == 12478008331234465636);
}
