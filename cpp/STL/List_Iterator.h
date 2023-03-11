#pragma once

template<typename T>
class Node
{
	T _value;
	Node* _next;

public:
	Node* next() const
	{
		return _next;
	}

	T value() const
	{
		return _value;
	}
};

template<class T>
class MyList
{
	Node<T>* _end;
	Node<T>* _frond;

};











namespace TestListIterator
{
	template <class InputIterator, class T>
	InputIterator findd(InputIterator first, InputIterator last, const T& value)
	{
		while (first != last && *first != value)
			++first;

		return first;
	}


	template <class Item>
	struct ListIter;

	template <typename T>
	class ListItem
	{
	public:
		T value() const { return _value; }
		ListItem* next() const { return _next; }

	private:
		T _value;
		ListItem* _next;
	};


	template <typename T>
	class List: public std::iterator_traits<T>
	{
	public:
		void insert_front(T value)
		{

		}
		void insert_end(T value)
		{

		}

		ListIter<ListItem<T>> front()
		{
			return ListIter<ListItem<T>>(_frond);
		}

		//ListIter<ListItem<T>> front()
		//{
		//	//return ListIter(_frond);
		//}

		void display(std::ostream& os = std::cout) const
		{

		}

	private:
		ListItem<T>* _frond;
		ListItem<T>* _end;
		long _size;
	};




	// ¼òµ¥µÄµü´úÆ÷
	template <class Item>
	struct ListIter
	{
		Item* ptr;

		ListIter(Item* p = 0) :ptr(p) {}

		Item& operator*() const { return *ptr; }
		Item* operator->() const { return ptr; }

		// pre-increment
		ListIter& operator++() { ptr = ptr->next(); return *this; }
		// post-increment
		ListIter operator++(int) { ListIter temp = *this; ++*this; return temp; }

		bool operator==(const ListIter& oth) const { return ptr == oth.ptr; }
		bool operator!=(const ListIter& oth) const { return ptr != oth.ptr; }
	};



	void test();

} // namespace ListIterator