#pragma once

#include <tchar.h>
#include <time.h>

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

//#define GTEST_LANG_CXX11 1 // GTest编译问题...
//#include "gtest/gtest.h"
#include "xtest.h"

#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

#define DESKTOP_FILE_TXT "C:\\Users\\Administrator\\Desktop\\Test.txt"
#define DESKTOP_FILE_XML "C:\\Users\\Administrator\\Desktop\\Test.xml"

#define PRINT() std::cout << "True " << __LINE__ << std::endl;

// GDAL库只编译了VS2015版本
#define _VERSION_VS2015_ 1900

#ifndef PI
    #define PI 3.1415926535897932384626433832795
#endif

template <class T>
class CompileTimeTypeDiagnosis;
