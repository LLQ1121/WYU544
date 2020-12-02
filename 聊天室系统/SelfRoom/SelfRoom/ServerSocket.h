#pragma once

// CServerSocket 命令目标

class CServerSocket : public CSocket
{
public:
	CServerSocket();
	virtual ~CServerSocket();

	CPtrList connectList;
	void OnAccept(int nErrorCode); //接受新成员的连接请求 //////////////?

	//成员函数
};


