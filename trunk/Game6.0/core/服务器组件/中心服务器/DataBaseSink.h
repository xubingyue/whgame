#ifndef DATA_BASE_SINK_HEAD_FILE
#define DATA_BASE_SINK_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "InitParamter.h"

//���ݿ����湳��
class CDataBaseSink : public IDataBaseSink
{
	//��������
protected:
	CInitParamter					* m_pInitParamter;					//���ò���
	IEventService					* m_pIEventService;					//�¼�����

	//�������
protected:
	CDataBaseHelper					m_CenterDataBase;					//�������ݿ�
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
	//����ģ������
	virtual bool __cdecl BeginService(IUnknownEx * pIUnknownEx);
	//����ģ��ر�
	virtual bool __cdecl EndService(IUnknownEx * pIUnknownEx);
	//���ݲ�������
	virtual bool __cdecl OnDataBaseRequest(const NTY_DataBaseEvent & DataBaseEvent, void * pDataBuffer, WORD wDataSize);

	//���ú��� 
public:
	//�����¼�
	bool SetEventService(IUnknownEx * pIUnknownEx);
	//���ú���
	bool InitDataBaseSink(CInitParamter * pInitParamter, IUnknownEx * pIUnknownEx);
};


#endif

