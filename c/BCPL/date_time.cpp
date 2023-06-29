#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <iostream>
#include <sstream>

#include "pch.h"

TEST(date_time, time_t)
{
    time_t     t   = time(nullptr);
    struct tm* now = localtime(&t);

    std::stringstream ss;
    ss << now->tm_year + 1900 << "年";
    ss << now->tm_mon + 1 << "月";
    ss << now->tm_mday << "日 ";
    ss << now->tm_hour << ":";
    ss << now->tm_min << ":";
    ss << now->tm_sec; // 最多精确到秒

    // 2023年6月15日 11:53:21
    auto str = ss.str();
    std::cout << str << std::endl;
}
