
// 1.在ThiefMember里面定义一个友元函数steal_impl，用于访问私有成员
template <typename T, auto... field>
struct ThiefMember
{
    friend auto steal_impl(T& t) { return std::make_tuple(field...); }
};

class Bank_t
{
    int         _id;
    std::string _name;

    int foo() { return 42; }

public:
    Bank_t(int i, std::string str) : _id(i), _name(str) {}
};

// 2.显式实例化类模版ThiefMember
// 【C++规则】显式实例化定义忽略成员访问说明符：形参类型和返回类型可以是 private
template struct ThiefMember<Bank_t, &Bank_t::_id, &Bank_t::_name, &Bank_t::foo>;

// Google test框架的 nicemock 也用了此技巧
TEST(member, access_private_member)
{
    Bank_t bank(1, "mike");
    auto   tp = steal_impl(bank);

    auto id = bank.*(std::get<0>(tp));
    EXPECT_TRUE(id == 1);

    auto name = bank.*(std::get<1>(tp));
    EXPECT_TRUE(name == "mike");

    auto r = (bank.*(std::get<2>(tp)))();
    EXPECT_TRUE(r == 42);
}
