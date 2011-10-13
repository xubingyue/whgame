#ifndef SERVER_KERNEL_HEAD_FILE
#define SERVER_KERNEL_HEAD_FILE

//////////////////////////////////////////////////////////////////////////

//ϵͳͷ�ļ�
#include <ICrsint.h>
#include <WinSock2.h>

//ƽ̨ͷ�ļ�
#include "Template.h"
#include "GlobalDef.h"
#include "IUnknownEx.h"
#include "ComService.h"

//////////////////////////////////////////////////////////////////////////

//ADO �����
#import "MSADO15.DLL" rename_namespace("ADOCG") rename("EOF","EndOfFile")
using namespace ADOCG;

//COM ��������
typedef _com_error					CComError;							//COM ����

//////////////////////////////////////////////////////////////////////////
//�����궨��

//ģ�鶨��
#ifdef _DEBUG
	#define SERVER_KERNEL_DLL_NAME	TEXT("ServerKernelD.dll")			//��� DLL ����
#else
	#define SERVER_KERNEL_DLL_NAME	TEXT("ServerKernel.dll")			//��� DLL ����
#endif

//�����궨��
#define EVENT_LEVEL_COUNT			4									//�¼��ȼ�
#define MAX_QUEUE_PACKET			10240								//������
#define INDEX_ALL_SOCKET			0xFFFF								//��������
#define TIMER_REPEAT_TIMER			DWORD(-1)							//�ظ�����

//////////////////////////////////////////////////////////////////////////
//ö�ٶ���

//����ȼ�
enum enTraceLevel
{
	Level_Normal					=0,									//��ͨ��Ϣ
	Level_Warning					=1,									//������Ϣ
	Level_Exception					=2,									//�쳣��Ϣ
	Level_Debug						=3,									//������Ϣ
};

//���ݿ�������
enum enADOErrorType
{
	ErrorType_Nothing				=0,									//û�д���
	ErrorType_Connect				=1,									//���Ӵ���
	ErrorType_Other					=2,									//��������
};

//////////////////////////////////////////////////////////////////////////
//�¼�����

//�¼���ʶ
#define EVENT_CONTROL				0x0001								//������Ϣ
#define EVENT_TIMER					0x0002								//��ʱ������
#define EVENT_DATABASE				0x0003								//���ݿ�����
#define EVENT_SOCKET_ACCEPT			0x0004								//����Ӧ��
#define EVENT_SOCKET_READ			0x0005								//�����ȡ
#define EVENT_SOCKET_CLOSE			0x0006								//����ر�

//��ʱ���¼�
struct NTY_TimerEvent
{
	WORD							wTimerID;							//��ʱ�� ID
	WPARAM							wBindParam;							//�󶨲���
};

//���ݿ������¼�
struct NTY_DataBaseEvent
{
	WORD							wIndex;								//��������
	WORD							wRoundID;							//�����ʶ
	WORD							wRequestID;							//�����ʶ
};

//����Ӧ���¼�
struct NTY_SocketAcceptEvent
{
	WORD							wIndex;								//��������
	WORD							wRoundID;							//���ӱ�ʶ
	DWORD							dwClientIP;							//���ӵ�ַ
};

//�����ȡ�¼�
struct NTY_SocketReadEvent
{
	WORD							wIndex;								//��������
	WORD							wRoundID;							//���ӱ�ʶ
	WORD							wDataSize;							//���ݴ�С
	CMD_Command						Command;							//������Ϣ
};

//����ر��¼�
struct NTY_SocketCloseEvent
{
	WORD							wIndex;								//��������
	WORD							wRoundID;							//���ӱ�ʶ
	DWORD							dwClientIP;							//���ӵ�ַ
	DWORD							dwConnectSecond;					//����ʱ��
};

//////////////////////////////////////////////////////////////////////////

#define VER_IADOError INTERFACE_VERSION(1,1)
static const GUID IID_IADOError={0x66463b5a,0x390c,0x42f9,0x85,0x19,0x13,0x31,0x39,0x36,0xfe,0x8f};

//���ݿ����ӿ�
interface IADOError : public IUnknownEx
{
	//��������
	virtual LPCTSTR __cdecl GetErrorDescribe()=NULL;
	//��������
	virtual enADOErrorType __cdecl GetErrorType()=NULL;
};

//////////////////////////////////////////////////////////////////////////

#define VER_IDataBase INTERFACE_VERSION(1,1)
static const GUID IID_IDataBase={0x9e962173,0x2a9f,0x4ebd,0x8e,0x98,0x40,0xe9,0x96,0x57,0x24,0xfb};

//���ݿ����ӽӿ�
interface IDataBase : public IUnknownEx
{
	//������
	virtual bool __cdecl OpenConnection()=NULL;
	//�رռ�¼
	virtual bool __cdecl CloseRecordset()=NULL;
	//�ر�����
	virtual bool __cdecl CloseConnection()=NULL;
	//��������
	virtual bool __cdecl TryConnectAgain(bool bFocusConnect, CComError * pComError)=NULL;
	//������Ϣ
	virtual bool __cdecl SetConnectionInfo(LPCTSTR szIP, WORD wPort, LPCTSTR szData, LPCTSTR szName, LPCTSTR szPass)=NULL;
	//�Ƿ����Ӵ���
	virtual bool __cdecl IsConnectError()=NULL;
	//�Ƿ��
	virtual bool __cdecl IsRecordsetOpened()=NULL;
	//�����ƶ�
	virtual void __cdecl MoveToNext()=NULL;
	//�Ƶ���ͷ
	virtual void __cdecl MoveToFirst()=NULL;
	//�Ƿ����
	virtual bool __cdecl IsEndRecordset()=NULL;
	//��ȡ��Ŀ
	virtual long __cdecl GetRecordCount()=NULL;
	//��ȡ��С
	virtual long __cdecl GetActualSize(LPCTSTR pszParamName)=NULL;
	//�󶨶���
	virtual bool __cdecl BindToRecordset(CADORecordBinding * pBind)=NULL;
	//��ȡ����
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, BYTE & bValue)=NULL;
	//��ȡ����
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, WORD & wValue)=NULL;
	//��ȡ����
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, INT & nValue)=NULL;
	//��ȡ����
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, LONG & lValue)=NULL;
	//��ȡ����
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, DWORD & ulValue)=NULL;
	//��ȡ����
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, UINT & ulValue)=NULL;
	//��ȡ����
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, DOUBLE & dbValue)=NULL;
	//��ȡ����
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, __int64 & llValue)=NULL;
	//��ȡ����
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, TCHAR szBuffer[], UINT uSize)=NULL;
	//��ȡ����
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, COleDateTime & Time)=NULL;
	//��ȡ����
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, bool & bValue)=NULL;
	//���ô洢����
	virtual void __cdecl SetSPName(LPCTSTR pszSpName)=NULL;
	//�������
	virtual void __cdecl AddParamter(LPCTSTR pszName, ADOCG::ParameterDirectionEnum Direction, ADOCG::DataTypeEnum Type, long lSize, _variant_t & vtValue)=NULL;
	//ɾ������
	virtual void __cdecl ClearAllParameters()=NULL;
	//��ò���
	virtual void __cdecl GetParameterValue(LPCTSTR pszParamName, _variant_t & vtValue)=NULL;
	//��ȡ������ֵ
	virtual long __cdecl GetReturnValue()=NULL;
	//ִ�����
	virtual bool __cdecl Execute(LPCTSTR pszCommand)=NULL;
	//ִ������
	virtual bool __cdecl ExecuteCommand(bool bRecordset)=NULL;
};

//////////////////////////////////////////////////////////////////////////

#ifdef _UNICODE
	#define VER_IDataBaseSink INTERFACE_VERSION(1,1)
	static const GUID IID_IDataBaseSink={0x5852e135,0x18cf,0x4893,0xa2,0x19,0x49,0x51,0x99,0xa2,0xf4,0xa5};
#else
	#define VER_IDataBaseSink INTERFACE_VERSION(1,1)
	static const GUID IID_IDataBaseSink={0x4ba5fef5,0x0fe4,0x4b3f,0x8f,0x28,0x79,0x6a,0x16,0x24,0x5b,0xd6};
#endif

//���ݿ⹳�ӽӿ�
interface IDataBaseSink : public IUnknownEx
{
	//���ݿ�ģ������
	virtual bool __cdecl StartService(IUnknownEx * pIUnknownEx)=NULL;
	//���ݿ�ģ��ر�
	virtual bool __cdecl StopService(IUnknownEx * pIUnknownEx)=NULL;
	//���ݲ�������
	virtual bool __cdecl OnDataBaseRequest(const NTY_DataBaseEvent & DataBaseEvent, void * pDataBuffer, WORD wDataSize)=NULL;
};

//////////////////////////////////////////////////////////////////////////

#ifdef _UNICODE
	#define VER_IDataBaseEngine INTERFACE_VERSION(1,1)
	static const GUID IID_IDataBaseEngine={0x394928f5,0x0aa1,0x414a,0xbe,0xe2,0x0c,0x42,0xb1,0xa8,0x86,0x63};
#else
	#define VER_IDataBaseEngine INTERFACE_VERSION(1,1)
	static const GUID IID_IDataBaseEngine={0xe6a05538,0xbf46,0x4661,0xa3,0xe1,0xa0,0x43,0x7a,0x18,0x22,0x7a};
#endif

//���ݿ�����ӿ�
interface IDataBaseEngine : public IUnknownEx
{
	//��������
	virtual bool __cdecl StartService()=NULL;
	//ֹͣ����
	virtual bool __cdecl StopService()=NULL;
	//ע�ṳ��
	virtual bool __cdecl SetDataBaseSink(IUnknownEx * pIUnknownEx)=NULL;
	//��ȡ�ӿ�
	virtual void * __cdecl GetQueueService(const IID & Guid, DWORD dwQueryVer)=NULL;
};

//////////////////////////////////////////////////////////////////////////

#ifdef _UNICODE
	#define VER_IQueueServiceSink INTERFACE_VERSION(1,1)
	static const GUID IID_IQueueServiceSink={0xbd0d29c2,0x5e92,0x4d8d,0x99,0x2c,0x74,0x3f,0xd6,0x7e,0x74,0x1f};
#else
	#define VER_IQueueServiceSink INTERFACE_VERSION(1,1)
	static const GUID IID_IQueueServiceSink={0x4d2c22dc,0xbcae,0x47e7,0x94,0x41,0x56,0x82,0x53,0x6d,0xa2,0xf0};
#endif

//���ݶ����๳�ӽӿ�
interface IQueueServiceSink : public IUnknownEx
{
	//֪ͨ�ص�����
	virtual void __cdecl OnQueueServiceSink(WORD wIdentifier, void * pBuffer, WORD wDataSize, DWORD dwInsertTime)=NULL;
};

//////////////////////////////////////////////////////////////////////////

#define VER_IQueueService INTERFACE_VERSION(1,1)
static const GUID IID_IQueueService={0xcc5310b5,0x3709,0x40aa,0x85,0x24,0xd6,0xc5,0x87,0xb0,0x32,0x22};

//���ݶ��нӿ�
interface IQueueService : public IUnknownEx
{
	//��������
	virtual bool __cdecl AddToQueue(WORD wIdentifier, void * const pBuffer, WORD wDataSize)=NULL;
};

//////////////////////////////////////////////////////////////////////////

#ifdef _UNICODE
	#define VER_IQueueServiceEngine INTERFACE_VERSION(1,1)
	static const GUID IID_IQueueServiceEngine={0xba9e9d45,0x81c8,0x4a18,0x88,0x86,0x22,0xa7,0x19,0x1c,0x8b,0x54};
#else
	#define VER_IQueueServiceEngine INTERFACE_VERSION(1,1)
	static const GUID IID_IQueueServiceEngine={0x3d205995,0x427b,0x4b30,0xaf,0xfe,0x7e,0x90,0xe4,0x77,0x80,0xc2};
#endif

//����������ӿ�
interface IQueueServiceEngine : public IUnknownEx
{
	//��ʼ����
	virtual bool __cdecl StartService()=NULL;
	//ֹͣ����
	virtual bool __cdecl StopService()=NULL;
	//���ýӿ�
	virtual bool __cdecl SetQueueServiceSink(IUnknownEx * pIUnknownEx)=NULL;
	//������Ϣ
	virtual bool __cdecl GetBurthenInfo(tagBurthenInfo & BurthenInfo)=NULL;
};

//////////////////////////////////////////////////////////////////////////

#ifdef _UNICODE
	#define VER_IEventService INTERFACE_VERSION(1,1)
	static const GUID IID_IEventService={0x0ba26480,0xb171,0x4726,0xa7,0xff,0x9d,0xe3,0x06,0x46,0x01,0xec};
#else
	#define VER_IEventService INTERFACE_VERSION(1,1)
	static const GUID IID_IEventService={0xb6f84de2,0x4c44,0x4bb0,0xb8,0x2d,0xb2,0x0e,0x80,0x01,0x05,0xd8};
#endif

//��������ӿ�
interface IEventService : public IUnknownEx
{
	//���þ��
	virtual bool __cdecl SetRichEditHwnd(HWND hRichEdit)=NULL;
	//���ü���
	virtual void __cdecl ConfigEventService(enTraceLevel TraceLevel, bool bShow)=NULL;
	//�¼�֪ͨ
	virtual void __cdecl ShowEventNotify(LPCTSTR pszString, enTraceLevel TraceLevel)=NULL;
};

//////////////////////////////////////////////////////////////////////////

#ifdef _UNICODE
	#define VER_ITimerEngine INTERFACE_VERSION(1,1)
	static const GUID IID_ITimerEngine={0x89255ac1,0x598f,0x4d67,0xb0,0x22,0xfc,0xaf,0x0a,0xeb,0x37,0x5d};
#else
	#define VER_ITimerEngine INTERFACE_VERSION(1,1)
	static const GUID IID_ITimerEngine={0xeeca6792,0x9508,0x4bf2,0xaf,0xda,0x4e,0x1b,0x0d,0x94,0x2e,0xc4};
#endif

//��ʱ������ӿ�
interface ITimerEngine : public IUnknownEx
{
	//���ö�ʱ��
	virtual bool __cdecl SetTimer(WORD wTimerID, DWORD dwElapse, DWORD dwRepeat, WPARAM wParam)=NULL; 
	//ɾ����ʱ��
	virtual bool __cdecl KillTimer(WORD wTimerID)=NULL;
	//ɾ����ʱ��
	virtual bool __cdecl KillAllTimer()=NULL;
};

//////////////////////////////////////////////////////////////////////////

#ifdef _UNICODE
	#define VER_ITimerEngineManager INTERFACE_VERSION(1,1)
	static const GUID IID_ITimerEngineManager={0xac341f6d,0x1106,0x4e4f,0xbc,0x8f,0x87,0xd0,0x63,0x5f,0xe1,0xbc};
#else
	#define VER_ITimerEngineManager INTERFACE_VERSION(1,1)
	static const GUID IID_ITimerEngineManager={0x26f7f428,0x7196,0x4517,0xb8,0x79,0x1e,0x43,0x01,0x74,0xe2,0x07};
#endif

//��ʱ������ӿ�
interface ITimerEngineManager : public IUnknownEx
{
	//��ʼ����
	virtual bool __cdecl StartService()=NULL;
	//ֹͣ����
	virtual bool __cdecl StopService()=NULL;
	//���ýӿ�
	virtual bool __cdecl SetTimerEngineSink(IUnknownEx * pIUnknownEx)=NULL;
};

//////////////////////////////////////////////////////////////////////////

#ifdef _UNICODE
	#define VER_ITCPSocketEngine INTERFACE_VERSION(1,1)
	static const GUID IID_ITCPSocketEngine={0x1b9f8424,0x639f,0x47e1,0x91,0x4b,0x2f,0xa2,0x57,0x24,0xa8,0x22};
#else
	#define VER_ITCPSocketEngine INTERFACE_VERSION(1,1)
	static const GUID IID_ITCPSocketEngine={0x0c7b943d,0x2f69,0x454e,0xb6,0xf4,0x81,0x7a,0xf6,0xa1,0x83,0x15};
#endif

//TCP SOCKET ����ӿ�
interface ITCPSocketEngine : public IUnknownEx
{
	//�������
	virtual bool __cdecl DetectSocket()=NULL;
	//���ͺ���
	virtual bool __cdecl SendData(WORD wIndex, WORD wRoundID, WORD wMainCmdID, WORD wSubCmdID)=NULL;
	//���ͺ���
	virtual bool __cdecl SendData(WORD wIndex, WORD wRoundID, WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize)=NULL;
	//��������
	virtual bool __cdecl SendDataBatch(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize)=NULL;
	//�ر�����
	virtual bool __cdecl CloseSocket(WORD wIndex, WORD wRoundID)=NULL;
	//�ر�����
	virtual bool __cdecl ShutDownSocket(WORD wIndex, WORD wRoundID)=NULL;
	//����Ⱥ��
	virtual bool __cdecl AllowBatchSend(WORD wIndex, WORD wRoundID, bool bAllow)=NULL;
};

//////////////////////////////////////////////////////////////////////////

#ifdef _UNICODE
	#define VER_ITCPSocketEngineManager INTERFACE_VERSION(1,1)
	static const GUID IID_ITCPSocketEngineManager={0xc255c9e4,0x5539,0x4fd1,0xb5,0xaf,0x71,0x4c,0x66,0x94,0x21,0xc3};
#else
	#define VER_ITCPSocketEngineManager INTERFACE_VERSION(1,1)
	static const GUID IID_ITCPSocketEngineManager={0x43a86f7d,0x4f25,0x47aa,0x8b,0x5a,0x05,0x5d,0x3a,0xc8,0x39,0xf3};
#endif

//TCP SOCKET �������ӿ�
interface ITCPSocketEngineManager : public IUnknownEx
{
	//���ýӿ�
	virtual bool __cdecl SetSocketEngineSink(IUnknownEx * pIUnknownEx)=NULL;
	//���ö˿�
	virtual bool __cdecl SetServicePort(WORD wListenPort)=NULL;
	//������Ŀ
	virtual bool __cdecl SetMaxSocketItem(WORD wMaxSocketItem)=NULL;
	//��������
	virtual bool __cdecl StartService()=NULL;
	//ֹͣ����
	virtual bool __cdecl StopService()=NULL;
};

//////////////////////////////////////////////////////////////////////////

#ifdef _UNICODE
	#define VER_IAttemperEngineSink INTERFACE_VERSION(1,1)
	static const GUID IID_IAttemperEngineSink={0x2a3aa509,0x1140,0x4dc3,0x88,0xbc,0xcb,0x6b,0xcd,0x7d,0x5e,0xcb};
#else
	#define VER_IAttemperEngineSink INTERFACE_VERSION(1,1)
	static const GUID IID_IAttemperEngineSink={0x12513790,0x36d0,0x48d2,0xa6,0xfa,0xc0,0x73,0x8c,0xb3,0xec,0xd5};
#endif

//����ģ�鹳�ӽӿ�
interface IAttemperEngineSink : public IUnknownEx
{
	//����ӿ�
public:
	//����ģ������
	virtual bool __cdecl StartService(IUnknownEx * pIUnknownEx)=NULL;
	//����ģ��ر�
	virtual bool __cdecl StopService(IUnknownEx * pIUnknownEx)=NULL;
	//�¼�����ӿ�
	virtual bool __cdecl OnAttemperEvent(WORD wIdentifier, void * pBuffer, WORD wDataSize, DWORD dwInsertTime)=NULL;

	//�¼��ӿ�
public:
	//��ʱ���¼�
	virtual bool __cdecl OnEventTimer(WORD wTimerID, WPARAM wBindParam)=NULL;
	//���ݿ��¼�
	virtual bool __cdecl OnEventDataBase(void * pDataBuffer, WORD wDataSize, NTY_DataBaseEvent * pDataBaseEvent)=NULL;
	//����Ӧ���¼�
	virtual bool __cdecl OnEventSocketAccept(NTY_SocketAcceptEvent * pSocketAcceptEvent)=NULL;
	//�����ȡ�¼�
	virtual bool __cdecl OnEventSocketRead(CMD_Command Command, void * pDataBuffer, WORD wDataSize, NTY_SocketReadEvent * pSocketReadEvent)=NULL;
	//����ر��¼�
	virtual bool __cdecl OnEventSocketClose(NTY_SocketCloseEvent * pSocketCloseEvent)=NULL;
};

//////////////////////////////////////////////////////////////////////////

#ifdef _UNICODE
	#define VER_IAttemperEngine INTERFACE_VERSION(1,1)
	static const GUID IID_IAttemperEngine={0x3b328b10,0xe670,0x4eae,0xad,0xc5,0xf3,0xb0,0x2f,0xe2,0xa2,0x34};
#else
	#define VER_IAttemperEngine INTERFACE_VERSION(1,1)
	static const GUID IID_IAttemperEngine={0x6351e550,0x5fc8,0x4620,0xbb,0xed,0xe3,0x5b,0x9b,0xe4,0x37,0x83};
#endif

//��������ӿ�
interface IAttemperEngine : public IUnknownEx
{
	//����ӿ�
public:
	//��������
	virtual bool __cdecl StartService()=NULL;
	//ֹͣ����
	virtual bool __cdecl StopService()=NULL;
	//��������
	virtual bool __cdecl SetSocketEngine(IUnknownEx * pIUnknownEx)=NULL;
	//���ù���
	virtual bool __cdecl SetAttemperEngineSink(IUnknownEx * pIUnknownEx)=NULL;
	//��ȡ�ӿ�
	virtual void * __cdecl GetQueueService(const IID & Guid, DWORD dwQueryVer)=NULL;
};

//////////////////////////////////////////////////////////////////////////

#ifdef _UNICODE
	#define VER_IServiceEngine INTERFACE_VERSION(1,1)
	static const GUID IID_IServiceEngine={0xea0f0398,0xde5d,0x4c57,0xbf,0xce,0x48,0xc7,0xde,0x9a,0xeb,0x54};
#else
	#define VER_IServiceEngine INTERFACE_VERSION(1,1)
	static const GUID IID_IServiceEngine={0x238751d4,0xa722,0x46e4,0x97,0x18,0xfc,0x19,0x0a,0x2c,0x59,0x76};
#endif

//��������ӿ�
interface IServiceEngine : public IUnknownEx
{
	//����ӿ�
public:
	//��������
	virtual bool __cdecl StartService()=NULL;
	//ֹͣ����
	virtual bool __cdecl StopService()=NULL;

	//���ýӿ�
public:
	//�����¼�
	virtual bool __cdecl SetEventService(IUnknownEx * pIUnknownEx)=NULL;
	//���ù���
	virtual bool __cdecl SetDataBaseSink(IUnknownEx * pIUnknownEx)=NULL;
	//���ù���
	virtual bool __cdecl SetAttemperEngineSink(IUnknownEx * pIUnknownEx)=NULL;
	//ע�ṳ��
	virtual bool __cdecl RegisterAsynchronismEngineSink(IUnknownEx * pIUnknownEx)=NULL;
	//������������ӿ�
	virtual bool __cdecl InitServiceEngine(WORD wListenPort, WORD wMaxSocketItem)=NULL;

	//�����ѯ
public:
	//��ȡ��ʱ���ӿ�
	virtual void * __cdecl GetTimerEngine(const IID & Guid, DWORD dwQueryVer)=NULL;
	//��ȡ���ݿ�����ӿ�
	virtual void * __cdecl GetDataBaseEngine(const IID & Guid, DWORD dwQueryVer)=NULL;
	//��ȡ��������ӿ�
	virtual void * __cdecl GetAttemperEngine(const IID & Guid, DWORD dwQueryVer)=NULL;
	//��ȡ��������ӿ�
	virtual void * __cdecl GetTCPSocketEngine(const IID & Guid, DWORD dwQueryVer)=NULL;
	//��ȡ�첽����ӿ�
	virtual void * __cdecl GetAsynchronismEngine(const IID & Guid, DWORD dwQueryVer)=NULL;
	//��ȡ�ӿ�
	virtual void * __cdecl GetDataBaseQueueService(const IID & Guid, DWORD dwQueryVer)=NULL;
	//��ȡ�ӿ�
	virtual void * __cdecl GetAttemperQueueService(const IID & Guid, DWORD dwQueryVer)=NULL;

	//���ܽӿ�
public:
	//����״̬
	virtual bool __cdecl IsService()=NULL;
	//�ⲿ����
	virtual bool __cdecl ControlService(void * pBuffer, WORD wDataSize)=NULL;
};

//////////////////////////////////////////////////////////////////////////

#ifdef _UNICODE
	#define VER_IAsynchronismEngine INTERFACE_VERSION(1,1)
	static const GUID IID_IAsynchronismEngine={0x31ef54c0,0xe000,0x4935,0xb5,0xa3,0x56,0x4f,0x29,0xd0,0x23,0x0a};
#else
	#define VER_IAsynchronismEngine INTERFACE_VERSION(1,1)
	static const GUID IID_IAsynchronismEngine={0xe0ee6282,0x3140,0x4aba,0xa3,0x6f,0x79,0x88,0x32,0xfd,0xe8,0xcf};
#endif

//�첽����ӿ�
interface IAsynchronismEngine : public IUnknownEx
{
	//����ӿ�
public:
	//��������
	virtual bool __cdecl StartService()=NULL;
	//ֹͣ����
	virtual bool __cdecl StopService()=NULL;
	//��������
	virtual bool __cdecl InsertRequest(WORD wRequestID, void * const pBuffer, WORD wDataSize, IUnknownEx * pIUnknownEx)=NULL;

	//���ܽӿ�
public:
	//ע�ṳ��
	virtual bool __cdecl RegisterAsynchronismEngineSink(IUnknownEx * pIUnknownEx)=NULL;
	//ȡ��ע��
	virtual bool __cdecl UnRegisterAsynchronismEngineSink(IUnknownEx * pIUnknownEx)=NULL;
};

//////////////////////////////////////////////////////////////////////////

#ifdef _UNICODE
	#define VER_IAsynchronismEngineSink INTERFACE_VERSION(1,1)
	static const GUID IID_IAsynchronismEngineSink={0x623dc53d,0xfe20,0x40fd,0xb7,0x7b,0xd8,0xab,0x3d,0xf6,0x7e,0x27};
#else
	#define VER_IAsynchronismEngineSink INTERFACE_VERSION(1,1)
	static const GUID IID_IAsynchronismEngineSink={0x7404a759,0xe429,0x4253,0x86,0xc5,0x12,0x25,0x60,0x90,0x4f,0xf7};
#endif

//�첽���湳�ӽӿ�
interface IAsynchronismEngineSink : public IUnknownEx
{
	//�����¼�
	virtual bool __cdecl OnAsynchronismEngineStart()=NULL;
	//ֹͣ�¼�
	virtual bool __cdecl OnAsynchronismEngineStop()=NULL;
	//�첽����
	virtual bool __cdecl OnAsynchronismRequest(WORD wRequestID, void * pBuffer, WORD wDataSize)=NULL;
};

//////////////////////////////////////////////////////////////////////////

//��������ļ�
#include "QueueServiceEvent.h"
#include "ServerKernelHelper.h"

//////////////////////////////////////////////////////////////////////////

#endif