
// TimeNote.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTimeNoteApp:
// �йش����ʵ�֣������ TimeNote.cpp
//

class CTimeNoteApp : public CWinApp
{
public:
	CTimeNoteApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTimeNoteApp theApp;