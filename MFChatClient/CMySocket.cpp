#include "pch.h"
#include "CMySocket.h"
#include "MFChatClient.h"
#include "MFChatClientDlg.h"

CMySocket::CMySocket()
{

};

//回调  当Dlg调用Connect函数时
void CMySocket::OnConnect(int nErroCode)
{
	TRACE("####OnConnect");
	CMFChatClientDlg* dlg = (CMFChatClientDlg*)AfxGetApp()->GetMainWnd();
	CString str;
	dlg->m_time = CTime::GetCurrentTime();
	str = dlg->m_time.Format("%X");
	str += _T("连接成功");
	dlg->m_list.AddString(str);

	CAsyncSocket::OnConnect(nErroCode);
};

void CMySocket::OnReceive(int nErroCode)
{

};

CMySocket::~CMySocket()
{

};