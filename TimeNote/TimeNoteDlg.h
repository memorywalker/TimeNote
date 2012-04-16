
// TimeNoteDlg.h : 头文件
//

#pragma once
#include "atlcomtime.h"


// CTimeNoteDlg 对话框
class CTimeNoteDlg : public CDialogEx
{
// 构造
public:
	CTimeNoteDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TIMENOTE_DIALOG };

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
	afx_msg void OnBnClickedBtnWrite();
	// 信息标题，可为空
	CString m_csTitle;
	// 详细内容
	CString m_csContent;
	// 记录当前时间
	COleDateTime m_dtWriteTime;
	// 是否使用当前时间
	BOOL m_bCurrentTime;
	// 初始化时创建XML文件
	void CreateXMLFile(void);
};
