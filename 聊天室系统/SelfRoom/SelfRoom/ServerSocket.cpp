// ServerSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "SelfRoom.h"
#include "ServerSocket.h"

#include "ClientSocket.h"

// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}

// CServerSocket 成员函数
void CServerSocket::OnAccept(int nErrorCode)
{
	CSocket::OnAccept(nErrorCode);
	CClientSocket *clientSocket = new CClientSocket(&connectList); //创建Socket队列结构
	Accept(*clientSocket); //接收连接
	clientSocket->m_dlgServer = (CSelfRoomDlg*)::AfxGetMainWnd();
	connectList.AddTail(clientSocket); //在队列中添加新成员的Socket
}
