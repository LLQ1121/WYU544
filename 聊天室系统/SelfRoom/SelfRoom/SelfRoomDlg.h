
// SelfRoomDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

class CServerSocket; //监听套接字类
class CClientSocket; //与客户端通信的套接字类

// CSelfRoomDlg 对话框
class CSelfRoomDlg : public CDialogEx
{
// 构造
public:
	CSelfRoomDlg(CWnd* pParent = NULL);	// 标准构造函数

	//实现指针机制
	CServerSocket *m_pSocket;
	CClientSocket *clientSocket; 
	void UpdateUser(CClientSocket *pSocket); //更新用户列表的函数

// 对话框数据
	enum { IDD = IDD_SELFROOM_DIALOG };

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
	afx_msg void OnStart(); //处理服务器开启服务器事件
	afx_msg void OnStop(); //处理服务器关闭服务器事件
	afx_msg void GetIPAndPort();
};
