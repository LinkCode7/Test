#pragma once

// 编译期诊断类型
template<typename T>
class type_displayer;

#define DIAGNOSE_TYPE(type) type_displayer<decltype(type)> xType;

void diagnose_compile_time();

void diagnose_run_time();

void test_auto();

/*
模板函数型别匹配规则：

template<typename T>
void template_function(ParamType param) {}

template_function(express);


1.如果ParamType是指针或引用，但不是万能引用（T&&）
1.1 若express具有引用型别，先将引用部分忽略
1.2 对express的型别和ParamType的型别执行模式匹配，最终决定T的型别

*/

template<typename R, typename T, typename U>
R add_function1(T t, U u)
{
	return t + u;
}

//// 在编译器读到decltype(t+u)时，t和u尚未被定义
//template<typename T, typename U>
//decltype(t+u) add_function2(T t, U u)
//{
//	return t + u;
//}

template<typename T, typename U>
auto add_function(T t, U u) -> decltype(t + u)
{
	return t + u;
}

template<typename T, typename U>
auto add_function_cpp14(T t, U u)
{
	return t + u;
}

class ForwardFunction
{
	std::string m_str;
public:
	std::string lookup1() { return m_str; }
	std::string& lookup2() { return m_str; }

	std::string look_up_a_str1() { return lookup1(); }
	std::string& look_up_a_str2() { return lookup2(); }

	// 简化代码
	decltype(auto) look_up_a_string1()
	{
		return lookup1();
	}
	decltype(auto) look_up_a_string2()
	{
		return lookup2();
	}
};
