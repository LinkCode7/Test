#include "pch.h"

using namespace std;
class Company
{
public:
	void SendClearText(const string& msg)
	{}
	void SendEncrypted(const string& msg)
	{}
};

class CompanyA
{
public:
	void SendClearText(const string& msg)
	{}
	void SendEncrypted(const string& msg)
	{}
};
class CompanyB
{
public:
	void SendClearText(const string& msg)
	{}
	void SendEncrypted(const string& msg)
	{}
};


class MsgInfo
{};

template<typename Company>
class MsgSender
{
public:
	void SendClear(const MsgInfo& info)
	{
		string msg;
		Company c;
		c.SendClearText(msg);
	}

	void SendSecret(const MsgInfo& info)
	{
		string msg;
		Company c;
		c.SendEncrypted(msg);
	}
};



template<typename Company>
class LoggingMsgSender :public MsgSender<Company>
{
public:
	void SendClearMsg(const MsgInfo& info)
	{
		// Before send log
		//this->SendClear(info);
		// After send log
	}
};


class CompanyZ:public Company
{
public:
	// 没有SendClearText函数
	void SendEncrypted(const string& msg)
	{}
};

template<> // MsgSender对CompanyZ的特化版
class MsgSender<CompanyZ>
{
public:
	void SendSecret(const MsgInfo& info)
	{}
};





/////////////////////////////////////////////////////////////////
// 模板化基类内的名称
void testTemplateBaseClass()
{
	MsgInfo info;

	LoggingMsgSender<CompanyZ> senderZ;
	senderZ.SendClearMsg(info);

	LoggingMsgSender<CompanyA> sender;
	sender.SendClearMsg(info);
}