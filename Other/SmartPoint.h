#pragma once



class Workspace
{
	int fieldCount;
	std::string tableName;

public:
	Workspace(int count, std::string name) :fieldCount(count), tableName(name) {}

};


Workspace* create_workspace( const std::string& connectInfo );
void connectSDE( Workspace** workspace, int flag );
void getConfig( int flag );