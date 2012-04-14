
// TimeNoteDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TimeNote.h"
#include "TimeNoteDlg.h"
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
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTimeNoteDlg 对话框




CTimeNoteDlg::CTimeNoteDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTimeNoteDlg::IDD, pParent)
	, m_csTitle(_T(""))
	, m_csContent(_T(""))
	, m_dtWriteTime(COleDateTime::GetCurrentTime())
	, m_bCurrentTime(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTimeNoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_csTitle);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_csContent);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_WRITETIME, m_dtWriteTime);
	DDX_Check(pDX, IDC_CHECK_CURRENT_TIME, m_bCurrentTime);
}

BEGIN_MESSAGE_MAP(CTimeNoteDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_WRITE, &CTimeNoteDlg::OnBnClickedBtnWrite)
END_MESSAGE_MAP()


// CTimeNoteDlg 消息处理程序

BOOL CTimeNoteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	((CButton*)GetDlgItem(IDC_CHECK_CURRENT_TIME))->SetCheck(1);//默认选种使用点击write按钮最新的时间

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTimeNoteDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTimeNoteDlg::OnPaint()
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
HCURSOR CTimeNoteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//使用控件数据关联的方式 将获取数据写入到文本中
void CTimeNoteDlg::OnBnClickedBtnWrite()
{
	UpdateData(TRUE);
	if (m_bCurrentTime)
	{
		m_dtWriteTime = COleDateTime::GetCurrentTime();
	}
	CString csTime = m_dtWriteTime.Format(_T("%Y-%m-%d %H:%M:%S"));
	csTime = _T("Time: ") + csTime;
	m_csContent = _T("Content: ") + m_csContent;
	m_csTitle = _T("Title: ") + m_csTitle;

	CFile FileOut = CFile(_T("TimeNote.xml"),  CFile::modeWrite|CFile::modeCreate|CFile::modeNoTruncate);
	if (0==FileOut.GetLength())
	{//第一次创建文件要加入Unicode标识
		unsigned short int feffA=0xfeff;   
		FileOut.Write(&feffA,sizeof(short int));
	}	
	FileOut.SeekToEnd();
	CString csNewLine = _T("\r\n----------------------------------------\r\n");
	FileOut.Write(csNewLine,csNewLine.GetLength()*sizeof(TCHAR));
	FileOut.Write(csTime,csTime.GetLength()*sizeof(TCHAR));	
	FileOut.Write(_T("\r\n"),2*sizeof(TCHAR));
	FileOut.Write(m_csTitle,m_csTitle.GetLength()*sizeof(TCHAR));
	FileOut.Write(_T("\r\n"),2*sizeof(TCHAR));
	FileOut.Write(m_csContent,m_csContent.GetLength()*sizeof(TCHAR));
	MessageBoxW(_T("Write Successfully!"));

	FileOut.Close();
}
/*//使用获取控件文本的方式获取数据，写入到普通的文本文件中
void CTimeNoteDlg::OnBnClickedBtnWrite()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd* EditTitle = GetDlgItem(IDC_EDIT_TITLE);
	CWnd* EditContent = GetDlgItem(IDC_EDIT_CONTENT);
	CWnd* TimePicker = GetDlgItem(IDC_DATETIMEPICKER_WRITETIME);
	CString csTitle, csContent, csTime;
	EditTitle->GetWindowTextW(csTitle);
	EditContent->GetWindowTextW(csContent);
	TimePicker->GetWindowTextW(csTime);

	csTime = _T("Time: ") + csTime;
	csContent = _T("Content: ") + csContent;
	csTitle = _T("Title: ") + csTitle;

	CFile FileOut = CFile(_T("TimeNote.xml"),  CFile::modeWrite|CFile::modeCreate|CFile::modeNoTruncate);
	if (0==FileOut.GetLength())
	{//第一次创建文件要加入Unicode标识
		unsigned short int feffA=0xfeff;   
		FileOut.Write(&feffA,sizeof(short int));
	}	
	FileOut.SeekToEnd();
	CString csNewLine = _T("\r\n----------------------------------------\r\n");
	FileOut.Write(csNewLine,csNewLine.GetLength()*sizeof(TCHAR));
	FileOut.Write(csTime,csTime.GetLength()*sizeof(TCHAR));	
	FileOut.Write(_T("\r\n"),2*sizeof(TCHAR));
	FileOut.Write(csTitle,csTitle.GetLength()*sizeof(TCHAR));
	FileOut.Write(_T("\r\n"),2*sizeof(TCHAR));
	FileOut.Write(csContent,csContent.GetLength()*sizeof(TCHAR));
	MessageBoxW(_T("Write Successfully!"));

	FileOut.Close();
}
*/
