#pragma once





// 宏控制，拷贝和构造，放在private下是不允许拷贝和构造
#define COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&); \
	TypeName& operator=(const TypeName&)

// 宏控制，操作符new和delete，放在private下是不允许堆上实例化
#define OPERATOR_NEW_DELETE(TypeName) \
	void * operator new (size_t size); \
	void operator delete (void *ptr)


class SimpleObject
{
private:
	COPY_AND_ASSIGN(SimpleObject);
	OPERATOR_NEW_DELETE(SimpleObject);

public:
	SimpleObject() { m_i = 0; }
	~SimpleObject() {}

private:
	int m_i;
};