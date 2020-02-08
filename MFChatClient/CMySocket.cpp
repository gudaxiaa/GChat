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

/*
	CString str;
	dlg->m_time = CTime::GetCurrentTime();
	str = dlg->m_time.Format("%X");
	str += _T("服务器端成功");
*/
	CString strShow;
	CString strMsg = _T("服务器端连接成功");
	CString strInfo = _T("");
	strShow = dlg->CatStrShow(strInfo, strMsg);

	dlg->m_list.AddString(strShow);
	dlg->m_list.UpdateData(FALSE);

	dlg->GetDlgItem(IDC_CONNECT_BTN)->EnableWindow(FALSE);
	dlg->GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(TRUE);
	dlg->GetDlgItem(IDC_SEND_BTN)->EnableWindow(TRUE);
	dlg->GetDlgItem(IDC_AUTOSEND_CHECK)->EnableWindow(TRUE);

	CAsyncSocket::OnConnect(nErroCode);
};

void CMySocket::OnReceive(int nErroCode)
{
	TRACE("#####OnReceive");
	//获取内容
	CMFChatClientDlg* dlg = (CMFChatClientDlg*)AfxGetApp()->GetMainWnd();
	char strTmp[BUFF_MAX_SIZE] = {0};
	Receive(strTmp, BUFF_MAX_SIZE, 0);

	USES_CONVERSION;
	CString szstrTmp = A2T(strTmp);
	
	//显示
/*	CString strShow;
	dlg->m_time = CTime::GetCurrentTime();
	strShow = dlg->m_time.Format("%X");
	strShow += _T("服务端发来的:") + szstrTmp;
*/
	//显示(优化版)
	CString strShow;
	CString strInfo = _T("服务端:");
	strShow = dlg->CatStrShow(strInfo, szstrTmp);


	dlg->m_list.AddString(strShow);
	//dlg->m_list.UpdateData(FALSE);

	//自动回复
	if (((CButton*)dlg->GetDlgItem(IDC_AUTOSEND_CHECK))->GetCheck())
	{
		//获取编辑框内容
		CString strAutoSend;
		dlg->GetDlgItemText(IDC_AUTOSEND_EDIT, strAutoSend);
		//获取昵称
		CString  strName;
		dlg->GetDlgItemText(IDC_SAVENAME_EDIT, strName);
		//发送消息
		CString strMsg;
		strMsg = strName + _T("[自动回复]") + strAutoSend;
		char* strSendBuff = T2A(strMsg);
		dlg->sockCli->Send(strSendBuff,BUFF_MAX_SIZE,0);

		//显示
		strShow = dlg->CatStrShow(_T(""), strMsg);
		dlg->m_list.AddString(strShow);

	}


	CAsyncSocket::OnReceive(nErroCode);
};

CMySocket::~CMySocket()
{

};