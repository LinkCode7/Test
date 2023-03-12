#include "pch.h"
#include "assert.h"

using std::cout;
using std::endl;

void getWidths(int count, float widths[])
{
	if (!widths)
		return;

	// logic...
	float* arrWidths = new float[count];
	for (auto i = 0; i < count; ++i)
		arrWidths[i] = 0.1;

	// out
	float* cursor = widths;
	for (auto i = 0; i < count; ++i)
		*cursor++ = arrWidths[i];

	delete[] arrWidths;
}

TEST(floating, increase)
{
	float value1 = 0;
	getWidths(1, &value1);

	float value2[3] = {};
	getWidths(3, value2);
}

TEST(std_atoi, atoi_case)
{
	assert(std::atoi("") == 0);
	assert(std::atoi(" ") == 0);
	assert(std::atoi("a") == 0);
	assert(std::atoi("+") == 0);
	assert(std::atoi("*") == 0);
	assert(std::atoi("@") == 0);
	assert(std::atoi(".") == 0);

	assert(std::atoi("0") == 0);
	assert(std::atoi("0.0") == 0);
	assert(std::atoi("0.1") == 0);
	assert(std::atoi("0.01") == 0);
	assert(std::atoi("3.14") == 3);

	assert(std::atoi("-1") == -1);
	assert(std::atoi("-0.1") == 0);
	assert(std::atoi("-0.01") == 0);
	assert(std::atoi("-3.14") == -3);
}

TEST(floating, convert_to_string)
{
#define DIGIT_COUNT 21
	float ff = 1024.1234567;
	double dd = 12345678901234.1234567;

	char strff[DIGIT_COUNT], strdd[DIGIT_COUNT];

	// 把浮点数ff转换为字符串，存放在strff中
	memset(strff, 0, sizeof(strff));
	snprintf(strff, DIGIT_COUNT, "%.2f", ff);
	assert(std::string(strff) == "1024.12");

	memset(strff, 0, sizeof(strff));
	snprintf(strff, DIGIT_COUNT, "%.5f", ff);
	assert(std::string(strff) == "1024.12341");

	// 双精度浮点数
	memset(strdd, 0, sizeof(strdd));
	snprintf(strdd, DIGIT_COUNT, "%.2lf", dd);
	assert(std::string(strdd) == "12345678901234.12");

	memset(strdd, 0, sizeof(strdd));
	snprintf(strdd, 11, "%.2lf", dd);
	assert(std::string(strdd) == "1234567890");
#undef DIGIT_COUNT
}

std::string convert_to_amount(double num)
{
	std::string unit[] = { "分","角","元","拾","佰","仟","万" }; // 单位
	std::string counts[] = { "零","壹","贰","叁","肆","伍","陆","柒","捌","玖" };

	std::string news;

	num = num * 100.0;
	int a = num; // 将数字转化为字符串
	std::stringstream ss;
	ss << a;
	std::string str = ss.str();

	size_t len = str.size();
	for (size_t i = 0; i < len; i++)
	{
		if (str[i] - '0' == 0) // 出现多个零时只保留一个零
		{
			if (str[i - 1] - '0' == 0)
				continue;
			else
				news = news + counts[str[i] - '0'];
		}
		else
			news = news + counts[str[i] - '0'] + unit[len - i - 1]; // 不出现零时正常表示
	}

	std::string::size_type position1 = news.find("角");
	std::string::size_type position2 = news.find("分");
	if (position1 == news.npos && position2 == news.npos) // 角和分同时不存在时表示为整
	{
		news.append("整");
	}
	if (news.find("零整") != -1)
		news.replace(news.find("零整"), 3, "整"); // 排除零整出现在一起的情况
	return news;
}

TEST(floating, convert_to_amount)
{
	assert(convert_to_amount(3.14) == "叁元壹角肆分");
	// assert(convert_to_amount(12345678.009) == "叁元壹角肆分");
}
