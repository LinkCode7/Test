#pragma once

void _test_smart_point();

void test_smart_point20200811();
void test_shared_ptr();
void test_my_shared_ptr();
void test_shared_ptr_leak();
void test_shared_ptr_counter_thread_safe();
void test_shared_ptr_counter_thread_safe2();
void test_shared_pointer_init();

void test_smart_point20210808();
void test_shared_ptr_function();




class MyObject
{
public:
	MyObject()
	{
		m_i = 0;
		std::cout << "MyObject()" << std::endl;
	}
	~MyObject()
	{
		std::cout << "~MyObject()" << std::endl;
	}

	void Show()
	{
		std::cout << "Show()" << std::endl;
	}

private:
	int m_i;
};


template<typename T>
class SharedPtr
{
public:
	SharedPtr() :m_p(nullptr), m_pUseCount(nullptr) {}

	SharedPtr& operator=(const SharedPtr& oth)
	{
		if (this == &oth)
			return *this;

		if ((m_p && m_pUseCount) && (--(*this->m_pUseCount) == 0))
		{
			delete m_p;
			delete m_pUseCount;
		}

		m_p = oth.m_p;
		m_pUseCount = &(++(*oth.m_pUseCount));
		return *this;
	}

	T& operator*()
	{
		return *m_p;
	}
	T* operator->()
	{
		return m_p;
	}

	SharedPtr(T* p)
	{
		m_p = p;
		m_pUseCount = new int(1);
	}

	SharedPtr(const SharedPtr& oth)
	{
		m_p = oth.m_p;
		m_pUseCount = &(++(*oth.m_pUseCount));
	}

	~SharedPtr()
	{
		if (m_p && --(*m_pUseCount) == 0)
		{
			delete m_p;
			delete m_pUseCount;
		}
	}

public:

	T* get() { return m_p; }
	int use_count() { return *m_pUseCount; }

private:
	T* m_p;
	int* m_pUseCount;
};









class Egg;
class Hen
{
public:
	Hen() { std::cout << "Hen()" << std::endl; }
	~Hen() { std::cout << "~Hen()" << std::endl; }

	std::shared_ptr<Egg> pointer_;
};

//#define _USE_WEAK_PTR_
#ifdef _USE_WEAK_PTR_
class Egg
{
public:
	Egg() { std::cout << "Egg()" << std::endl; }
	~Egg() { std::cout << "~Egg()" << std::endl; }

	std::weak_ptr<Hen> pointer_;
};
#else
class Egg
{
public:
	Egg() { std::cout << "Egg()" << std::endl; }
	~Egg() { std::cout << "~Egg()" << std::endl; }

	std::shared_ptr<Hen> pointer_;
};
#endif // _USE_WEAK_PTR_











#pragma warning(disable:4996)

void print_pointer(std::shared_ptr<int> p)
{
	std::cout << *(p.get()) << std::endl;
}



template <typename T>
class Ptr
{
	T *_ptr;
	size_t *_reference_count;


	void releaseCount()
	{
		if (_ptr)
		{
			(*_reference_count)--;
			if ((*_reference_count) == 0)
			{
				delete _ptr;
				delete _reference_count;
			}
		}
	}
public:
	//构造函数  
	Ptr(T* p = 0) : _ptr(p), _reference_count(new size_t)
	{
		if (p)
			*_reference_count = 1;
		else
			*_reference_count = 0;
	}
	//拷贝构造函数  
	Ptr(const Ptr& src)
	{
		if (this != &src)
		{
			_ptr = src._ptr;
			_reference_count = src._reference_count;
			(*_reference_count)++;
		}
	}
	//重载赋值操作符  
	Ptr& operator=(const Ptr& src)
	{
		if (_ptr == src._ptr)
			return *this;

		releaseCount();
		_ptr = src._ptr;
		_reference_count = src._reference_count;
		(*_reference_count)++;
		return *this;
	}

	//重载操作符
	T& operator*()
	{
		if (_ptr)
			return *_ptr;

		//throw exception  
	}
	//重载操作符
	T* operator->()
	{
		if (_ptr)
			return _ptr;

		//throw exception  
	}
	//析构函数
	~Ptr()
	{
		if (--(*_reference_count) == 0)
		{
			delete _ptr;
			delete _reference_count;
		}
	}

};

// Test class
class Table
{
	char* _name;
public:
	Table(const char* na)
	{
		if (!na) return;
		_name = new char(static_cast<int>(strlen(na)) + 1);
		strcpy(_name, na);
	}
	Table& operator=(const Table table)
	{
		if (!table._name) return *this;
		_name = new char[strlen(table._name) + 1];
		strcpy(_name, table._name);
	}

	~Table() {}
};


//typedef _com_ptr_t<_com_IIID<IFeatureClass, &__uuidof(IFeatureClass)>> IFeatureClassPtr;
typedef Ptr<Table> TablePtr;












struct Base
{
	Base() { std::cout << "  Base::Base()\n"; }
	// Note: non-virtual destructor is OK here
	~Base() { std::cout << "  Base::~Base()\n"; }
};

struct Derived : public Base
{
	Derived() { std::cout << "  Derived::Derived()\n"; }
	~Derived() { std::cout << "  Derived::~Derived()\n"; }
};