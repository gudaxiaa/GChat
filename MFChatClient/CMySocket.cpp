#include "pch.h"
#include "CMySocket.h"
#include "MFChatClient.h"
#include "MFChatClientDlg.h"

CMySocket::CMySocket()
{

};

//�ص�  ��Dlg����Connect����ʱ
void CMySocket::OnConnect(int nErroCode)
{
	TRACE("####OnConnect");
	CMFChatClientDlg* dlg = (CMFChatClientDlg*)AfxGetApp()->GetMainWnd();
	CString str;
	dlg->m_time = CTime::GetCurrentTime();
	str = dlg->m_time.Format("%X");
	str += _T("�������˳ɹ�");
	dlg->m_list.AddString(str);

	dlg->m_list.UpdateData(FALSE);

	CAsyncSocket::OnConnect(nErroCode);
};

void CMySocket::OnReceive(int nErroCode)
{
	
};

CMySocket::~CMySocket()
{

};