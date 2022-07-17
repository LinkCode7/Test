#include "pch.h"
#include "lambda_experssion.h"






void test_lambda_experssion()
{
	test_lambda_function_object();
	test_lambda_normal();

	// 值捕获
	lambda_value_capture();
	// 引用捕获
	lambda_reference_capture();

	// 捕获右值
	lambda_rvalue_capture();
	// 泛型lambda
	generic_lambda();


	// 引用捕获可能导致空悬指针（野指针）
	dangling_pointer_if_reference_capture();

	// 捕获成员变量
	lambda_member_variable_capture();
}


// 1. 值捕获 与参数传值类似，值捕获的前提是变量可以拷贝，不同之处则在于，被捕获的变量在 Lambda
// 表达式被创建时拷贝，而非调用时才拷贝：
void lambda_value_capture()
{
	int value = 1;
	auto copy_value = [value] { return value; }; // 创建时刻
	value = 100;

	auto stored_value = copy_value();
	std::cout << "stored_value = " << stored_value << std::endl;
	// 这时, stored_value == 1, 而 value == 100.
	// 因为 copy_value 在创建时就保存了一份 value 的拷贝
}

// 2. 引用捕获 与引用传参类似，引用捕获保存的是引用，值会发生变化。
void lambda_reference_capture()
{
	int value = 1;
	auto copy_value = [&value] { return value; };
	value = 100;

	auto stored_value = copy_value();
	std::cout << "stored_value = " << stored_value << std::endl;
	// 这时, stored_value == 100, value == 100.
	// 因为 copy_value 保存的是引用
}

// 捕获右值引用
void lambda_rvalue_capture()
{
	// 这里的unique_ptr<int>是独占指针，不能被捕获到
	auto important = std::make_unique<int>(1);
	auto add = [v1 = 1, v2 = std::move(important)](int x, int y) -> int {
		return x + y + v1 + (*v2);
	};
	std::cout << add(3, 4) << std::endl;
}

// 泛型lambda
void generic_lambda()
{
	auto add = [](auto x, auto y) { return x + y; };

	std::cout << add(1, 1) << std::endl;
	std::cout << add(1, 3.14) << std::endl;
}

int get_value_10_if() { return 10; }
void _dangling_pointer(FilterContainer& filter)
{
	// 经过计算后得到的值
	int calculate_value = get_value_10_if();
	filter.emplace_back([&calculate_value](int value) { return value > calculate_value; });
}

bool greater_than_10(int value)
{
	return value > 10;
}

void dangling_pointer_if_reference_capture()
{
	FilterContainer filter;
	_dangling_pointer(filter);
	filter.emplace_back(greater_than_10);

	int parameter = 0;

	bool result = false;
	std::cout << std::endl;
	for (const auto& fun : filter)
	{
		// fun(parameter);
		std::cout << parameter << " > 10 is " << fun(parameter) << std::endl;
	}
}

void lambda_member_variable_capture()
{
	FilterContainer filter;

	MemberCapture object;
	object.addDivisorFilter(filter);
	object.addDivisorFilter2(filter);
}

void test_lambda_function_object()
{
	auto fun = [](auto x) { return x; };
	fun(1);

	SomeCompilerGeneratedClassName object;
	object(1);
}

void test_lambda_normal()
{
	std::vector<int> arr = {1,5,9,3,2,6,7};
	for(const auto& value : arr)
		std::cout << value << ",";

	// 经典使用场景（使用STL算法）
	std::sort(arr.begin(), arr.end(), [](int left, int right) { return left < right; });
	//std::sort(arr.begin(), arr.end(), SomeCompilerGeneratedClassName());


	std::cout << std::endl;
	std::for_each(arr.begin(), arr.end(), [](auto value) { std::cout << value << ","; });
}
