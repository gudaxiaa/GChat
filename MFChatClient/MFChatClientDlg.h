﻿
// MFChatClientDlg.h: 头文件
//

#pragma once
#include "CMySocket.h"

// CMFChatClientDlg 对话框
class CMFChatClientDlg : public CDialogEx
{
// 构造
public:
	CMFChatClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCHATCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSendBtn();
	afx_msg void OnBnClickedConnectBtn();
	CString  CatStrShow(CString strInfo, CString strMsg);
	CMySocket* sockCli;
	CListBox m_list;
	//CTime m_time;
	CEdit m_input;
	afx_msg void OnBnClickedNameBtn();
	
	afx_msg void OnBnClickedCleanBtn();
	afx_msg void OnBnClickedDisconnectBtn();
	afx_msg void OnBnClickedAutosendCheck();
	CComboBox CWordColor;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
