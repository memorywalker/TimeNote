#include "StdAfx.h"
#include "XMLHandle.h"


CXMLHandle::CXMLHandle(CString &csRoot)
{
	HRESULT hr;
	hr = ::CoInitialize(NULL);	

	hr = m_pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument40));
	if (!SUCCEEDED(hr))
	{
		AfxMessageBox(_T("无法创建DOMDocument对象"));
		return;
	}
	m_pDoc->load("TimeNotes.xml");
	m_pDoc->preserveWhiteSpace = TRUE;
	//创建root元素并添加到文档中
	//m_xmlRoot = m_pDoc->createElement((_bstr_t)csRoot);
	//m_xmlRoot = m_pDoc->selectSingleNode("Notes");
	hr = m_pDoc->get_documentElement(&m_xmlRoot);
	//设置属性
	//m_xmlRoot->setAttribute("id",_T("root"));
	//m_pDoc->appendChild(m_xmlRoot);	
}

CXMLHandle::~CXMLHandle(void)
{
	::CoUninitialize();
}


// 写入XML文件
void CXMLHandle::Write(CString &csFile)
{
	HRESULT hr;
	hr = m_pDoc->save((_bstr_t)csFile);
	if (!SUCCEEDED(hr))
	{
		AfxMessageBox(_T("无法写入DOMDocument对象"));
		return;
	}
}


// 添加一个节点到根节点
void CXMLHandle::AppendToRoot(MSXML2::IXMLDOMElementPtr pNode)
{
	m_xmlRoot->appendChild(m_pDoc->createTextNode("\r\n\t")); //增加缩进
	m_xmlRoot->appendChild(pNode);
}


// 创建一个节点
MSXML2::IXMLDOMElementPtr CXMLHandle::CreateNode(CString &csName, CString csContent)
{
	MSXML2::IXMLDOMElementPtr pNode;
	pNode=m_pDoc->createElement((_bstr_t)csName);
	pNode->Puttext((_bstr_t)csContent);
	return pNode;
}

// 创建一个文本节点
MSXML2::IXMLDOMTextPtr CXMLHandle::CreateTextNode( CString csContent)
{
	MSXML2::IXMLDOMTextPtr pNode;
	pNode=m_pDoc->createTextNode((_bstr_t)csContent);
	return pNode;
}