#pragma once
#include <boost/regex.hpp>

#include <boost/xpressive/xpressive.hpp>
#include <boost/algorithm/string.hpp>



// ¸ñÊ½»¯Æ÷
struct Formater
{
	std::string operator()(boost::cmatch const & m) const;
};