#include "pch.h"
#include "std_advance.h"

using namespace std;

template<class InputIterator, class Distance>
void advance_II(InputIterator it, Distance n)
{
	// 单向，逐一前进
	while (n--) ++it;
}

template<class BidIrectionalIterator, class Distance>
void advance_BI(BidIrectionalIterator it, Distance n)
{
	// 双向，逐一前进
	if (n >= 0)
		while (n--) ++it;
	else
		while (n++) --it;
}

template<class RandomAccessIterator, class Distance>
void advance_RAI(RandomAccessIterator it, Distance n)
{
	// 双向，跳跃前进
	it += n;
}

////////////////////////////////////////////////////////////////////
// 选择不同效率的版本？

// 运行期间选择：
template<class InputIterator, class Distance>
void Advance(InputIterator i, Distance n)
{
	//if (isRandomAccessIterator(i)) // 待实现
	//	advance_RAI(it, n);
	//else if(isBidIrectionalIterator(i)) // 待实现
	//	advance_BI(it, n);
	//else
	//	advance_II(it, n);
}

// 更效率的方式：编译期选择（函数重载）
// void advance(InputIterator i, Distance n，ClassType)








void testAdvance()
{
	////vector<int> vec = {1,2,3};
	//int p[] = {1,2,3};
	//auto itr = p;

	//MyAdvance(itr,1);
}