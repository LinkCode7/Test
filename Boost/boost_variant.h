#pragma once
#include <boost/variant/static_visitor.hpp>




void boost_variant();



void boost_variant2();

void boost_variant_visitor();




struct var_double_print :public boost::static_visitor<>
{
	// Ä£°å²ÎÊý
	template<typename T>
	void operator()(T& t) const
	{
		t *= 2;
		std::cout << t << std::endl;
	}

	void operator()(std::vector<int>& vec) const;
};