#pragma once




class ILineData
{
	ILineData() {} // 禁止实例，不占空间

	void LineFunction()
	{
		//std::cout << this->m_i << std::endl;
	}
};


class LineData:public ILineData
{
public:
	int m_i;
};




struct A
{
	virtual void exec() = 0;
};

struct B : public A
{
	int i_ = 1;
	virtual void exec()
	{
		return;
	}
};



class parent
{
public:
	virtual void output() { std::cout << "parent::output" << std::endl; }
};

class son: public parent
{
public:
	virtual void output() { std::cout << "parent::son" << std::endl; }
};