#include "competition2018.h"

#include <sstream>

#include "stdio.h"
#include "stdlib.h"
//#include <sstring>

#include <algorithm>
#include <iomanip>

#pragma warning(disable : 4267)

using namespace std;

// 找到iNumber以内的连续素数(孪生素数)
int    GetPrimeTwins(int iNumber);
string DealString(const string& strSrc, int index, char letter);

int  test1();
int  test2();
int  test3();
void test4();

//////////////////////////////////////////////////////////////////

void BcJs()
{
    // test1();
    // test2();
    test3();

    int i1 = GetPrimeTwins(5);
    int i2 = GetPrimeTwins(13);
    int i3 = GetPrimeTwins(100);
}

// 找到iNumber以内的连续素数(孪生素数)
int GetPrimeTwins(int iNumber)
{
    cout << endl << "iNumber以内的孪生素数：" << endl;

    if (iNumber < 5)
        return 0;

    int iResult = 0;
    int iPreSs  = 3;
    for (int i = 3; i <= iNumber; ++i)
    {
        bool isSsCur(true);

        int iTemp = int(sqrt(i));
        for (int j = 2; j <= iTemp; ++j)
        {
            if (i % j == 0)
            {
                isSsCur = false;
                break;
            }
        }

        if (!isSsCur)
        {
            continue;
        }
        else
        {
            if (i - iPreSs == 2) // 相连的素数
            {
                cout << "找到(" << iPreSs << "," << i << ")" << endl;
                ++iResult;

                iPreSs = 0; // 重置
            }
            else
                iPreSs = i;
        }

        ++i; // 偶数不会是素数
    }
    return iResult;
}

string DealString(const string& strSrc, int index, char letter)
{
    string strAdd(&letter);

    string strSrcCopy(strSrc);
    strSrcCopy.insert(index, strAdd);

    char chSame = strSrcCopy.at(0);
    int  iSame  = 0;

    int iCout = 0;
    int iSize = strSrcCopy.size();
    for (int i = 0; i < iSize; ++i)
    {
        if (chSame == strSrcCopy.at(i))
        {
            ++iCout;
            if (iCout == 3)
            {
                strSrcCopy.erase(i - 3, i);
                iSize  = strSrcCopy.size();
                chSame = strSrcCopy.at(0);
                i      = 0; // 提升
            }
            else
            {
            }
        }
    }

    return string();
}

int test1()
{
    string strSrc1("qwertyuiop[");
    string strSrc2("asdfghjkl;");
    string strSrc3("zxcvbnm,");

    int iTestNum;
    cin >> iTestNum;

    vector<string> vecResult;

    for (int i = 0; i < iTestNum; ++i)
    {
        string strInput;
        cin >> strInput;

        string strOut;
        for (size_t j = 0; j < strInput.size(); ++j)
        {
            int iPos = strSrc1.find(strInput.at(j));
            if (iPos > 0)
            {
                strOut += strSrc1.at(iPos - 1);
                continue;
            }

            iPos = strSrc2.find(strInput.at(j));
            if (iPos > 0)
            {
                strOut += strSrc2.at(iPos - 1);
                continue;
            }

            iPos = strSrc3.find(strInput.at(j));
            if (iPos > 0)
            {
                strOut += strSrc3.at(iPos - 1);
                continue;
            }
        }

        vecResult.push_back(strOut);
    }

    for (size_t k = 0; k < vecResult.size(); ++k)
    {
        cout << vecResult.at(k) << endl;
    }

    return 0;
}

struct Node
{
    string name;
    int    iXn;
    int    iJg;

    int iCmp;
};
bool cpm(const Node& node1, const Node& node2)
{
    if (node1.iCmp < node2.iCmp)
        return false;
    return true;
}
int test2()
{
    int iGroup;
    cin >> iGroup;

    vector<vector<Node>> vecAll;
    for (int g = 0; g < iGroup; ++g)
    {
        int iNum;
        cin >> iNum;

        vector<Node> vecOne;
        for (int i = 0; i < iNum; ++i)
        {
            Node node;
            cin >> node.name >> node.iXn >> node.iJg;

            node.iCmp = node.iXn / node.iJg;
            vecOne.push_back(node);
        }

        std::sort(vecOne.begin(), vecOne.end(), cpm);
        vecAll.push_back(vecOne);
    }

    for (size_t k = 0; k < vecAll.size(); ++k)
    {
        const vector<Node>& vecOut = vecAll.at(k);
        for (size_t k2 = 0; k2 < vecOut.size(); ++k2)
        {
            cout << k2 + 1 << " " << vecOut.at(k2).name << " " << vecOut.at(k2).iXn << " " << vecOut.at(k2).iJg << endl;
        }
    }

    return 0;
}

int test3()
{
    // 共几组数据
    int iGroup = 0;
    cin >> iGroup;

    vector<int>         vecOne;
    vector<vector<int>> vecAll;

    int iMin      = 0;
    int iMinCount = 0;
    for (int g = 0; g < iGroup; ++g)
    {
        // 每组数据的数量
        int iNum;
        cin >> iNum;

        vecOne.clear();
        for (int i = 0; i < iNum; ++i)
        {
            int a;
            cin >> a;
            vecOne.push_back(a);
        }

        vecAll.push_back(vecOne);
    }

    for (size_t m = 0; m < vecAll.size(); ++m)
    {
        const vector<int>& vecOne1 = vecAll.at(m);
        // if (vecOne1.size() < 2) continue;

        // 找每组数据中最小的数据iMin及个数iMinCount
        iMin      = abs(vecOne1.at(0) - vecOne1.at(1));
        iMinCount = 0;
        for (size_t j = 0; j < vecOne1.size() - 1; ++j)
        {
            int c1 = vecOne1.at(j);

            for (size_t k = j + 1; k < vecOne1.size(); ++k)
            {
                int c2 = abs(c1 - vecOne1.at(k));

                if (c2 > iMin)
                    continue;
                else if (c2 == iMin)
                    ++iMinCount;
                else // 小于
                {
                    iMin      = c2;
                    iMinCount = 1;
                }
            }
        }

        cout << iMin << " " << iMinCount << endl;
    }

    return 0;
}

void test4()
{
    int iGroup = 0;
    cin >> iGroup;

    for (int g = 0; g < iGroup; ++g)
    {
        int a, b, c;
        cin >> a >> b >> c;

        int iRow    = 0;
        int iColumn = 0;
        int iHealth = 0;
        cin >> iRow >> iColumn >> iHealth;

        for (int n = 0; n < iRow; ++n)
        {
            for (int m = 0; m < iColumn; ++m)
            {
                // cin >>
            }
        }
    }
}