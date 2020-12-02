
// SelfChatDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SelfChat.h"
#include "SelfChatDlg.h"
#include "afxdialogex.h"
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


// CSelfChatDlg 对话框




CSelfChatDlg::CSelfChatDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSelfChatDlg::IDD, pParent)
	, m_strName(_T(""))
	, strport(_T(""))
	, m_strMessage(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSelfChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Usr);
	DDX_Text(pDX, IDC_EDIT1, m_strName);
	DDX_Control(pDX, IDC_IPADDRESS1, ServerIP);
	DDX_Control(pDX, IDC_EDIT2, m_port);
	DDX_Text(pDX, IDC_EDIT2, strport);
	DDX_Control(pDX, IDC_LIST1, m_UserList);
	DDX_Control(pDX, IDC_EDIT3, m_MessageList);
	DDX_Control(pDX, IDC_EDIT4, m_EditWords);
	DDX_Text(pDX, IDC_EDIT4, m_strMessage);
	DDX_Control(pDX, IDC_BUTTON4, m_Send);
	DDX_Control(pDX, IDC_BUTTON3, m_Refresh);
	DDX_Control(pDX, IDC_BUTTON1, m_Enter);
	DDX_Control(pDX, IDC_BUTTON2, m_Quit);
	DDX_Control(pDX, IDC_BUTTON6, m_Exit);
}

BEGIN_MESSAGE_MAP(CSelfChatDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSelfChatDlg::OnEnter)
	ON_BN_CLICKED(IDC_BUTTON4, &CSelfChatDlg::OnSend)
	ON_BN_CLICKED(IDC_BUTTON2, &CSelfChatDlg::OnQuit)
	ON_BN_CLICKED(IDC_BUTTON3, &CSelfChatDlg::OnRefresh)
	ON_BN_CLICKED(IDC_BUTTON5, &CSelfChatDlg::GetIPAndPort)
END_MESSAGE_MAP()


// CSelfChatDlg 消息处理程序

BOOL CSelfChatDlg::OnInitDialog()
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
	//初始界面
	m_Usr.SetFocus();
	m_Quit.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_Send.EnableWindow(false);
	m_Refresh.EnableWindow(false);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSelfChatDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSelfChatDlg::OnPaint()
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
HCURSOR CSelfChatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSelfChatDlg::OnEnter()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_pSocket = new CClientSocket;
	m_pSocket->GetDlg(this); //获取主界面指针

	//获取用户输入的服务器IP
	BYTE nFild[4];
	CString sip;
	ServerIP.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);
	sip.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);

	//输入完整性验证
	if(m_strName.IsEmpty())
	{
		AfxMessageBox("请输入昵称!");
		return;
	}
	if(sip.IsEmpty())
	{
		AfxMessageBox("请输入ip!");
		return;
	}
	if(strport.IsEmpty())
	{
		AfxMessageBox("请输入连接端口!");
		return;
	}

	//发起连接
	if(!m_pSocket->Create())
	{
		AfxMessageBox("网络创建错误!");
		m_pSocket->Close();
		return;
	}
	if(!m_pSocket->Connect(sip,atoi(strport)))
	{
		AfxMessageBox("连接服务器失败!");
		m_pSocket->Close();
		return;
	}

	//界面
	m_Usr.EnableWindow(false);
	ServerIP.EnableWindow(false);
	m_port.EnableWindow(false);
	m_Enter.EnableWindow(false);
	m_Quit.EnableWindow(true);
	m_EditWords.EnableWindow(true);
	m_EditWords.SetFocus();
	m_Send.EnableWindow(true);
	m_Refresh.EnableWindow(true);
	m_Exit.EnableWindow(false);

	Header head;
	head.type = LOGIN_IO;
	head.len = m_strName.GetLength();

	m_pSocket->Send((char*)&head,sizeof(Header));
	m_pSocket->Send(m_strName,m_strName.GetLength()); //发送会话消息

	theApp.m_strName = m_strName;
	m_MessageList.SetWindowTextA("");
	this->SetWindowTextA(m_strName + "-SelfChat"); //标题栏实时动态显示用户名
}


void CSelfChatDlg::OnSend()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if(m_strMessage == "")
	{
		AfxMessageBox("不能发送空消息!");
		m_EditWords.SetFocus();
		return;
	}
	Header head;
	head.type = SEND_MESSAGE; //聊天内容头型为SEND_MESSAGE
	head.len = m_strMessage.GetLength();

	m_pSocket->Send((char*)&head,sizeof(Header));
	if(m_pSocket->Send(m_strMessage,m_strMessage.GetLength()))
	{
		m_strMessage = "";
		UpdateData(FALSE);
		m_EditWords.SetFocus();
		return;
	}
	else
	{
		AfxMessageBox("网络传输错误!");
	}
}

BOOL CSelfChatDlg::GetMsgFromRoom()
{
	char buff[1000];
	memset(buff,0,sizeof(buff));
	m_pSocket->Receive(buff,sizeof(buff)); //接收信息
	m_pSocket->AsyncSelect(FD_CLOSE|FD_READ|FD_WRITE);

	CString strTemp =buff;
	strTemp += "\r\n";
	m_MessageList.ReplaceSel(strTemp); //直接显示在界面上即可
	return TRUE;
}

void CSelfChatDlg::UpdateUser()
{
	char buff[1000];
	memset(buff,0,sizeof(buff));
	m_pSocket->Receive(buff,sizeof(buff)); //接收到最新的在线用户名单
	m_pSocket->AsyncSelect(FD_CLOSE|FD_READ|FD_WRITE);

	CString user_info = buff;
	CString array[100];
	int b = 0;
	for(int i=0; i<user_info.GetAllocLength(); i++) //遍历名单中的所有用户
	{
		if(i != (user_info.GetLength() - 1))
		{
			if(user_info[i] == '&')
			{
				b++;
			}
			else
			{
				array[b] = array[b] + user_info[i];
			}	
		}
	}
	m_UserList.ResetContent();
	for(int j=0; j<b; j++)
	{
		m_UserList.AddString(array[j]); //用户名一次显示与界面列表中
	}
}

void CSelfChatDlg::OnQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_pSocket)
	{
		m_pSocket->Close();
		delete m_pSocket; //销毁Socket队列
	}
	m_UserList.ResetContent();
	m_MessageList.ReplaceSel("已经退出聊天室");
	this->SetWindowTextA("聊天室客户端-SelfChat");

	//界面
	m_Usr.EnableWindow(true);
	m_Usr.SetFocus();
	ServerIP.EnableWindow(true);
	m_port.EnableWindow(true);
	m_Enter.EnableWindow(true);
	m_Quit.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_Send.EnableWindow(false);
	m_Exit.EnableWindow(true);
}


void CSelfChatDlg::OnRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
	m_MessageList.SetWindowTextA("");
}


void CSelfChatDlg::GetIPAndPort()
{
	// TODO: 在此添加控件通知处理程序代码
	CAboutDlg dlg;
	dlg.DoModal();
}
