#ifndef LOGON_SERVICE_HEAD_FILE
#define LOGON_SERVICE_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "CenterSocket.h"
#include "DataBaseSink.h"
#include "AttemperEngineSink.h"

//////////////////////////////////////////////////////////////////////////

//��¼������
class CLogonService
{
	//��������
protected:
	CCenterSocket					m_CenterSocket;						//��������
	CDataBaseSink					m_DataBaseSink;						//���ݿ⹳��
	CAttemperEngineSink				m_AttemperSink;						//���ȹ���

	//�������
protected:
	CServiceEngineHelper			m_ServiceEngine;					//��������

	//���ñ���
protected:
	CInitParamter					m_InitParamter;						//���ò���
	IEventService					* m_pIEventService;					//�¼�����

	//��������
public:
	//���캯��
	CLogonService(void);
	//��������
	virtual ~CLogonService(void);

	//���ܺ���
public:
	//����״̬
	bool IsService();
	//��ʼ����
	bool BeginService();
	//ֹͣ����
	bool EndService();
	//�����¼�
	bool SetEventService(IUnknownEx * pIEventService);

	//�ڲ�����
private:
	//��ʾ����
	void TraceEventString(LPCTSTR pszString, enTraceLevel TraceLevel);
};

//////////////////////////////////////////////////////////////////////////

#endif