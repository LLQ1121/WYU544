// ClientSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "SelfChat.h"
#include "ClientSocket.h"
#include "SelfChatDlg.h"
#include "tagHeader.h"

// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket 成员函数
void CClientSocket::GetDlg(CSelfChatDlg *dlg) //获得窗口界面的指针
{
	chatDlg = dlg;
}

void CClientSocket::OnReceive(int nErrorCode)
{
	char buff[sizeof(Header)];
	memset(buff,0,sizeof(buff));
	Receive(buff,sizeof(buff)); //收到服务器发来的消息
	this->AsyncSelect(FD_CLOSE|FD_READ|FD_WRITE);

	Header *header = (Header*)buff;
	int length = header->len; 
	char type = header ->type; //解析消息头部
	if(type == SEND_MESSAGE) //聊天内容直接接收
	{
		chatDlg->GetMsgFromRoom();
	}
	if(type == LOGIN_IO) //更新用户表
	{
		chatDlg->UpdateUser();
	}
	CSocket::OnReceive(nErrorCode);
}