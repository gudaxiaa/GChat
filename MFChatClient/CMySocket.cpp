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

/*
	CString str;
	dlg->m_time = CTime::GetCurrentTime();
	str = dlg->m_time.Format("%X");
	str += _T("�������˳ɹ�");
*/
	CString strShow;
	CString strMsg = _T("�����������ӳɹ�");
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
	//��ȡ����
	CMFChatClientDlg* dlg = (CMFChatClientDlg*)AfxGetApp()->GetMainWnd();
	char strTmp[BUFF_MAX_SIZE] = {0};
	Receive(strTmp, BUFF_MAX_SIZE, 0);

	USES_CONVERSION;
	CString szstrTmp = A2T(strTmp);
	
	//��ʾ
/*	CString strShow;
	dlg->m_time = CTime::GetCurrentTime();
	strShow = dlg->m_time.Format("%X");
	strShow += _T("����˷�����:") + szstrTmp;
*/
	//��ʾ(�Ż���)
	CString strShow;
	CString strInfo = _T("�����:");
	strShow = dlg->CatStrShow(strInfo, szstrTmp);


	dlg->m_list.AddString(strShow);
	//dlg->m_list.UpdateData(FALSE);

	//�Զ��ظ�
	if (((CButton*)dlg->GetDlgItem(IDC_AUTOSEND_CHECK))->GetCheck())
	{
		//��ȡ�༭������
		CString strAutoSend;
		dlg->GetDlgItemText(IDC_AUTOSEND_EDIT, strAutoSend);
		//��ȡ�ǳ�
		CString  strName;
		dlg->GetDlgItemText(IDC_SAVENAME_EDIT, strName);
		//������Ϣ
		CString strMsg;
		strMsg = strName + _T("[�Զ��ظ�]") + strAutoSend;
		char* strSendBuff = T2A(strMsg);
		dlg->sockCli->Send(strSendBuff,BUFF_MAX_SIZE,0);

		//��ʾ
		strShow = dlg->CatStrShow(_T(""), strMsg);
		dlg->m_list.AddString(strShow);

	}


	CAsyncSocket::OnReceive(nErroCode);
};

CMySocket::~CMySocket()
{

};