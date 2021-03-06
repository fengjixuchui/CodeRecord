// CShowMsgDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFC_04_dig.h"
#include "CShowMsgDlg.h"
#include "afxdialogex.h"


// CShowMsgDlg 对话框

IMPLEMENT_DYNAMIC(CShowMsgDlg, CDialogEx)

CShowMsgDlg::CShowMsgDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ShowMsgDlg, pParent)
	, m_szPWD(_T(""))
	, m_szUSER(_T(""))
{

}

CShowMsgDlg::~CShowMsgDlg()
{
}

void CShowMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT1, m_szID);
	//  DDX_Control(pDX, IDC_EDIT2, m_szPASS);
	DDX_Text(pDX, IDC_EDIT2, m_szPWD);
	DDX_Text(pDX, IDC_EDIT1, m_szUSER);
}


BEGIN_MESSAGE_MAP(CShowMsgDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_Function, &CShowMsgDlg::OnBnClickedBtnFunction)
END_MESSAGE_MAP()


// CShowMsgDlg 消息处理程序


void CShowMsgDlg::OnBnClickedBtnFunction()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);


	CString szId = m_szUSER;
	CString szPwd = m_szPWD;

	MessageBox(szId + szPwd, szId + szPwd, MB_OK);

	UpdateData(FALSE);
}
