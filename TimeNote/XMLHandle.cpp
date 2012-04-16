#include "StdAfx.h"
#include "XMLHandle.h"


CXMLHandle::CXMLHandle(CString &csRoot)
{
	HRESULT hr;
	hr = ::CoInitialize(NULL);	

	hr = m_pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument40));
	if (!SUCCEEDED(hr))
	{
		AfxMessageBox(_T("�޷�����DOMDocument����"));
		return;
	}
	m_pDoc->load("TimeNotes.xml");
	m_pDoc->preserveWhiteSpace = TRUE;
	//����rootԪ�ز���ӵ��ĵ���
	//m_xmlRoot = m_pDoc->createElement((_bstr_t)csRoot);
	//m_xmlRoot = m_pDoc->selectSingleNode("Notes");
	hr = m_pDoc->get_documentElement(&m_xmlRoot);
	//��������
	//m_xmlRoot->setAttribute("id",_T("root"));
	//m_pDoc->appendChild(m_xmlRoot);	
}

CXMLHandle::~CXMLHandle(void)
{
	::CoUninitialize();
}


// д��XML�ļ�
void CXMLHandle::Write(CString &csFile)
{
	HRESULT hr;
	hr = m_pDoc->save((_bstr_t)csFile);
	if (!SUCCEEDED(hr))
	{
		AfxMessageBox(_T("�޷�д��DOMDocument����"));
		return;
	}
}


// ���һ���ڵ㵽���ڵ�
void CXMLHandle::AppendToRoot(MSXML2::IXMLDOMElementPtr pNode)
{
	m_xmlRoot->appendChild(m_pDoc->createTextNode("\r\n\t")); //��������
	m_xmlRoot->appendChild(pNode);
}


// ����һ���ڵ�
MSXML2::IXMLDOMElementPtr CXMLHandle::CreateNode(CString &csName, CString csContent)
{
	MSXML2::IXMLDOMElementPtr pNode;
	pNode=m_pDoc->createElement((_bstr_t)csName);
	pNode->Puttext((_bstr_t)csContent);
	return pNode;
}

// ����һ���ı��ڵ�
MSXML2::IXMLDOMTextPtr CXMLHandle::CreateTextNode( CString csContent)
{
	MSXML2::IXMLDOMTextPtr pNode;
	pNode=m_pDoc->createTextNode((_bstr_t)csContent);
	return pNode;
}