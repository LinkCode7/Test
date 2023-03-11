#include "pch.h"
#include "LFUCache.h"

#include <algorithm>



using namespace std;




//////////////////////////////////////////////////////////////////////////

void LFUCacheEntry()
{
	WrongAnswer();
	return;

	LFUCache lfu(3);

	lfu.set(2, 2);
	lfu.set(1, 1);

	cout << lfu.get(2) << endl;

	cout << lfu.get(1) << endl;

	cout << lfu.get(2) << endl;

	lfu.set(3, 3);
	bool isOk = is_heap(lfu.m_vec.begin(), lfu.m_vec.end(), std::greater<>());
	lfu.set(4, 4);

	cout << lfu.get(3) << endl;

	cout << lfu.get(2) << endl;

	cout << lfu.get(1) << endl;

	cout << lfu.get(4) << endl;
}

// 调用set且需要从容器中取出一个元素时，此时若存在相同元素，会取出先push_back的
void WrongAnswer()
{
	return;

	LFUCache lfu(3);
	lfu.set(1, 10);
	lfu.set(2, 20);
	lfu.set(3, 30);

	cout << lfu.get(1) << endl << endl;

	lfu.set(4, 40);

	cout << lfu.get(4) << endl;
	cout << lfu.get(3) << endl;
	cout << lfu.get(2) << endl;
	cout << lfu.get(1) << endl << endl;

	bool isOk = is_heap(lfu.m_vec.begin(), lfu.m_vec.end(), std::greater<>());
	lfu.set(5, 50);

	cout << lfu.get(1) << endl;
	cout << lfu.get(2) << endl;
	cout << lfu.get(3) << endl;
	cout << lfu.get(4) << endl;
	cout << lfu.get(5) << endl;
}


//报错：expression:invalid heap
//
//主要原因是：sort_heap执行以后原有数据已经再是是heap了。而push_heap和pop_heap使用之前必须保证原有数据仍是heap。
//本人想到的比较笨的方法在执行sort_heap以后如果还要使用push_heap或pop_heap更改数据时，首先执行make_heap, 是原有数据重新生成为heap。

void Exception()
{
	vector<int> vecTest = { 0,1,2,3,4,8,9,3,5 };
	make_heap(vecTest.begin(), vecTest.end());

	vecTest.push_back(7);
	push_heap(vecTest.begin(), vecTest.end());

	pop_heap(vecTest.begin(), vecTest.end());
	vecTest.pop_back(); //

	sort_heap(vecTest.begin(), vecTest.end()); // Exception
}






class File
{
public:
	virtual void open() {};
	virtual void close() {};

	File() {
		std::cout << "File Constructor" << std::endl;
		open(); // 此时子类未构造出来
	}

	~File() {
		std::cout << "File Destructor" << std::endl;
		close(); // 此时子类已析构
	}
};

class SubFile : File
{
	void open() override { std::cout << " SubFile open" << std::endl; };
	void close() override { std::cout << " SubFile close" << std::endl; };
};