
// MFC_06_FileBrowseDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFC_06_FileBrowse.h"
#include "MFC_06_FileBrowseDlg.h"
#include "afxdialogex.h"

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


// CMFC06FileBrowseDlg 对话框



CMFC06FileBrowseDlg::CMFC06FileBrowseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_06_FILEBROWSE_DIALOG, pParent)
	, m_szPath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC06FileBrowseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_szPath);
}

BEGIN_MESSAGE_MAP(CMFC06FileBrowseDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, &CMFC06FileBrowseDlg::OnBnClickedButtonBrowse)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CMFC06FileBrowseDlg 消息处理程序

BOOL CMFC06FileBrowseDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFC06FileBrowseDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFC06FileBrowseDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFC06FileBrowseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC06FileBrowseDlg::OnBnClickedButtonBrowse()
{
	// TODO: 在此添加控件通知处理程序代码
		// TODO: Add your control notification handler code here
	// 过滤器
	static TCHAR BASED_CODE szFilter[] = _T("JPG (*.jpg)|*.jpg|")
		_T("BMP文件 (*.bmp)|*.bmp|")
		_T("PNG文件 (*.png)|*.png|")
		/*_T("All Files (*.*)|*.*||")*/;

	
	CFileDialog Filedlg(TRUE, _T(""), NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter, NULL);
	
	// 弹出对话框
	if (Filedlg.DoModal() != IDOK)
	{
		return;
	}
	m_szPath = Filedlg.GetPathName();

	UpdateData(FALSE);
}


void CMFC06FileBrowseDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UINT count;
	TCHAR filePath[MAX_PATH] = { 0 };

	count = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	if (count == 1)
	{
		DragQueryFile(hDropInfo, 0, filePath, sizeof(filePath));
		m_szPath = filePath;
		UpdateData(FALSE);
		DragFinish(hDropInfo);

		CDialog::OnDropFiles(hDropInfo);
		return;

	}
	else
	{
		//m_vectorFile.clear();
		for (UINT i = 0; i < count; i++)
		{
			int pathLen = DragQueryFile(hDropInfo, i, filePath, sizeof(filePath));
			m_szPath = filePath;
			//m_vectorFile.push_back(filePath);
			//break;
		}

		UpdateData(FALSE);
		DragFinish(hDropInfo);
	}

	CDialogEx::OnDropFiles(hDropInfo);
}
