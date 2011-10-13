#pragma once

#include "Expression.h"
#include "ClientShare.h"

//////////////////////////////////////////////////////////////////////////

//��Ϣ�������
class CMessageProxy : public IMessageProxy
{
	//��������
protected:
	CSkinRichEdit					* m_pSkinRichEdit;					//��Ϣ���
	tagMessageOption				m_MessageOption;					//������Ϣ

	//��������
public:
	//���캯��
	CMessageProxy(void);
	//��������
	virtual ~CMessageProxy(void);

	//�����ӿ�
public:
	//�ͷŶ���
	virtual bool __cdecl Release() { if (IsValid()) delete this; return true; }
	//�Ƿ���Ч
	virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CMessageProxy))?true:false; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//���ýӿ�
public:
	//���þ��
	virtual bool __cdecl SetRichEditHwnd(CSkinRichEdit * pSkinRichEdit);
	//������ɫ
	virtual bool __cdecl SetMessageOption(tagMessageOption & MessageOption);

	//���ƽӿ�
public:
	//�����Ļ
	virtual bool __cdecl CleanScreen();
	//���ù���
	virtual bool __cdecl SetAutoScroll(bool bScroll);
	//������Ϣ
	virtual bool __cdecl LoadMessage(LPCTSTR pszFileName);
	//������Ϣ
	virtual bool __cdecl SaveMessage(LPCTSTR pszFileName);

	//��Ϣ�ӿ�
public:
	//����ͼƬ
	virtual bool __cdecl InsertImage(CBitmap * pBitmap);
	//����ʱ��
	virtual bool __cdecl InsertSystemTime(COLORREF crColor);
	//�û�����
	virtual bool __cdecl InsertUserName(LPCTSTR pszUserName);
	//ϵͳ��Ϣ
	virtual bool __cdecl InsertSystemString(LPCTSTR pszString, UINT uSize);
	//��ɫ��Ϣ
	virtual bool __cdecl InsertShtickString(LPCTSTR pszString, COLORREF crColor, UINT uSize, bool bNewLine);
	//��ͨ��Ϣ
	virtual bool __cdecl InsertGeneralString(LPCTSTR pszString, COLORREF crColor, UINT uSize, bool bNewLine);
	//�û�����
	virtual bool __cdecl InsertUserChat(LPCTSTR pszSendName, LPCTSTR pszString, COLORREF crColor, UINT uSize);
	//�û�����
	virtual bool __cdecl InsertUserChat(LPCTSTR pszSendName, LPCTSTR pszRecvName, LPCTSTR pszString, COLORREF crColor, UINT uSize);

	//�ڲ�����
private:
	//���Ͳ���
	bool TranslateInsert(LPCTSTR pszString, COLORREF crColor, UINT uSize, LPCTSTR pszFontName);
	//�����ַ�
	CExpressionItem * TranslateChar(LPCTSTR szCharString, int iCharLength, int & iPassCharCount);
};

//////////////////////////////////////////////////////////////////////////
