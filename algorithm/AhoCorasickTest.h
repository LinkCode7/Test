#ifndef TEST_AHO_CORASICK_H
#define TEST_AHO_CORASICK_H

#include <functional>
#include <string>
#include <vector>

typedef size_t SkUnichar;

class TestCodePointInfo;
class TestSchemaCodePointInfo;
class AcAutomata;

class TestCodePoint
{
public:
	void entry();

private:
	void initSchemaList();
	void getEmojiList(std::vector<std::string>& arrPng);
	int  hexStringToInt(std::string& str) { return std::stoi(str.c_str(), nullptr, 16); }

	void initMainContents();
	void initContents(std::vector<std::string>& arrInfo);

	int _testBF(std::shared_ptr<TestCodePointInfo> pContents);
	int _testAC(AcAutomata& acMata, std::shared_ptr<TestCodePointInfo> pContents);

	std::string schemaFind(SkUnichar code);

private:
	std::vector<std::shared_ptr<TestCodePointInfo>>       m_contents;  // 主串
	std::vector<std::shared_ptr<TestSchemaCodePointInfo>> m_schema;    // 模式串
};

const size_t           EMPTY_INDEX = std::numeric_limits<size_t>::max();

template <typename T>
struct BasicRange {
	BasicRange() : start(EMPTY_INDEX), end(EMPTY_INDEX) {}
	BasicRange(T s, T e) : start(s), end(e) {}

	T start, end;

	bool operator==(const BasicRange<T>& other) const { return start == other.start && end == other.end; }
	bool operator!=(const BasicRange<T>& other) const { return !this->operator==(other); }

	T width() const { return end - start; }

	void Shift(T delta)
	{
		start += delta;
		end += delta;
	}

	bool contains(BasicRange<size_t> other) const { return start <= other.start && end >= other.end; }

	bool intersects(BasicRange<size_t> other) const { return std::max(start, other.start) <= std::min(end, other.end); }

	BasicRange<size_t> intersection(BasicRange<size_t> other) const
	{
		return BasicRange<size_t>(std::max(start, other.start), std::min(end, other.end));
	}

	bool empty() const { return start == EMPTY_INDEX && end == EMPTY_INDEX; }

	size_t getBytesUsed() const { return sizeof(T) * 2; }
};

const BasicRange<size_t> EMPTY_RANGE = BasicRange<size_t>(EMPTY_INDEX, EMPTY_INDEX);

using TextIndex = size_t;
using TextRange = BasicRange<TextIndex>;

class TestSchemaCodePointInfo
{
public:
	std::string            m_strUtf8;
	std::vector<SkUnichar> m_codePoints;
};
using TestSchemaCodePointInfoSp = std::shared_ptr<TestSchemaCodePointInfo>;

class TestCodePointInfo
{
public:
	std::string                                  m_strUtf8;
	std::vector<std::pair<SkUnichar, TextRange>> m_codePoints;

	TestCodePointInfo() {}
	TestCodePointInfo(const TestCodePointInfo& other)
	{
		m_strUtf8 = other.m_strUtf8;

		m_codePoints.reserve(other.m_codePoints.size());
		for (const auto& item : other.m_codePoints) {
			m_codePoints.emplace_back(std::make_pair(item.first, item.second));
		}
	}
};
using TestCodePointInfoSp = std::shared_ptr<TestCodePointInfo>;

#endif  // !TEST_AHO_CORASICK_H
