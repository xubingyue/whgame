#ifndef ATTEMPER_ENGINE_SINK_HEAD_FILE
#define ATTEMPER_ENGINE_SINK_HEAD_FILE

#pragma once

#include "Commonality.h"
#include "ServerList.h"
#include "InitParamter.h"
#include "CenterSocket.h"

//////////////////////////////////////////////////////////////////////////

//������Ϣ�ṹ
struct tagConnectItemInfo
{
	BYTE							bConnect;							//�Ƿ�����
	WORD							wRoundID;							//ѭ������
	DWORD							dwClientIP;							//���ӵ�ַ
};

//////////////////////////////////////////////////////////////////////////

//�������湳��
class CAttemperEngineSink : public IAttemperEngineSink
{
	//��������
protected:
	CInitParamter					* m_pInitParamter;					//���ò���
	tagConnectItemInfo				* m_pConnectItemInfo;				//������Ϣ

	//���ķ�����
protected:
	enSocketState					m_SocketState;						//����״̬
	CCenterSocket					* m_pCenterSocket;					//��������

	//�������
protected:
	CServerList						m_ServerList;						//�������б�
	CQueueServiceEvent				m_DataBaseEvent;					//���ݿ�֪ͨ

	//�ӿڱ���
protected:
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
	bool InitAttemperSink(CInitParamter * pInitParamter, CCenterSocket * pCenterSocket, IUnknownEx * pIUnknownEx);

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

	//���������¼�
public:
	//���������¼�
	virtual bool __cdecl OnEventCenterSocketConnect(int iErrorCode);
	//���Ķ�ȡ�¼�
	virtual bool __cdecl OnEventCenterSocketRead(CMD_Command Command, void * pDataBuffer, WORD wDataSize);
	//���Ĺر��¼�
	virtual bool __cdecl OnEventCenterSocketClose(bool bCloseByServer);

	//���ݿ⺯��
private:
	//�û���¼�ɹ�
	bool OnDBLogonSuccess(void * pDataBuffer, WORD wDataSize, NTY_DataBaseEvent * pDataBaseEvent);
	//�û���¼ʧ��
	bool OnDBLogonError(void * pDataBuffer, WORD wDataSize, NTY_DataBaseEvent * pDataBaseEvent);

	//���纯��
private:
	//��¼��Ϣ����
	bool OnSocketMainLogon(CMD_Command Command, void * pDataBuffer, WORD wDataSize, NTY_SocketReadEvent * pSocketReadEvent);

	//��������
private:
	//�б���Ϣ����
	bool OnCenterMainServerList(CMD_Command Command, void * pDataBuffer, WORD wDataSize);
};

//////////////////////////////////////////////////////////////////////////

#endif