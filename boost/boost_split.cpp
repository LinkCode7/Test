#ifdef TEST_BOOST_RTREE

    #include "boost_split.h"

    #include <boost/algorithm/string.hpp>
//#include <boost/algorithm/string/split.hpp>

using namespace boost;

TEST(boost_split, split)
{
    std::string str1("234	kl	j9	111");
    // string str2("009	pl	oo	222");
    std::vector<std::string> vectorResult;

    boost::split(vectorResult, str1, boost::is_any_of("	") /*, boost::token_compress_on*/);
    // boost::split(vectorResult, str2, boost::is_any_of("	")/*, boost::token_compress_on*/);
}

void boost_split_wrap(std::vector<std::string>& vecResult, const std::string& strSource, const std::string& strSplit)
{
    boost::split(vecResult, strSource, boost::is_any_of(strSplit));
}
#endif // TEST_BOOST_RTREE