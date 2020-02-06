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
	str += _T("服务器端成功");
	dlg->m_list.AddString(str);

	dlg->m_list.UpdateData(FALSE);

	CAsyncSocket::OnConnect(nErroCode);
};

void CMySocket::OnReceive(int nErroCode)
{
	TRACE("#####OnReceive");
	//获取内容
	CMFChatClientDlg* dlg = (CMFChatClientDlg*)AfxGetApp()->GetMainWnd();
	char strTmp[200] = {0};
	Receive(strTmp, 200, 0);

	USES_CONVERSION;
	CString szstrTmp = A2T(strTmp);
	
	//显示
	CString strShow;
	dlg->m_time = CTime::GetCurrentTime();
	strShow = dlg->m_time.Format("%X");
	strShow += _T("服务端发来的:") + szstrTmp;
	dlg->m_list.AddString(strShow);
	//dlg->m_list.UpdateData(FALSE);

	CAsyncSocket::OnReceive(nErroCode);
};

CMySocket::~CMySocket()
{

};