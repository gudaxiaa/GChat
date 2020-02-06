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
	TRACE("#####OnReceive");
	//��ȡ����
	CMFChatClientDlg* dlg = (CMFChatClientDlg*)AfxGetApp()->GetMainWnd();
	char strTmp[200] = {0};
	Receive(strTmp, 200, 0);

	USES_CONVERSION;
	CString szstrTmp = A2T(strTmp);
	
	//��ʾ
	CString strShow;
	dlg->m_time = CTime::GetCurrentTime();
	strShow = dlg->m_time.Format("%X");
	strShow += _T("����˷�����:") + szstrTmp;
	dlg->m_list.AddString(strShow);
	//dlg->m_list.UpdateData(FALSE);

	CAsyncSocket::OnReceive(nErroCode);
};

CMySocket::~CMySocket()
{

};