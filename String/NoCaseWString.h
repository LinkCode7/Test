#pragma once


struct no_case_char_traits :public std::char_traits<wchar_t>
{
	static bool eq(wchar_t c1, wchar_t c2)
	{
		return towupper(c1) == towupper(c2);
	}
	static bool ne(wchar_t c1, wchar_t c2)
	{
		return towupper(c1) != towupper(c2);
	}
	static bool lt(wchar_t c1, wchar_t c2)
	{
		return towupper(c1) < towupper(c2);
	}
	static int compare(const wchar_t* s1, const wchar_t* s2, size_t n)
	{
		// Compare no case
		return _memicmp(s1, s2, n);
	}

	static const wchar_t* find(const wchar_t* s, int n, wchar_t a)
	{
		while (n-- > 0 && towupper(*s) != towupper(a))
		{
			++s;
		}
		return s;
	}
};

typedef std::basic_string<wchar_t, no_case_char_traits > no_case_wstring;




//int compare(const wchar_t* s1, const wchar_t* s2, size_t n)
//{
//	//const size_t size1 = sizeof s1 / sizeof *s1;
//	//const size_t size2 = sizeof s2 / sizeof *s2;
//
//	//wchar_t p1[size1];
//	//wchar_t p2[size2];
//	//std::wmemcpy(p1, s1, size1);
//	//std::wmemcpy(p2, s2, size2);
//
//	//// To upper
//	//for (size_t n = 0; n < sizeof p1 / sizeof *p1; ++n)
//	//{
//	//	if (p1[n])
//	//		towupper(p1[n]);
//	//}
//	//for (size_t n = 0; n < sizeof p2 / sizeof *p2; ++n)
//	//{
//	//	if (p2[n])
//	//		towupper(p2[n]);
//	//}
//
//	//return _memicmp(p1, p2, n);
//	return _memicmp(s1, s2, n);// No case
//}