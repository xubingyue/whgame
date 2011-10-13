#ifndef GAME_SERVICE_HEAD_FILE
#define GAME_SERVICE_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "DataBaseSink.h"
#include "AttemperEngineSink.h"

//////////////////////////////////////////////////////////////////////////

//��Ϸ������
class CGameService : public IGameService
{
	//��������
protected:
	CCenterSocket					m_CenterSocket;						//��������
	CDataBaseSink					m_DataBaseSink;						//���ݿ⹳��
	CAttemperEngineSink				m_AttemperSink;						//���ȹ���
	CServiceEngineHelper			m_ServiceEngine;					//��������

	//���ñ���
protected:
	TCHAR							m_szModule[32];						//ģ������
	tagDataBaseInfo					m_GameUserDBInfo;					//��������
	tagDataBaseInfo					m_GameScoreDBInfo;					//��������
	tagGameServiceAttrib			m_GameServiceAttrib;				//��������
	tagGameServiceOption			m_GameServiceOption;				//��������

	//����ӿ�
protected:
	HINSTANCE						m_hDllInstance;						//��Ϸʵ��
	IEventService					* m_pIEventService;					//�¼�����
	IGameServiceManager				* m_pIGameServiceManager;			//����ӿ�

	//��������
public:
	//���캯��
	CGameService(void);
	//��������
	virtual ~CGameService(void);

	//�����ӿ�
public:
	//�ͷŶ���
	virtual bool __cdecl Release() { if (IsValid()) delete this; return true; }
	//�Ƿ���Ч
	virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CGameService))?true:false; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//����ӿ�
public:
	//����״̬
	virtual bool __cdecl IsService();
	//�����¼�
	virtual bool __cdecl SetEventService(IUnknownEx * pIEventService);
	//��ʼ����
	virtual bool __cdecl BeginService(tagGameServiceParameter * pGameServiceParameter);
	//ֹͣ����
	virtual bool __cdecl EndService();

	//�ڲ�����
private:
	//�ͷ�ģ��
	bool UnLoadGameServiceModule();
	//����ģ��
	bool LoadGameServiceModule(LPCTSTR pszModuleName);
	//��ʾ����
	void ShowErrorMessasge(LPCTSTR pszString, enTraceLevel TraceLevel);
};

//////////////////////////////////////////////////////////////////////////

#endif