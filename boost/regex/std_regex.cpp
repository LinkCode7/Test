#include "pch.h"
#include <regex>

/*
* std::regex与boost的不同处?
*/

using namespace std;

std::string my_callback(const std::smatch& m)
{
	int int_m = atoi(m.str(0).c_str());
	return std::to_string(int_m + 1);
}

void stl_formater()
{
	char str[] = "*Link*||+Mario+||Zelda!!!||Metroid";
	//regex reg("\\w+", std::regex::icase);

	//cout << regex_replace(str, reg, my_callback) << endl;

	//cout << std::regex_replace("my values are 9, 19", regex("\\d+"), my_callback) << endl;
}

void std_regex()
{
	stl_formater();

	if (false)
	{
		std::string text = "Quick brown fox";
		std::regex vowel_re("a|e|i|o|u");

		// write the results to an output iterator
		std::regex_replace(std::ostreambuf_iterator<char>(std::cout),
			text.begin(), text.end(), vowel_re, "*");

		// construct a string holding the results
		std::cout << '\n' << std::regex_replace(text, vowel_re, "[$&]") << '\n';

		//std::regex_replace(text, vowel_re, my_callback);
	}
}