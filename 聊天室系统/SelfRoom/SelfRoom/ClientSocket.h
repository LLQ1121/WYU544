#pragma once

// CClientSocket ����Ŀ��
#include "SelfRoomDlg.h" //���жԻ���ָ�����

class CClientSocket : public CSocket
{
	public:
		CClientSocket();
		virtual ~CClientSocket();

		CString m_strName; //��ʾ�û�����
		CPtrList *clist; //����ʹ�õ�Socket�������ݽṹ
		CSelfRoomDlg *m_dlgServer; //Ӧ�öԻ�ָ�����
		CClientSocket(CPtrList *list); //����һ��Socket����

		//��Ա����
		void OnReceive(int nErrorCode); //���տͻ��˷�������Ϣ
		void OnClose(int nErrorCode); //����ͻ����뿪����
		
};


