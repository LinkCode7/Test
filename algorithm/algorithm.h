#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <string>
#include <vector>

std::string numberToLetterString(unsigned int levelCount)
{
	if (levelCount < 0)
		return std::string();

	std::string numStr;
	levelCount++;
	do {
		levelCount--;
		auto rest = levelCount % 26;
		numStr = (char)('a' + rest) + numStr;
		levelCount /= 26;
	} while (levelCount > 0);
	return numStr;
}

std::string getLetterEncodeNum(uint32_t num)
{
	std::string ret;
	while (num) {
		int n = (--num) % 26;
		ret += ('a' + n);
		num /= 26;
	}
	std::reverse(ret.begin(), ret.end());
	return ret;
}

std::string numberToRomanString(size_t levelCount)
{
	levelCount++;
	std::string res = "";
	if (levelCount >= 6000)
		return "mmmmmcmxcix";  // 超过5999直接返回最大的，因为罗马数字最大就只有5999
	std::vector<std::string> v1{ "", "m", "mm", "mmm", "mmmm", "mmmmm" };
	std::vector<std::string> v2{ "", "c", "cc", "ccc", "cd", "d", "dc", "dcc", "dccc", "cm" };
	std::vector<std::string> v3{ "", "x", "xx", "xxx", "xl", "l", "lx", "lxx", "lxxx", "xc" };
	std::vector<std::string> v4{ "", "i", "ii", "iii", "iv", "v", "vi", "vii", "viii", "ix" };
	return v1[levelCount / 1000] + v2[(levelCount % 1000) / 100] + v3[(levelCount % 100) / 10] + v4[levelCount % 10];
}
std::string getRomeEncodeNum(uint32_t num)
{
	constexpr int values[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
	const std::string  reps[] = { "m", "cm", "d", "cd", "c", "xc", "l", "xl", "x", "ix", "v", "iv", "i" };

	std::string ret;
	for (int i = 0; i < 13; i++) {  // len = reps->size()
		while (num >= values[i]) {
			num -= values[i];
			ret += reps[i];
		}
	}
	return ret;
}

#endif
