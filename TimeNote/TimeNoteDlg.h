
// TimeNoteDlg.h : ͷ�ļ�
//

#pragma once
#include "atlcomtime.h"


// CTimeNoteDlg �Ի���
class CTimeNoteDlg : public CDialogEx
{
// ����
public:
	CTimeNoteDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TIMENOTE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnWrite();
	// ��Ϣ���⣬��Ϊ��
	CString m_csTitle;
	// ��ϸ����
	CString m_csContent;
	// ��¼��ǰʱ��
	COleDateTime m_dtWriteTime;
	// �Ƿ�ʹ�õ�ǰʱ��
	BOOL m_bCurrentTime;
	// ��ʼ��ʱ����XML�ļ�
	void CreateXMLFile(void);
};
