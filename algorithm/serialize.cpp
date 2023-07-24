#include "serialize.h"

#include "..\boost\boost_split.h"

using namespace std;

// 将树(数据结构)写入一个文件(数据库等等)被称为“序列化”，读取文件后重建同样的树被称为“反序列化”。
namespace BinaryTreeSerialize
{
constexpr int UnKnownInt   = -999999999;
const string& strHasValue  = "#";
const string& strNoneValue = "!";
const string& strSplitRow  = ";";
const string& strSplitNode = ",";

void AnalyzeNode(const string& str, int& iValue, bool& hasLeftNode, bool& hasRightNode)
{
    auto iSize = str.size();

    if (str.at(iSize - 1) == strHasValue.at(0))
        hasRightNode = true;
    else
        hasRightNode = false;

    if (str.at(iSize - 2) == strHasValue.at(0))
        hasLeftNode = true;
    else
        hasLeftNode = false;

    string strTemp(str.begin(), str.begin() + iSize - 2);
    iValue = atoi(strTemp.c_str());
}

void SetNode(TreeNode* pNode, int iValue, bool hasLeftValue, bool hasRightValue)
{
    // 当前节点赋值
    pNode->val = iValue;

    // new出下一层的子节点
    if (hasLeftValue)
        pNode->left = new TreeNode(UnKnownInt); // 临时值

    if (hasRightValue)
        pNode->right = new TreeNode(UnKnownInt);
}

void _serialize(string& strResult, vector<TreeNode*>* pVecRoot)
{
    if (!strResult.empty())
        strResult += strSplitRow;

    vector<TreeNode*>* pVecNextRoot = new vector<TreeNode*>;
    for (size_t i = 0; i < pVecRoot->size(); ++i)
    {
        TreeNode* pNode = pVecRoot->at(i);

        if (i > 0)
            strResult += strSplitNode;

        strResult += to_string(pNode->val);

        if (pNode->left)
        {
            pVecNextRoot->push_back(pNode->left);
            strResult += strHasValue;
        }
        else
        {
            strResult += strNoneValue;
        }

        if (pNode->right)
        {
            pVecNextRoot->push_back(pNode->right);
            strResult += strHasValue;
        }
        else
        {
            strResult += strNoneValue;
        }
    }

    if (pVecNextRoot->empty())
    {
        delete pVecNextRoot;
        // delete pVecRoot;
    }
    else
    {
        delete pVecRoot;
        pVecRoot = pVecNextRoot;

        _serialize(strResult, pVecRoot);
    }
}

string serialize(TreeNode* root)
{
    if (!root)
        return string();

    string             str;
    vector<TreeNode*>* pVecRoot = new vector<TreeNode*>;
    pVecRoot->push_back(root);

    _serialize(str, pVecRoot);

    delete pVecRoot;

    return str;
}

void _deserialize(const vector<string>& vecRow, int index, vector<TreeNode*>& vecLastNode)
{
    string strOneRowNode(vecRow.at(index));

    TreeNode*         pCurNode = nullptr;
    vector<TreeNode*> vecNextNode;

    vector<string> vecNode;
    boost_split_wrap(vecNode, strOneRowNode, strSplitNode);

    size_t iFindIndex = 0;
    for (const auto& strNode : vecNode)
    {
        int  iValue = -1;
        bool hasLeftValue(false), hasRightValue(false);
        AnalyzeNode(strNode, iValue, hasLeftValue, hasRightValue);

        // 上一层的子节点中找到当前节点
        for (; iFindIndex < vecLastNode.size(); ++iFindIndex)
        {
            TreeNode* pLastNodeTemp = vecLastNode.at(iFindIndex);
            if (pLastNodeTemp->left && pLastNodeTemp->left->val == UnKnownInt)
            {
                pCurNode = pLastNodeTemp->left;
                break;
            }

            if (pLastNodeTemp->right && pLastNodeTemp->right->val == UnKnownInt)
            {
                pCurNode = pLastNodeTemp->right;
                break;
            }
        }

        if (false) // 待优化查找起始处
            ++iFindIndex;

        if (!pCurNode)
            continue; // Error

        SetNode(pCurNode, iValue, hasLeftValue, hasRightValue);

        if (hasLeftValue || hasRightValue)
            vecNextNode.push_back(pCurNode);
    }

    if (!vecNextNode.empty())
    {
        // 此节点左右子树都已匹配过
        ++index;
        _deserialize(vecRow, index, vecNextNode);
    }
}

// 测试后记得释放
TreeNode* deserialize(string& data)
{
    if (data.empty())
        return nullptr;

    vector<string> vecRow;
    boost_split_wrap(vecRow, data, strSplitRow);

    int       index = 0;
    TreeNode* pRoot = NULL;
    {
        int  iValue = -1;
        bool hasLeftValue(false), hasRightValue(false);

        string strRoot(vecRow.at(index));
        AnalyzeNode(strRoot, iValue, hasLeftValue, hasRightValue);

        pRoot = new TreeNode(iValue);

        SetNode(pRoot, iValue, hasLeftValue, hasRightValue);
    }

    ++index;
    vector<TreeNode*> vecLastNode{pRoot};
    _deserialize(vecRow, index, vecLastNode);

    return pRoot;
}

void DestoryTree(TreeNode* pRoot)
{
    if (pRoot->left)
        delete pRoot->left;

    if (pRoot->right)
        delete pRoot->right;

    delete pRoot;
    pRoot = nullptr;
}

} // namespace BinaryTreeSerialize

//////////////////////////////////////////////////////////////////////////////////

void serialize(int)
{
    if (true)
    {
        return;
    }
    using namespace BinaryTreeSerialize;

    int index = 0;

    // 创建一棵树
    TreeNode* pRoot = new TreeNode(GetIndex(index));
    pRoot->left     = new TreeNode(GetIndex(index));
    pRoot->right    = new TreeNode(GetIndex(index));

    TreeNode* pL1 = pRoot->left;
    pL1->left     = new TreeNode(GetIndex(index));
    pL1->right    = new TreeNode(GetIndex(index));

    TreeNode* pR1 = pRoot->right;
    pR1->left     = new TreeNode(GetIndex(index));
    // pR1->right = new TreeNode(GetIndex(index));

    // 序列化
    string str = serialize(pRoot);

    // 反序列化
    TreeNode* pNewRoot = nullptr;
    pNewRoot           = deserialize(str);

    {
        // 再次序列化，比较字符串
        string strNew = serialize(pNewRoot);
    }

    // 销毁
    DestoryTree(pRoot);
    DestoryTree(pNewRoot);
}