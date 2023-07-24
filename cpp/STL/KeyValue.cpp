
using namespace std;

void TestPairCompare()
{
    pair<int, int> p1 = make_pair(1, 1);
    pair<int, int> p2 = make_pair(1, 2);

    if (p1 == p2)
    {
        cout << "std::pair只比较First" << endl;
    }
    else
    {
        cout << "std::pair比较First、Second" << endl; //
    }
}

// std::find是用来查找容器元素算法，但是它只能查找容器元素为基本数据类型，
// 如果想要查找类类型，应该使用find_if.STL算法的一个版本采用缺省的运算行为，该算法的另一个版本提供额外参数，接收外界传入的一个仿函数（functor），以便采用其他策略。
// 可以采用其他策略的算法通常是以_if作为尾词，例如find_if(), replace_if().
//
// 与此类似的，质变算法（改变操作区间内元素的值）分为in - place（就地计算）和copy（将对象内容拷贝一份副本，在副本上运算完毕后返回）版，
// copy版总是以_copy作为函数名称尾词。