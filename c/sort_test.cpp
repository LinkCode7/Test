#include "pch.h"
#include "sort_test.h"
#include <set>
#include <algorithm>

using namespace std;

constexpr auto BUBBLE_MAX = 10;
constexpr auto QUICK_MAX = 10000000;

TEST(sort, bubble_sort)
{
	return;
	int array[BUBBLE_MAX];
	for (int j = 0; j < BUBBLE_MAX; ++j)
	{
		array[j] = rand() % BUBBLE_MAX;
	}
	bubble_sort(array, BUBBLE_MAX);

	int array2[] = { 3,2,1,4,3 };
	bubble_sort(array2, 5);

	// C++版
	std::vector<int> arr = { 5,4,3,2,1 };
	bubble_sort_cpp(arr);
}

TEST(sort, insertion_sort)
{
	std::vector<int> arr = { 5,4,3,2,1 };
	insertion_sort_cpp(arr);
}

TEST(sort, quick_sort)
{
	return;
	int* array = (int*)malloc(sizeof(int) * QUICK_MAX);
	for (int j = 0; j < QUICK_MAX; ++j)
	{
		array[j] = rand() % QUICK_MAX;
	}
	quick_sort(array, 0, QUICK_MAX - 1);

	free(array);
}

TEST(sort, std_sort)
{
	set<std::string> set{ "DN15", "DN10", "DN100", "DN110", "DN150" };

	vector<std::string> vec = { "B", "BYJ", "BY", "WD", "WDZ" };

	// 从大到小greater，BYJ会排在BY前面
	std::sort(vec.begin(), vec.end(), std::greater<std::string>());

	std::map<std::string, std::string, std::greater<std::string>> mapValue = { {"a","1"},{"b","2"} };
}
