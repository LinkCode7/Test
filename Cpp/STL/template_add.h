#pragma once
template<bool T, class T1, class T2>
class BoolTrait;

template<typename T1, typename T2>
class BoolTrait<true, T1, T2>
{
public:
	typedef T1 ResultT;
};

template<typename T1, typename T2>
class BoolTrait<false, T1, T2>
{
public:
	typedef T2 ResultT;
};

////////////////////////////////////////////////////////////

template<typename bigSize, typename smallSize>
class ReturnValue
{
public:
	// 通过字节长度判断精度
	typedef typename BoolTrait<(sizeof(bigSize) > sizeof(smallSize)), bigSize, smallSize>::ResultT ResultT;
};

//因为int和float类型所占的字节相同，所以无法通过比较大小来判断类型的精度，需要偏特化  
template<>
class ReturnValue<float, int>
{
public:
	typedef float ResultT;
};
template<>
class ReturnValue<int, float>
{
public:
	typedef float ResultT;
};

// Add
template<typename t1, typename t2>
typename ReturnValue<t1, t2>::ResultT Add(T1 lhs, T2 rhs)
{
	return lhs + rhs;
}