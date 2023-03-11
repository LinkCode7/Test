#pragma once
#include <iostream>

#pragma warning(disable:4312)


namespace test_vtable
{

#define SHOW_FUNC_ADDRESS(function) _asm{\
mov eax, function}\
_axm{mov p,eax}\
std::cout << "Address of "#function":" << p << std::endl;





	void ShowVtableContent(const char* className, void* pObj, int index)
	{
		unsigned long* pAddr = nullptr;
		pAddr = reinterpret_cast<unsigned long*>(pAddr);
		pAddr = (unsigned long*)*pAddr; // 获取虚函数表指针

		std::cout << className << "' vtable[" << index << "]";
		std::cout << ":0x" << (void*)pAddr[index] << std::endl;
	}





	class Base
	{
		int m_i;
	public:

		virtual void f1()
		{
			std::cout << "Base f1()" << std::endl;
		}

		virtual void f2()
		{
			std::cout << "Base f2()" << std::endl;
		}

		virtual void f3()
		{
			std::cout << "Base f2()" << std::endl;
		}
	};



	class Derived :public Base
	{
		int m_ii;
	public:

		virtual void f4()
		{
			std::cout << "Derived f4()" << std::endl;
		}

		void f1()
		{
			std::cout << "Derived f1()" << std::endl;
		}

		void f3()
		{
			std::cout << "Derived f3()" << std::endl;
		}
	};

} // namespace test_vtable
