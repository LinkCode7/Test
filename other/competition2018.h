#pragma once

using namespace std;

void AddStr(string& strContainer, const string& strAdd, const string& strSplit)
{
    if (strContainer.empty())
    {
        strContainer = strAdd;
    }
    else
    {
        strContainer += strSplit;
        strContainer += strAdd;
    }
}

void Split(const string& strSrc, const string& strSplit, vector<string>& vec)
{
}