#ifndef SORT_TEST_H
#define SORT_TEST_H

void swap_int(int v[], int i, int j)
{
	int temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

// 快速排序
void quick_sort(int vec[], int leftIndex, int rightIndex)
{
	if (leftIndex >= rightIndex) // 出口
		return;

	int last = 0;
	const int high = rightIndex;
	const int low = leftIndex;
	while (leftIndex < rightIndex)
	{
		if (vec[leftIndex] > vec[rightIndex])
		{
			swap_int(vec, leftIndex, rightIndex);
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

// 冒泡排序
void bubble_sort(int num[], int size)
{
	int flag = 0;
	int i(0), j(0), min(0);
	for ( ; i < size - 1; ++i)
	{
		flag = 0; // 如果有交换flag = 1

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
		if (flag == 0)
		{
			// 已经有序
			break;
		}
	}
}

template <typename T>
void bubble_sort_cpp(std::vector<T>& array)
{
	auto size = array.size();
	for (auto i = 0; i < size - 1; ++i)
	{
		for (auto j = 0; j < size - 1 - i; ++j)
		{
			if (array[j] > array[j + 1])
				std::swap(array[j], array[j + 1]);
		}
	}
}

template <typename T>
void insertion_sort_cpp(std::vector<T>& array)
{
	auto size = array.size();
	for (auto i = 1; i < size; ++i)
	{
		auto value = array[i];
		auto j = i - 1;
		for ( ; j >= 0; --j) // 查找插入位置
		{
			if (array[j] > value)
				array[j + 1] = array[j]; // 移动数据
			else
				break;
		}
		array[j + 1] = value;
	}
}

#endif // !SORT_TEST_H