
#if (_MSC_VER == _VERSION_VS2015_)

    #include "GDAL.h"

    #include "..\String\NoCaseWString.h"
    #include "atlconv.h"
    #include "ogrsf_frmts.h" // Link gdal_i.lib(附加依赖项)

using namespace std;
    #define DATA_PATH_VIETMAP_ALL "D:\\Data\\02_vietmap-2017-06-release-20170823"
    #define DATA_PATH_CAMBODIA "D:\\Data\\Cambodia"
    #define FEATURECLASS "addressed_roadMap_V6.93_Points_Province"

void testExecuteSQL()
{
    ReadData data("D:\\Data\\02_vietmap-2017-06-release-20170823");
    // "select a.FID ,Code_Khet,Khet_Rom,Khet_unico from addressed_roadMap_V6.93_Points_Province as
    // a,addressed_roadMap_V6.93_Points_Updated_Commune as b where a.FID = b.FID "
    // OGRLayer* layer = data.m_pGdalDataset->ExecuteSQL("select * from poi and hydro where NameEn = 'Agribank'", nullptr, nullptr);

    // ReadData data("D:\\Data\\02_vietmap-2017-06-release-20170823");
    //// "select a.FID ,Code_Khet,Khet_Rom,Khet_unico from addressed_roadMap_V6.93_Points_Province as
    ///a,addressed_roadMap_V6.93_Points_Updated_Commune as b where a.FID = b.FID "
    OGRLayer* layer =
        data.m_pGdalDataset->ExecuteSQL("select * from like admin-point left join poi on admin-point.Id=poi.Id", nullptr, nullptr);

    std::string tableName = layer->GetName();
    int         count     = layer->GetFeatureCount();
}

vector<OGRwkbGeometryType> g_type;

void test_OGRwkbGeometryType(const char* database)
{
    ReadData data(database);
    for (int layerCount = 0; layerCount < data.getLayerCount(); ++layerCount)
    {
        OGRLayer*          ogrLayer        = data.getLayer(layerCount);
        OGRwkbGeometryType ogrGeometryType = ogrLayer->GetGeomType();
        g_type.push_back(ogrGeometryType);
    }
}

void test03()
{
    // Connect database
    GDALAllRegister();
    // GDAL_OF_VECTOR;GDAL_OF_UPDATE;GDAL_OF_READONLY;GDAL_OF_SHARED
    GDALDataset* GdalDataset = (GDALDataset*)GDALOpenEx("D:\\Data\\Cambodia", GDAL_OF_SHARED, NULL, NULL, NULL);

    OGRLayer* layer1 = GdalDataset->GetLayerByName("addressed_roadMap_V6.93_Points_Province");
    OGRLayer* layer2 = GdalDataset->GetLayerByName("addressed_roadMap_V6.93_Points_Province");
    int       a      = 1;
}

void CaseSensitive()
{
    // Connect database
    GDALAllRegister();
    // GDAL_OF_VECTOR;GDAL_OF_UPDATE;GDAL_OF_READONLY;GDAL_OF_SHARED
    GDALDataset* GdalDataset = (GDALDataset*)GDALOpenEx("D:\\Data\\Cambodia", GDAL_OF_SHARED, NULL, NULL, NULL);

    /*OGRLayer* layer1 = GdalDataset->GetLayerByName("addressed_roadMap_V6.93_Points_Province");
    const char* name1 = layer1->GetName();*/

    OGRLayer*   layer2 = GdalDataset->GetLayerByName("addressed_roadMap_V6.93_Points_PROVINCE");
    const char* name2  = layer2->GetName();
}

void gdalTest()
{
    std::map<int, std::vector<int>> m_typeIndex; // zh,-+
    std::map<string, int>           m_nameIndex;
    // std::vector<Data>								m_openedDataset;
    GDALDataset* GdalDataset1 = (GDALDataset*)GDALOpenEx("D:\\Data\\Cambodia", GDAL_OF_SHARED, NULL, NULL, NULL);

    for (int i = 0; i < (int)GdalDataset1->GetLayerCount(); ++i)
    {
        OGRLayer*   layer = GdalDataset1->GetLayer(i);
        std::string name  = layer->GetName();
        m_nameIndex[name] = i;
    }

    CaseSensitive();
    test03();
    // Connect database
    GDALAllRegister();
    // GDAL_OF_VECTOR;GDAL_OF_UPDATE;GDAL_OF_READONLY;GDAL_OF_SHARED
    GDALDataset* GdalDataset = (GDALDataset*)GDALOpenEx("D:\\Data\\Cambodia", GDAL_OF_SHARED, NULL, NULL, NULL);

    OGRLayer* layer1 = GdalDataset->GetLayerByName("addressed_roadMap_V6.93_Points_Province");
    OGRLayer* layer2 = GdalDataset->GetLayerByName("addressed_roadMap_V6.93_Points_Province");

    ///////////////////////////////////////////////////////////////////////////////

    vector<OGRwkbGeometryType> type;
    test_OGRwkbGeometryType("D:\\Data\\Cambodia");
    test_OGRwkbGeometryType("D:\\Data\\02_vietmap-2017-06-release-20170823");
    test_OGRwkbGeometryType("D:\\Data\\05shp_Road\\5135\\513534");

    ReadData data("D:\\Data\\Cambodia");
    for (int layerCount = 0; layerCount < data.getLayerCount(); ++layerCount)
    {
        OGRLayer*   ogrLayer = data.getLayer(layerCount);
        std::string name     = ogrLayer->GetName();
    }
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

/*
or
and
<>
is   not   null
like %
*/

// Open shapefile
void ReadData::openShapeFile(const char* pNamePath)
{
    GDALAllRegister();
    m_pathName     = pNamePath;
    m_pGdalDataset = (GDALDataset*)GDALOpenEx(pNamePath, GDAL_OF_UPDATE, NULL, NULL, NULL);
}

// Open shapefile's table
OGRLayer* ReadData::getLayerByName(const char* pLayerName)
{
    if (!m_pGdalDataset)
        return nullptr;
    else
        return m_pGdalDataset->GetLayerByName(pLayerName);
}

// Get feature by feature object id
OGRFeature* ReadData::getFeature(OGRLayer* pLayer, int id)
{
    if (!pLayer)
        return nullptr;
    else
        return pLayer->GetFeature(id);
}

//  Get feature
OGRFeature* ReadData::nextFeatrue(OGRLayer* pLayer)
{
    if (!pLayer)
        return nullptr;
    else
        return pLayer->GetNextFeature();
}

// Get search object for attribute query filter
OGRLayer* ReadData::searchByAttributeFilter(OGRLayer* pLayer, const char* pQueryFilter)
{
    if (!pLayer)
        return nullptr;

    pLayer->ResetReading();
    pLayer->SetAttributeFilter(pQueryFilter);
    return pLayer;
}

// Get search object for spatial query filter
OGRLayer* ReadData::searchBySpatialFilter(OGRLayer* pLayer, OGRGeometry* pGeometry)
{
    if (!pLayer)
        return nullptr;
    pLayer->ResetReading();
    pLayer->SetSpatialFilter(pGeometry);
    return pLayer;
}

// Get feature count
long ReadData::getFeatureCount(OGRLayer* pLayer)
{
    if (!pLayer)
        return 0;
    else
        return (long)pLayer->GetFeatureCount();
}

// Get shape geometry type
OGRwkbGeometryType ReadData::getShapeType(OGRLayer* pLayer)
{
    if (!pLayer)
        return OGRwkbGeometryType(-1); // zh+,accept:if(type==null) else?
    else
        return pLayer->GetGeomType();
}

//  Get field index by field name
int ReadData::findFieldIndex(OGRLayer* pLayer, const char* pName, int bExactMatch)
{
    if (!pLayer)
        return -1;
    else
        return pLayer->FindFieldIndex(pName, bExactMatch);
}

// Get field type
OGRFieldType ReadData::getFieldType(OGRFeature* pFeature, int fieldIndex)
{
    OGRFieldDefn* pFieldDefn = pFeature->GetFieldDefnRef(fieldIndex);
    if (!pFieldDefn)
        return OGRFieldType(-1);
    else
        return pFieldDefn->GetType();
}

// Get fields define
OGRFeatureDefn* ReadData::getFeatureDefine(OGRLayer* pLayer)
{
    if (!pLayer)
        return nullptr;
    else
        return pLayer->GetLayerDefn();
}

// Get shape geometry
OGRGeometry* ReadData::getShape(OGRFeature* pFeature)
{
    if (!pFeature)
        return nullptr;
    return pFeature->GetGeometryRef();
}

// Close shapefile
void ReadData::closeShapeFile()
{
    GDALClose(m_pGdalDataset);
    m_pGdalDataset = nullptr;
}

// Get GDAL/OGR spatial reference
OGRSpatialReference* ReadData::getOgrSpatial(OGRLayer* pLayer)
{
    OGRSpatialReference* pOgrSpatialReference(nullptr);
    if (!pLayer)
        return nullptr;

    pOgrSpatialReference = pLayer->GetSpatialRef();

    if (pOgrSpatialReference)
    {
        // 普通のShapeフォルダ構成
        return pOgrSpatialReference;
    }
    else
    {
        // 05 Shapeフォルダ構成
        OGRSpatialReference* p05OgrSpatialReference = new OGRSpatialReference();

        if (p05OgrSpatialReference)
            p05OgrSpatialReference->SetFromUserInput(get05ShapefilePrjFileName().c_str());
        return p05OgrSpatialReference;
    }
}

//  Get dataset name
const char* ReadData::getDatasetName()
{
    if (!m_pGdalDataset)
        return "";
    else
        return m_pGdalDataset->GetDescription();
}

// Get layer name
const char* ReadData::getLayerName(OGRLayer* pLayer)
{
    if (!pLayer)
        return "";
    else
        return pLayer->GetName();
}

std::string ReadData::get05ShapefilePrjFileName()
{
    std::string shape05PrjFolder = "";

    //  まず入力のshapefileのフォルダから上のフォルダにprjという拡張子を探し、prj測地ファイルがあればprjという拡張子のファイル名に戻る。
    //	上のフォルダにprjという拡張子がない場合に、prj測地ファイルを探せるまでに上の上のフォルダへ探しを行う

    return shape05PrjFolder;
}

#endif
