#include "pch.h"
#include "cpp11_basic.h"

#include <climits>
//#include <cstdint>

using namespace std;


void TestCpp11Class::initArray()
{
	m_arr = { {1},{2},{3} };
}

void TestCpp11Class::initMap()
{
	m_mapInt2Array = { {100, {1,11}},{200, {2,22}},{300, {3,33}} };
}

TEST(range_for, return_reference)
{
	TestCpp11Class object;
	cout << "------initArray------" << endl << endl;
	object.initArray();
	cout << "------initMap------" << endl << endl;
	object.initMap();

	bool construct = false;

	cout << "------0------" << endl << endl;
	for (auto& data : object.getArray())
	{
		construct = true;
	}

	cout << "------1------" << endl << endl;
	for (auto& data : object.getArrayReference())
	{
		construct = false;
	}

	cout << "------2------" << endl << endl;
	for (auto& data : *object.getArrayPoint())
	{
		construct = false;
	}

	cout << "------3------" << endl << endl;
	for (const auto& [id, arr] : object.getMap())
	{
		construct = false;
	}

	cout << "------4------" << endl << endl;
	for (const auto& [id, arr] : *object.getMapPoint())
	{
		construct = false;
	}

	cout << "------5------" << endl << endl;
	for (const auto& [id, arr] : object.getMapReference())
	{
		construct = false;
	}
}
