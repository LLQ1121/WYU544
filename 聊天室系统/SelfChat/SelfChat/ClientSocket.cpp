// ClientSocket.cpp : ʵ���ļ�
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


// CClientSocket ��Ա����
void CClientSocket::GetDlg(CSelfChatDlg *dlg) //��ô��ڽ����ָ��
{
	chatDlg = dlg;
}

void CClientSocket::OnReceive(int nErrorCode)
{
	char buff[sizeof(Header)];
	memset(buff,0,sizeof(buff));
	Receive(buff,sizeof(buff)); //�յ���������������Ϣ
	this->AsyncSelect(FD_CLOSE|FD_READ|FD_WRITE);

	Header *header = (Header*)buff;
	int length = header->len; 
	char type = header ->type; //������Ϣͷ��
	if(type == SEND_MESSAGE) //��������ֱ�ӽ���
	{
		chatDlg->GetMsgFromRoom();
	}
	if(type == LOGIN_IO) //�����û���
	{
		chatDlg->UpdateUser();
	}
	CSocket::OnReceive(nErrorCode);
}