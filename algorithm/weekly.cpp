#include "weekly.h"

#pragma warning(disable : 4267)

using namespace std;

int         kthLargestElement(int n, vector<int> &nums);
vector<int> mergeSortedArray(vector<int> &A, vector<int> &B);

void        sortLetters(string &chars);
vector<int> searchRange(TreeNode *root, int k1, int k2);

int binarySearch(vector<int> &nums, int target);

bool searchMatrix(vector<vector<int>> &matrix, int target);

void testt()
{
    if (0)
    {
        TreeNode *pRoot = new TreeNode(20);
        pRoot->left     = new TreeNode(8);
        pRoot->right    = new TreeNode(22);

        pRoot->left->left  = new TreeNode(4);
        pRoot->left->right = new TreeNode(12);

        vector<int> vec = searchRange(pRoot, 6, 10);

        delete pRoot->left->left;
        delete pRoot->left->right;
        delete pRoot->left;
        delete pRoot->right;
        delete pRoot;
    }

    vector<int> vec = {5};
    // vector<int> vec2 = { 6,7,8 };

    vector<vector<int>> matrix;
    matrix.push_back(vec);
    // matrix.push_back(vec2);

    bool isFind = searchMatrix(matrix, 2);
    return;
}

bool searchMatrix(vector<vector<int>> &matrix, int target)
{
    size_t size = matrix.size();
    if (size == 0)
        return false;

    size_t i = 0;
    if (size > 1)
    {
        for (; i < size; ++i)
        {
            const vector<int> &vec = matrix.at(i);
            if (vec.empty())
                continue;
            if (vec.at(0) > target)
                break;
        }
        --i;
    }

    const vector<int> &vec2 = matrix.at(i);
    if (std::find(vec2.begin(), vec2.end(), target) == vec2.end())
        return false;
    else
        return true;
}

int CheckSame(const vector<int> &nums, size_t index, int target)
{
    int i = index - 1;
    for (; i >= 0; --i)
    {
        if (nums.at(i) != target)
        {
            return i + 1;
        }
    }
    return index;
}

// 二分查找
int binarySearch(vector<int> &nums, int target)
{
    size_t right = nums.size();
    size_t left  = 0;

    size_t index = nums.size() / 2;

    while (true)
    {
        int iValue = nums.at(index);
        if (iValue == target)
        {
            // "3,4,5,8,8,8,8,10"要返回3
            return CheckSame(nums, index, target);
        }
        else if (target < iValue)
        {
            if (index == 0)
                return -1;

            right = index;
            index = left + (index - left) / 2;
        }
        else
        {
            if (index == right - 1)
                return -1;

            left  = index;
            index = index + (right - index) / 2;
        }
    }

    return -1;
}

void _flatten(const vector<NestedInteger> &nestedList, vector<int> &vecResult)
{
    for (const auto &object : nestedList)
    {
        if (object.isInteger())
        {
            vecResult.push_back(object.getInteger());
        }
        else
        {
            const vector<NestedInteger> &nestedListNext = object.getList();
            _flatten(nestedListNext, vecResult);
        }
    }
}

vector<int> flatten(vector<NestedInteger> &nestedList)
{
    vector<int> vecResult;
    _flatten(nestedList, vecResult);

    return vecResult;
}

void _searchRange(const vector<TreeNode *> &vecOneRow, int k1, int k2, vector<int> &vecResult)
{
    vector<TreeNode *> vecNextRow;

    for (const auto &pNode : vecOneRow)
    {
        if (!pNode)
            continue;

        if (k1 <= pNode->val && pNode->val <= k2)
        {
            vecResult.push_back(pNode->val);
        }

        if (pNode->left)
            vecNextRow.push_back(pNode->left);
        if (pNode->right)
            vecNextRow.push_back(pNode->right);
    }

    if (!vecNextRow.empty())
        _searchRange(vecNextRow, k1, k2, vecResult);
}
vector<int> searchRange(TreeNode *root, int k1, int k2)
{
    vector<int> vecResult;

    if (!root)
        return vecResult;

    vector<TreeNode *> vecNextRow;
    vecNextRow.push_back(root);
    _searchRange(vecNextRow, k1, k2, vecResult);

    std::sort(vecResult.begin(), vecResult.end());

    return vecResult;
}

vector<string> fizzBuzz(int n)
{
    vector<string> vecResult;

    for (int i = 1; i <= n; ++i)
    {
        if (i % 3 == 0)
        {
            if (i % 5 == 0)
                vecResult.push_back(string("fizz buzz"));
            else
                vecResult.push_back(string("fizz"));
        }
        else if (i % 5 == 0)
        {
            vecResult.push_back(string("buzz"));
        }
        else
        {
            vecResult.push_back(std::to_string(i));
        }
    }

    return vecResult;
}

void sortLetters(string &chars)
{
    auto size = chars.size();
    if (size < 2)
        return;

    size_t i = 0;
    for (size_t j = 0; j < size; ++j)
    {
        if ('a' <= chars.at(j) && chars.at(j) <= 'z')
        {
            std::swap(chars[i], chars[j]);
            ++i;
        }
    }
}

int kthLargestElement2(int n, vector<int> &nums)
{
    std::set<int> set;

    for (size_t i = 0; i < nums.size(); ++i)
    {
        set.insert(nums.at(i));
    }

    int                                   iCount = 0;
    std::set<int>::const_reverse_iterator iter   = set.rbegin();
    for (; iter != set.rend(); ++iter)
    {
        ++iCount;
        if (iCount == n)
            return *iter;
    }

    return -1;
}

int QuickSort(std::vector<int> &nums, int iLeft, int iRight)
{
    int iSize = nums.size();
    if (iSize == 0)
        return 0;

    int iKey = nums.at(0);

    int i = iLeft;
    int j = iRight;

    while (i < j)
    {
        while (i < j && iKey >= nums.at(j))
        {
            --j;
        }
        if (i < j)
        {
            nums[i] = nums[j];
            --j;
        }

        while (i < j && iKey < nums.at(i))
        {
            ++i;
        }
        if (i < j)
        {
            nums[j] = nums[i];
            ++i;
        }
    }

    nums[i] = iKey;
    return i;
}

int kthLargestElement(int n, vector<int> &nums)
{
    int iSize = nums.size();

    int iKey   = nums.at(0);
    int iLeft  = iKey;
    int iRight = iSize - 1;

    iKey = QuickSort(nums, iLeft, iRight);

    do
    {
        if (iKey < n - 1)
        {
            iKey = QuickSort(nums, iKey, iSize - 1);
        }
        else if (iKey > n - 1)
        {
            iKey = QuickSort(nums, 0, iKey);
        }
        else
        {
            return nums.at(iKey);
        }

    } while (iKey != n);

    return iKey;
}

vector<int> mergeSortedArray(vector<int> &A, vector<int> &B)
{
    int iSizeA = A.size();
    int iSizeB = B.size();

    std::vector<int> vec;

    if (iSizeA == 0)
        return B;
    else if (iSizeB == 0)
        return A;

    int iAMin = *(A.begin());
    int iAMax = *(A.begin() + iSizeA - 1); // STL迭代器左闭右开

    int iBMin = *(B.begin());
    int iBMax = *(B.begin() + iSizeB - 1);

    if (iBMax <= iAMin)
    {
        vec.assign(B.begin(), B.end());
        vec.insert(vec.end(), A.begin(), A.end());
    }
    else if (iBMin >= iAMax)
    {
        vec.assign(A.begin(), A.end());
        vec.insert(vec.end(), B.begin(), B.end());
    }
    else
    {
        /*vec.assign(A.begin(), A.end());
        vec.insert(vec.end(), B.begin(), B.end());

        std::sort(vec.begin(), vec.end());*/

        int iSize = std::max(iSizeA, iSizeB);

        int  iAIndex = 0;
        int  iBIndex = 0;
        bool isAValid(true), isBValid(true);

        for (; isAValid || isBValid;)
        {
            if (isAValid && isBValid)
            {
                if (iAMin == iBMin)
                {
                    vec.push_back(iAMin);
                    ++iAIndex;
                    if (iAIndex < iSizeA)
                        iAMin = *(A.begin() + iAIndex);
                    else
                        isAValid = false;

                    vec.push_back(iBMin);
                    ++iBIndex;
                    if (iBIndex < iSizeB)
                        iBMin = *(B.begin() + iBIndex);
                    else
                        isBValid = false;
                }
                else if (iAMin < iBMin)
                {
                    vec.push_back(iAMin);
                    ++iAIndex;
                    if (iAIndex < iSizeA)
                        iAMin = *(A.begin() + iAIndex);
                    else
                        isAValid = false;
                }
                else
                {
                    vec.push_back(iBMin);
                    ++iBIndex;
                    if (iBIndex < iSizeB)
                        iBMin = *(B.begin() + iBIndex);
                    else
                        isBValid = false;
                }
            }
            else if (isAValid)
            {
                vec.push_back(iAMin);
                ++iAIndex;
                if (iAIndex < iSizeA)
                    iAMin = *(A.begin() + iAIndex);
                else
                    isAValid = false;
            }
            else if (isBValid)
            {
                vec.push_back(iBMin);
                ++iBIndex;
                if (iBIndex < iSizeB)
                    iBMin = *(B.begin() + iBIndex);
                else
                    isBValid = false;
            }
            else
            {
                break;
            }
        }
    }

    return vec;
}