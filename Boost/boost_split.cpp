#include "pch.h"
#include <boost/algorithm/string.hpp>
//#include <boost/algorithm/string/split.hpp>


using namespace boost;
using namespace std;






void SimpleSplit(vector<string>& vecResult, const string& strSource, const string& strSplit)
{
	boost::split(vecResult, strSource, boost::is_any_of(strSplit));
}

///////////////////////////////////////////////////////////////////////

void boost_split()
{
	string str1("234	kl	j9	111");
	//string str2("009	pl	oo	222");
	vector<string> vectorResult;

	boost::split(vectorResult, str1, boost::is_any_of("	")/*, boost::token_compress_on*/);
	//boost::split(vectorResult, str2, boost::is_any_of("	")/*, boost::token_compress_on*/);
}