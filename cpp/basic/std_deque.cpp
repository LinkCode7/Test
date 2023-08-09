#include <deque>
/*
 * @brief 双端队列，可以在常数时间复杂度内完成对两端的插入、删除工作
 * @detail vector是单向开口的连续线性空间，deque则是双向开口的连续线性空间
 */
using std::deque;

TEST(std_deque, access)
{
    deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_front(0);
}
