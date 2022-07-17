#include "pch.h"





using namespace std;

void iteratorInvalid()
{
	// 1.vector
	vector<int>::iterator iter1;
	vector<int> vec = {1,2,3,4,5,6,7};
	
	for (iter1 = vec.begin(); iter1 != vec.end(); iter1++)
	{
		if (*iter1 == 2)
		{
			// erase()会返回迭代器下一个位置，正确写法：
			iter1 = vec.erase(iter1);

			//错误写法：vec.erase(iter); // 此时迭代器iter指向的值已被删除
			cout << *iter1 << endl;// vec.erase(iter); 将导致崩溃
		}
	}

	// 2.map
	map<int, string>::iterator iter2;
	map<int, string> ma = { {1,"a"},{2,"b"},{3,"c"},{4,"d"} };

	for (iter2 = ma.begin(); iter2 != ma.end(); iter2++)
	{
		if (iter2->first == 2)
		{
			// erase()会返回迭代器下一个位置，正确写法两种：
			iter2 = ma.erase(iter2);
			//ma.erase(iter2++);

			//错误写法：ma.erase(iter2); // 此时迭代器iter指向的值已被删除
			cout << iter2->first << endl;// ma.erase(iter2); 将导致崩溃
		}
	}

}

/////////////////////////////////////////////////////////////////

void testIterator()
{
	iteratorInvalid();

}