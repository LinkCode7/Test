#include "pch.h"
#include "virtual_function.h"

#pragma warning(disable:4312)


using namespace std;
class AClass
{
	char a_val;
public:

	virtual void show(){ cout << "class AClass:show()" << endl; }
	virtual void say() { cout << "class AClass:say()" << endl; }

	inline void setA_Val(char val) { a_val = val; }
	inline char getA_Val()const { return a_val; }
};
class BClass : public AClass
{
	int b_val;
public:

	void say() { cout << "class BClass: say()" << endl; }

	virtual void PrintHello() { cout << "class BClass:hello" << endl; }
	virtual void print1() { cout << "class BClass: print1" << endl; }

	inline void setB_Val(int val) { b_val = val; }
	inline int getB_Val()const { return b_val; }
};

void virtualFunction()
{
	BClass b;
	b.setB_Val(123);
	b.setA_Val(_T('A'));

	int *vfptr = new int;
	int *pf = new int;
	memcpy(vfptr, &b, 4);// BClass类型的指针赋给vfptr
	memcpy(pf, reinterpret_cast<int *>(*vfptr) + 2, 4);// 取BClass中的第2个函数

	void(*pfun)() = reinterpret_cast<void(*)()>(*pf);// 构造函数指针
	pfun();// "class BClass hello"


	char *pa_val = new char;
	int *pb_val = new int;
	memcpy(pa_val, reinterpret_cast<int *>(&b) + 1, sizeof(char));
	memcpy(pb_val, reinterpret_cast<int *>(&b) + 2, sizeof(int));
	cout << *pa_val << endl;// AClass
	cout << *pb_val << endl;// 123
	cout << "<<<<<<<<<<<<<<" << endl;


	*pa_val = _T('B');
	*pb_val = 999;
	memcpy(reinterpret_cast<int *>(&b) + 1, pa_val, sizeof(char));
	memcpy(reinterpret_cast<int *>(&b) + 2, pb_val, 4);
	cout << b.getA_Val() << endl;// BClass
	cout << b.getB_Val() << endl;// 999
}