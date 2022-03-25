#pragma once








class TreeNode
{
 public:
	int val;
	TreeNode *left, *right;


	TreeNode(int val)
	{
		this->val = val;
		this->left = this->right = nullptr;
	}
};


// This is the interface that allows for creating nested lists.
// You should not implement it, or speculate about its implementation
class NestedInteger
{
public:
	// Return true if this NestedInteger holds a single integer,
	// rather than a nested list.
	bool isInteger() const { return false; }

	// Return the single integer that this NestedInteger holds,
	// if it holds a single integer
	// The result is undefined if this NestedInteger holds a nested list
	int getInteger() const { return false; }

	// Return the nested list that this NestedInteger holds,
	// if it holds a nested list
	// The result is undefined if this NestedInteger holds a single integer
	std::vector<NestedInteger> getList() const { return std::vector<NestedInteger>(); }
	// const std::vector<NestedInteger> &getList() const;
};