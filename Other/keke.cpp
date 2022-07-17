#include "pch.h"
#include "keke.h"

#include <stdio.h>
#include <stdlib.h>


#pragma warning(disable:4244)
#pragma warning(disable:4996)


TEST(Other, keke)
{
	return;
	keke1();
	keke2();
	keke3();
}



void keke1()
{
	/*char a[20];
	gets(a);

	int i;
	for (i = 0; a[i] != '\0'; i++)
	{
	if (a[i] >= 'a'&&a[i] <= 'z')
	a[i] += 32;
	else if (a[i] >= 'A'&&a[i] <= 'Z')
	a[i] -= 32;
	puts(a);
	}*/



	/*char a[20];
	int i, digit = 0;
	gets(a);
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] >= 'a'&&a[i] <= 'z')
			a[i] = a[i] - 'a' + 'A';
		else if (a[i] >= 'A'&&a[i] <= 'Z')
			a[i] = a[i] - 'A' + 'a';
		else if (a[i] >= 1 && a[i] <= 9) digit++;
	}
	printf("digit=%d,", digit);
	puts(a);*/
}

void keke2()
{
	int i, a, f, m = 0, n = 0;
	char y = 'y';
	printf("\n\t\t\t欢迎使用小学算术考试系统！\n\n");
	printf("\t本考试系统出题题型有：加法题、减法题、乘法题和除法题\n");
	printf("\n\t\t本次测试量为10题，请按回车键开始答题！");
	getchar();
	srand(time(0));
	for (i = 1; i <= 10; i++)
	{
		a = rand() % 4 + 1;
		switch (a)
		{
		case 1:
			printf("\t\n第%2d题:加法题！\n", i);
			f = add();
			break;
		case 2:
			printf("\t\n第%2d题:减法题！\n", i);
			f = sub();
			break;
		case 3:
			printf("\t\n第%2d题:乘法题！\n", i);
			f = mul();
			break;
		case 4:
			printf("\t\n第%2d题:除法题！\n", i);
			f = div();
			break;
		}

		if (f == 1)
		{
			printf("你答对了！再接再厉！");
			m++;
		}
		else
		{
			printf("你答错了！加倍努力！");
			n++;
		}
	}
	printf("\n\n本次测试结束！你共测了了%d道，答对了%d道！答错了%d道\n", i - 1, m, n);
	printf("你的成绩为：%d分！欢迎下次再次测试！！\n", m * 10);
}
int add()
{
	int a, b, r;
	a = rand() % 30;
	b = rand() % 30;
	printf("%d+%d=", a, b);
	scanf("%d", &r);
	if (r == a + b) return(1);
	else return(0);
}
int sub()
{
	int a, b, r;
	a = rand() % 30;
	b = rand() % 30;
	if (a > b)
	{
		printf("%d-%d=", a, b);
		scanf("%d", &r);
		if (a - b == r) return(1);
		else return(0);
	}
	else sub();

	return -1; //
}
int mul()
{
	int a, b, r;
	a = rand() % 30;
	b = rand() % 30;
	printf("%d*%d=", a, b);
	scanf("%d", &r);
	if (a*b == r) return(1);
	else return(0);
}
int div()
{
	int r = 0;
	int a = rand() % 30;
	int b = rand() % 30;

	if (b == 0)
	{
		return div();
	}

	if (a % b == 0)
	{
		printf("%d/%d=", a, b);
		scanf("%d", &r);
		if (a / b == r) return(1);
		else return(0);
	}
	else
	{
		return div();
	}
}

void keke3()
{
	// 写入成绩
	// wb,a
	char file_path[] = "C:\\Users\\siyuj\\Desktop\\data.txt";
	FILE *fp = fopen(file_path, "a");
	if (fp == NULL)
	{
		exit(1);
	}

	Student student;
	printf("请依次输入学生的姓名、班级、分数：\n");
	scanf("%s%s%s", &student.name, &student.class_name, &student.grade);

	//fputs("张三 3班 80分", fp);

	// 以追加的方式写入一个人的班级、成绩
	fprintf(fp, "%s\t%s\t%s\n", student.name, student.class_name, student.grade);
	fclose(fp);




	// 读出成绩
	//rewind(fp);
	fp = fopen(file_path, "r");

	Student s2;
	while (fscanf(fp, "%s\t%s\t%s\n", s2.name, s2.class_name, s2.grade) != -1)
	{
		// 这里得到的就是一行数据了
	}

	fclose(fp);
}