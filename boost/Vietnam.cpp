#include "pch.h"
#include "Vietnam.h"
#if (defined TEST_BOOST_RTREE && defined _IS_WINDOWS_PLATFORM_)
#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;

namespace uh
{
	typedef std::basic_string<TCHAR> tstring;

	template<class T>
	boost::program_options::typed_value<T, TCHAR>* tvalue(T* v)
	{
		return new boost::program_options::typed_value<T, TCHAR>(v);
	}
}

/**
* @brief 必要なオプション情報があるかをチェックする
* @param vm [in] 引数のmap
* @param option [in] オプション名称
* @param desctiption [in] オプションの記述
* @retval true 必要なオプションあり
* @retval false 必要なオプションなし
*/
bool check_required_option(const po::variables_map& vm, LPCSTR option, LPCSTR desctiption)
{
	if (vm.count(option) == 0) {
		std::cerr << desctiption << "が未設定です。" << std::endl;
		return false;
	}
	return true;
}

// --in_db D:\data\02_元データ\cutData_Vietmap --log D:\Env\Log\log.txt --out_db D:\Env\Data\dione_template_170606.gdb --site
int __main(int argc, _TCHAR* argv[])
{
	po::options_description desc("Allowed options");

	const char* const k_in_db = "in_db";
	const char* const k_log = "log";
	const char* const k_out_db = "out_db";
	const char* const k_mesh_db = "mesh_db";

	const char* const k_site = "site";
	const char* const k_building = "building";
	const char* const k_admin = "admin";
	const char* const k_hnp = "hnp";
	const char* const k_road = "road";
	const char* const k_poi = "poi";

	const char* const k_in_poi_db_date = "in_poi_db_date";
	const char* const k_poi_code = "in_poi_code";
	const char* const k_chainmastername_code = "in_chainmaster_code";
	const char* const k_adminid_list = "in_adminid_list";

	// コマンドライン引数処理
	Arguments args;
	desc.add_options()
		(k_in_db, uh::tvalue<uh::tstring>(&args.in_db), "[必須]インプットDB")
		(k_log, uh::tvalue<uh::tstring>(&args.log), "[必須]ログ")
		(k_out_db, uh::tvalue<uh::tstring>(&args.out_db), "[必須]アウトプットDB")
		(k_mesh_db, uh::tvalue<uh::tstring>(&args.mesh_db), "[道路変換時使用]メッシュDB")
		(k_poi_code, uh::tvalue<uh::tstring>(&args.poi_code), "[必須]poiコードファイル")
		(k_chainmastername_code, uh::tvalue<uh::tstring>(&args.chainmaster_code), "[必須]chainmasterコードファイル")
		(k_adminid_list, uh::tvalue<uh::tstring>(&args.adminid_list), "[必須]adminid listファイル")

		(k_site, "背景ポリゴン変換モード")
		(k_building, "建物変換モード")
		(k_admin, "行政界変換モード")
		(k_road, "道路変換モード")
		(k_poi, "POI変換モード")
		(k_hnp, "ハウスナンバーポイント")

		(k_in_poi_db_date, uh::tvalue<uh::tstring>(&args.in_poi_db_date), "インプットDB作成日期")
		;

	if (argc == 1) {
		cerr << "コマンドライン引数に問題があります" << endl;
		return 1;
	}

	// argc, argv を解析して、結果をvmに格納
	po::variables_map vm;
	store(parse_command_line(argc, argv, desc), vm);
	notify(vm);

	// 必須パラメータチェック
	bool bMust = true;

	bMust &= check_required_option(vm, k_in_db, "[必須]インプットDB");
	bMust &= check_required_option(vm, k_log, "[必須]ログ");
	bMust &= check_required_option(vm, k_out_db, "[必須]アウトプットPGDB");

	// パラメータが正常ではない場合は、オプション表示して終了
	if (!bMust) {
		std::cerr << "VietmapデータのPGDB変換ツール" << std::endl;
		std::cerr << desc << std::endl;
		return 1;
	}

	if (vm.count(k_site) != 0) { args.site = true; }
	if (vm.count(k_building) != 0) { args.building = true; }
	if (vm.count(k_admin) != 0) { args.admin = true; }
	if (vm.count(k_road) != 0) { args.road = true; }
	if (vm.count(k_poi) != 0) { args.poi = true; }
	if (vm.count(k_hnp) != 0) { args.hnp = true; }

	// 実処理
	CConvertVietmapSiNDY_Vietnam app(args);
	if (app.execute())
	{
		cerr << "正常終了" << endl;
		return 0;
	}
	else
	{
		cerr << "異常終了" << endl;
		return 1;
	}
}
#endif // TEST_BOOST_RTREE && _IS_WINDOWS_PLATFORM_