#pragma once
#include <boost/filesystem.hpp>

// µü´úÄ¿Â¼




std::string FindFile(const std::string& strDir, const std::string& strFile);

bool FindFileRegex(const std::string& strDir, const std::string& strRegex, std::map<std::string, std::vector<std::string>>& mapPath2Files);

std::string FindFileOnePath(const std::string& strDir, const std::string& strFile);