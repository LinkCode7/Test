#ifdef TEST_BOOST_RTREE

    #include <stdlib.h>

    #include <boost/regex.hpp>
//#include <boost/algorithm/string.hpp>
//#include <boost/algorithm/string/split.hpp>

    #pragma warning(disable : 4267)

using namespace std;
using namespace boost;

//#include <regex>
void match()
{
    /*boost::regex reg("a,\g");
    string strResult;
    match_flag_type flags = match_any;
    auto result1 = boost::regex_match(string("a,jkla,"), strResult, reg);*/

    std::string str = "192.168.1.1";

    boost::regex  expression("([0-9]+).([0-9]+).([0-9]+)");
    boost::smatch what;

    if (boost::regex_search(str, what, expression))
    {
        std::cout << what.size() << std::endl;
        for (size_t i = 0; i < what.size(); ++i)
        {
            if (what[i].matched)
                std::cout << what[i] << std::endl;
        }
    }
}

void matchUser()
{
    // string* msg(NULL);
    // regex expression("([^\[][a-zA-Z]\>)");
    // cmatch what;
    // if (regex_match("", what, expression))
    //{
    //	// what[0] contains the whole string
    //	// what[1] contains the response code
    //	// what[2] contains the separator character
    //	// what[3] contains the text message.
    //	if (msg)
    //		msg->assign(what[3].first, what[3].second);
    //	atoi(what[1].first);
    //}
    //// failure did not match
    // if (msg)
    //	msg->erase();
}
#endif // TEST_BOOST_RTREE