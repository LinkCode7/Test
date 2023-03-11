#include "pch.h"
#include "std_string.h"
#include <map>
#include <iostream>
#include <cassert>

using namespace std;

TEST(std_string, NoCaseWString)
{
	map<std::string, int> mapDatas = { { "a",1 },{ "CC",3 } };
	assert(mapDatas.find("A") == mapDatas.end());

	// 条款2-3 不区分大小写的string
	string str = "a";
	assert(str != "A");

	my_string myStr = "a";
	assert(myStr == "A");
}

/*
//string类的查找函数：
int find(char c, int pos = 0) const;//从pos开始查找字符c在当前字符串的位置
int find(const char *s, int pos = 0) const;//从pos开始查找字符串s在当前串中的位置
int find(const char *s, int pos, int n) const;//从pos开始查找字符串s中前n个字符在当前串中的位置
int find(const string &s, int pos = 0) const;//从pos开始查找字符串s在当前串中的位置
//查找成功时返回所在位置，失败返回string::npos的值
int rfind(char c, int pos = npos) const;//从pos开始从后向前查找字符c在当前串中的位置
int rfind(const char *s, int pos = npos) const;
int rfind(const char *s, int pos, int n = npos) const;
int rfind(const string &s,int pos = npos) const;
//从pos开始从后向前查找字符串s中前n个字符组成的字符串在当前串中的位置，成功返回所在位置，失败时返回string::npos的值
int find_first_of(char c, int pos = 0) const;//从pos开始查找字符c第一次出现的位置
int find_first_of(const char *s, int pos = 0) const;
int find_first_of(const char *s, int pos, int n) const;
int find_first_of(const string &s,int pos = 0) const;
//从pos开始查找当前串中第一个在s的前n个字符组成的数组里的字符的位置。查找失败返回string::npos
int find_first_not_of(char c, int pos = 0) const;
int find_first_not_of(const char *s, int pos = 0) const;
int find_first_not_of(const char *s, int pos,int n) const;
int find_first_not_of(const string &s,int pos = 0) const;
//从当前串中查找第一个不在串s中的字符出现的位置，失败返回string::npos
int find_last_of(char c, int pos = npos) const;
int find_last_of(const char *s, int pos = npos) const;
int find_last_of(const char *s, int pos, int n = npos) const;
int find_last_of(const string &s,int pos = npos) const;
int find_last_not_of(char c, int pos = npos) const;
int find_last_not_of(const char *s, int pos = npos) const;
int find_last_not_of(const char *s, int pos, int n) const;
int find_last_not_of(const string &s,int pos = npos) const;
//find_last_of和find_last_not_of与find_first_of和find_first_not_of相似，只不过是从后向前查找
*/
TEST(std_string, BasicString)
{
	string str("aa.txt");
	auto pos = str.find(".txt");
	assert(pos == 2);
}

TEST(std_string, substr)
{
	string str(u8"");
	assert(str.substr(0, str.size() - 1) == u8"");

	str = u8"-";
	assert(str.substr(0, str.size() - 1) == u8"");
	str.pop_back();
	assert(str == u8"");

	// 单个字符占的字节数大于1
	str = u8"中国";
	auto sub = str.substr(0, str.size() - 1); // 无效字符串

	const char ch = '国';

	str.erase(str.end() - 1); // 无效字符串

	str = u8"中国";
	str.pop_back(); // 无效字符串
}
