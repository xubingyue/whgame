#ifndef QUEUE_SERVICE_HEAD_FILE
#define QUEUE_SERVICE_HEAD_FILE

#include "ServerKernel.h"

#pragma once

//////////////////////////////////////////////////////////////////////////

//�����߳���
class CQueueServiceThread : public CServiceThread
{
	//��Ա����
	friend class CQueueService;

	//���ö���
protected:
	HANDLE							m_hCompletionPort;					//��ɶ˿�

	//��������
private:
	BYTE							m_cbBuffer[MAX_QUEUE_PACKET];		//���ջ���

	//��������
protected:
	//���캯��
	CQueueServiceThread(void);
	//��������
	virtual ~CQueueServiceThread(void);

	//���ܺ���
public:
	//���ú���
	bool InitThread(HANDLE hCompletionPort);
	//ȡ������
	bool UnInitThread();

	//���غ���
private:
	//���к���
	virtual bool RepetitionRun();
};

//////////////////////////////////////////////////////////////////////////

//���ݶ�����
class CQueueService : public IQueueServiceEngine, public IQueueService 
{
	friend class CQueueServiceThread;

	//��������
protected:
	bool							m_bService;							//�����־
	HANDLE							m_hCompletionPort;					//��ɶ˿�
	IQueueServiceSink				* m_pIQueueServiceSink;				//�ص��ӿ�

	//�������
protected:
	CThreadLock						m_ThreadLock;						//�߳���
	CDataStorage					m_DataStorage;						//���ݴ洢
	CQueueServiceThread				m_QueueServiceThread;				//�����߳�

	//��������
public:
	//���캯��
	CQueueService(void);
	//��������
	virtual ~CQueueService(void);

	//�����ӿ�
public:
	//�ͷŶ���
	virtual bool __cdecl Release() { if (IsValid()) delete this; return true; }
	//�Ƿ���Ч
	virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CQueueService))?true:false; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//���нӿ�
public:
	//��������
	virtual bool __cdecl AddToQueue(WORD wIdentifier, void * const pBuffer, WORD wDataSize);

	//����ӿ�
public:
	//��ʼ����
	virtual bool __cdecl BeginService();
	//ֹͣ����
	virtual bool __cdecl EndService();
	//���ýӿ�
	virtual bool __cdecl SetQueueServiceSink(IUnknownEx * pIUnknownEx);
	//������Ϣ
	virtual bool __cdecl GetBurthenInfo(tagBurthenInfo & BurthenInfo);

	//��������
private:
	//��ȡ����
	bool GetData(tagDataHead & DataHead, void * pBuffer, WORD wBufferSize);
	//������Ϣ
	void OnQueueServiceThread(const tagDataHead & DataHead, void * pBuffer, WORD wDataSize);
};

//////////////////////////////////////////////////////////////////////////

#endif