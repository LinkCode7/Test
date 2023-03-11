#pragma once
//#include <functional>


// 注意：这里使用的是min-heap，编译器默认的是max-heap
// 所有_heap函数要传第三个参数：std::greater<>()


// 可以将这个类写成模板类，将m_iKey、m_iValue泛化
class LFUCache
{
public:
	class Node
	{
	public:
		int m_iWeight;

		int m_iKey;
		int m_iValue;

		Node(int iKey, int iValue) :m_iWeight(0), m_iKey(iKey), m_iValue(iValue) {}

		bool operator<(const Node& other) { return m_iWeight < other.m_iWeight; }
		bool operator>(const Node& other) { return m_iWeight > other.m_iWeight; }
	};

	std::vector<Node> m_vec;
	int m_capacity;

public:

	LFUCache(int capacity):m_capacity(capacity) {}

	void set(int key, int value)
	{
		int iSize = static_cast<int>(m_vec.size());

		if (iSize < 3 && iSize < m_capacity)
		{
			m_vec.push_back(Node(key, value));
			std::make_heap(m_vec.begin(), m_vec.end(), std::greater<>());
			return;
		}

		if (iSize < m_capacity - 1)
		{
			m_vec.push_back(Node(key, value));
			push_heap(m_vec.begin(), m_vec.end(), std::greater<>());
		}
		else
		{
			pop_heap(m_vec.begin(), m_vec.end(), std::greater<>());
			m_vec.pop_back();

			m_vec.push_back(Node(key, value));
			push_heap(m_vec.begin(), m_vec.end(), std::greater<>());
		}
	}

	int get(int key)
	{
		for (auto& node : m_vec)
		{
			if (node.m_iKey == key)
			{
				node.m_iWeight++;
				int iValue = node.m_iValue;

				make_heap(m_vec.begin(), m_vec.end(), std::greater<>());
				return iValue;
			}
		}

		return -1;
	}
};







void Exception();


void WrongAnswer();