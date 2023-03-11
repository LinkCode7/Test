#include "pch.h"
#ifdef TEST_BOOST_RTREE

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/progress.hpp>
//#include <boost/timer/timer.hpp>
//#include <boost/timer/progress_display.hpp>

using namespace std;
using namespace boost;

std::string FindFile(const std::string& strDir, const std::string& strFile);
bool FindFileRegex(const std::string& strDir, const std::string& strRegex, std::map<std::string, std::vector<std::string>>& mapPath2Files);
std::string FindFileOnePath(const std::string& strDir, const std::string& strFile);

void FileSystemSearchDirectory()
{
	return;

	boost::filesystem::path path("C:\\Users\\Administrator\\Desktop\\7");

	auto strDir = FindFile(path.string(), "醉小城.doc");

	// filesystem抛出异常，可能是遇到系统不允许访问的文件，std::filesystem可以忽略异常
	// https://stackoverflow.com/questions/52318249/the-stdfilesystemrecursive-directory-iterator-exception
	//for (auto& el : std::filesystem::recursive_directory_iterator(dir, std::filesystem::directory_options::skip_permission_denied))
	//{
	//	std::cout << el.path() << '\n';
	//}

	std::map<std::string, std::vector<std::string>> mapPath2Files;
	{
		boost::progress_timer t;
		FindFileRegex("C:\\Users\\Administrator\\Desktop\\新建文件夹", ".*\\.txt$", mapPath2Files);
	}
}

std::string FindFile(const std::string& strDir, const std::string& strFile)
{
	namespace bf = boost::filesystem;

	if (!bf::exists(strDir) || !bf::is_directory(strDir))
		return std::string();

	typedef bf::recursive_directory_iterator fd_iterator;

	fd_iterator end;

	// 遍历目录下的文件
	for (fd_iterator pos(strDir); pos != end; ++pos)
	{
		cout << pos->path() << endl;
		if (!bf::is_directory(*pos) && strFile == pos->path().filename())
		{
			return pos->path().parent_path().string();
		}
	}

	return std::string();
}

bool FindFileRegex(const std::string& strDir, const std::string& strRegex, std::map<std::string, std::vector<std::string>>& mapPath2Files)
{
	namespace bf = boost::filesystem;

	if (!bf::exists(strDir) || !bf::is_directory(strDir))
		return false;

	typedef bf::recursive_directory_iterator fd_iterator;

	fd_iterator end;

	boost::smatch what;
	boost::regex reg(strRegex);

	// 遍历目录下的文件
	//for (auto& el : std::filesystem::recursive_directory_iterator(dir, std::filesystem::directory_options::skip_permission_denied))

	for (fd_iterator pos(strDir, bf::symlink_option::_detail_no_push); pos != end; ++pos)
	{
		if (!bf::is_directory(*pos))
		{
			bf::path pa = pos->path();

			//if (boost::regex_match(pa.filename().string(), what, reg))
			if (pa.filename().string().find(".txt") != std::string::npos)
			{
				string strPath(pa.parent_path().string());

				auto iter = mapPath2Files.find(strPath);
				if (iter == mapPath2Files.end())
				{
					std::vector<string> vec{ pa.filename().string() };
					mapPath2Files[strPath] = vec;
				}
				else
				{
					iter->second.push_back(pa.filename().string());
				}

				cout << strPath << endl;
			}
		}
	}

	return !mapPath2Files.empty();
}

std::string FindFileOnePath(const std::string& strDir, const std::string& strFile)
{
	namespace bf = boost::filesystem;

	if (!bf::exists(strDir) || !bf::is_directory(strDir))
		return "";

	typedef bf::recursive_directory_iterator fd_iterator;

	fd_iterator end;

	// 遍历目录下的文件
	for (fd_iterator pos(strDir); pos != end; ++pos)
	{
		cout << pos->path() << endl;
		if (bf::is_directory(*pos))
		{
			// 不遍历其子目录
			pos.no_push();
		}

		if (strFile == pos->path().filename())
		{
			return pos->path().parent_path().string();
		}
	}

	return std::string();
}
#endif // TEST_BOOST_RTREE