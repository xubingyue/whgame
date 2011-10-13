#ifndef ATTEMPER_ENGINE_SINK_HEAD_FILE
#define ATTEMPER_ENGINE_SINK_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "ServerList.h"
#include "CenterSocket.h"
#include "DataBaseSink.h"
#include "GameServiceExport.h"
#include "ServerUserManager.h"

//////////////////////////////////////////////////////////////////////////
//�ṹ�嶨��

//���Ȳ���
struct tagAttemperSinkParameter
{
	//���ñ���
	DWORD							dwCenterServer;						//���ĵ�ַ
	tagGameServiceAttrib			* pGameServiceAttrib;				//��������
	tagGameServiceOption			* pGameServiceOption;				//������Ϣ

	//�������
	CCenterSocket					* pCenterSocket;					//��������
	IAttemperEngine					* pIAttemperEngine;					//��������
	IGameServiceManager				* pIGameServiceManager;				//����ӿ�
};

//������Ϣ�ṹ
struct tagConnectItemInfo
{
	bool							bConnect;							//�Ƿ�����
	WORD							wRoundID;							//ѭ������
	DWORD							dwClientIP;							//���ӵ�ַ
	IServerUserItem					* pIServerUserItem;					//�û�ָ��
};

//����״��
struct tagTableUserStatus
{
	WORD							wLessUserCount;						//��������
	WORD							wTableUserCount;					//�û���Ŀ
	WORD							wTableAndroidCount;					//�û���Ŀ
};

//////////////////////////////////////////////////////////////////////////

//��˵��
class CTableFrame;

//�������湳��
class CAttemperEngineSink : public IAttemperEngineSink, public IGameServiceFrame
{
	//��������
protected:
	WORD							m_wMaxUserItem;						//����û�
	CTableFrame						* m_pTableFrame;					//����ָ��
	tagConnectItemInfo				* m_pNormalParameter;				//������Ϣ
	tagConnectItemInfo				* m_pAndroidParameter;				//������Ϣ

	//��Ϣ����
protected:
	BYTE							m_cbRoomMsgIndex;					//��Ϣ����			
	BYTE							m_cbGameMsgIndex;					//��Ϣ����			

	//���ķ�����
protected:
	enSocketState					m_SocketState;						//����״̬
	CCenterSocket					* m_pCenterSocket;					//��������

	//���Ʊ���
protected:
	bool							m_bShallClose;						//�رձ�־
	bool							m_bAllowWisper;						//˽�ı�־
	bool							m_bAllowRoomChat;					//�����־
	bool							m_bAllowGameChat;					//�����־
	bool							m_bAllowEnterRoom;					//�����־
	bool							m_bAllowEnterGame;					//�����־

	//������Ϣ
protected:
	DWORD							m_dwCenterServer;					//���ĵ�ַ
	tagGameServiceAttrib			* m_pGameServiceAttrib;				//��������
	tagGameServiceOption			* m_pGameServiceOption;				//��������

	//��Ϸ���
protected:
	HINSTANCE						m_hDllInstance;						//��Ϸʵ��
	IGameServiceManager				* m_pIGameServiceManager;			//����ӿ�

	//�б����
protected:
	CMD_GR_ColumnInfo				m_ColumnInfo;						//�б����
	WORD							m_wColumnInfoSize;					//�б���

	//��������
protected:
	WORD							m_wOnLineInfoSize;					//��Ϣ����
	tagOnLineCountInfo				m_OnLineCountInfo[64];				//������Ϣ

	//�������
protected:
	CServerList						m_ServerList;						//�������б�
	CQueueServiceEvent				m_DataBaseEvent;					//���ݿ�֪ͨ
	CServerUserManager				m_ServerUserManager;				//�û�����

	//�ӿڱ���
protected:
	ITimerEngine					* m_pITimerEngine;					//��ʱ���ӿ�
	IEventService					* m_pIEventService;					//�¼��ӿ�
	IAttemperEngine					* m_pIAttemperEngine;				//��������
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

	//״̬�ӿ�
public:
	//�رղ�ѯ
	virtual bool __cdecl IsShallClose() { return m_bShallClose; }
	//˽�Ĳ�ѯ
	virtual bool __cdecl IsAllowWisper() { return m_bAllowWisper; }
	//�����ѯ
	virtual bool __cdecl IsAllowRoomChat() { return m_bAllowRoomChat; }
	//�����ѯ
	virtual bool __cdecl IsAllowGameChat() { return m_bAllowGameChat; }
	//�����ѯ
	virtual bool __cdecl IsAllowEnterRoom() { return m_bAllowEnterRoom; }
	//�����ѯ
	virtual bool __cdecl IsAllowEnterGame() { return m_bAllowEnterGame; }

	//״̬֪ͨ
public:
	//����״̬
	virtual bool __cdecl SendTableStatus(WORD wTableID);
	//���ͷ���
	virtual bool __cdecl SendUserScore(IServerUserItem * pIServerUserItem);
	//����״̬
	virtual bool __cdecl SendUserStatus(IServerUserItem * pIServerUserItem);

	//����ӿ�
public:
	//��������
	virtual bool __cdecl SendData(IServerUserItem * pIServerUserItem, WORD wMainCmdID, WORD wSubCmdID);
	//��������
	virtual bool __cdecl SendData(IServerUserItem * pIServerUserItem, WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize);

	//��ʱ���ӿ�
public:
	//���ö�ʱ��
	virtual bool __cdecl SetTableTimer(WORD wTableID, WORD wTimerID, DWORD dwElapse, DWORD dwRepeat, WPARAM wBindParam);
	//ɾ����ʱ��
	virtual bool __cdecl KillTableTimer(WORD wTableID, WORD wTimerID);

	//����ӿ�
public:
	//ɾ���û�
	virtual bool __cdecl DeleteUserItem(IServerUserItem * pIServerUserItem);
	//�����Ϣ
	virtual void __cdecl ExportInformation(LPCTSTR pszString, enTraceLevel TraceLevel);

	//���ú��� 
public:
	//�����¼�
	bool SetEventService(IUnknownEx * pIUnknownEx);
	//���ú���
	bool InitAttemperSink(tagAttemperSinkParameter * pAttemperSinkParameter, IUnknownEx * pIUnknownEx);

	//��Ϣ����
public:
	//���ͷ�����Ϣ
	bool SendRoomMessage(WORD wIndex, WORD wRoundID, LPCTSTR lpszMessage, WORD wMessageType);
	//������Ϸ��Ϣ
	bool SendGameMessage(WORD wIndex, WORD wRoundID, LPCTSTR lpszMessage, WORD wMessageType);
	//���ͷ�����Ϣ
	bool SendRoomMessage(IServerUserItem * pIServerUserItem, LPCTSTR lpszMessage, WORD wMessageType);
	//������Ϸ��Ϣ
	bool SendGameMessage(IServerUserItem * pIServerUserItem, LPCTSTR lpszMessage, WORD wMessageType);

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
	//�û���Ϣ����
	bool OnSocketMainUser(CMD_Command Command, void * pDataBuffer, WORD wDataSize, NTY_SocketReadEvent * pSocketReadEvent);
	//������Ϣ����
	bool OnSocketMainManager(CMD_Command Command, void * pDataBuffer, WORD wDataSize, NTY_SocketReadEvent * pSocketReadEvent);
	//�����Ϣ����
	bool OnSocketMainFrame(CMD_Command Command, void * pDataBuffer, WORD wDataSize, NTY_SocketReadEvent * pSocketReadEvent);
	//��Ϸ��Ϣ����
	bool OnSocketMainGame(CMD_Command Command, void * pDataBuffer, WORD wDataSize, NTY_SocketReadEvent * pSocketReadEvent);
	//��Ƶ��Ϣ����
	bool OnSocketMainVideo(CMD_Command Command, void * pDataBuffer, WORD wDataSize, NTY_SocketReadEvent * pSocketReadEvent);

	//��������
private:
	//����ʧ��
	bool SendLogonFailed(WORD wIndex, WORD wRoundID, LPCTSTR pszMessage, LONG lErrorCode);
	//�����û�
	bool SendUserItem(IServerUserItem * pIServerUserItem, WORD wTargetIndex, WORD wTargetRoundID);
	//������Ϣ
	bool SendGameServerInfo(IServerUserItem * pIServerUserItem, WORD wIndex, WORD wRoundID);

	//��������
private:
	//�б���Ϣ����
	bool OnCenterMainServerList(CMD_Command Command, void * pDataBuffer, WORD wDataSize);

	//��������
protected:
	//�󶨲���
	tagConnectItemInfo * GetBindParameter(WORD wBindIndex);
	//���û�
	IServerUserItem * GetServerUserItem(WORD wBindIndex);
};

//////////////////////////////////////////////////////////////////////////

#endif