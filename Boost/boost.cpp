#include "pch.h"

//#include <boost/thread.hpp>
//#include <boost/thread/future.hpp>

using namespace std;


void testPath()
{
	
}



///*
//*shared_ptr除了最基本的可以用new初始化以外，还可以使用其他方式初始化。在使用一些c的api时候，这种初始化方式非常有用，如下
//*boost::shared_ptr<CURL> curl_(curl_easy_init(), curl_easy_cleanup);
//*上面这段代码用来初始化一个curl的shared_ptr。
//*
//*/
//void test()
//{
//	// promise,future
//
//	boost::promise<int> pi;
//	boost::unique_future<int> fi;
//	fi = pi.get_future();
//	//等待2s，超时返回0，被promise被set返回1
//	cout << "wait over:" << fi.timed_wait(boost::posix_time::milliseconds(2000)) << endl;
//	//检查promise是否被set
//	cout << "is ready:" << fi.is_ready() << endl;
//
//	pi.set_value(42);
//	cout << "wait over:" << fi.timed_wait(boost::posix_time::milliseconds(2000)) << endl;
//	cout << "is ready:" << fi.is_ready() << endl;
//	cout << fi.get() << endl;
//
//}
//
//void testRegEx()
//{
//	// match
//	boost::regex r("(a*)ddd(b*)ddd");
//	boost::smatch m;
//	if (boost::regex_match(string("aaaadddbbbddd"), m, r))
//	{
//		cout << m.size() << endl;
//		for (size_t i = 0; i < m.size(); ++i)
//		{
//			//0表示匹配到的整个字符串，1以后的index表示括号中匹配的内容
//			cout << m[i] << endl;
//		}
//	}
//
//
//	// search
//	boost::regex r("(a+)");
//	string content = "bbbaaaaacccaaaaddddaaaeeeaaa";
//	boost::smatch m;
//	string::const_iterator strstart = content.begin();
//	string::const_iterator strend = content.end();
//	while (boost::regex_search(strstart, strend, m, r))
//	{
//		//search到的结果，0表示整个，1以后表示括号的index匹配的结果
//		cout << m[1] << endl;
//		//从上次搜索到的地方接着搜索
//		strstart = m[0].second;
//	}
//
//
//	// regex_token_iterator
//	boost::regex r("(a)c");
//	string content = "bbbaaaaacccaaaaddddaaaeeeaaa";
//	//第四个参数0表示匹配到的整个字符串，1以后表示括号中的index，-1表示匹配除了本字符串以外的，可以用来分割字符串
//	boost::sregex_token_iterator iter(content.begin(), content.end(), r, -1);
//	boost::sregex_token_iterator end;
//
//	for (; iter != end; ++iter)
//	{
//		cout << *iter << endl;
//	}
//
//
//	// regex_replace
//	class func {
//	public:
//		func(vector<string> vec) {
//			_vec = vec;
//			_index = 0;
//		}
//		string aaa(boost::match_results<std::string::const_iterator> match) {
//			string  aa = _vec[_index];
//			cout << _index << endl;
//			_index++;
//			cout << _index << endl;
//			return aa;
//		}
//	private:
//		vector<string> _vec;
//		int _index;
//	};
//
//	vector<string> test;
//	test.push_back("1");
//	test.push_back("2");
//	test.push_back("3");
//	test.push_back("4");
//	test.push_back("5");
//	test.push_back("6");
//	test.push_back("7");
//	std::string s = "a ? b ?b c? d? e?";
//	std::string b = "a ? b ?b c? d? e?";
//	std::cout << s << std::endl;
//	boost::regex reg("\\?");
//
//	func f(test);
//	boost::function<std::string(boost::match_results<std::string::const_iterator>)> function1 =
//		boost::bind(&func::aaa, &f, _1);
//	//替换s中的所有符合r的字符串
//	//第三个参数可以放一个函数对象或者boost::function类型，用来实现特殊逻辑
//	s = boost::regex_replace(s, reg, function1);
//	std::cout << s << std::endl;
//}