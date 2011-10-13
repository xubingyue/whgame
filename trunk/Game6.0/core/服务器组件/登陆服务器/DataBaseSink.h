#ifndef DATA_BASE_SINK_HEAD_FILE
#define DATA_BASE_SINK_HEAD_FILE

#pragma once

#include "Afxinet.h"
#include "Commonality.h"
#include "InitParamter.h"

//////////////////////////////////////////////////////////////////////////

//���ݿ����湳��
class CDataBaseSink : public IDataBaseSink
{
	//��������
protected:
	CInitParamter					* m_pInitParamter;					//���ò���
	IEventService					* m_pIEventService;					//�¼�����

	//�������
protected:
	CDataBaseHelper					m_UserDataBase;						//�û����ݿ�
	CQueueServiceEvent				m_AttemperEvent;					//����֪ͨ

	//��������
public:
	//���캯��
	CDataBaseSink();
	//��������
	virtual ~CDataBaseSink();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual bool __cdecl Release() { if (IsValid()) delete this; return true; }
	//�Ƿ���Ч
	virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CDataBaseSink))?true:false; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//���Ƚӿ�
public:
	//ģ������
	virtual bool __cdecl BeginService(IUnknownEx * pIUnknownEx);
	//ģ��ر�
	virtual bool __cdecl EndService(IUnknownEx * pIUnknownEx);
	//���ݲ�������
	virtual bool __cdecl OnDataBaseRequest(const NTY_DataBaseEvent & DataBaseEvent, void * pDataBuffer, WORD wDataSize);

	//���ú��� 
public:
	//�����¼�
	bool SetEventService(IUnknownEx * pIUnknownEx);
	//���ú���
	bool InitDataBaseSink(CInitParamter * pInitParamter, IUnknownEx * pIUnknownEx);

	//������
private:
	//��¼������
	bool OnRequestLogon(const NTY_DataBaseEvent & DataBaseEvent, void * pDataBuffer, WORD wDataSize);

	//�洢����
private:
	//I D �洢����
	LONG SPLogonByUserID(DWORD dwGameID, LPCTSTR pszPassword, DWORD dwClientIP, LPCTSTR pszComputerID);
	//�ʺŴ洢����
	LONG SPLogonByAccounts(LPCTSTR pszAccounts, LPCTSTR pszPassword, DWORD dwClientIP, LPCTSTR pszComputerID);
	//ע��洢����
	LONG SPRegisterAccounts(LPCTSTR pszAccounts, LPCTSTR pszPassword, LPCTSTR pszSpreader, WORD wFaceID, BYTE cbGender, DWORD dwClientIP, LPCTSTR pszComputerID);
};

//////////////////////////////////////////////////////////////////////////

#endif