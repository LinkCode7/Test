#include "pch.h"
#include <boost/algorithm/string.hpp>
//#include <boost/algorithm/string/split.hpp>

using namespace boost;
using namespace std;



void testSuffix(string name,const string& suffix)
{
	if (ends_with(name, suffix))
		cout << "yes" << endl;
	else
		cout << "no" << endl;
}


////////////////////////////////////////////////////////////

void boost_string()
{
	// 1
	testSuffix("name.txt",".txt");
	testSuffix("name..txt", ".txt");
	testSuffix("name.txt.txt", ".txt");
	testSuffix(".txt", ".txt");
	//complex c;
	// key explicit


}