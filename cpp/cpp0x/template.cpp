#include "pch.h"
#include "template.h"



void fold_expression();
void not_type_param();
void print_enum();

int get_value() { return 10; }


void test_template()
{
	// 变长参数模板
	magic_function(1);
	magic_function(1, 3.14);
	magic_function(1, 3.14, "");

	//std::array<int, 3> arr2 = {1,2,3};
	auto arr = make_array(1, 2, 3);
	std::cout << arr.size() << '\n';


	std::cout << std::endl << "--------------my_printf--------------" << std::endl;
	printf1(1, 2, "hello", 3.14);
	printf2(1, get_value(), "hello", 3.14);
	printf3(1, get_value(), "hello", 3.14);

	fold_expression();
	not_type_param();
	print_enum();
}


template<typename ... T>
constexpr auto sum(T... t)
{
	return (t + ...);
}

// 折叠表达式
void fold_expression()
{
	std::cout << sum(1, 2, 3, 4, 5) << std::endl;
}

#pragma warning(disable:4101)
void not_type_param()
{
	buffer_t<int, 100> buff; // 100 作为模板参数
}


enum class MyClass : unsigned int
{
	kValue1,
	kValue2,
	kValue3 = 100,
	kValue4 = 100,
};

//template<typename T>
//std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
//{
//	return stream << static_cast<typename std::underlying_type<T>::type>(e);
//}

void print_enum()
{
	std::cout << int(MyClass::kValue3) << std::endl;
}