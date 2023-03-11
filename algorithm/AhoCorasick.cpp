#include "pch.h"
#include "AhoCorasick.h"

#include <assert.h>
#include <queue>

// AcTrieNode中保存了word才能打印
#ifdef NEED_ACTRIE_NODE_SELF_WORD
#    define TEST_AHO_CORASICK_PRINT
#endif

// 开启打印
#ifdef TEST_AHO_CORASICK_PRINT
#    include <iostream>
#endif

AcAutomata::~AcAutomata()
{
	if (root_)
		deleteNode(root_);
}
void AcAutomata::deleteNode(AcTrieNode* node)
{
	if (!node)
		return;

	if (node->next_) {
		AcTrieNode::NextMap::iterator it;
		for (it = node->next_->begin(); it != node->next_->end(); ++it) {
			deleteNode(it->second);
		}

		delete node->next_;
	}

	delete node;
}

const AcTrieNode* AcAutomata::find(const std::vector<AcTrieKey>& arr) const
{
	const AcTrieNode* pNode = root_;
	assert(pNode);

	AcTrieNode::NextMap::const_iterator citer;
	for (const auto& item : arr) {
		if (!pNode->next_)
			continue;

		if (citer = pNode->next_->find(item); citer == pNode->next_->end())
			continue;

		pNode = citer->second;
	}

	return pNode;
}

void AcAutomata::buildFailurePointer()
{
	assert(root_->next_);

	std::queue<AcTrieNode*> que;
	root_->fail_ = nullptr;

	for (AcTrieNode::NextMap::iterator iter = root_->next_->begin(); iter != root_->next_->end(); ++iter) {
		iter->second->fail_ = root_;
		que.push(iter->second);
	}

	AcTrieNode* back = nullptr;
	AcTrieNode::NextMap::iterator backiter;

	while (!que.empty()) {
		AcTrieNode* now = que.front();
		que.pop();

		if (now->next_ == nullptr)
			continue;

		for (AcTrieNode::NextMap::iterator iter = now->next_->begin(); iter != now->next_->end(); ++iter) {
			back = now->fail_;
			while (back != nullptr) {
				if (back->next_ && (backiter = back->next_->find(iter->first)) != back->next_->end()) {
					iter->second->fail_ = backiter->second;
					break;
				}
				back = back->fail_;
			}

			if (back == nullptr)
				iter->second->fail_ = root_;

			que.push(iter->second);
		}
	}
}

void AcAutomata::printFailurePointer()
{
#ifdef TEST_AHO_CORASICK_PRINT
	std::queue<AcTrieNode*> que;
	assert(root_->next_);

	for (AcTrieNode::NextMap::iterator iter = root_->next_->begin(); iter != root_->next_->end(); iter++) {
		que.push(iter->second);
	}

	while (!que.empty()) {
		AcTrieNode* now = que.front();
		que.pop();

		std::cout << now->word_;

		if (now->fail_ == nullptr)
			continue;
		else
			std::cout << "| fail_ word_:" << now->fail_->word_ << std::endl;

		if (now->next_ == nullptr) {
			continue;
		}

		for (AcTrieNode::NextMap::iterator iter = now->next_->begin(); iter != now->next_->end(); iter++) {
			que.push(iter->second);
		}
	}
#endif  // TEST_AHO_CORASICK_PRINT
}

void AcAutomata::insertNode(const std::vector<AcTrieKey>& arr)
{
	int                                 len = 0;
	AcTrieNode* pNode = root_;
	AcTrieNode::NextMap::const_iterator kmIter;

	for (const auto& code : arr) {
		if (nullptr == pNode->next_) {
			pNode->next_ = new AcTrieNode::NextMap;
		}

		kmIter = pNode->next_->find(code);
		len += calcUnicodeLen(code);

		if (kmIter == pNode->next_->end()) {
			AcTrieNode* nextNode = new AcTrieNode;
#ifdef NEED_ACTRIE_NODE_SELF_WORD
			nextNode->word_ = (code);
#endif

			(*pNode->next_)[code] = nextNode;
			pNode = nextNode;
		}
		else {
			pNode = kmIter->second;
		}
	}

	pNode->isEnding_ = true;
	pNode->length_ = len;
}

std::string AcAutomata::replace(const std::vector<AcTrieKey>& arr, std::string text, char strReplace)
{
	std::unordered_map<int, int> matched;
	match(arr, matched);

	for (const auto& item : matched) {
		text.replace(item.first, item.second, item.second, strReplace);
	}
	return text;
}

void AcAutomata::match(const std::vector<AcTrieKey>& arr, std::unordered_map<int, int>& matched)
{
	if (!root_ || !root_->next_)  // 没有初始化
		return;

	int         index = 0;
	AcTrieNode* pNode = root_;

	for (const auto& code : arr) {
		/**
		 * 使用 fail_指针对 p的值进行矫正
		 * 比如查询到某个模式串, p 值不是指向root. 然后主串继续遍历，主串的值在p上匹配不到值，需要fail_指针把p指向root
		 */
		while (pNode != nullptr && pNode != root_ && pNode->next_ != nullptr &&
			pNode->next_->find(code) == pNode->next_->end()) {
			pNode = pNode->fail_;  // 失败指针发挥作用的地方
		}

		if (pNode != nullptr && pNode->next_ != nullptr) {
			if (auto it = pNode->next_->find(code); it != pNode->next_->end())
				pNode = it->second;
		}
		else {
			pNode = nullptr;
		}

		if (pNode == nullptr) {
			pNode = root_;  // 没有匹配，从root开始重新匹配
			if (auto it = pNode->next_->find(code); it != pNode->next_->end())
				pNode = it->second;
		}

		AcTrieNode* tmp = pNode;
		int         len = calcUnicodeLen(code);
		while (tmp != nullptr && tmp != root_) {
			if (tmp->isEnding_) {
				matched[index - tmp->length_ + len] = tmp->length_;
			}
			tmp = tmp->fail_;
		}

		index += len;
	}
}

int AcAutomata::calcUnicodeLen(AcTrieKey code)
{
	if (code <= 0x7f)
		return 1;
	else if (code <= 0x7ff)
		return 2;
	else
		return 3;
}
