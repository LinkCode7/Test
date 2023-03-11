#include "pch.h"
#include "type_index.h"

//#include <boost/type_index.hpp>
#include <stdio.h>



void test_type_index()
{
	test_auto();

	diagnose_compile_time();

	diagnose_run_time();
}



void diagnose_compile_time()
{
	//#define TEST_TYPE_COMPILE_TIME

#ifdef TEST_TYPE_COMPILE_TIME
	auto value = 1;
	DIAGNOSE_TYPE(value);
#endif // TEST_TYPE_COMPILE_TIME
}




class Widget {};

template<typename T>
void func(const T& param)
{
	// 两者的类型不应该相同
	std::cout << std::endl << "typeid" << std::endl;
	std::cout << "T = " << typeid(T).name() << std::endl;
	std::cout << "param = " << typeid(param).name() << std::endl;


	std::cout << std::endl << "boost::typeindex::type_id" << std::endl;
	std::cout << "T = " << boost::typeindex::type_id<T>().pretty_name() << std::endl;
	std::cout << "param = " << boost::typeindex::type_id<decltype(param)>().pretty_name() << std::endl;

	// 准确的型别信息
	using boost::typeindex::type_id_with_cvr;
	std::cout << std::endl << "boost::typeindex::type_id_with_cvr" << std::endl;
	std::cout << "T = " << type_id_with_cvr<T>().pretty_name() << std::endl;
	std::cout << "param = " << type_id_with_cvr<decltype(param)>().pretty_name() << std::endl;
}

std::vector<Widget> create_vector()
{
	std::vector<Widget> vec = { Widget() };
	return vec;
}

void diagnose_run_time()
{
	int value = 1;
	const char* type_name = typeid(value).name();
	std::cout << type_name << std::endl;


	// 复杂情况
	const auto vw = create_vector();
	if (!vw.empty())
	{
#ifdef TEST_BOOST_RTREE
		func(&vw[0]);
#endif
	}
}


void test_auto()
{
	auto i = 1;
	auto p = new auto(0);

	std::vector<int> vec = { 1,2,3,4,5 };
	auto iter = vec.begin();
	auto const_iter = vec.cbegin();

	for (const auto& value : vec)
	{
		std::cout << value << ", ";
	}

	//auto arr[10] = {}; // error
	//void fun(auto lhs); // error


	std::cout << std::endl << "---------------尾返回类型---------------" << std::endl;
	auto x = 1.0;
	auto y = 1.0;
	//auto(x + y) z0 = 1.0; // error
	decltype(x + y) z = 1.0;

	// 检查类型是否正确
	if (std::is_same<decltype(x), double>::value)
		std::cout << "type x == double" << std::endl;

	if (std::is_same<decltype(x), decltype(z)>::value)
		std::cout << "type x == type z" << std::endl;

	auto result1 = add_function1<int, int, int>(1, 2);
	auto result = add_function(1, 2);

	auto result14 = add_function_cpp14(1.0, 2.0);

	// decltype(auto)
}