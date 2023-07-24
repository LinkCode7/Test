#ifdef TEST_BOOST_RTREE
    #include <boost/algorithm/string.hpp>

using namespace boost;

TEST(boost_string, ends_with)
{
    assert(ends_with("name.txt", ".txt"));
    assert(ends_with("name..txt", ".txt"));
    assert(ends_with("name.txt.txt", ".txt"));
    assert(ends_with(".txt", ".txt"));
}
#endif // TEST_BOOST_RTREE