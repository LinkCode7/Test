
//#include "D:\gdal-1.5.0\ogr\ogrsf_frmts\ogrsf_frmts.h"

void readShapeFile()
{
    //	OGRRegisterAll();
    //
    //	OGRDataSource *poDS;
    //
    //	poDS = OGRSFDriverRegistrar::Open( "G:\\LJF\\point.shp", FALSE );//shape文件存放的路径（point.shp即为自己创建的文件）
    //	if( poDS == NULL )
    //	{
    //		printf( "Open failed.\n%s" );
    //		exit( 1 );
    //	}
    //
    //	OGRLayer  *poLayer;
    //
    //	poLayer = poDS->GetLayerByName( "point" );
    //
    //	OGRFeature *poFeature;
    //
    //	poLayer->ResetReading();
    //	while( (poFeature = poLayer->GetNextFeature()) != NULL )//获得要素，本实例指的是五个点，所以会循环5次
    //	{
    //		OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();
    //		int iField;
    //		int i=poFDefn->GetFieldCount();
    ////获得字段的数目，本实例返回5，不包括前两个字段（FID,Shape），这两个字段在arcgis里也不能被修改; 		for( iField = 0; iField <
    //poFDefn->GetFieldCount(); iField++ )
    //		{
    //			OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn( iField );
    //           //根据字段值得类型，选择对应的输出
    //			if( poFieldDefn->GetType() == OFTInteger )
    //				printf( "%d,", poFeature->GetFieldAsInteger( iField ) );
    //			else if( poFieldDefn->GetType() == OFTReal )
    //				printf( "%.3f,", poFeature->GetFieldAsDouble(iField) );
    //			else if( poFieldDefn->GetType() == OFTString )
    //				printf( "%s,", poFeature->GetFieldAsString(iField) );
    //			else
    //				printf( "%s,", poFeature->GetFieldAsString(iField) );
    //		}
    //
    //		OGRGeometry *poGeometry;
    //
    //		poGeometry = poFeature->GetGeometryRef();
    //		if( poGeometry != NULL
    //			&& wkbFlatten(poGeometry->getGeometryType()) == wkbPoint )
    //		{
    //			OGRPoint *poPoint = (OGRPoint *) poGeometry;
    //
    //			printf( "%.3f,%3.f\n", poPoint->getX(), poPoint->getY() );
    //		}
    //		else
    //		{
    //			printf( "no point geometry\n" );
    //		}
    //		OGRFeature::DestroyFeature( poFeature );
    //	}
    //
    //	OGRDataSource::DestroyDataSource( poDS );
}