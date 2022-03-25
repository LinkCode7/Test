#include "pch.h"
#include "SmartPoint.h"

using namespace std;

void getConfig( int flag )
{
	//Workspace work(1, "1");
	Workspace* workspace = nullptr;
	connectSDE( &workspace, flag );
}

void connectSDE( Workspace** workspace, int flag )
{
	// ...
	//(*workspace) = nullptr;
	
	if ( flag == 1 )
	{
		Workspace* tempWorkspace;
		tempWorkspace = create_workspace("hello");

		*workspace = tempWorkspace;
	}
	else if (flag == 0)
	{
		*workspace = create_workspace("hello");
	}
}

Workspace* create_workspace( const std::string& connectInfo )
{
	// ...
	int count(100);
	Workspace* workspace(nullptr);
	//Workspace* work = workspace;

	return workspace;
}