#pragma once
#define  BUFF_MAX_SIZE  1024
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

