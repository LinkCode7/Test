#pragma once

//#include <atlstr.h>
//#include <boost/tokenizer.hpp>

template <typename T>
inline std::string join(const T& target, const std::string& join_char)
{
	std::string strRet;
	for (T::const_iterator itr = target.begin(); itr != target.end(); ++itr)
	{
		if (itr != target.begin())
			strRet.Append(join_char);

		strRet.Append(ToString(*itr));
	}

	return strRet;
}




// STL±ê×¼ÈÝÆ÷
template<typename Container>
std::string GetString(const Container& c, const std::string& strSplit = ";", bool isCheckEmpty = true)
{
	std::string str;
	Container::const_iterator iter = c.begin();
	for (; iter != c.end(); ++iter)
	{
		std::string strAdd(std::to_string(*iter));

		if (isCheckEmpty && strAdd.IsEmpty())
			continue;

		if (str.length() > 0)
			str += strSplit;

		str += strAdd;
	}

	return str;
}