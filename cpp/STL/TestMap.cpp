#include "pch.h"
#include "TestMap.h"

#include <map>

using namespace std;





void TestMap()
{
	map<int, string> mapId2Name;
	mapId2Name[1] = "a";
	mapId2Name[1] = "b";

	map<int, TestMapObjectPtr> mapId2Object;
	mapId2Object[1] = std::make_shared<TestMapObject>(1);
	mapId2Object[1] = std::make_shared<TestMapObject>(2);
}
