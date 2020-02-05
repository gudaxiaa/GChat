#pragma once
#include <afxsock.h>
class CMySocket :
	public CAsyncSocket
{
public:
	CMySocket();
	virtual void OnConnect(int nErroCode);
	virtual void OnReceive(int nErroCode);
	virtual ~CMySocket();
};

