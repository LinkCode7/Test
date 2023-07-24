#ifdef TEST_BOOST_RTREE
    #include <boost/random.hpp>

using namespace std;
using namespace boost;

    #pragma warning(disable : 4244)

// 随机数发生器
TEST(boost_random, random_generator)
{
    // 设定范围
    mt19937 rng(500);

    cout << mt19937::min() << "<->" << mt19937::max() << endl;

    // 产生100个随机数
    for (int i = 0; i < 100; ++i)
    {
        cout << rng() << endl;
    }

    // 去掉5个
    rng.discard(5);

    // 填充容器
    vector<int> vec(10);
    rng.generate(vec.begin(), vec.end());
}

// 随机数分布器
TEST(boost_random, random_distribution)
{
    mt19937 rng(time(0));

    cout << endl << "--------------uniform_int_distribution--------------" << endl;
    random::uniform_int_distribution<> ui(0, 255);

    for (int i = 0; i < 10; ++i)
    {
        cout << ui(rng) << ",";
    }
    assert(ui.a() == 0 && ui.b() == 255);

    cout << endl << "--------------uniform_01--------------" << endl;
    uniform_01<> u01;
    for (int j = 0; j < 10; ++j)
    {
        cout << u01(rng) << ",";
    }

    cout << endl << "--------------normal_distribution--------------" << endl;
    normal_distribution<> nd(1, 2);

    int iCount = 0;
    for (int k = 0; k < 10000; ++k)
    {
        if (abs(nd(rng) - 1) <= 2.0)
            ++iCount;
    }

    cout << endl << endl;
    cout << 1.0 * iCount / 10000 << endl;
}
#endif // TEST_BOOST_RTREE