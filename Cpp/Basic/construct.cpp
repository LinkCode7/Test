#include "pch.h"
#include "construct.h"



void TestCppClass()
{
	SimpleObject s;

	// error C2248 : “SimpleObject::operator new” : 无法访问 private 成员
	//SimpleObject* pSimpleObject = new SimpleObject;
}