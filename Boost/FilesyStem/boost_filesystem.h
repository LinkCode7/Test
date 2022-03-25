#pragma once
#include <boost/filesystem.hpp>


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