#pragma once

// CClientSocket 命令目标
class CSelfChatDlg; //建立指针机制

class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();

	CSelfChatDlg *chatDlg;//建立指针机制
	CString m_strName;
	void GetDlg(CSelfChatDlg *dlg);
	void OnReceive(int nErrorCode);
};


