#include "pch.h"
#include <iostream>
#include <string>
#include <assert.h>
#include <vector>
//#include "TDC/useful_headers/tstring.h"

//using namespace uh;
//
///**
//* @brief ディレクトリ直下のディレクトリ群を得る
//* @note FindFirstFileの仕様に依存する為、specに拡張子を指定したときは、
//*       拡張子の前方一致で絞り込まれる
//* @param[in]	dir		ディレクトリ
//* @param[in]	spec	ディレクトリ名フィルタ。"*.*"のように指定する。
//* @param[out]	dirs	出力ディレクトリ群
//*/
//inline void getDirectoryNames(LPCTSTR dir, LPCTSTR spec, std::vector<tstring>& dirs)
//{
//	assert(dir);
//	assert(spec);
//
//	tstring filespec = tstring(dir) + _T("\\") + spec;
//
//	WIN32_FIND_DATA fd;
//	HANDLE hFind = ::FindFirstFile(filespec.c_str(), &fd);
//	if (hFind == INVALID_HANDLE_VALUE)
//	{
//		// specに適合するファイルがないときは例外にしない
//		if (::GetLastError() == ERROR_FILE_NOT_FOUND)
//			return;
//
//		std::string msg = std::string("Fail FindFirstFile: ") + toStr(filespec);
//		throw std::runtime_error(msg);
//	}
//
//	do
//	{
//		tstring filename = fd.cFileName;
//		if ((filename == _T(".")) || (filename == _T("..")))
//			continue;
//
//		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
//		{
//			dirs.push_back(filename);
//		}
//	} while (::FindNextFile(hFind, &fd));
//	::FindClose(hFind);
//}