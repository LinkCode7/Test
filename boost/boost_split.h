#pragma once

#ifdef TEST_BOOST_RTREE

void boost_split_wrap(std::vector<std::string>& vecResult, const std::string& strSource, const std::string& strSplit);

#else

void boost_split_wrap(std::vector<std::string>& vecResult, const std::string& strSource, const std::string& strSplit) {}

#endif // TEST_BOOST_RTREE