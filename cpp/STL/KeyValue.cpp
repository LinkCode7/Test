#include "pch.h"





using namespace std;


void TestPairCompare()
{
	pair<int, int> p1 = make_pair(1, 1);
	pair<int, int> p2 = make_pair(1, 2);

	if (p1 == p2)
	{
		cout << "std::pairֻ�Ƚ�First" << endl;
	}
	else
	{
		cout << "std::pair�Ƚ�First��Second" << endl; //
	}
}






//std::find��������������Ԫ���㷨��������ֻ�ܲ�������Ԫ��Ϊ�����������ͣ�
//�����Ҫ���������ͣ�Ӧ��ʹ��find_if.STL�㷨��һ���汾����ȱʡ��������Ϊ�����㷨����һ���汾�ṩ���������������紫���һ���º�����functor�����Ա�����������ԡ�
//���Բ����������Ե��㷨ͨ������_if��Ϊβ�ʣ�����find_if(), replace_if().
//
//������Ƶģ��ʱ��㷨���ı����������Ԫ�ص�ֵ����Ϊin - place���͵ؼ��㣩��copy�����������ݿ���һ�ݸ������ڸ�����������Ϻ󷵻أ��棬
//copy��������_copy��Ϊ��������β�ʡ�