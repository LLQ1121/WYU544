
// SelfRoom.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSelfRoomApp:
// �йش����ʵ�֣������ SelfRoom.cpp
//

class CSelfRoomApp : public CWinApp
{
public:
	CSelfRoomApp();

	CString m_strName; //��ʾ�û�����

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSelfRoomApp theApp;