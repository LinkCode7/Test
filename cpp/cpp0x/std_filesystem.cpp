#include "pch.h"
#include "std_filesystem.h"

#include <filesystem> // C++17
#include <fstream>

void test_filesystem_std()
{
	//recursive_directory();
}

void recursive_directory()
{
	// 将全局locale设为本地语言
	std::locale loc = std::locale::global(std::locale(std::locale(), "", LC_CTYPE));

	const std::wstring dir = L"E:\\";
	std::filesystem::path path("E:\\", loc);
	//std::filesystem::path path("E:\\");
	//std::filesystem::path path = std::filesystem::u8path(u8"E:\\");

	// filesystem抛出异常，可能是遇到系统不允许访问的文件，std::filesystem可以忽略异常
	// https://stackoverflow.com/questions/52318249/the-stdfilesystemrecursive-directory-iterator-exception
	try
	{
		//for (auto& el : std::filesystem::recursive_directory_iterator(path))
		for (auto& el : std::filesystem::recursive_directory_iterator(path, std::filesystem::directory_options::skip_permission_denied))
		{
			std::cout << el.path() << '\n';
		}
	}
	catch (const std::exception& err)
	{
		// 在多字节的目标代码页中，没有此 Unicode 字符可以映射到的字符
		std::cout << std::endl << ">> error: " << err.what() << std::endl;
	}

	// 将全局locale恢复
	std::locale::global(loc);
}

TEST(std_filesystem, recursive_directory)
{
	return;
	namespace fs = std::filesystem;

	fs::path path("C:\\code");

	//for (auto& el : std::filesystem::recursive_directory_iterator(path))
	for (auto& el : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied))
	{
		std::cout << el.path().filename() << '\n'; // el.path()
	}
}