
// SelfRoomDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SelfRoom.h"
#include "SelfRoomDlg.h"
#include "afxdialogex.h"

#include "ServerSocket.h"
#include "ClientSocket.h"
#include "tagHeader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSelfRoomDlg 对话框




CSelfRoomDlg::CSelfRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSelfRoomDlg::IDD, pParent)
	, m_strName(_T(""))
	, sPort(_T(""))
	, m_history(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSelfRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_Admin);
	DDX_Text(pDX, IDC_EDIT2, m_strName);
	DDX_Control(pDX, IDC_IPADDRESS1, ServerIP);
	DDX_Control(pDX, IDC_EDIT3, ServerPort);
	DDX_Text(pDX, IDC_EDIT3, sPort);
	DDX_Control(pDX, IDC_EDIT_INFO, m_MessageList);
	DDX_Text(pDX, IDC_EDIT_INFO, m_history);
	DDX_Control(pDX, IDC_LIST1, m_UserList);
	DDX_Control(pDX, IDC_BUTTON1, m_Start);
	DDX_Control(pDX, IDC_BUTTON2, m_Stop);
	DDX_Control(pDX, IDC_BUTTON3, m_Exit);
}

BEGIN_MESSAGE_MAP(CSelfRoomDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSelfRoomDlg::OnStart)
	ON_BN_CLICKED(IDC_BUTTON2, &CSelfRoomDlg::OnStop)
	ON_BN_CLICKED(IDC_BUTTON4, &CSelfRoomDlg::GetIPAndPort)
END_MESSAGE_MAP()


// CSelfRoomDlg 消息处理程序

BOOL CSelfRoomDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_pSocket = NULL;
	clientSocket = NULL;
	//初始界面
	m_Admin.SetFocus();
	m_Stop.EnableWindow(false);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSelfRoomDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSelfRoomDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSelfRoomDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSelfRoomDlg::OnStart()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(); //刷新界面，获取用户输入
	m_pSocket = new CServerSocket;

	//获取管理员配置的IP
	BYTE nFild[4];
	CString sIP;
	ServerIP.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);

	CTime time = CTime::GetCurrentTime();//获取当前时间
	
	//输入完整性验证
	if(m_strName.IsEmpty())
	{
		AfxMessageBox("请先登记管理员名!");
		return;
	}
	if(sIP.IsEmpty())
	{
		AfxMessageBox("请配置聊天室IP!");
		return;
	}
	if(sPort.IsEmpty())
	{
		AfxMessageBox("请配置要开放的端口!");
		return;
	}

	//界面
	m_Admin.EnableWindow(false);
	ServerIP.EnableWindow(false);
	ServerPort.EnableWindow(false);
	m_Start.EnableWindow(false);
	m_Stop.EnableWindow(true);
	m_Exit.EnableWindow(false);

	//开启聊天室，首先建立用于监听的套接字
	if(m_pSocket->Create(atoi(sPort),1,sIP))
	{
		m_MessageList.SetWindowTextA("");
		m_MessageList.ReplaceSel("聊天室开启成功!\r\n");
		CString t = time.Format("%Y-%m-%d");
		m_MessageList.ReplaceSel("日期: "+ t +"\r\n");
		t = time.Format("%H:%M:%S"); //获得聊天室开启的时刻
		theApp.m_strName = m_strName; //记录管理员名
		m_MessageList.ReplaceSel(t+" 管理员" + theApp.m_strName + " 开放聊天室\r\n");
	}
	//开始监听
	if(m_pSocket->Listen())
	{
		m_MessageList.ReplaceSel("等待成员加入...\r\n");
	}

	m_UserList.ResetContent();
	m_UserList.AddString(theApp.m_strName + "(管理员)");
	this->SetWindowTextA("管理员:" + m_strName + "-SelfRoom");
}

void CSelfRoomDlg::UpdateUser(CClientSocket *pSocket)
{
	m_UserList.ResetContent();
	m_UserList.AddString(theApp.m_strName + "(管理员)"); //首先添加管理员用户
	CString user_info;
	user_info = theApp.m_strName + "(管理员)" + "&";
	if(pSocket != NULL)
	{
		CClientSocket *pSock = NULL;
		POSITION pos = pSocket->clist->GetHeadPosition();
		while(pos != NULL)
		{
			pSock = (CClientSocket*)pSocket->clist->GetNext(pos);
			m_UserList.AddString(pSock->m_strName); //然后逐个添加已经记录的用户名
			user_info += (pSock->m_strName + "&");
		}
		Header head;
		head.type = LOGIN_IO;
		head.len = user_info.GetLength();

		POSITION po = pSocket->clist->GetHeadPosition();
		while(po != NULL) //将最新的用户列表转发给各个用户
		{
			pSock = (CClientSocket*)pSocket->clist->GetNext(po);
			pSock->Send((char*)&head, sizeof(Header));
			pSock->Send((LPCTSTR)user_info, user_info.GetLength());
		}
	}
}


void CSelfRoomDlg::OnStop()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pSocket->Close();
	m_pSocket = NULL;
	CTime time = CTime::GetCurrentTime();
	CString t = time.Format("%H:%M:%S");
	CString strTemp = t + " 管理员" + theApp.m_strName + " 关闭聊天室\r\n";
	m_MessageList.ReplaceSel(strTemp);
	m_UserList.ResetContent();
	this->SetWindowTextA("聊天室管理-SelfRoom");

	//界面
	m_Admin.EnableWindow(true);
	m_Admin.SetFocus();
	ServerIP.EnableWindow(true);
	ServerPort.EnableWindow(true);
	m_Start.EnableWindow(true);
	m_Stop.EnableWindow(false);
	m_Exit.EnableWindow(true);
}


void CSelfRoomDlg::GetIPAndPort()
{
	// TODO: 在此添加控件通知处理程序代码
	CAboutDlg dlg;
	dlg.DoModal();
}
