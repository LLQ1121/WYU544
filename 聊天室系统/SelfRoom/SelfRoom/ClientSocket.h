#pragma once

// CClientSocket 命令目标
#include "SelfRoomDlg.h" //进行对话框指针操作

class CClientSocket : public CSocket
{
	public:
		CClientSocket();
		virtual ~CClientSocket();

		CString m_strName; //显示用户名称
		CPtrList *clist; //程序使用的Socket队列数据结构
		CSelfRoomDlg *m_dlgServer; //应用对话指针机制
		CClientSocket(CPtrList *list); //生成一个Socket队列

		//成员函数
		void OnReceive(int nErrorCode); //接收客户端发出的消息
		void OnClose(int nErrorCode); //处理客户端离开操作
		
};


