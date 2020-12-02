
// SelfChatDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "ClientSocket.h"

// CSelfChatDlg �Ի���
class CSelfChatDlg : public CDialogEx
{
// ����
public:
	CSelfChatDlg(CWnd* pParent = NULL);	// ��׼���캯��

	CClientSocket *m_pSocket; //ָ�����
	void UpdateUser(); //���¿ͻ����û��б�
	BOOL GetMsgFromRoom(); //����������Ա��������

// �Ի�������
	enum { IDD = IDD_SELFCHAT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Usr;
	CString m_strName;
	CIPAddressCtrl ServerIP;
	CEdit m_port;
	CString strport;
	CListBox m_UserList;
	CEdit m_MessageList;
	CEdit m_EditWords;
	CString m_strMessage;
	CButton m_Send;
	CButton m_Refresh;
	CButton m_Enter;
	CButton m_Quit;
	CButton m_Exit;
	afx_msg void OnEnter();
	afx_msg void OnSend();
	afx_msg void OnQuit();
	afx_msg void OnRefresh();
	afx_msg void GetIPAndPort();
};
