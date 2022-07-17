#pragma once





// 捕获列表提供了 Lambda 表达式对外部值进行使用的功能
void lambda_value_capture(); // 默认
void lambda_reference_capture();

/*
3. 隐式捕获
手动书写捕获列表有时候是非常复杂的，这种机械性的工作可以交给编译器来处理，这时候可以在
捕获列表中写一个 & 或 = 向编译器声明采用引用捕获或者值捕获.
总结一下，捕获列表的最常用的四种形式可以是：
• [] 空捕获列表
• [name1, name2, ... ] 捕获一系列变量
• [&] 引用捕获, 让编译器自行推导引用列表
• [=] 值捕获, 让编译器自行推导值捕获列表

注意：捕获只能针对于创建lambda表达式的作用域内可见的非静态局部变量（包括形参）
*/


// 捕获右值引用
void lambda_rvalue_capture();

// 泛型lambda
void generic_lambda();



/*
以前的...

[capture](parameters) mutable ->return-type{statement}
1.[capture]：捕捉列表。捕捉列表总是出现在Lambda函数的开始处。实际上，[]是Lambda引出符。编译器根据该引出符判断接下来的代码是否是Lambda函数。捕捉列表能够捕捉上下文中的变量以供Lambda函数使用;

2.(parameters)：参数列表。与普通函数的参数列表一致。如果不需要参数传递，则可以连同括号“()”一起省略;

3.mutable：mutable修饰符。默认情况下，Lambda函数总是一个const函数，mutable可以取消其常量性。在使用该修饰符时，参数列表不可省略（即使参数为空）;

4.->return-type：返回类型。用追踪返回类型形式声明函数的返回类型。我们可以在不需要返回值的时候也可以连同符号”->”一起省略。此外，在返回类型明确的情况下，也可以省略该部分，让编译器对返回类型进行推导;

5.{statement}：函数体。内容与普通函数一样，不过除了可以使用参数之外，还可以使用所有捕获的变量。

与普通函数最大的区别是，除了可以使用参数以外，Lambda函数还可以通过捕获列表访问一些上下文中的数据。具体地，捕捉列表描述了上下文中哪些数据可以被Lambda使用，以及使用方式（以值传递的方式或引用传递的方式）。语法上，在“[]”包括起来的是捕捉列表，捕捉列表由多个捕捉项组成，并以逗号分隔。捕捉列表有以下几种形式：

1.[var]表示值传递方式捕捉变量var；
2.[=]表示值传递方式捕捉所有父作用域的变量（包括this）；
3.[&var]表示引用传递捕捉变量var；
4.[&]表示引用传递方式捕捉所有父作用域的变量（包括this）；
5.[this]表示值传递方式捕捉当前的this指针。

上面提到了一个父作用域，也就是包含Lambda函数的语句块，说通俗点就是包含Lambda的“{}”代码块。上面的捕捉列表还可以进行组合，例如：

1.[=,&a,&b]表示以引用传递的方式捕捉变量a和b，以值传递方式捕捉其它所有变量;
2.[&,a,this]表示以值传递的方式捕捉变量a和this，引用传递方式捕捉其它所有变量。

不过值得注意的是，捕捉列表不允许变量重复传递。下面一些例子就是典型的重复，会导致编译时期的错误。例如：

3.[=,a]这里已经以值传递方式捕捉了所有变量，但是重复捕捉a了，会报错的;
4.[&,&this]这里&已经以引用传递方式捕捉了所有变量，再捕捉this也是一种重复
*/









using FilterContainer = std::vector<std::function<bool(int)>>;

void _dangling_pointer(FilterContainer& filter);
void dangling_pointer_if_reference_capture();



class MemberCapture
{
	int divisor_;
public:
	MemberCapture() : divisor_(1) {}

	void addDivisorFilter(FilterContainer& filter) const
	{
		filter.emplace_back([=](int value) { return value > divisor_; });

		//  error C3480: lambda 捕获变量必须来自封闭函数范围
		//filter.emplace_back([divisor_](int value) { return value > divisor_; });
		/*
		以上语句等同于：
		auto currentObjectPtr = this;
		filter.emplace_back([currentObjectPtr](int value) { return value > currentObjectPtr->divisor_; });
		*/
	}

	void addDivisorFilter2(FilterContainer& filter) const
	{
		auto divisor_copy = divisor_;
		filter.emplace_back([divisor_copy](int value) { return value > divisor_copy; });
	}

	// 广义lambda捕获(C++14)
	void addDivisorFilter3(FilterContainer& filter) const
	{
		filter.emplace_back([divisor_copy = divisor_](int value) { return value > divisor_copy; });
	}
};

// 捕获成员变量
void lambda_member_variable_capture();








// 编译器在编译lambda时动态生成一个struct，将捕获的变量放到struct中
struct SomeCompilerGeneratedClassName
{
public:
	template<typename T>
	auto operator()(T x) const
	{
		return x;
	}

public:
	bool operator()(int left, int right)
	{
		return left < right;
	}
};

void test_lambda_function_object();


void test_lambda_normal();
