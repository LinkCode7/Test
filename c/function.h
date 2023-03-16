#ifndef C_FUNCTION_H
#define C_FUNCTION_H

char* my_strcpy(char* destination, const char* source)
{
	if (!destination || !source)
		return destination;

	char* ret = destination;
	// 拷贝source指向的字符串到destination指向的空间，包含'\0'
	while (*destination++ = *source++)
	{
	}

	return ret; 	// 返回目的空间的起始地址
}
char* my_strcpy2(char* src, char* dst)
{
	if (!src || !dst) return nullptr;

	char* temp = src;
	while (*src != '\0')
	{
		*dst = *src;
		src = src + 1;
		dst = dst + 1;
	}

	return temp;
}

char* my_strncpy(char* dest, const char* source, size_t count)
{
	char* start = dest;

	while (count && (*dest++ = *source++))    /* copy string */
		count--;

	if (count)                              /* pad out with zeroes */
		while (--count)
			*dest++ = '\0';

	return(start);
}

int my_strcmp(const char* src, const char* dst)
{
	int ret = 0;

	while (!(ret = *(unsigned char*)src - *(unsigned char*)dst) && *dst)
		++src, ++dst;

	if (ret < 0)
		ret = -1;
	else if (ret > 0)
		ret = 1;

	return(ret);
}

// 考虑src、dst内存地址交叉，此时应该用memmove
// 考虑dst长度比n小，此时应返回，让用户处理
void* my_memcpy(void* src, void* dst, size_t n)
{
	if (!src || !dst) return nullptr;

	void* temp = dst;

	while (n-- != 0)
	{
		*(char*)dst = *(char*)src;
		src = (char*)src + 1;
		dst = (char*)dst + 1;
	}

	return temp;
}

void* my_memset(void* src, int val, size_t n)
{
	if (!src) return nullptr;

	void* temp = src;

	while (n-- != 0)
	{
		*(char*)src = val;
		src = (char*)src + 1;
	}

	return temp;
}

#endif // !C_FUNCTION_H
