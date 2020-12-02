
// SelfRoomDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CSelfRoomDlg �Ի���




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


// CSelfRoomDlg ��Ϣ�������

BOOL CSelfRoomDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_pSocket = NULL;
	clientSocket = NULL;
	//��ʼ����
	m_Admin.SetFocus();
	m_Stop.EnableWindow(false);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSelfRoomDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSelfRoomDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSelfRoomDlg::OnStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(); //ˢ�½��棬��ȡ�û�����
	m_pSocket = new CServerSocket;

	//��ȡ����Ա���õ�IP
	BYTE nFild[4];
	CString sIP;
	ServerIP.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);

	CTime time = CTime::GetCurrentTime();//��ȡ��ǰʱ��
	
	//������������֤
	if(m_strName.IsEmpty())
	{
		AfxMessageBox("���ȵǼǹ���Ա��!");
		return;
	}
	if(sIP.IsEmpty())
	{
		AfxMessageBox("������������IP!");
		return;
	}
	if(sPort.IsEmpty())
	{
		AfxMessageBox("������Ҫ���ŵĶ˿�!");
		return;
	}

	//����
	m_Admin.EnableWindow(false);
	ServerIP.EnableWindow(false);
	ServerPort.EnableWindow(false);
	m_Start.EnableWindow(false);
	m_Stop.EnableWindow(true);
	m_Exit.EnableWindow(false);

	//���������ң����Ƚ������ڼ������׽���
	if(m_pSocket->Create(atoi(sPort),1,sIP))
	{
		m_MessageList.SetWindowTextA("");
		m_MessageList.ReplaceSel("�����ҿ����ɹ�!\r\n");
		CString t = time.Format("%Y-%m-%d");
		m_MessageList.ReplaceSel("����: "+ t +"\r\n");
		t = time.Format("%H:%M:%S"); //��������ҿ�����ʱ��
		theApp.m_strName = m_strName; //��¼����Ա��
		m_MessageList.ReplaceSel(t+" ����Ա" + theApp.m_strName + " ����������\r\n");
	}
	//��ʼ����
	if(m_pSocket->Listen())
	{
		m_MessageList.ReplaceSel("�ȴ���Ա����...\r\n");
	}

	m_UserList.ResetContent();
	m_UserList.AddString(theApp.m_strName + "(����Ա)");
	this->SetWindowTextA("����Ա:" + m_strName + "-SelfRoom");
}

void CSelfRoomDlg::UpdateUser(CClientSocket *pSocket)
{
	m_UserList.ResetContent();
	m_UserList.AddString(theApp.m_strName + "(����Ա)"); //������ӹ���Ա�û�
	CString user_info;
	user_info = theApp.m_strName + "(����Ա)" + "&";
	if(pSocket != NULL)
	{
		CClientSocket *pSock = NULL;
		POSITION pos = pSocket->clist->GetHeadPosition();
		while(pos != NULL)
		{
			pSock = (CClientSocket*)pSocket->clist->GetNext(pos);
			m_UserList.AddString(pSock->m_strName); //Ȼ���������Ѿ���¼���û���
			user_info += (pSock->m_strName + "&");
		}
		Header head;
		head.type = LOGIN_IO;
		head.len = user_info.GetLength();

		POSITION po = pSocket->clist->GetHeadPosition();
		while(po != NULL) //�����µ��û��б�ת���������û�
		{
			pSock = (CClientSocket*)pSocket->clist->GetNext(po);
			pSock->Send((char*)&head, sizeof(Header));
			pSock->Send((LPCTSTR)user_info, user_info.GetLength());
		}
	}
}


void CSelfRoomDlg::OnStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pSocket->Close();
	m_pSocket = NULL;
	CTime time = CTime::GetCurrentTime();
	CString t = time.Format("%H:%M:%S");
	CString strTemp = t + " ����Ա" + theApp.m_strName + " �ر�������\r\n";
	m_MessageList.ReplaceSel(strTemp);
	m_UserList.ResetContent();
	this->SetWindowTextA("�����ҹ���-SelfRoom");

	//����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAboutDlg dlg;
	dlg.DoModal();
}
