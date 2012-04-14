
// TimeNoteDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TimeNote.h"
#include "TimeNoteDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CTimeNoteDlg �Ի���




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


// CTimeNoteDlg ��Ϣ�������

BOOL CTimeNoteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	((CButton*)GetDlgItem(IDC_CHECK_CURRENT_TIME))->SetCheck(1);//Ĭ��ѡ��ʹ�õ��write��ť���µ�ʱ��

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTimeNoteDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTimeNoteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//ʹ�ÿؼ����ݹ����ķ�ʽ ����ȡ����д�뵽�ı���
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
	{//��һ�δ����ļ�Ҫ����Unicode��ʶ
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
/*//ʹ�û�ȡ�ؼ��ı��ķ�ʽ��ȡ���ݣ�д�뵽��ͨ���ı��ļ���
void CTimeNoteDlg::OnBnClickedBtnWrite()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	{//��һ�δ����ļ�Ҫ����Unicode��ʶ
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
