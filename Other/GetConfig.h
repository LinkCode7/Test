#pragma once
#include <list>
#include <map>
#include <vector>

#define		CONFIGFILE	"config.txt"
typedef	std::vector<std::string> stringArray;

//void outMessage(const char* message)
//{
//	std::cout << std::endl << message << "line:" << __LINE__ << std::endl;
//}

struct ConnectionInfo
{
	std::string connectLink;

	std::string strUser;
	std::string strPassword;
	std::string strVersion;
	std::string strServer;

	std::string configFile1;
	std::string configFile2;
	std::string strReseave;

	std::string m_strLogFileName;

	std::list<long> m_listInfoID;
	std::map<long, long> m_mapInfoID;
};




/// 読み込みタイプ
enum LOADTYPE
{
	TYPE_PGDB,
	TYPE_ROAD,
	TYPE_MAP,
	TYPE_RASTER,
	TYPE_PATTERN,
};
/// レイヤ情報
struct LAYERINFO {
	std::string					strLayerName;		//!< 設定ファイルのlayers、またはdataset内にあるレイヤ
	std::string					strAliasName;		//!< 設定ファイルのlayers、またはdataset内にあるレイヤ(エイリアス名)
	std::string					strSymbolName;		//!< レイヤのシンボル
	std::string					strCheck;			//!< チェックボックス 0:なし,1:チェック
	LOADTYPE				lLoadType;			//!< 0:PGDB,1:道路,2:地図,3:ラスタ
	std::string					strPurpose;			//!< 作業目的
};
/// SDE接続情報
struct CONNECTIONINFO {
	std::string					strConnectionName;	//!< 接続名コンボボックス

	std::string					strServer;
	std::string					strInstance;
	std::string					strUser;
	std::string					strPasswd;
	std::string					strVersion;

	std::string					strDataset;			//!< 設定ファイルのdataset
	std::string					strAddMode;			//!< 設定ファイルのAddMode(セクション部にある場合はセクション部の記述が優先される)
	std::string					strGroupName;		//!< 設定ファイルのgroupname
	std::list<LAYERINFO>	listLayerInfo;		//!< 設定ファイルのlayers
	bool					bGroupLayerSDE;		//!< SDE読込み時グループレイヤに追加するか
	bool					bGroupLayer;		//!< グループレイヤ表示フラグ
};

//bool GetPrivateProfileSectionTCharArray(LPCTSTR lpAppName, LPCTSTR lpFileName, std::vector<TCHAR>& vecResult);