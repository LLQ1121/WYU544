// ServerSocket.cpp : ʵ���ļ�
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

// CServerSocket ��Ա����
void CServerSocket::OnAccept(int nErrorCode)
{
	CSocket::OnAccept(nErrorCode);
	CClientSocket *clientSocket = new CClientSocket(&connectList); //����Socket���нṹ
	Accept(*clientSocket); //��������
	clientSocket->m_dlgServer = (CSelfRoomDlg*)::AfxGetMainWnd();
	connectList.AddTail(clientSocket); //�ڶ���������³�Ա��Socket
}
