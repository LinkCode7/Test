#include "pch.h"
//#include "ArcObject.h"
////#include "ogrsf_frmts.h"
//using namespace std;
//
//
//#ifdef USE_ESRI
//void testQueryDef(const IQueryDefPtr& ipQueryDef)
//{
//	CComBSTR subFields;
//	ipQueryDef->get_SubFields(&subFields);
//	CComBSTR tables;
//	ipQueryDef->get_Tables(&tables);
//	CComBSTR whereClause;
//	ipQueryDef->get_WhereClause(&whereClause);
//
//	// Use test
//	//std::string table1(L"addressed_roadMap_V6.93_Points_Province");
//	//std::string table2(L"addressed_roadMap_V6.93_Polygons_4_Import");
//	//ipQueryDef->put_Tables(CComBSTR(table1 +L"," + table2));
//	////ipQueryDef->put_SubFields(CComBSTR(L""));
//	//ipQueryDef->put_WhereClause(L"");
//
//	std::string table1(L"POI_POINT");
//	std::string table2(L"POI_SUB_POINT");
//	ipQueryDef->put_Tables(CComBSTR(table1 + L"," + table2));
//	ipQueryDef->put_SubFields(CComBSTR(L"*"));
//	ipQueryDef->put_WhereClause(L"OBJECTID < 5");
//
//	ICursorPtr ipCursor;
//	ipQueryDef->Evaluate(&ipCursor);
//
//	//testCursor(ipCursor, L"testQueryDef", LINE_INFO());
//}
//
//
//
//void testObject()
//{
//	//IWorkspaceFactoryPtr ipWorkspaceFactory(CLSID_ShapefileWorkspaceFactory);
//	//IWorkspacePtr ipWorkspace;
//	//ipWorkspaceFactory->OpenFromFile(CComBSTR(L"D:\\Data\\testData_Vietmap"), 0, &ipWorkspace);// SHAPEFILE_PATH
//
//	//IFeatureWorkspacePtr ipFeatureWorkspace = ipWorkspace;
//
//	//IFeatureClassPtr ipFeatureClass;
//	//ipFeatureWorkspace->OpenFeatureClass(L"hydro",&ipFeatureClass);
//
//	//CComBSTR fullQualifiedName;
//	//ISQLSyntaxPtr(ipFeatureWorkspace)->QualifyTableName(CComBSTR(L"testData_Vietmap"), CComBSTR(L"testData_Vietmap"), CComBSTR(L"hydro"), &fullQualifiedName);
//
//	//IFeatureClassNamePtr ipFeatureClassName(CLSID_FeatureClassName);
//
//}
//
//
//
//
//#endif