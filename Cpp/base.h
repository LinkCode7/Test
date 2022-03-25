#pragma once


class Fun
{
	int m_count;

public:
	Fun(int count=0) :m_count(count)
	{
	}
	// Function object
	int operator()(int number)
	{
		std::cout << "operator() parameter: " << number << std::endl;
		return number;
	}
};




template<typename Fun>
class C
{
public:
	Fun * f;

	C(Fun* a) :f(a) {}

	operator Fun*()
	{
		return f;
	}
};



//template<class T1, class T2>
//class ATL_NO_VTABLE IEnumImpl : public T1
//{
//	//typedef _com_ptr_t<_com_IIID<T2, &__uuidof(T2)>> T_Ptr;
//public:
//	std::list< T2 >								m_list;
//	typename std::list< T2 >::iterator			m_it;
//	bool										m_bEnded;
//
//public:
//	STDMETHOD(Next)(T2 * item)
//	{
//		if (!item)
//			return E_POINTER;
//
//		HRESULT hr = S_FALSE;
//
//		if (!m_bEnded)
//		{
//			*item = nullptr;
//			if (m_list.end() != m_it)
//			{
//				*item = *m_it;
//				m_it++;
//
//				if (*item)
//				{
//					(*item)->AddRef();
//					hr = S_OK;
//				}
//			}
//			else {
//				m_bEnded = true;
//				hr = S_FALSE;
//			}
//		}
//		return hr;
//	}
//	STDMETHOD(Reset)()
//	{
//		m_it = m_list.begin();
//		m_bEnded = false;
//
//		return S_OK;
//	}
//
//	virtual HRESULT Add(T2 item)
//	{
//		HRESULT hr = S_OK;
//
//		if (item)
//		{
//			m_list.push_back(item);
//			item->AddRef();
//
//			if (m_list.end() == m_it)
//				m_it = m_list.begin();
//		}
//		else
//			hr = E_INVALIDARG;
//
//		return hr;
//	}
//};



template<typename Subtype>
class Geometry
{
	int m_i;
public:

	Geometry() :m_i(0) {};

	Subtype Cast()
	{
		return static_cast<Subtype*>(this);
	}
};

class Line :public Geometry<Line>
{
	int m_ii;
public:
	
	Line() :m_ii(0) {};
};