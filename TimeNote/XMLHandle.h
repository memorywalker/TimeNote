#pragma once
class CXMLHandle
{
public:
	CXMLHandle(CString &csRoot);
	~CXMLHandle(void);
	// д��XML�ļ�
	void Write(CString &csFile);
public:
	MSXML2::IXMLDOMDocumentPtr m_pDoc;
	MSXML2::IXMLDOMElementPtr m_xmlRoot;
	// ���һ���ڵ㵽���ڵ�
	void AppendToRoot(MSXML2::IXMLDOMElementPtr pNode);
	// ����һ���ڵ�
	MSXML2::IXMLDOMElementPtr CreateNode(CString &csName, CString csContent=(_T("")));
	// ����һ���ı��ڵ�
	MSXML2::IXMLDOMTextPtr CXMLHandle::CreateTextNode( CString csContent);
};

