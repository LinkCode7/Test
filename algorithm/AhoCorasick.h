#ifndef AHO_CORASICK_H
#define AHO_CORASICK_H

#include <string>
#include <unordered_map>
#include <vector>

using AcTrieKey = size_t;
using UnicodeValueType = uint32_t;

// AcTrieNode是否需要保存word
#define NEED_ACTRIE_NODE_SELF_WORD

class AcTrieNode
{
public:
	using NextMap = std::unordered_map<AcTrieKey, AcTrieNode*>;

	AcTrieNode* fail_;      // 失败指针，类似KMP算法的next数组
	NextMap* next_;      // 多叉树结构
	bool        isEnding_;  // 结尾字符为true
	int         length_;    // 字素的字节长度

#ifdef NEED_ACTRIE_NODE_SELF_WORD
	UnicodeValueType word_;
#endif

public:
#ifdef NEED_ACTRIE_NODE_SELF_WORD
	AcTrieNode() : fail_(nullptr), next_(nullptr), word_(0), isEnding_(false), length_(-1) {}
#else
	AcTrieNode() : fail_(nullptr), next_(nullptr), isEnding_(false), length_(-1) {}
#endif

	const AcTrieNode* findNext(AcTrieKey key) const
	{
		if (next_ == nullptr)
			return nullptr;

		NextMap::const_iterator iter = next_->find(key);
		if (iter == next_->end())
			return nullptr;

		return iter->second;
	}
};

// AC自动机
class AcAutomata
{
	AcTrieNode* root_;

public:
	~AcAutomata();
	AcAutomata() : root_(new AcTrieNode) {}
	void deleteNode(AcTrieNode* node);

public:
	// 创建trie树
	void insertNode(const std::vector<AcTrieKey>& arr);

	// 失败指针
	void buildFailurePointer();
	void printFailurePointer();

	// 多模式串匹配算法
	void match(const std::vector<AcTrieKey>& arr, std::unordered_map<int, int>& matched);
	// 经典案例：敏感词替换
	std::string replace(const std::vector<AcTrieKey>& arr, std::string text, char strReplace);

	const AcTrieNode* find(const std::vector<AcTrieKey>& arr) const;

private:
	int calcUnicodeLen(AcTrieKey code);
};

#endif  // !AHO_CORASICK_H
