#include "pch.h"
#include "std_advance.h"

using namespace std;

template<class InputIterator, class Distance>
void advance_II(InputIterator it, Distance n)
{
	// ������һǰ��
	while (n--) ++it;
}

template<class BidIrectionalIterator, class Distance>
void advance_BI(BidIrectionalIterator it, Distance n)
{
	// ˫����һǰ��
	if (n >= 0)
		while (n--) ++it;
	else
		while (n++) --it;
}

template<class RandomAccessIterator, class Distance>
void advance_RAI(RandomAccessIterator it, Distance n)
{
	// ˫����Ծǰ��
	it += n;
}

////////////////////////////////////////////////////////////////////
// ѡ��ͬЧ�ʵİ汾��

// �����ڼ�ѡ��
template<class InputIterator, class Distance>
void Advance(InputIterator i, Distance n)
{
	//if (isRandomAccessIterator(i)) // ��ʵ��
	//	advance_RAI(it, n);
	//else if(isBidIrectionalIterator(i)) // ��ʵ��
	//	advance_BI(it, n);
	//else
	//	advance_II(it, n);
}

// ��Ч�ʵķ�ʽ��������ѡ�񣨺������أ�
// void advance(InputIterator i, Distance n��ClassType)








void testAdvance()
{
	////vector<int> vec = {1,2,3};
	//int p[] = {1,2,3};
	//auto itr = p;

	//MyAdvance(itr,1);
}