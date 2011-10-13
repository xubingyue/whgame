#include "StdAfx.h"
#include "Afxinet.h"
#include "DataBaseSink.h"

//���캯��
CDataBaseSink::CDataBaseSink()
{
	m_pInitParamter=NULL;
	m_pIEventService=NULL;
}

CDataBaseSink::~CDataBaseSink()
{
}

//�ӿڲ�ѯ
void * __cdecl CDataBaseSink::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IDataBaseSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IDataBaseSink,Guid,dwQueryVer);
	return NULL;
}

//����ģ������
bool __cdecl CDataBaseSink::BeginService(IUnknownEx * pIUnknownEx)
{
	//Ч�����
	ASSERT(m_pInitParamter!=NULL);
	ASSERT(m_pIEventService!=NULL);
	ASSERT(m_AttemperEvent.IsValid()==true);

	//����ʵ��
	if ((m_CenterDataBase.IsValid()==false)&&(m_CenterDataBase.CreateInstance()==false))
	{
		m_pIEventService->ShowEventNotify(TEXT("�������ݿ���󴴽�ʧ��"),
									Level_Exception);
		return false;
	}

	try
	{
		//�����������ݿ�
		m_CenterDataBase->SetConnectionInfo(m_pInitParamter->m_szServerDataBaseAddr,
									m_pInitParamter->m_wServerDataBasePort,
									m_pInitParamter->m_szServerDataBaseName,
									m_pInitParamter->m_szServerDataBaseUser,
									m_pInitParamter->m_szServerDataBasePass);
		m_CenterDataBase->OpenConnection();

		return true;
	}
	catch (IADOError * pIADOError)
	{
		m_pIEventService->ShowEventNotify(pIADOError->GetErrorDescribe(),Level_Exception);
	}

	return false;
}

//����ģ��ر�
bool __cdecl CDataBaseSink::EndService(IUnknownEx * pIUnknownEx)
{
	return false;
}

//���ݲ�������
bool __cdecl CDataBaseSink::OnDataBaseRequest(const NTY_DataBaseEvent & DataBaseEvent, void * pDataBuffer, WORD wDataSize)
{
	return false;
}

//�����¼�
bool CDataBaseSink::SetEventService(IUnknownEx * pIUnknownEx)
{
	ASSERT(pIUnknownEx!=NULL);
	m_pIEventService=GET_OBJECTPTR_INTERFACE(pIUnknownEx,IEventService);
	ASSERT(m_pIEventService!=NULL);
	return (m_pIEventService!=NULL);
}

//���ú���
bool CDataBaseSink::InitDataBaseSink(CInitParamter * pInitParamter, IUnknownEx * pIUnknownEx)
{
	//Ч�����
	ASSERT(pIUnknownEx!=NULL);
	ASSERT(pInitParamter!=NULL);

	//���ñ���
	m_pInitParamter=pInitParamter;

	//��ѯ�ӿ�
	IServiceEngine * pIServiceEngine=(IServiceEngine *)pIUnknownEx->QueryInterface(IID_IServiceEngine,VER_IServiceEngine);
	ASSERT(pIServiceEngine!=NULL);
	if (pIServiceEngine==NULL) 
	{
		throw TEXT("��������ӿڲ�ѯʧ��");
	}

	//��ȡ�߼�����
	IAttemperEngine * pIAttemperEngine=(IAttemperEngine *)pIServiceEngine->GetAttemperEngine(IID_IAttemperEngine,VER_IAttemperEngine);
	ASSERT(pIAttemperEngine!=NULL);
	if (pIAttemperEngine==NULL) 
	{
		throw TEXT("��������ӿڲ�ѯʧ��");
	}

	//����֪ͨ���
	IUnknownEx * pIQueueService=(IUnknownEx *)pIAttemperEngine->GetQueueService(IID_IQueueService,VER_IQueueService);
	if (m_AttemperEvent.SetQueueService(pIQueueService)==false) 
	{
		throw TEXT("�߼�����֪ͨ�ӿ�����ʧ��");
	}

	return true;
}
