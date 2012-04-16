
// TimeNoteDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TimeNote.h"
#include "TimeNoteDlg.h"
#include "afxdialogex.h"
#include "XMLHandle.h"

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

	//����XML�ļ�
	CreateXMLFile();
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
	
	//��ȡʱ��
	if (m_bCurrentTime)
	{
		m_dtWriteTime = COleDateTime::GetCurrentTime();
	}
	CString csTime = m_dtWriteTime.Format(_T("%Y-%m-%d %H:%M:%S"));

	//д��XML�ļ�
	CString xmlRoot = _T("Notes");
	CString xmlFile = _T("TimeNotes.xml");
	CXMLHandle xmlhandle(xmlRoot);
	CString NoteNode = _T("Note");
	CString TitleNode = _T("Title");
	CString TimeNode = _T("Time");
	CString ContentNode = _T("Content");

	MSXML2::IXMLDOMElementPtr pNoteNode = xmlhandle.CreateNode(NoteNode);
	MSXML2::IXMLDOMElementPtr pTitleNode = xmlhandle.CreateNode(TitleNode,m_csTitle);
	MSXML2::IXMLDOMElementPtr pContentNode = xmlhandle.CreateNode(ContentNode,m_csContent);
	MSXML2::IXMLDOMElementPtr pTimeNode = xmlhandle.CreateNode(TimeNode,csTime);

	pNoteNode->appendChild(pTimeNode);
	pNoteNode->appendChild(pTitleNode);
	pNoteNode->appendChild(pContentNode);
	
	xmlhandle.AppendToRoot(pNoteNode);
	xmlhandle.Write(xmlFile);

	//д���ı��ļ�
	csTime = _T("Time: ") + csTime;
	m_csContent = _T("Content: ") + m_csContent;
	m_csTitle = _T("Title: ") + m_csTitle;	

	CFile FileOut = CFile(_T("TimeNote.txt"),  CFile::modeWrite|CFile::modeCreate|CFile::modeNoTruncate);
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
	//�������
 	m_csContent.Empty();
	m_csTitle.Empty();
	UpdateData(FALSE);
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


// ��ʼ��ʱ����XML�ļ�
void CTimeNoteDlg::CreateXMLFile(void)
{
	CString filename = _T("TimeNotes.xml");
	//COleDateTime now = COleDateTime::GetCurrentTime();
	CFile FileOut = CFile(filename,  CFile::modeWrite|CFile::modeCreate|CFile::modeNoTruncate);
	//if (FileOut.GetLength()==5*1024*1024) //file size is less than 5MB
	//{
	//	FileOut = 
	//}
	if (0==FileOut.GetLength())
	{//��һ�δ����ļ�Ҫ����Unicode��ʶ
		//unsigned short int feffA=0xfeff;   
		//FileOut.Write(&feffA,sizeof(short int));
		//utf-8
		const unsigned char LeadBytes[]= {0xEF, 0xBB, 0xBF};
		FileOut.Write(LeadBytes, sizeof(LeadBytes));
		//��д��xmlͷ
		//CString header = _T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n<Notes id=\"root\"></Notes>");
		// unicode to UTF8 
		wchar_t* wszString =_T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n<Notes id=\"root\"></Notes>");
		//Ԥת�����õ�����ռ�Ĵ�С������õĺ��������������෴ 
		int u8Len = ::WideCharToMultiByte(CP_UTF8, NULL, wszString, wcslen(wszString), NULL, 0, NULL, NULL); 
		//ͬ�ϣ�����ռ�Ҫ��'\0'�����ռ� 
		//UTF8��Ȼ��Unicode��ѹ����ʽ����Ҳ�Ƕ��ֽ��ַ��������Կ�����char����ʽ���� 
		char* szU8 = new char[u8Len + 1];
		//ת�� 
		//unicode���Ӧ��strlen��wcslen 
		::WideCharToMultiByte(CP_UTF8, NULL, wszString, wcslen(wszString), szU8, u8Len, NULL, NULL); 
		//������'\0' 
		szU8[u8Len] = '\0'; 
		//д������ 
		FileOut.Write(szU8, u8Len * sizeof(char)); 
		FileOut.Flush(); 
		delete[] szU8; 
		szU8 =NULL; 		
	}
	FileOut.Close();
}
