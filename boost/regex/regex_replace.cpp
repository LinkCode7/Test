#ifdef TEST_BOOST_RTREE
    #include <boost/algorithm/string.hpp>
    #include <boost/regex.hpp>
    #include <boost/xpressive/xpressive.hpp>

    #pragma warning(disable : 4996)

using namespace std;

struct Formater
{
    std::string operator()(boost::cmatch const& m) const;
};

void replace()
{
    // 问号(?)表示之前的可以选择
    string       phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})";
    boost::regex rule(phone);
    // 代替
    string fmt("$2.$5.$7");
    string number("(908)555-1800");
    cout << regex_replace(number, rule, fmt) << std::endl;

    string strSource("Caroline (201)555-2368 862-55-0123");
    cout << boost::regex_replace(strSource, rule, fmt) << std::endl;
    cout << boost::regex_replace(strSource, rule, fmt, boost::regex_constants::format_no_copy) << std::endl;

    // 匹配位置
    boost::regex sourceRegex(string("(?![a-zA-Z])")); // "(?=al)" 匹配位置，al前面;"(?![a-zA-Z])" 匹配字母后面位置
    string       targetRegex("@");                    // "$0(字母)" $0取到结果集中的第一个(即匹配项)

    string strInput("al*alaol");
    auto   result1 = regex_replace(strInput, sourceRegex, targetRegex);
}

// 环视
void LookAround()
{
    // string strResult;
    // string re;
    // back_insert_iterator<string> it(re);
    // it = boost::regex_replace(std::back_inserter(strResult), str.begin(), str.end(), reg, "$0,");

    boost::regex reg("(\\d)(?=(\\d\\d\\d)+(?!\\d))");
    string       str    = "The population of 298444215 is growing";
    string       strend = regex_replace(str, reg, "$`");
    // 匹配位置前的$` 匹配位置后的$´

    boost::regex reg1("(\\d)((\\d\\d\\d)+\\b)");
    string       str1    = "The population of 298444215 is growing";
    string       strend1 = regex_replace(str1, reg1, "$1,$2");
}

// 引用正则表达式匹配的子表达式
void UseReferenceIndex()
{
    using namespace boost::xpressive;
    string strTxt("readme.txt");
    sregex reg1 = sregex::compile("(.*)(me)");
    sregex reg2 = sregex::compile("(t)(.)(t)");

    cout << regex_replace(strTxt, reg1, "manual") << endl;
    cout << regex_replace(strTxt, reg1, "$1you") << endl;
    cout << regex_replace(strTxt, reg1, "$&$&") << endl;

    /// cout << regex_replace(strTxt, reg2, "$0A") << endl; // 从1开始
    cout << regex_replace(strTxt, reg2, "$1N$3") << endl;
    cout << regex_replace(strTxt, reg2, "$1$3") << endl;

    cout << strTxt << endl;
}

// 正则分词，split
void regex_token_iterator()
{
    using namespace boost::xpressive;

    char str[] = "*Link*||+Mario+||Zelda!!!||Metroid";

    cregex reg = cregex::compile("\\w+", icase);

    cregex_token_iterator end;
    cregex_token_iterator pos(str, str + strlen(str), reg);

    // for (; pos != cregex_token_iterator(); ++pos)
    for (; pos != end; ++pos)
    {
        cout << "[" << *pos << "] ";
    }
    cout << endl << endl;

    cregex split_reg = cregex::compile("\\|\\|");
    pos              = cregex_token_iterator(str, str + strlen(str), split_reg, -1);

    for (; pos != end; ++pos)
    {
        cout << "[" << *pos << "] ";
    }
}

// 自定义replace结果的处理函数
void formater()
{
    using namespace boost::xpressive;

    char   str[] = "*Link*||+Mario+||Zelda!!!||Metroid";
    cregex reg   = cregex::compile("\\w+", icase);

    // cout << regex_replace(str, reg, my_callback) << endl;
}

void regex_replace()
{
    LookAround();

    UseReferenceIndex();

    regex_token_iterator();

    formater();
}

std::string Formater::operator()(boost::cmatch const& m) const
{
    return boost::to_upper_copy(m[0].str());
}
#endif // TEST_BOOST_RTREE