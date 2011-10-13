#include "Stdafx.h"
#include "SkinButton.h"
#include "SkinAttribute.h"

//����¼����
#define MAX_RECORD_BUF				256

//////////////////////////////////////////////////////////////////////////

//��̬����
bool					CSkinAttribute::m_bFlags=false;							//�ڲ���־
CFont					CSkinAttribute::m_DefaultFont;							//Ĭ������
ISkinRecord	*			CSkinAttribute::m_pISkinRecord=NULL;					//���ýӿ�
ISkinAttribute *		CSkinAttribute::m_SkinPtrArray[MAX_SKIN];				//��������

//////////////////////////////////////////////////////////////////////

//���캯��
CSkinRecordFile::CSkinRecordFile()
{
	m_szIniFileName[0]=0;
	m_szResDirectory[0]=0;
}

//��������
CSkinRecordFile::~CSkinRecordFile()
{
}

//�ӿڲ�ѯ
void * __cdecl CSkinRecordFile::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ISkinRecord,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ISkinRecord,Guid,dwQueryVer);
	return NULL;
}

//��ȡĿ¼
LPCTSTR __cdecl CSkinRecordFile::GetResourceDirectory()
{
	return m_szResDirectory;
}

//��ȡ����
int __cdecl CSkinRecordFile::ReadInt(LPCTSTR pszClassName, LPCTSTR pszItem, int iDefValue)
{
	return GetPrivateProfileInt(pszClassName,pszItem,iDefValue,m_szIniFileName);
}

//��ȡ����
COLORREF __cdecl CSkinRecordFile::ReadColor(LPCTSTR pszClassName, LPCTSTR pszItem, COLORREF crDefValue)
{
	TCHAR szBuffer[MAX_RECORD_BUF]=TEXT("");
	GetPrivateProfileString(pszClassName,pszItem,TEXT(""),szBuffer,sizeof(szBuffer),m_szIniFileName);
	if (szBuffer[0]!=0)
	{
		int nColorRed=GetRValue(crDefValue);
		int nColorGreen=GetGValue(crDefValue);
		int nColorBule=GetBValue(crDefValue);
		sscanf(szBuffer,TEXT("RGB(%d,%d,%d)"),&nColorRed,&nColorGreen,&nColorBule);
		return RGB(nColorRed,nColorGreen,nColorBule);
	}
	return crDefValue;
}

//��ȡ����
RECT __cdecl CSkinRecordFile::ReadRect(LPCTSTR pszClassName, LPCTSTR pszItem, const RECT & rcDefValue)
{
	TCHAR szBuffer[MAX_RECORD_BUF]=TEXT("");
	GetPrivateProfileString(pszClassName,pszItem,TEXT(""),szBuffer,sizeof(szBuffer),m_szIniFileName);
	if (szBuffer[0]!=0)
	{
		RECT Rect=rcDefValue;
		sscanf(szBuffer,TEXT("%d,%d,%d,%d"),&Rect.left,&Rect.top,&Rect.right,&Rect.bottom);
		return Rect;
	}
	return rcDefValue;
}

//��ȡ����
POINT __cdecl CSkinRecordFile::ReadPoint(LPCTSTR pszClassName, LPCTSTR pszItem, const POINT & ptDefValue)
{
	TCHAR szBuffer[MAX_RECORD_BUF]=TEXT("");
	GetPrivateProfileString(pszClassName,pszItem,TEXT(""),szBuffer,sizeof(szBuffer),m_szIniFileName);
	if (szBuffer[0]!=0)
	{
		POINT Point=ptDefValue;
		sscanf(szBuffer,TEXT("%d,%d"),&Point.x,&Point.y);
		return Point;
	}
	return ptDefValue;
}

//��ȡ����
CString __cdecl CSkinRecordFile::ReadString(LPCTSTR pszClassName, LPCTSTR pszItem, LPCTSTR pszDefValue)
{
	TCHAR szBuffer[MAX_RECORD_BUF]=TEXT("");
	GetPrivateProfileString(pszClassName,pszItem,TEXT(""),szBuffer,sizeof(szBuffer),m_szIniFileName);
	if (szBuffer[0]!=0) return szBuffer;
	return pszDefValue;
}

//����Ŀ¼
bool CSkinRecordFile::InitSkinRecordFile(LPCTSTR pszIniFileName, LPCTSTR pszResDirectory)
{
	m_szIniFileName[0]=0;
	m_szResDirectory[0]=0;
	if (pszIniFileName!=NULL) lstrcpyn(m_szIniFileName,pszIniFileName,sizeof(m_szIniFileName));
	if (pszResDirectory!=NULL)  lstrcpyn(m_szResDirectory,pszResDirectory,sizeof(m_szResDirectory));

	return true;
}

//////////////////////////////////////////////////////////////////////

//���캯��
CSkinAttribute::CSkinAttribute(LPCTSTR pszClassName) 
{ 
	//���ñ���
	ASSERT(pszClassName);
	lstrcpyn(m_szClassName,pszClassName,sizeof(m_szClassName));
	RegisterAttribute(SKIN_CONTROL_CLASS_NAME_STRING,m_szClassName,true);

	//��������
	if (m_DefaultFont.GetSafeHandle()==NULL) 
		m_DefaultFont.CreateFont(-12,0,0,0,400,0,0,0,134,3,2,1,2,TEXT("����"));

	//ע�����
	if (m_bFlags==false)
	{
		m_bFlags=true;
		memset(m_SkinPtrArray,0,sizeof(m_SkinPtrArray));
	}
	IUnknownEx * pIUnknownEx=GET_MYSELF_INTERFACE(IUnknownEx);
	ASSERT(pIUnknownEx!=NULL);
	RegisterSkinClass(pIUnknownEx);

	return;
}

//��������
CSkinAttribute::~CSkinAttribute()
{
	//ע�����
	IUnknownEx * pIUnknownEx=GET_MYSELF_INTERFACE(IUnknownEx);
	ASSERT(pIUnknownEx!=NULL);
	UnRegisterSkinClass(pIUnknownEx);

	return;
}

//�ӿڲ�ѯ
void * CSkinAttribute::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ISkinAttribute,Guid,dwQueryVer);
	return CAttributeManager::QueryInterface(Guid,dwQueryVer);
}

//��ȡ����
int CSkinAttribute::ReadInt(LPCTSTR pszItem, int iDefValue)
{
	if (m_pISkinRecord==NULL) return iDefValue;
	return m_pISkinRecord->ReadInt(GetClassName(),pszItem,iDefValue);
}

//��ȡ����
COLORREF CSkinAttribute::ReadColor(LPCTSTR pszItem, COLORREF crDefValue)
{
	if (m_pISkinRecord==NULL) return crDefValue;
	return m_pISkinRecord->ReadColor(GetClassName(),pszItem,crDefValue);
}

//��ȡ����
RECT CSkinAttribute::ReadRect(LPCTSTR pszItem, const RECT & rcDefValue)
{
	if (m_pISkinRecord==NULL) return rcDefValue;
	return m_pISkinRecord->ReadRect(GetClassName(),pszItem,rcDefValue);
}

//��ȡ����
POINT CSkinAttribute::ReadPoint(LPCTSTR pszItem, const POINT & ptDefValue)
{
	if (m_pISkinRecord==NULL) return ptDefValue;
	return m_pISkinRecord->ReadPoint(GetClassName(),pszItem,ptDefValue);
}

//��ȡ����
CString CSkinAttribute::ReadString(LPCTSTR pszItem, LPCTSTR pszDefValue)
{
	if (m_pISkinRecord==NULL) return pszDefValue;
	return m_pISkinRecord->ReadString(GetClassName(),pszItem,pszDefValue);
}

//д�����
bool CSkinAttribute::WriteInt(LPCTSTR pszItem, int iValue)
{
	if (m_pISkinRecord==NULL) return false;
	return m_pISkinRecord->WriteInt(GetClassName(),pszItem,iValue);
}

//д�����
bool CSkinAttribute::WriteColor(LPCTSTR pszItem, COLORREF crValue)
{
	if (m_pISkinRecord==NULL) return false;
	return m_pISkinRecord->WriteColor(GetClassName(),pszItem,crValue);
}

//д�����
bool CSkinAttribute::WriteRect(LPCTSTR pszItem, const RECT & rcValue)
{
	if (m_pISkinRecord==NULL) return false;
	return m_pISkinRecord->WriteRect(GetClassName(),pszItem,rcValue);
}

//д�����
bool CSkinAttribute::WritePoint(LPCTSTR pszItem, const POINT & ptValue)
{
	if (m_pISkinRecord==NULL) return false;
	return m_pISkinRecord->WritePoint(GetClassName(),pszItem,ptValue);
}

//д�����
bool CSkinAttribute::WriteString(LPCTSTR pszItem, LPCTSTR pszValue)
{
	if (m_pISkinRecord==NULL) return false;
	return m_pISkinRecord->WriteString(GetClassName(),pszItem,pszValue);
}

//���ؽ�����Ϣ
bool CSkinAttribute::LoadSkinAttribute(IUnknownEx * pIUnknownEx)
{
	//��ѯ�ӿ�
	ASSERT(pIUnknownEx!=NULL);
	ISkinRecord * pISkinRecord=GET_OBJECTPTR_INTERFACE(pIUnknownEx,ISkinRecord);
	ASSERT(pISkinRecord!=NULL);
	if (pISkinRecord==NULL) return false;

	//���ýӿ�
	m_pISkinRecord=pISkinRecord;

	//�ı����
	bool bSuccess=true;
	for (int i=0;i<MAX_SKIN;i++)
	{
		if (m_SkinPtrArray[i]==NULL) break;
		if (!m_SkinPtrArray[i]->LoadSkinOption()) bSuccess=false;
	}

	return bSuccess;
}

//���������Ϣ
bool CSkinAttribute::SaveSkinAttribute()
{
	bool bSuccess=true;
	for (int i=0;i<MAX_SKIN;i++)
	{
		if (m_SkinPtrArray[i]==NULL) break;
		if (!m_SkinPtrArray[i]->SaveSkinOption()) bSuccess=false;
	}
	return bSuccess;
}

//��ԴĿ¼
LPCTSTR CSkinAttribute::GetResourceDirectory()
{
	ASSERT(m_pISkinRecord!=NULL);
	if (m_pISkinRecord==NULL) return NULL;
	return m_pISkinRecord->GetResourceDirectory();
}

//ö������
void * CSkinAttribute::GetAttributeManager(INT_PTR nIndex, const IID & Guid, DWORD dwQueryVer)
{
	if (nIndex>=MAX_SKIN) return NULL;
	ISkinAttribute * pISkinAttribute=m_SkinPtrArray[nIndex];
	if (pISkinAttribute==NULL) return NULL;
	return pISkinAttribute->QueryInterface(Guid,dwQueryVer);
}

//ע�������
bool CSkinAttribute::RegisterSkinClass(IUnknownEx * pIUnknownEx)
{
	//��ѯ����
	ASSERT(pIUnknownEx!=NULL);
	ISkinAttribute * pISkinAttribute=GET_OBJECTPTR_INTERFACE(pIUnknownEx,ISkinAttribute);
	ASSERT(pISkinAttribute!=NULL);
	if (pISkinAttribute==NULL) return false;

	//�������
	int i=0;
	for ( i=0;i<MAX_SKIN;i++)	
	{
		if (m_SkinPtrArray[i]==NULL) break;
		if (pISkinAttribute==m_SkinPtrArray[i])
		{
			ASSERT(FALSE);
			return false;
		}
	}

	//ע�����
	ASSERT(i<MAX_SKIN);
	if (i>=MAX_SKIN) return false;
	m_SkinPtrArray[i]=pISkinAttribute;

	return true;
}

//ע��������
bool CSkinAttribute::UnRegisterSkinClass(IUnknownEx * pIUnknownEx)
{
	//��ѯ����
	ASSERT(pIUnknownEx!=NULL);
	ISkinAttribute * pISkinAttribute=GET_OBJECTPTR_INTERFACE(pIUnknownEx,ISkinAttribute);
	ASSERT(pISkinAttribute!=NULL);
	if (pISkinAttribute==NULL) return false;

	//�������
	for (int i=0;i<MAX_SKIN;i++)
	{
		if (m_SkinPtrArray[i]==NULL) break;
		if (pISkinAttribute==m_SkinPtrArray[i])
		{
			int j=0;
			for ( j=i;j<MAX_SKIN-1;j++) 
			{
				if (m_SkinPtrArray[j+1]==NULL) break;
				m_SkinPtrArray[j]=m_SkinPtrArray[j+1];
			}
			m_SkinPtrArray[j]=NULL;
			return true;
		}
	}

	ASSERT(FALSE);
	return false;
}

//////////////////////////////////////////////////////////////////////////
