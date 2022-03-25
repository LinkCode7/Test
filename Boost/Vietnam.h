#pragma once
#include <tchar.h>	// TCHAR
#include <windows.h>  // LPCSTR
#include "winver.h"







struct Arguments
{
	// ﾔｭﾏﾈuh::tstring
	std::wstring in_db;	  //!< インプットDB
	std::wstring log;      //!< ログ
	std::wstring out_db;   //!< アウトプットDB
	std::wstring mesh_db;  //!< メッシュDB
	std::wstring in_poi_db_date;  //!< インプットDB日期
	std::wstring poi_code;	//!< poi コードファイル
	std::wstring chainmaster_code;	//!< chainmaster コードファイル
	std::wstring adminid_list;	//!< adminid listファイル

	bool        admin;
	bool        site;
	bool        building;
	bool        road;
	bool        hnp;
	bool        poi;

	Arguments() {
		admin = false;
		site = false;
		building = false;
		road = false;
		poi = false;
		hnp = false;
	}
};










// #pragma comment( lib, "*****.lib
// class CVersion
class CVersion 
{

	VOID *pData;
	WORD *pLang;
	VS_FIXEDFILEINFO *pFixedFileInfo;
	std::string fullPathName;

	VOID init(LPCTSTR filename)
	{
		/*pData = NULL;
		pLang = NULL;
		pFixedFileInfo = NULL;

		fullPathName = filename;
		DWORD size = GetFileVersionInfoSize((LPTSTR)filename, NULL);
		pData = new BYTE[size];

		UINT len;
		if (GetFileVersionInfo((LPTSTR)filename, NULL, size, pData)) {
			VerQueryValue(pData, _T("\\"), (LPVOID *)&pFixedFileInfo, &len);
			VerQueryValue(pData, _T("\\VarFileInfo\\Translation"), (LPVOID *)&pLang, &len);
		}*/
	}

public:
	CVersion()
	{
		//HINSTANCE hInstance = AfxGetApp()->m_hInstance;
		TCHAR szFilename[MAX_PATH];
		GetModuleFileName(NULL, szFilename, MAX_PATH);
		init((LPTSTR)szFilename);
	}

	CVersion(LPCTSTR Filename)
	{
		init(Filename);
	}

	~CVersion()
	{
		delete[] pData;
	}

	std::string GetInternalName()
	{
		//if (pData == NULL) return("");

		//std::string SubBlock;
		//SubBlock.Format(_T("\\StringFileInfo\\%04X%04X\\InternalName"), *pLang, *(pLang + 1));

		//TCHAR *p(nullptr);
		//UINT len(0);
		////VerQueryValue(pData, (LPTSTR)(LPCTSTR)SubBlock, (LPVOID *)&p, &len);

		//std::string str;
		//if (len > 0) str = p;
		//else str = "";

		//return(str);

		return std::string();
	}
};




class CConvertVietmapSiNDY_Vietnam
{
	std::string           m_strInDB;
	std::string           m_strLog;
	std::string           m_strOutDB;
	std::string           m_strMeshDB;
	std::string           m_strInFileName;
	std::string           m_internalName;
	std::string			  m_strInPOIDBDate;
	std::string			  m_strPoiCodePath;
	std::string			  m_strChainmasterCodePath;
	std::string			  m_strAdminIdListPath;

	// 出力フラグ
	bool              m_admin;
	bool              m_road;
	bool              m_poi;
	bool              m_site;             //!< 背景出力フラグ
	bool              m_building;         //!< 建物出力フラグ
	bool              m_hnp;		      //!< ハウスナンバーポイント

public:
	struct PoiInfo
	{
		std::string catldsStr;
		std::string chainNameStr;

		PoiInfo(const std::string &catlds, const std::string & chainName) :catldsStr(catlds), chainNameStr(chainName)
		{};

		bool operator <(const PoiInfo&poiInfo)const
		{
			/*if (poiInfo.catldsStr.Compare(catldsStr) < 0) return true;
			if (poiInfo.catldsStr.Compare(catldsStr) > 0) return false;
			return  poiInfo.chainNameStr.Compare(chainNameStr) < 0 ? true : false;*/
			return false;
		}
	};

	/**
	* @brief   コンストラクタ
	* @param   args [in]  引数
	*/
	CConvertVietmapSiNDY_Vietnam(const Arguments& Args)
	{
		/*m_strInDB = (Args.in_db).c_str();
		m_strLog = (Args.log).c_str();
		m_strOutDB = (Args.out_db).c_str();
		m_strMeshDB = (Args.mesh_db).c_str();
		m_strInPOIDBDate = (Args.in_poi_db_date).c_str();
		m_strPoiCodePath = (Args.poi_code).c_str();
		m_strChainmasterCodePath = (Args.chainmaster_code).c_str();
		m_strAdminIdListPath = (Args.adminid_list).c_str();

		m_admin = Args.admin;
		m_road = Args.road;
		m_poi = Args.poi;
		m_site = Args.site;
		m_hnp = Args.hnp;
		m_building = Args.building;

		m_internalName = CVersion().GetInternalName();*/
	};

	/**
	* @brief   実行
	* @retval  true  成功
	* @retval  false 失敗
	*/
	bool execute() { return true; }

};