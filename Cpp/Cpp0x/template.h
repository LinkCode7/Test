#pragma once

#include <array>
#include <type_traits>


/*
外部模板
传统C++中，模板只有在使用时才会被编译器实例化，换句话说，只要在每个
编译单元（文件）编译的代码中遇到了被完整定义的模板，都会实例化，
这种重复实例化导致编译时间变长。
*/

// 通知编译器不要触发实例化：
template class std::vector<bool>; // 强制实例化
extern template class std::vector<double>; // 不在当前编译文件中实例化





template<typename... Ts>
constexpr auto make_array(Ts&&... ts)->std::array<std::common_type_t<Ts...>, sizeof...(Ts)>
{
	return { std::forward<Ts>(ts)... };
}




template<typename ... Ts>
void magic_function(Ts... args)
{
	// operator sizeof...
	std::cout << sizeof...(args) << std::endl;
	//std::cout << sizeof...(args) << std::end; // maddening
}




// 可变参数模板 解包1（递归模板函数）
template<typename T0>
void printf1(T0 value)
{
	std::cout << value << std::endl;
}

template<typename T, typename... Ts>
void printf1(T value, Ts... args)
{
	std::cout << value << std::endl;
	printf1(args...);
}



// 可变参数模板 解包2（展开变参模板）
template<typename T0, typename... T>
void printf2(T0 t0, T... t)
{
	std::cout << t0 << std::endl;
	if constexpr (sizeof...(t) > 0)
		printf2(t...);
}



// 可变参数模板 解包（初始化列表展开）
template<typename T, typename... Ts>
auto printf3(T value, Ts... args)
{
	std::cout << value << std::endl;

	// 转换为void是为了避免编译器警告
	(void)std::initializer_list<T>{([&args] {
		std::cout << args << std::endl;
	}(), value)...};
}







template <typename T, int BufSize>
class buffer_t
{
public:
	T& alloc() { return data; }
	void free(T& item) {}
private:
	T data[BufSize];
};
