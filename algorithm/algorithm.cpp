#include "algorithm.h"

#include <cassert>
#include <iostream>

using namespace std;
// 判断一个数时候为回文数(121,12321,35653)
// unsigned char Symmetry(long n)
bool Symmetry(long n)
{
    long i, temp, cout(0);
    i    = n;
    temp = 0;
    // cout << "begin:		i: " << i << endl;
    // cout << "        temp: " << temp << endl;

    // while (i) //不用出现长度问题,将数按高低位掉换
    //{
    //	temp = temp * 10 + i % 10;
    //	i /= 10;

    //	cout << "count:" << cout++  << "i:" << i << endl;
    //	cout << "      " << "temp:" << temp << endl;
    //}

    // cout << "end:		i: " << i << endl;
    // cout << "        temp: " << temp << endl;
    return (temp == n);
}

void algorithm()
{
    Symmetry(12321);
}

TEST(multibyte, letter)
{
    assert(numberToLetterString(0) == "a");
    assert(numberToLetterString(1) == "b");
    assert(numberToLetterString(2) == "c");
    assert(numberToLetterString(3) == "d");
    assert(numberToLetterString(25) == "z");

    assert(numberToLetterString(26) == "aa");
    assert(numberToLetterString(27) == "ab");
    assert(numberToLetterString(28) == "ac");
    assert(numberToLetterString(51) == "az");

    assert(numberToLetterString(52) == "ba");
    assert(numberToLetterString(53) == "bb");
    assert(numberToLetterString(54) == "bc");

    assert(getLetterEncodeNum(0) == "");
    assert(getLetterEncodeNum(1) == "a");
    assert(getLetterEncodeNum(2) == "b");
    assert(getLetterEncodeNum(3) == "c");
    assert(getLetterEncodeNum(24) == "x");
    assert(getLetterEncodeNum(25) == "y");
    assert(getLetterEncodeNum(26) == "z");

    assert(getLetterEncodeNum(27) == "aa");
    assert(getLetterEncodeNum(28) == "ab");
    assert(getLetterEncodeNum(29) == "ac");

    assert(getLetterEncodeNum(51) == "ay");
    assert(getLetterEncodeNum(52) == "az");
    assert(getLetterEncodeNum(53) == "ba");
}

TEST(multibyte, rome_number)
{
    assert(numberToRomanString(0) == "i");
    assert(numberToRomanString(1) == "ii");
    assert(numberToRomanString(2) == "iii");
    assert(numberToRomanString(3) == "iv");
    assert(numberToRomanString(4) == "v");

    auto str = numberToRomanString(6);
    assert(getRomeEncodeNum(0) == "");
    assert(getRomeEncodeNum(1) == "i");
    assert(getRomeEncodeNum(2) == "ii");
    assert(getRomeEncodeNum(3) == "iii");
    assert(getRomeEncodeNum(4) == "iv");
    assert(getRomeEncodeNum(5) == "v");
}
