
// MFChatClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFChatClient.h"
#include "MFChatClientDlg.h"
#include "afxdialogex.h"
#include "CMySocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFChatClientDlg 对话框



CMFChatClientDlg::CMFChatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCHATCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDC_SENDMS_EDIT, m_input);
	DDX_Control(pDX, IDC_COLOR_COMBO, CWordColor);
}

BEGIN_MESSAGE_MAP(CMFChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFChatClientDlg::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_CONNECT_BTN, &CMFChatClientDlg::OnBnClickedConnectBtn)
	ON_BN_CLICKED(IDC_NAME_BTN, &CMFChatClientDlg::OnBnClickedNameBtn)
	ON_BN_CLICKED(IDC_CLEAN_BTN, &CMFChatClientDlg::OnBnClickedCleanBtn)
	ON_BN_CLICKED(IDC_DISCONNECT_BTN, &CMFChatClientDlg::OnBnClickedDisconnectBtn)
	ON_BN_CLICKED(IDC_AUTOSEND_CHECK, &CMFChatClientDlg::OnBnClickedAutosendCheck)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMFChatClientDlg 消息处理程序

BOOL CMFChatClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("6000"));
	GetDlgItem(IDC_IPADDRESS)->SetWindowText(_T("127.0.0.1"));

	//显示昵称
	CString strName;
	//获取路径
	WCHAR strPath[MAX_PATH] = { 0 };
	WCHAR szstrName[MAX_PATH] = { 0 };
	GetCurrentDirectoryW(MAX_PATH, strPath);
	TRACE("####strPath:%ls", strPath);
	//配置昵称文件
	CString strFilePath;
	strFilePath.Format(L"%ls//Text.ini", strPath);

	//读取配置文件
	DWORD dwNum = GetPrivateProfileStringW(_T("CLIENT"), _T("NAME"),NULL, szstrName,MAX_PATH, strFilePath);
	if (dwNum > 0)
	{
		GetDlgItem(IDC_SAVENAME_EDIT)->SetWindowTextW(szstrName);
		UpdateData(FALSE);
	}
	else
	{
		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), L"客户端:", strFilePath);
		GetDlgItem(IDC_SAVENAME_EDIT)->SetWindowText(L"客户端:");
		UpdateData(FALSE);
	}

	GetDlgItem(IDC_CONNECT_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_AUTOSEND_CHECK)->EnableWindow(FALSE);

	CWordColor.AddString(_T("黑色"));
	CWordColor.AddString(_T("红色"));
	CWordColor.AddString(_T("绿色"));
	CWordColor.AddString(_T("蓝色"));

	CWordColor.SetCurSel(0);
	GetDlgItem(IDC_COLOR_COMBO)->SetWindowText(_T("黑色"));

	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFChatClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//1.获取目标区域
		CPaintDC dc(this); // 用于绘制的设备上下文
		CRect Rect;
		GetClientRect(&Rect);

		//2.加载图片资源并存到兼容设备上下文中
		CDC dcBmp;
		dcBmp.CreateCompatibleDC(&dcBmp);

		CBitmap bmpBackground;
		bmpBackground.LoadBitmap(IDB_HILL_BITMAP);

		BITMAP bBitmap;
		bmpBackground.GetBitmap(&bBitmap);

		//3.显示图片
		CBitmap* pOldBitmp = dcBmp.SelectObject(&bmpBackground);
		
		dc.StretchBlt(0, 0, Rect.Width(), Rect.Height(), &dcBmp, 
			0, 0, bBitmap.bmWidth, bBitmap.bmHeight, SRCCOPY);



		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString  CMFChatClientDlg::CatStrShow(CString strInfo,CString strMsg)
{
	CString strShow;
	CTime ctim;
	ctim = CTime::GetCurrentTime();
	strShow = ctim.Format("%X");
	strShow += strInfo + strMsg;
	return strShow;
}


void CMFChatClientDlg::OnBnClickedSendBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//1.获取发送的内容
	CString strTmpMsg;
	CString strName;
	GetDlgItem(IDC_SENDMS_EDIT)->GetWindowText(strTmpMsg);
	GetDlgItem(IDC_SAVENAME_EDIT)->GetWindowTextW(strName);
	strTmpMsg = strName + _T(":") + strTmpMsg;
	USES_CONVERSION;
	char* szstrTmpMsg = T2A(strTmpMsg);
	//发送
	sockCli->Send(szstrTmpMsg, BUFF_MAX_SIZE,0);

	//2.显示
	CString strShow;
	strName = _T("");
	strShow = CatStrShow(strName, strTmpMsg);


	m_list.AddString(strShow);
	m_list.UpdateData(FALSE);

	GetDlgItem(IDC_SENDMS_EDIT)->SetWindowText(_T(""));
	
}


void CMFChatClientDlg::OnBnClickedConnectBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	TRACE("##OnBnClickedConnectBtn");
	CString strIP, strPort;
	//获取组控件内容
	GetDlgItem(IDC_IPADDRESS)->GetWindowText(strIP);
	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(strPort);

	//CString 转化成char*
	//使用宏转化
	USES_CONVERSION;
	LPCSTR szIP = (LPCSTR)T2A(strIP);
	LPCSTR szPort = (LPCSTR)T2A(strPort);

	TRACE("szIP = %s,szPort = %s",szIP,szPort);

	int iPort = _ttoi(strPort);
	//创建套接字
	sockCli = new CMySocket;

	if (!sockCli->Create())
	{
		TRACE("sockCli Create erroCode %d",GetLastError());
		return;
	}

	if (sockCli->Connect(strIP, iPort) != SOCKET_ERROR)
	{
		TRACE("socckCli Connect erroCode %d",GetLastError());
		return;
	}
	
}


void CMFChatClientDlg::OnBnClickedNameBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strName;
	GetDlgItem(IDC_SAVENAME_EDIT)->GetWindowText(strName);

	if (strName.GetLength()<=0)
	{
		//写入配置文件
		MessageBox(_T("昵称不能为空"));
		return;
	}
	if (IDOK == AfxMessageBox(_T("确定要修改昵称吗?"),MB_OKCANCEL))
	{

		//获取路径
		WCHAR strPath[MAX_PATH] = { 0 };
		GetCurrentDirectoryW(MAX_PATH, strPath);
		TRACE("####strPath:%ls", strPath);
		//配置昵称文件
		CString strFilePath;
		strFilePath.Format(L"%ls//Text.ini", strPath);
		//写入配置文件
		WritePrivateProfileStringW(_T("CLIENT"),_T("NAME"),strName, strFilePath);
	}

}
	




void CMFChatClientDlg::OnBnClickedCleanBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.ResetContent();
}


void CMFChatClientDlg::OnBnClickedDisconnectBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//控制按键状态
	GetDlgItem(IDC_CONNECT_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_AUTOSEND_CHECK)->EnableWindow(FALSE);

	CString strTmpMsg = _T("断开连接");
	CString strName;
	GetDlgItem(IDC_SAVENAME_EDIT)->GetWindowTextW(strName);
	strTmpMsg = strName + strTmpMsg;
	USES_CONVERSION;
	char* szstrTmpMsg = T2A(strTmpMsg);
	//发送
	sockCli->Send(szstrTmpMsg, BUFF_MAX_SIZE, 0);

	//2.显示
	CString strShow;
	strName = _T("");
	strShow = CatStrShow(strName, strTmpMsg);
	m_list.AddString(strShow);
	m_list.UpdateData(FALSE);



	//释放内存
	sockCli->Close();
	if (sockCli != NULL)
	{
		delete sockCli;
		sockCli = NULL;
	}

}


void CMFChatClientDlg::OnBnClickedAutosendCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(IDC_AUTOSEND_CHECK))->GetCheck())
	{
		((CButton*)GetDlgItem(IDC_AUTOSEND_CHECK))->SetCheck(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_AUTOSEND_CHECK))->SetCheck(TRUE);
	}

}


HBRUSH CMFChatClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	CString str;
	GetDlgItem(IDC_COLOR_COMBO)->GetWindowText(str);//能否可行?

	if(IDC_LIST == pWnd->GetDlgCtrlID() || IDC_SENDMS_EDIT == pWnd->GetDlgCtrlID())
	{
		if (str == _T("黑色"))
		{
			pDC->SetTextColor(RGB(0,0,0));
		}
		else if(str == _T("红色"))
		{
			pDC->SetTextColor(RGB(255, 0, 0));
		}
		else if (str == _T("绿色"))
		{
			pDC->SetTextColor(RGB(0, 255, 0));
		}
		else if (str == _T("蓝色"))
		{
			pDC->SetTextColor(RGB(0, 0, 255));
		}
	}
	
	return hbr;
}


BOOL CMFChatClientDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	//实现Ctrl+ X键 的退出功能
	if (pMsg->message == WM_KEYDOWN)
	{
		if (GetKeyState(VK_CONTROL))
		{
			if (pMsg->wParam == 'X')
			{
				CDialogEx::OnOK();
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
