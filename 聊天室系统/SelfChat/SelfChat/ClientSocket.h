#pragma once

// CClientSocket ����Ŀ��
class CSelfChatDlg; //����ָ�����

class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();

	CSelfChatDlg *chatDlg;//����ָ�����
	CString m_strName;
	void GetDlg(CSelfChatDlg *dlg);
	void OnReceive(int nErrorCode);
};


