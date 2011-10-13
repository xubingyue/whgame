#ifndef ATTEMPER_ENGINE_SINK_HEAD_FILE
#define ATTEMPER_ENGINE_SINK_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "InitParamter.h"
#include "ConnectInfoManager.h"

//////////////////////////////////////////////////////////////////////////

//�������湳��
class CAttemperEngineSink : public IAttemperEngineSink
{
	//�������
protected:
	CQueueServiceEvent				m_DataBaseEvent;					//���ݿ�֪ͨ
	CConnectInfoManager				m_ConnectInfoManager;				//���ӹ���
	CServerListCenterHelper			m_ServerListCenter;					//�б����

	//�ӿڱ���
protected:
	CInitParamter					* m_pInitParamter;					//���ò���
	ITimerEngine					* m_pITimerEngine;					//��ʱ���ӿ�
	IEventService					* m_pIEventService;					//�¼�����
	ITCPSocketEngine				* m_pITCPSocketEngine;				//����ӿ�

	//��������
public:
	//���캯��
	CAttemperEngineSink();
	//��������
	virtual ~CAttemperEngineSink();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual bool __cdecl Release() { if (IsValid()) delete this; return true; }
	//�Ƿ���Ч
	virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CAttemperEngineSink))?true:false; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//���Ƚӿ�
public:
	//����ģ������
	virtual bool __cdecl BeginService(IUnknownEx * pIUnknownEx);
	//����ģ��ر�
	virtual bool __cdecl EndService(IUnknownEx * pIUnknownEx);
	//�¼�����ӿ�
	virtual bool __cdecl OnAttemperEvent(WORD wIdentifier, void * pDataBuffer, WORD wDataSize, DWORD dwInsertTime);

	//���ú��� 
public:
	//�����¼�
	bool SetEventService(IUnknownEx * pIUnknownEx);
	//���ú���
	bool InitAttemperSink(CInitParamter * pInitParamter, IUnknownEx * pIUnknownEx);

	//�¼��ӿ�
public:
	//��ʱ���¼�
	virtual bool __cdecl OnEventTimer(WORD wTimerID, WPARAM wBindParam);
	//���ݿ��¼�
	virtual bool __cdecl OnEventDataBase(void * pDataBuffer, WORD wDataSize, NTY_DataBaseEvent * pDataBaseEvent);
	//����Ӧ���¼�
	virtual bool __cdecl OnEventSocketAccept(NTY_SocketAcceptEvent * pSocketAcceptEvent);
	//�����ȡ�¼�
	virtual bool __cdecl OnEventSocketRead(CMD_Command Command, void * pDataBuffer, WORD wDataSize, NTY_SocketReadEvent * pSocketReadEvent);
	//����ر��¼�
	virtual bool __cdecl OnEventSocketClose(NTY_SocketCloseEvent * pSocketCloseEvent);

	//���纯��
private:
	//�б���Ϣ����
	bool OnSocketMainServerList(CMD_Command Command, void * pDataBuffer, WORD wDataSize, NTY_SocketReadEvent * pSocketReadEvent);
	//������Ϣ����
	bool OnSocketMainServerManager(CMD_Command Command, void * pDataBuffer, WORD wDataSize, NTY_SocketReadEvent * pSocketReadEvent);
};

//////////////////////////////////////////////////////////////////////////

#endif