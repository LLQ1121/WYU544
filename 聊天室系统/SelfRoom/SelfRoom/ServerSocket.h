#pragma once

// CServerSocket ����Ŀ��

class CServerSocket : public CSocket
{
public:
	CServerSocket();
	virtual ~CServerSocket();

	CPtrList connectList;
	void OnAccept(int nErrorCode); //�����³�Ա���������� //////////////?

	//��Ա����
};


