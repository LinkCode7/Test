#include "pch.h"
using namespace std;


struct Node
{
	int m_count;
	Node* m_next;

	Node(int c) :m_count(c), m_next(nullptr) {}
};


class MyLink
{
	Node* m_head;
	Node* m_tail;
public:

	MyLink() :m_head(nullptr), m_tail(nullptr) {}

	bool addNode(Node* node)
	{
		if (!node) return false;

		if (!m_head)
		{// 添加第一个节点
			m_head = node;
			m_tail = m_head;
			m_tail->m_next = nullptr;
		}
		else
		{
			m_tail->m_next = node;
			m_tail->m_next->m_next = nullptr;
			m_tail = node; // 记得调整尾指针
		}
		return true;
	}
	void print()
	{
		Node* p = m_head;
		while (p)
		{
			printf("%d	", p->m_count);
			p = p->m_next;
		}
		printf("\n");
	}

	void reverseNode()
	{// 不使用m_tail

	 // 链表为空或者只有一个节点
		if (!m_head || !m_head->m_next) return;

		Node* pre = nullptr;
		Node* p = m_head;
		Node* q = m_head->m_next;
		while (p->m_next)
		{
			p->m_next = pre;
			pre = p;
			p = q;
			q = p->m_next;
		}	
		p->m_next = pre;

		// Key：逆序思路的关键，每一个节点的next指向前一个节点
		// 最后让返回的头指针指向：原始顺序的最后一个节点
		// 原始顺序：1 -> 2 -> 3 -> 4，head -> 1
		// 逆序思路：1 <- 2 <- 3 <- 4，最后让 head 指向 4
		m_head = p;
	}

	~MyLink()
	{
		while (m_head)
		{// 释放所有节点所占的内存
			Node* p = m_head->m_next;
			delete[]m_head;
			m_head = p;
		}
	}
};

/////////////////////////////////////////////////////////////////
void oneWayLinkedList()
{
	MyLink link;
	for (int i = 0; i < 10; ++i)
	{
		// 必须申请堆上内存，否则临时变量释放后指针指向的地址变成未知
		Node* node = new Node(i);
		link.addNode(node);
	}

	link.print();
	link.reverseNode();
	link.print();
}