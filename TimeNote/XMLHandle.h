#pragma once
class CXMLHandle
{
public:
	CXMLHandle(CString &csRoot);
	~CXMLHandle(void);
	// 写入XML文件
	void Write(CString &csFile);
public:
	MSXML2::IXMLDOMDocumentPtr m_pDoc;
	MSXML2::IXMLDOMElementPtr m_xmlRoot;
	// 添加一个节点到根节点
	void AppendToRoot(MSXML2::IXMLDOMElementPtr pNode);
	// 创建一个节点
	MSXML2::IXMLDOMElementPtr CreateNode(CString &csName, CString csContent=(_T("")));
	// 创建一个文本节点
	MSXML2::IXMLDOMTextPtr CXMLHandle::CreateTextNode( CString csContent);
};

