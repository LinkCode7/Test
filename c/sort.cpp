#include "pch.h"
#include <set>
#include <algorithm>

using namespace std;

void bubble_sort(int num[], int size)
{
	int flag = 0;
	int i, j, min;
	for (i = 0; i < size - 1; ++i)
	{
		flag = 0;//如果有交换flag=1
		///////////////////////////////////////////////////////////////
		// 这段内层for循环代码，暂称为：代码X。
		// 代码X执行一遍即：外层for循环走一次，内层for循环走size - i - 1次
		for (j = 0; j < size - i - 1; ++j)
		{
			// 第一次：1号元素和2号元素比较，更大的交换到右边
			// 第二次：2和3比较，更大的放到右边
			// 第三次：3和4比较，更大的放到右边
			// 。。。"代码X" 第N次进入且执行完毕，
			// 从右往左的N个数已经有序
			if (num[j] > num[j + 1])
			{
				min = num[j + 1];
				num[j + 1] = num[j];
				num[j] = min;
				flag = 1;
			}
		}
		///////////////////////////////////////////////////////////////
		if (flag == 0)
		{
			// 已经有序
			break;
		}
	}
}

void swap(int v[], int i, int j)
{
	int temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
void quick_sort(int vec[], int leftIndex, int rightIndex)
{
	int last = 0;

	const int high = rightIndex;
	const int low = leftIndex;
	if (leftIndex >= rightIndex)// 出口
		return;
	while (leftIndex < rightIndex)
	{
		if (vec[leftIndex] > vec[rightIndex])
		{
			swap(vec, leftIndex, rightIndex);

			last = ~last;

		}
		if (last == 0)
			rightIndex--;
		else
			leftIndex++;
	}
	quick_sort(vec, low, leftIndex - 1);
	quick_sort(vec, leftIndex + 1, high);
}

////////////////////////////////////////////////////////////////////
constexpr auto BUBBLE_MAX = 10;
constexpr auto QUICK_MAX = 10000000;

void testSort()
{
	return;

	// 1
	int array1[BUBBLE_MAX];
	for (int j = 0; j < BUBBLE_MAX; ++j)
	{
		array1[j] = rand() % BUBBLE_MAX;
	}
	bubble_sort(array1, BUBBLE_MAX);

	// 2
	int* array2 = (int*)malloc(sizeof(int) * QUICK_MAX);
	for (int j = 0; j < QUICK_MAX; ++j)
	{
		array2[j] = rand() % QUICK_MAX;
	}
	quick_sort(array2, 0, QUICK_MAX - 1);

	free(array2);
}







void ContainerSort()
{
	set<std::string> set{ "DN15", "DN10", "DN100", "DN110", "DN150" };

	vector<std::string> vec = { "B", "BYJ", "BY", "WD", "WDZ" }; // _T(""),

	//// 从大到小greater，BYJ会排在BY前面
	//std::sort(vec.begin(), vec.end(), std::greater<std::string>());


	std::map<std::string, std::string, std::greater<std::string>> mapValue = { {"a","1"},{"b","2"} };
}