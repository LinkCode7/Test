#pragma once




#if(_MSC_VER == _VERSION_VS2015_)

class ReadData
{
public:
	std::string m_pathName;
	GDALDataset* m_pGdalDataset;

public:
	//ReadData(const char* path)
	ReadData(const std::string& path)
	{
		m_pathName = path;
		// Connect database
		GDALAllRegister();
		// GDAL_OF_VECTOR;GDAL_OF_UPDATE;GDAL_OF_READONLY;GDAL_OF_SHARED
		m_pGdalDataset = (GDALDataset*)GDALOpenEx(path.c_str(), GDAL_OF_SHARED, NULL, NULL, NULL);
	}

	~ReadData()
	{
		if (!m_pGdalDataset) return;
		delete[]m_pGdalDataset;
	}

public:

	OGRLayer* getLayerByName(const char *pLayerName);

	OGRFieldType getFieldType(const char* tableName,GIntBig featureIndex,int fieldIndex)
	{
		// 这个方法返回的type不包含ID列和Shape列
		OGRLayer* table = getLayerByName(tableName);

		OGRFeature* feature = table->GetFeature(featureIndex);
		OGRFieldDefn* fieldDefn = feature->GetFieldDefnRef(fieldIndex);
		return fieldDefn->GetType();
	}

	// Get layer count
	long getLayerCount()//zh+
	{
		if (!m_pGdalDataset)
			return 0;
		else
			return (long)m_pGdalDataset->GetLayerCount();
	}

	// Get layer
	OGRLayer* getLayer(int iLayer)
	{
		if (!m_pGdalDataset)
			return nullptr;
		return
			m_pGdalDataset->GetLayer(iLayer);
	}

	void openShapeFile(const char * pPathName);


	void closeShapeFile();


	OGRFeature* getFeature(OGRLayer* pLayer, int id);


	OGRLayer* searchByAttributeFilter(OGRLayer* pLayer, const char *pQueryFilter);


	OGRLayer* searchBySpatialFilter(OGRLayer* pLayer, OGRGeometry *pGeometry);


	long getFeatureCount(OGRLayer* pLayer);


	OGRwkbGeometryType getShapeType(OGRLayer* pLayer);


	int findFieldIndex(OGRLayer* pLayer, const char *pName, int bExactMatch = 1);


	OGRFieldType getFieldType(OGRFeature *pFeature, int fieldIndex);


	OGRFeatureDefn* getFeatureDefine(OGRLayer* pLayer);


	OGRGeometry * getShape(OGRFeature * pFeature);


	OGRFeature* nextFeatrue(OGRLayer* pLayer);


	OGRSpatialReference* getOgrSpatial(OGRLayer* pLayer);


	const char* getDatasetName();


	const char* getLayerName(OGRLayer* pLayer);


	std::string get05ShapefilePrjFileName();
};

#endif