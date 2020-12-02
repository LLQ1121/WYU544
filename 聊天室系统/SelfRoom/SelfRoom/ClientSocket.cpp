// ClientSocket.cpp : ʵ���ļ�
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

// CClientSocket ��Ա����

CClientSocket::CClientSocket(CPtrList *list):m_dlgServer(NULL)
{
	clist = list;
}

void CClientSocket::OnReceive(int nErrorCode)
{
	char buff1[sizeof(Header)];
	memset(buff1,0,sizeof(buff1));
	Receive(buff1,sizeof(buff1)); //�Ƚ�����Ϣ��ͷ��
	this->AsyncSelect(FD_CLOSE|FD_READ|FD_WRITE);

	Header *header = (Header*)buff1;
	int length = header->len; 
	char type = header->type; //����ͷ������
	if(type == LOGIN_IO) //�³�Ա����
	{
		char buff[1000];
		memset(buff,0,sizeof(buff));
		Receive(buff,length); //��������������Ϣ�����ݲ���(�³�Ա��)
		this->AsyncSelect(FD_CLOSE|FD_READ|FD_WRITE);
		m_dlgServer->UpdateData();
		CTime time = CTime::GetCurrentTime();
		CString t = time.Format("%H:%M:%S");
		CEdit *p_Edit = (CEdit*)::AfxGetMainWnd()->GetDlgItem(IDC_EDIT_INFO);

		//����֪ͨ��Ϣ
		CString strTemp = t + " " + CString(buff) + " ����������\r\n";
		p_Edit->ReplaceSel(strTemp);

		m_strName = buff; //���¼����Ա���û����Ǽ��ڷ������Ķ�ӦSocket��
		Header head;
		head.type = SEND_MESSAGE;
		head.len = strTemp.GetLength();

		Header head_history;
		head_history.type = SEND_MESSAGE;
		//���ɡ���ӭ����Ϣ
		m_dlgServer->m_history += m_strName + ",��ӭ������!";
		head_history.len = m_dlgServer->m_history.GetLength();

		CClientSocket *curr = NULL;
		POSITION pos = clist->GetHeadPosition();
		while(pos != NULL) //�ж����³�Ա�����ϳ�Ա
		{
			curr = (CClientSocket*)clist->GetNext(pos);
			if(curr->m_strName == m_strName) //���³�Ա����ӭ��Ϣ
			{
				curr->Send((char*)&head_history,sizeof(Header));
				curr->Send(m_dlgServer->m_history,m_dlgServer->m_history.GetLength());
			}
			else //��֪�ϳ�Ա���³�Ա����
			{
				curr->Send((char*)&head,sizeof(Header));
				curr->Send(strTemp,strTemp.GetLength());
			}
		}
		m_dlgServer->UpdateUser(this); //�����û��б�
	}

	if(type == SEND_MESSAGE) //ͷ������ΪSEND_MESSAGE��ʾ�ǳ�Ա������
	{
		char buff[1000];
		memset(buff,0,sizeof(buff));
		Receive(buff,sizeof(buff));
		this->AsyncSelect(FD_CLOSE|FD_READ|FD_WRITE);

		CTime time = CTime::GetCurrentTime();
		CString t = time.Format("%H:%M:%S");
		CString nikeName = this->m_strName;
		CString strTemp = t + " " + nikeName + " ˵:" + CString(buff) + "\r\n";
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
		clist->RemoveAt(pos); //һ��������Socket�����е��׽���

		CTime time = CTime::GetCurrentTime();
		CString t = time.Format("%H:%M:%S");
		CEdit *p_Edit = (CEdit*)m_dlgServer->GetDlgItem(IDC_EDIT_INFO);
		CString strTemp = t + " " + this->m_strName + " �뿪������\r\n";
		p_Edit->ReplaceSel(strTemp);
		Header head;
		head.type = SEND_MESSAGE;
		head.len = strTemp.GetLength();
		CClientSocket *curr = NULL;
		POSITION pos = clist->GetHeadPosition();
		while(pos != NULL) //���û��뿪����Ϣ��֪������Ա
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