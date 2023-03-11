#include "pch.h"

#ifdef TEST_BOOST_RTREE
#include <boost/filesystem.hpp>
#include <boost/ratio.hpp>

//using namespace std;
using namespace boost;

#pragma warning(disable:4566) // "a•w"

/*
is_directory
is_regular_file
exists
is_other
is_symlink
*/

bool check(const boost::filesystem::path& pathDir, const boost::filesystem::path& pathFile);
void info(const boost::filesystem::path& pathDir, const boost::filesystem::path& pathFile);
void change(boost::filesystem::path& pathDir, boost::filesystem::path& pathFile);
void FileStatus(const boost::filesystem::path& pathDir, const boost::filesystem::path& pathFile);
void property(const boost::filesystem::path& pathDir, const boost::filesystem::path& pathFile);
void file_operator();

void test20230311()
{
	if (ispunct(_T('•')))
	{
		std::cout << std::endl;
	}
	if (!filesystem::windows_name("a•w"))
	{
		std::cout << std::endl;
	}
}

void boost_filesystem()
{
	test20230311();
	return;

	// 判断文件是否存在: "\\" is must
	filesystem::path pathDir("C:\\Users\\Administrator\\Desktop\\7");
	filesystem::path pathFile("C:\\Users\\Administrator\\Desktop\\Test.ini");

	if (!check(pathDir, pathFile))
		return;

	info(pathDir, pathFile);

	change(pathDir, pathFile);

	FileStatus(pathDir, pathFile);

	property(pathDir, pathFile);

	file_operator();

	// Windows:		Shlwapi.h: PathIsDirectory(path)
}

bool check(const filesystem::path& pathDir, const filesystem::path& pathFile)
{
	// 是不是目录
	if (!filesystem::is_directory(pathDir))
		return false;

	// 是不是普通文件
	if (!filesystem::is_regular_file(pathFile))
		return false;

	// 是否存在
	if (!filesystem::exists(pathDir))
		return false;

	if (!filesystem::exists(pathFile))
		return false;

	// 判断文件名是否符合Windows规范，不允许"<>?:|/\"
	if (!filesystem::windows_name(pathFile.filename().string()))
		return false;

	return true;
}

void info(const filesystem::path& pathDir, const filesystem::path& pathFile)
{
	std::cout << pathDir.string() << std::endl;
	std::cout << pathFile.c_str() << std::endl;

	// 返回path对象
	std::cout << pathDir.parent_path() << std::endl;
	std::cout << pathFile.stem() << std::endl; // 不含扩展名的文件名
	std::cout << pathDir.stem() << std::endl; // 最里层的目录名

	std::cout << pathDir.has_filename() << std::endl; // true?
	std::cout << pathFile.has_filename() << std::endl;

	std::cout << pathFile.has_parent_path() << std::endl;
	std::cout << pathFile.filename() << std::endl; // 带后缀的文件名

	std::cout << pathFile.extension() << std::endl; // 后缀名
	std::cout << pathDir.extension() << std::endl;

	std::cout << pathDir.root_name() << std::endl; // C:
	std::cout << pathDir.root_directory() << std::endl;
	std::cout << pathDir.root_path() << std::endl; // 根目录的路径 C:\

	// 相对路径
	std::cout << pathDir.relative_path() << std::endl;

	bool isAbsolute = system_complete(pathDir).is_absolute();
}

void change(filesystem::path& pathDir, filesystem::path& pathFile)
{
	filesystem::path path("C:\\Users\\Administrator\\Desktop");
	path.append("7\\Test.ini"); // path /= "7";

	path.replace_extension(".txt");
	path.remove_filename();
	//boost::system_complete();
}

void FileStatus(const filesystem::path& pathDir, const filesystem::path& pathFile)
{
	using namespace filesystem;

	// 验证文件权限
	assert((status("C:\\Users\\Administrator\\Desktop").permissions() & owner_exe) != owner_exe);
}

void property(const filesystem::path& pathDir, const filesystem::path& pathFile)
{
	using namespace filesystem;
	std::cout << std::endl << "----------property----------" << std::endl;
	std::cout << current_path() << std::endl;
	std::cout << initial_path() << std::endl;

	std::cout << file_size(pathFile) << std::endl;

	time_t t = last_write_time(pathFile);
	last_write_time(pathFile, time(0));


	// 磁盘空间信息
	space_info si = space(pathDir);
	std::cout << si.capacity / boost::giga::num << std::endl; // 使用ratio库的giga单位
	std::cout << si.available / boost::giga::num << std::endl;
	std::cout << si.free / boost::giga::num << std::endl;
}

void file_operator()
{
	namespace fs = boost::filesystem;

	fs::path pathCur = fs::current_path();
	pathCur.append("\\FileSystemTestDir");

	// 创建目录，若存在该目录则不会创建
	bool isOk = fs::create_directory(pathCur);
	// 创建多级目录，这里是纵向创建
	isOk = fs::create_directories(pathCur / "FileSystemTestDir_sub" / "FileSystemTestDir_sub_sub");

	if (fs::is_empty(pathCur))
	{
		isOk = fs::remove(pathCur); // 注意：remove只能删除空目录或文件
	}
	else
	{
		isOk = fs::remove_all(pathCur); // 删除目录、子目录及文件，All
	}
}
#endif // TEST_BOOST_RTREE