#pragma once


#include <stdio.h>
#include <tchar.h>

//#define _ATL_APARTMENT_THREADED
//
//#define _ATL_NO_AUTOMATIC_NAMESPACE
//
//#define _ATL_std::string_EXPLICIT_CONSTRUCTORS	// some std::string constructors will be explicit
//
//#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>
#include <exception>
using namespace ATL;
#include <list>
#include <map>
#pragma	warning(disable : 4192)
#pragma	warning(disable : 4278)


#ifdef USE_ESRI
#if defined(_ARC) || defined(FORCE_USING_ARC)
#import "libid:6FCCEDE0-179D-4D12-B586-58C88D26CA78" raw_interfaces_only no_namespace no_implementation rename("esriProductCode","esriVersionProductCode")
#endif
// esriSystem.olb
#import "libid:5E1F7BC3-67C5-4AEE-8EC6-C4B73AAC42ED"  raw_interfaces_only no_namespace named_guids exclude("OLE_HANDLE","OLE_COLOR") rename("XMLSerializer","_XMLSerializer")

// Geometry
#import "libid:C4B094C2-FF32-4FA1-ABCB-7820F8D6FB68"  raw_interfaces_only, no_namespace, named_guids, rename("ISegment","_ISegment")

// esriDisplay.olb
#import "libid:59FCCD31-434C-4017-BDEF-DB4B7EDC9CE0"  raw_interfaces_only, no_namespace, named_guids

// esriDataSourcesFile.olb
#import "libid:1CE6AC65-43F5-4529-8FC0-D7ED298E4F1A"  raw_interfaces_only, no_namespace, named_guids

// esriGeoDatabase.olb
#import "libid:0475BDB1-E5B2-4CA2-9127-B4B1683E70C2"  raw_interfaces_only, no_namespace, named_guids




#endif