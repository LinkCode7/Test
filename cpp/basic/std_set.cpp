#include "pch.h"
#include "std_set.h"
#include <set>
#include <unordered_set>
#include "assert.h"

using namespace std;

TEST(std_set, insert_result)
{
	set<int> digits;
	auto result = digits.insert(100);
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
	auto temp = std::make_shared<TestFunctionObjectOfSet>("a");
	auto theFind = setObjectPtr.find(temp);
	assert(theFind != setObjectPtr.end());

	int* pElement = reinterpret_cast<int*>(&**theFind);
	int* pTemp = reinterpret_cast<int*>(&*temp);
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
	//unordered_set<TestFunctionObjectOfUnorderedSet> setObject;
	//setObject.emplace(TestFunctionObjectOfUnorderedSet("b", "2"));
	//setObject.emplace(TestFunctionObjectOfUnorderedSet("a", "1"));
	//setObject.emplace(TestFunctionObjectOfUnorderedSet("c", "3"));

	unordered_set<TestFunctionObjectOfUnorderedSet, TestFunctionObjectOfUnorderedSetCompare> setObject2;
	setObject2.emplace(TestFunctionObjectOfUnorderedSet("b", "2"));
	setObject2.emplace(TestFunctionObjectOfUnorderedSet("a", "1"));
	setObject2.emplace(TestFunctionObjectOfUnorderedSet("c", "3"));

	unordered_set<TestFunctionObjectOfUnorderedSetPtr, TestFunctionObjectOfUnorderedSetPtrCompare> setObjectPtr;
	setObjectPtr.emplace(std::make_shared<TestFunctionObjectOfUnorderedSet>("b", "2"));
	setObjectPtr.emplace(std::make_shared<TestFunctionObjectOfUnorderedSet>("a", "1"));
	setObjectPtr.emplace(std::make_shared<TestFunctionObjectOfUnorderedSet>("c", "3"));
}