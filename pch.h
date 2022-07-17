#pragma once



#include <cstdio>
#include <cstdlib>

#include <tchar.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <sstream>
#include <memory>

#include <array>
#include <functional>

#include <time.h>






//#define GTEST_LANG_CXX11 1 // GTest编译问题...
//#include "gtest/gtest.h"
#include "xtest.h"






#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string	tstring;
#endif


#define DESKTOP_FILE_TXT "C:\\Users\\Administrator\\Desktop\\Test.txt"
#define DESKTOP_FILE_XML "C:\\Users\\Administrator\\Desktop\\Test.xml"

#define PRINT() std::cout << "True " << __LINE__ << std::endl;


#define PmDelete(TYPE) {delete TYPE;(TYPE)=NULL;}


class TestOperator
{
	bool m_isTestRand;
public:
	static TestOperator& instance()
	{
		static TestOperator opr;
		return opr;
	}
	bool TestRand()
	{
		return false;
	}
};

#define TestOpr TestOperator::instance()


// GDAL库只编译了VS2015版本
#define _VERSION_VS2015_ 1900