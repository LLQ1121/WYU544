// ClientSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "SelfRoom.h"
#include "ClientSocket.h"

#include "tagHeader.h"


// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}

// CClientSocket 成员函数

CClientSocket::CClientSocket(CPtrList *list):m_dlgServer(NULL)
{
	clist = list;
}

void CClientSocket::OnReceive(int nErrorCode)
{
	char buff1[sizeof(Header)];
	memset(buff1,0,sizeof(buff1));
	Receive(buff1,sizeof(buff1)); //先接收信息的头部
	this->AsyncSelect(FD_CLOSE|FD_READ|FD_WRITE);

	Header *header = (Header*)buff1;
	int length = header->len; 
	char type = header->type; //解析头部内容
	if(type == LOGIN_IO) //新成员加入
	{
		char buff[1000];
		memset(buff,0,sizeof(buff));
		Receive(buff,length); //继续接收这条信息的数据部分(新成员名)
		this->AsyncSelect(FD_CLOSE|FD_READ|FD_WRITE);
		m_dlgServer->UpdateData();
		CTime time = CTime::GetCurrentTime();
		CString t = time.Format("%H:%M:%S");
		CEdit *p_Edit = (CEdit*)::AfxGetMainWnd()->GetDlgItem(IDC_EDIT_INFO);

		//生成通知信息
		CString strTemp = t + " " + CString(buff) + " 进入聊天室\r\n";
		p_Edit->ReplaceSel(strTemp);

		m_strName = buff; //将新加入成员的用户名登记在服务器的对应Socket中
		Header head;
		head.type = SEND_MESSAGE;
		head.len = strTemp.GetLength();

		Header head_history;
		head_history.type = SEND_MESSAGE;
		//生成“欢迎”信息
		m_dlgServer->m_history += m_strName + ",欢迎您加入!";
		head_history.len = m_dlgServer->m_history.GetLength();

		CClientSocket *curr = NULL;
		POSITION pos = clist->GetHeadPosition();
		while(pos != NULL) //判断是新成员还是老成员
		{
			curr = (CClientSocket*)clist->GetNext(pos);
			if(curr->m_strName == m_strName) //给新成员发欢迎信息
			{
				curr->Send((char*)&head_history,sizeof(Header));
				curr->Send(m_dlgServer->m_history,m_dlgServer->m_history.GetLength());
			}
			else //告知老成员有新成员加入
			{
				curr->Send((char*)&head,sizeof(Header));
				curr->Send(strTemp,strTemp.GetLength());
			}
		}
		m_dlgServer->UpdateUser(this); //更新用户列表
	}

	if(type == SEND_MESSAGE) //头部类型为SEND_MESSAGE表示是成员在聊天
	{
		char buff[1000];
		memset(buff,0,sizeof(buff));
		Receive(buff,sizeof(buff));
		this->AsyncSelect(FD_CLOSE|FD_READ|FD_WRITE);

		CTime time = CTime::GetCurrentTime();
		CString t = time.Format("%H:%M:%S");
		CString nikeName = this->m_strName;
		CString strTemp = t + " " + nikeName + " 说:" + CString(buff) + "\r\n";
		CString str = nikeName + " " + t + "\r\n" + " " + CString(buff);

		CEdit *p_Edit = (CEdit*)::AfxGetMainWnd()->GetDlgItem(IDC_EDIT_INFO);
		p_Edit->ReplaceSel(strTemp);

		CClientSocket *curr =NULL;
		POSITION pos = clist->GetHeadPosition();
		while(pos != NULL)
		{
			curr = (CClientSocket*)clist->GetNext(pos);
			curr->Send((char*)header,sizeof(Header));
			curr->Send(str,str.GetLength());
		}
	}
	CSocket::OnReceive(nErrorCode);
}

void CClientSocket::OnClose(int nErrorCode)
{
	POSITION pos = clist->Find(this);
	if(pos != NULL)
	{
		clist->RemoveAt(pos); //一处服务器Socket队列中的套接字

		CTime time = CTime::GetCurrentTime();
		CString t = time.Format("%H:%M:%S");
		CEdit *p_Edit = (CEdit*)m_dlgServer->GetDlgItem(IDC_EDIT_INFO);
		CString strTemp = t + " " + this->m_strName + " 离开聊天室\r\n";
		p_Edit->ReplaceSel(strTemp);
		Header head;
		head.type = SEND_MESSAGE;
		head.len = strTemp.GetLength();
		CClientSocket *curr = NULL;
		POSITION pos = clist->GetHeadPosition();
		while(pos != NULL) //将用户离开的消息告知其他成员
		{
			curr = (CClientSocket*)clist->GetNext(pos);
			curr->Send((char*)&head,sizeof(Header));
			curr->Send(strTemp,strTemp.GetLength());
		}
		m_dlgServer->UpdateUser(this);
		this->Close();
		delete this;
	}
	CSocket::OnClose(nErrorCode);
}