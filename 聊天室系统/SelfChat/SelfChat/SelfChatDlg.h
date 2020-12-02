
// SelfChatDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "ClientSocket.h"

// CSelfChatDlg 对话框
class CSelfChatDlg : public CDialogEx
{
// 构造
public:
	CSelfChatDlg(CWnd* pParent = NULL);	// 标准构造函数

	CClientSocket *m_pSocket; //指针机制
	void UpdateUser(); //更新客户端用户列表
	BOOL GetMsgFromRoom(); //接收其他成员发言内容

// 对话框数据
	enum { IDD = IDD_SELFCHAT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
