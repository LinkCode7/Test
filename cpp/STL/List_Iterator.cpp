#include "pch.h"
#include "List_Iterator.h"


using namespace std;

template<class T>
struct MyIterator
{
	typedef T value_type;
	T* m_ptr;

	MyIterator(T* p) :m_ptr(p) {}
	~MyIterator() { delete m_ptr; } //

	T& operator*() const { return *m_ptr; }
};

template<class I>
typename I::value_type func(const I& ite)
{
	return *ite;
}

/////////////////////////////////////////

template<class I>
struct iterator_trait
{
	// ���I������value_type����ô���ﶨ���value_type����I::value_type
	// ԭ��ָ��������Ҫƫ�ػ�
	typedef typename I::value_type value_type;

	/*I* m_ptr;
	iterator_trait(I* p) :m_ptr(p) {}
	I& operator*() const { return *m_ptr; }*/
};

template<class T>
struct iterator_trait<T*> // ƫ�ػ�����������ԭ��ָ��(��ΪT*): int -> int*
{
	typedef T value_type;
};

template<class I>
typename iterator_trait<I>::value_type _function(const I& ite)
{
	return *ite;
}

template<class T>
auto f(const T& it)
{
	return *it;
}







/////////////////////////////////////////////////////////////////


void List_Iterator()
{
	TestListIterator::test();

	MyIterator<int> ite(new int(6));
	cout << *ite << endl;
	cout << func(ite) << endl;

	int* p = new int(7);
	cout << *p << endl;
	//cout << func(p) << endl; // compile error: value_type
	cout << _function(p) << endl; // ԭ��ָ��

	cout << _function(ite) << endl;

	
	cout << f(p) << endl;
	cout << f(ite) << endl;

}







namespace TestListIterator
{
	void test()
	{
		List<int> mylist;

		for (int i = 0; i < 5; ++i)
		{
			mylist.insert_front(i);
			mylist.insert_end(i + 2);
		}

		mylist.display();

		ListIter<ListItem<int>> begin(mylist.front());
		ListIter<ListItem<int>> end(nullptr);
		//ListIter<ListItem<int>> theFindIter = std::find(begin, end, 3);

		//if (theFindIter == end)
		//{
		//	cout << "not found" << endl;
		//}
		//else
		//{
		//	//cout << "found:" << (*theFindIter)->value << endl;
		//}
	}
}