#pragma once






namespace BinaryTreeSerialize
{
	class TreeNode
	{
	public:
		int val;
		TreeNode *left, *right;

		TreeNode(int val)
		{
			this->val = val;
			this->left = this->right = NULL;
		}
	};




	

	void _serialize(std::string& strResult, std::vector<TreeNode*>* pVecRoot);
	std::string serialize(TreeNode* root);


	void AnalyzeNode(const std::string& str, int& iValue, bool& hasLeftNode, bool& hasRightNode);
	void SetNode(TreeNode* pNode, int iValue, bool hasLeftValue, bool hasRightValue);
	void _deserialize(const std::vector<std::string>& vecRow, int index, std::vector<TreeNode*>& vecLastNode);

	// ���Ժ�ǵ��ͷ�
	TreeNode * deserialize(std::string &data);


	int GetIndex(int& index)
	{
		int iTemp = index;
		++index;
		return iTemp;
	}

	void DestoryTree(TreeNode* pRoot);

} // namespace BinaryTreeSerialize