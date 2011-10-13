#include "Stdafx.h"
#include "Attribute.h"

//////////////////////////////////////////////////////////////////////////

//���캯��
CAttributeManager::CAttributeManager()
{
}

//��������
CAttributeManager::~CAttributeManager()
{
}

//�ӿڲ�ѯ
void * __cdecl CAttributeManager::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IAttributeManager,Guid,dwQueryVer);
	QUERYINTERFACE(IAttributeService,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IAttributeManager,Guid,dwQueryVer);
	return NULL;
}

//��ѯ����
IAttribute * CAttributeManager::QueryAttribute(LPCTSTR pszName)
{
	ASSERT(pszName);
	INT_PTR nAttributeCount=m_Attribute.GetCount();
	if (nAttributeCount>0)
	{
		CAttribute * pAttribute=NULL;
		DWORD dwHashValue=CAttribute::HashAttribute(pszName);
		for (INT_PTR i=0;i<nAttributeCount;i++)
		{
			pAttribute=&m_Attribute[i];
			if (pAttribute->GetHashValue()==dwHashValue)
			{
				LPCTSTR szAttributeName=pAttribute->GetAttributeName();
				bool bSame=(lstrcmp(pszName,szAttributeName)==0);
				if (bSame) return pAttribute;
			}
		}
	}
	return NULL;
}

//��ѯ����
IAttribute * CAttributeManager::QueryAttribute(WORD wIndex)
{
	if (wIndex>=m_Attribute.GetCount()) return NULL;
	return &m_Attribute[wIndex];
}

//ע������
bool CAttributeManager::RegisterAttribute(LPCTSTR pszName, void * pPtr, bool bReadOnly)
{
	//����������
	IAttribute * pAttribute=QueryAttribute(pszName);
	if (pAttribute) return false;

	//����������
	CAttribute Attribute(pszName,pPtr,bReadOnly);
	m_Attribute.Add(Attribute);

	return true;
}


//ע������
bool CAttributeManager::RegisterAttribute(LPCTSTR pszName, INT * pInt, bool bReadOnly)
{
	//����������
	IAttribute * pAttribute=QueryAttribute(pszName);
	if (pAttribute) return false;

	//����������
	CAttribute Attribute(pszName,pInt,bReadOnly);
	m_Attribute.Add(Attribute);

	return true;
}

//ע������
bool CAttributeManager::RegisterAttribute(LPCTSTR pszName, BYTE * pByte, bool bReadOnly)
{
	//����������
	IAttribute * pAttribute=QueryAttribute(pszName);
	if (pAttribute) return false;

	//����������
	CAttribute Attribute(pszName,pByte,bReadOnly);
	m_Attribute.Add(Attribute);

	return true;
}

//ע������
bool CAttributeManager::RegisterAttribute(LPCTSTR pszName, WORD * pWord, bool bReadOnly)
{
	//����������
	IAttribute * pAttribute=QueryAttribute(pszName);
	if (pAttribute) return false;

	//����������
	CAttribute Attribute(pszName,pWord,bReadOnly);
	m_Attribute.Add(Attribute);

	return true;
}

//ע������
bool CAttributeManager::RegisterAttribute(LPCTSTR pszName, LONG * pLong, bool bReadOnly)
{
	//����������
	IAttribute * pAttribute=QueryAttribute(pszName);
	if (pAttribute) return false;

	//����������
	CAttribute Attribute(pszName,pLong,bReadOnly);
	m_Attribute.Add(Attribute);

	return true;
}

//ע������
bool CAttributeManager::RegisterAttribute(LPCTSTR pszName, DWORD * pDword, bool bReadOnly)
{
	//����������
	IAttribute * pAttribute=QueryAttribute(pszName);
	if (pAttribute) return false;

	//����������
	CAttribute Attribute(pszName,pDword,bReadOnly);
	m_Attribute.Add(Attribute);

	return true;
}

//ע������
bool CAttributeManager::RegisterAttribute(LPCTSTR pszName, DOUBLE * pDouble, bool bReadOnly)
{
	//����������
	IAttribute * pAttribute=QueryAttribute(pszName);
	if (pAttribute) return false;

	//����������
	CAttribute Attribute(pszName,pDouble,bReadOnly);
	m_Attribute.Add(Attribute);

	return true;
}

//ע������
bool CAttributeManager::RegisterAttribute(LPCTSTR pszName, CString * pString, bool bReadOnly)
{
	//����������
	IAttribute * pAttribute=QueryAttribute(pszName);
	if (pAttribute) return false;

	//����������
	CAttribute Attribute(pszName,pString,bReadOnly);
	m_Attribute.Add(Attribute);

	return true;
}

//ע������
bool CAttributeManager::UnRegisterAttribute(LPCTSTR pszName)
{
	ASSERT(pszName);
	INT_PTR nAttributeCount=m_Attribute.GetCount();
	if (nAttributeCount>0)
	{
		CAttribute * pAttribute=NULL;
		DWORD dwHashValue=CAttribute::HashAttribute(pszName);
		for (int i=0;i<nAttributeCount;i++)
		{
			pAttribute=&m_Attribute[i];
			if (pAttribute->GetHashValue()==dwHashValue)
			{
				LPCTSTR szAttributeName=pAttribute->GetAttributeName();
				if (lstrcmp(pszName,szAttributeName)==0)
				{
					m_Attribute.RemoveAt(i);
					return true;
				}
			}
		}
	}
	return false;
}

//��ȡ����
bool CAttributeManager::GetAttributeValue(LPCTSTR pszName, VOID * * ppvValue)
{
	IAttribute * pAttribute=QueryAttribute(pszName);
	if (pAttribute==NULL) return false;
	return pAttribute->GetValue(ppvValue);
}

//��ȡ����
bool CAttributeManager::GetAttributeValue(LPCTSTR pszName, INT & iValue)
{
	IAttribute * pAttribute=QueryAttribute(pszName);
	if (pAttribute==NULL) return false;
	return pAttribute->GetValue(iValue);
}

//��ȡ����
bool CAttributeManager::GetAttributeValue(LPCTSTR pszName, BYTE & cbValue)
{
	IAttribute * pAttribute=QueryAttribute(pszName);
	if (pAttribute==NULL) return false;
	return pAttribute->GetValue(cbValue);
}

//��ȡ����
bool CAttributeManager::GetAttributeValue(LPCTSTR pszName, WORD & wValue)
{
	IAttribute * pAttribute=QueryAttribute(pszName);
	if (pAttribute==NULL) return false;
	return pAttribute->GetValue(wValue);
}

//��ȡ����
bool CAttributeManager::GetAttributeValue(LPCTSTR pszName, LONG & lValue)
{
	IAttribute * pAttribute=QueryAttribute(pszName);
	if (pAttribute==NULL) return false;
	return pAttribute->GetValue(lValue);
}

//��ȡ����
bool CAttributeManager::GetAttributeValue(LPCTSTR pszName, DWORD & dwValue)
{
	IAttribute * pAttribute=QueryAttribute(pszName);
	if (pAttribute==NULL) return false;
	return pAttribute->GetValue(dwValue);
}

//��ȡ����
bool CAttributeManager::GetAttributeValue(LPCTSTR pszName, DOUBLE & dValue)
{
	IAttribute * pAttribute=QueryAttribute(pszName);
	if (pAttribute==NULL) return false;
	return pAttribute->GetValue(dValue);
}

//��ȡ����
bool CAttributeManager::GetAttributeValue(LPCTSTR pszName, CString & strValue)
{
	IAttribute * pAttribute=QueryAttribute(pszName);
	if (pAttribute==NULL) return false;
	return pAttribute->GetValue(strValue);
}

//��ȡ����
bool CAttributeManager::GetAttributeVarValue(LPCTSTR pszName, CString & strValue)
{
	IAttribute * pAttribute=QueryAttribute(pszName);
	if (pAttribute==NULL) return false;
	return pAttribute->GetVarValue(strValue);
}

//��������
bool CAttributeManager::SetAttributeValue(LPCTSTR pszName, void * pValue)
{
	IAttribute * pAttribute=QueryAttribute(pszName);
	if (pAttribute==NULL) return false;
	return pAttribute->SetValue(pValue);
}

//��������
bool CAttributeManager::SetAttributeValue(LPCTSTR pszName, INT iValue)
{
	IAttribute * pAttribute=QueryAttribute(pszName);
	if (pAttribute==NULL) return false;
	return pAttribute->SetValue(iValue);
}

//��������
bool CAttributeManager::SetAttributeValue(LPCTSTR pszName, BYTE cbValue)
{
	IAttribute * pAttribute=QueryAttribute(pszName);
	if (pAttribute==NULL) return false;
	return pAttribute->SetValue(cbValue);
}

//��������
bool CAttributeManager::SetAttributeValue(LPCTSTR pszName, WORD wValue)
{
	IAttribute * pAttribute=QueryAttribute(pszName);
	if (pAttribute==NULL) return false;
	return pAttribute->SetValue(wValue);
}

//��������
bool CAttributeManager::SetAttributeValue(LPCTSTR pszName, LONG lValue)
{
	IAttribute * pAttribute=QueryAttribute(pszName);
	if (pAttribute==NULL) return false;
	return pAttribute->SetValue(lValue);
}

//��������
bool CAttributeManager::SetAttributeValue(LPCTSTR pszName, DWORD dwValue)
{
	IAttribute * pAttribute=QueryAttribute(pszName);
	if (pAttribute==NULL) return false;
	return pAttribute->SetValue(dwValue);
}

//��������
bool CAttributeManager::SetAttributeValue(LPCTSTR pszName, DOUBLE dValue)
{
	IAttribute * pAttribute=QueryAttribute(pszName);
	if (pAttribute==NULL) return false;
	return pAttribute->SetValue(dValue);
}

//��������
bool CAttributeManager::SetAttributeValue(LPCTSTR pszName, LPCTSTR pszValue)
{
	IAttribute * pAttribute=QueryAttribute(pszName);
	if (pAttribute==NULL) return false;
	return pAttribute->SetValue(pszValue);
}

//////////////////////////////////////////////////////////////////////////
