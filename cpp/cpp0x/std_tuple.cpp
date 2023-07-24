#include "std_tuple.h"

#include <tuple>

void test_tuple()
{
    how_to_use_tuple();

    about_variant();
}

auto get_student(int id)
{
    if (id == 0)
        return std::make_tuple(3.8, 'A', "张三");
    else if (id == 1)
        return std::make_tuple(2.9, 'C', "李四");
    else if (id == 2)
        return std::make_tuple(1.7, 'D', "王五");

    return std::make_tuple(0.0, 'D', "null");
}

void how_to_use_tuple()
{
    auto student = get_student(0);
    std::cout << typeid(std::get<0>(student)).name() << std::endl;
    std::cout << typeid(std::get<1>(student)).name() << std::endl;
    std::cout << typeid(std::get<2>(student)).name() << std::endl;

    // get<index>获取值
    std::cout << "ID: 1, GPA: " << std::get<0>(student);
    std::cout << ", 成绩: " << std::get<1>(student) << ", 姓名: " << std::get<2>(student) << '\n';

    // get<type>获取值
    std::cout << std::endl;
    std::cout << "ID: 1, GPA: " << std::get<double>(student);
    std::cout << ", 成绩: " << std::get<char>(student) << ", 姓名: " << std::get<const char*>(student) << '\n';

    // 元组进行拆包
    double      gpa;
    char        grade;
    std::string name;
    std::tie(gpa, grade, name) = get_student(1);

    std::cout << std::endl << std::endl << std::endl;
    std::cout << "ID: 1, GPA: " << gpa << ", 成绩: " << grade << ", 姓名: " << name << '\n';
}

void about_variant()
{
    std::tuple<std::string, double, double, int> values("123", 4.5, 6.7, 8);
    std::cout << std::get<std::string>(values) << std::endl;
    // std::cout << std::get<double>(values) << std::endl; // error C2338: duplicate type T in get<T>(tuple)
    std::cout << std::get<3>(values) << std::endl;

    std::cout << "tuple_index..." << std::endl;
    // std::cout << tuple_index(values, 0) << std::endl;
    // std::cout << tuple_index(values, 1) << std::endl;

    // 合并两个元组
    auto new_tuple = std::tuple_cat(get_student(1), std::move(values));

    // 迭代
    for (int i = 0; i != tuple_len(new_tuple); ++i)
    {
        // 运行期索引
        std::cout << tuple_index(new_tuple, i) << std::endl;
    }
}