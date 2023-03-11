#include "pch.h"
#include "suspicious.h"

#include<stdio.h>


#pragma warning(disable : 4996)

void keke();
void test20200409();

void test1024();







bool _Main()
{
	//test20200409();
	return true;
}












void test1024()
{
	time_t t;
	struct tm *p;
	t = 1540350000;
	p = gmtime(&t);
	char s[80];
	strftime(s, 80, "%Y-%m-%d %H:%M:%S::%Z", p);
	printf("%d: %s\n", (int)t, s);

	std::string str = "\u0042\u5e62\u0043\u5ea7\u4f1a\u8bae\u5ba4\u0032";
}

void test20200409()
{
	// 输入一个字符串，将大写转成小写、小写转成大写，并统计数字个数

	char ch[50];
	scanf("%s", ch);

	int iDigitCount = 0;

	int i = 0;
	while (ch[i] != '\0')
	{
		if (ch[i] >= 'a'&& ch[i] <= 'z')
		{
			ch[i] = ch[i] - 'a' + 'A'; // 小写转大写
		}
		else if (ch[i] >= 'A' && ch[i] <= 'Z')
		{
			ch[i] = ch[i] - 'A' + 'a'; // 大写转小写
		}
		else if (ch[i] >= '0' && ch[i] <= '9')
		{
			++iDigitCount;
		}

		++i;
	}

	printf("Digit:%d\n%s", iDigitCount, ch);
	//puts(ch);
}
