
// SelfRoomDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

class CServerSocket; //�����׽�����
class CClientSocket; //��ͻ���ͨ�ŵ��׽�����

// CSelfRoomDlg �Ի���
class CSelfRoomDlg : public CDialogEx
{
// ����
public:
	CSelfRoomDlg(CWnd* pParent = NULL);	// ��׼���캯��

	//ʵ��ָ�����
	CServerSocket *m_pSocket;
	CClientSocket *clientSocket; 
	void UpdateUser(CClientSocket *pSocket); //�����û��б�ĺ���

// �Ի�������
	enum { IDD = IDD_SELFROOM_DIALOG };

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
	CEdit m_Admin;
	CString m_strName;
	CIPAddressCtrl ServerIP;
	CEdit ServerPort;
	CString sPort;
	CEdit m_MessageList;
	CString m_history;
	CListBox m_UserList;
	CButton m_Start;
	CButton m_Stop;
	CButton m_Exit;
	afx_msg void OnStart(); //��������������������¼�
	afx_msg void OnStop(); //����������رշ������¼�
	afx_msg void GetIPAndPort();
};
