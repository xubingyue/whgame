#ifndef DATA_BASE_SINK_HEAD_FILE
#define DATA_BASE_SINK_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "GameServiceExport.h"

//////////////////////////////////////////////////////////////////////////
//�ṹ����

//���ݿ����
struct tagDataBaseSinkParameter
{
	tagDataBaseInfo						* pGameUserDBInfo;				//������Ϣ
	tagDataBaseInfo						* pGameScoreDBInfo;				//������Ϣ
	tagGameServiceAttrib				* pGameServiceAttrib;			//��������
	tagGameServiceOption				* pGameServiceOption;			//������Ϣ
};

//////////////////////////////////////////////////////////////////////////
//���ݿ��������ݰ�

//���ݿ������ʶ
#define	DBR_GR_LOGON_BY_USERID			1								//I D ��¼
#define DBR_GR_WRITE_GAME_SCORE			2								//�뿪����
#define DBR_GR_LEAVE_GAME_SERVER		3								//�޸Ļ���
#define DBR_GR_GAME_SCORE_RECORD		4								//���ּ�¼
#define DBR_GR_LOAD_ANDROID				5								//�����û�
#define DBR_GR_LIMIT_ACCOUNTS			6								//�����ʻ�
#define DBR_GR_SET_USER_RIGHT			7								//����Ȩ��

//���ݿ������ʶ
#define DBR_GR_LOGON_SUCCESS			100								//��¼�ɹ�
#define DBR_GR_LOGON_ERROR				101								//��¼ʧ��
#define DBR_GR_ANDROID_USER				102								//������Ϣ

//ID ��¼
struct DBR_GR_LogonByUserID
{
	DWORD								dwUserID;						//�û� I D
	DWORD								dwClientIP;						//���ӵ�ַ
	TCHAR								szPassWord[PASS_LEN];			//��¼����
	TCHAR								szComputerID[COMPUTER_ID_LEN];	//��������
};

//�����ʻ�
struct DBR_GR_LimitAccounts
{
	DWORD								dwUserID;						//�û� I D
	DWORD								dwMasterUserID;					//���� I D
	DWORD								dwMasterClientIP;				//���ӵ�ַ
};

//����Ȩ��
struct DBR_GR_SetUserRight
{
	//Ȩ�޷�Χ
	BYTE								cbGame;							//������Ϸ
	BYTE								cbAccounts;						//�����ʺ�

	//Ȩ����Ϣ
	DWORD								dwUserID;						//�û� I D
	DWORD								dwUserRight;					//�û�Ȩ��
	DWORD								dwMasterUserID;					//���� I D
	DWORD								dwMasterClientIP;				//���ӵ�ַ
};

//�����û�
struct DBO_GR_AndroidUser
{
	LONG								lResultCode;					//�������
	WORD								wAndroidCount;					//�û���Ŀ
	DWORD								dwAndroidID[MAX_ANDROID];		//�û� I D
};

//��¼�ɹ�
struct DBR_GR_LogonSuccess
{
	//������Ϣ
	WORD								wFaceID;						//ͷ������
	DWORD								dwUserID;						//�û� I D
	DWORD								dwGameID;						//�û� I D
	DWORD								dwGroupID;						//��������
	DWORD								dwUserRight;					//�û��ȼ�
	DWORD								dwMasterRight;					//����Ȩ��
	TCHAR								szAccounts[NAME_LEN];			//��¼�ʺ�
	TCHAR								szPassWord[PASS_LEN];			//��¼����
	TCHAR								szGroupName[GROUP_LEN];			//��������
	TCHAR								szUnderWrite[UNDER_WRITE_LEN];	//����ǩ��

	//�û�����
	BYTE								cbGender;						//�û��Ա�
	BYTE								cbMemberOrder;					//��Ա�ȼ�
	BYTE								cbMasterOrder;					//����ȼ�

	//������Ϣ
	LONG								lScore;							//�û�����
	LONG								lWinCount;						//ʤ������
	LONG								lLostCount;						//ʧ������
	LONG								lDrawCount;						//�;�����
	LONG								lFleeCount;						//������Ŀ
	LONG								lExperience;					//�û�����
};

//��¼ʧ��
struct DBR_GR_LogonError
{
	LONG								lErrorCode;						//�������
	TCHAR								szErrorDescribe[128];			//������Ϣ
};

//�޸Ļ���
struct DBR_GR_WriteUserScore
{
	//�û�����
	DWORD								dwUserID;						//�û���ַ
	DWORD								dwClientIP;						//���ӵ�ַ
	DWORD								dwPlayTimeCount;				//��Ϸʱ��
	DWORD								dwOnlineTimeCount;				//����ʱ��

	//������Ϣ
	LONG								lRevenue;						//��Ϸ˰��
	tagUserScore						ScoreModifyInfo;				//�޸Ļ���
};

//�뿪����
struct DBR_GR_LeaveGameServer
{
	//�û�����
	DWORD								dwUserID;						//�û���ַ
	DWORD								dwClientIP;						//���ӵ�ַ
	DWORD								dwPlayTimeCount;				//��Ϸʱ��
	DWORD								dwOnlineTimeCount;				//����ʱ��

	//������Ϣ
	LONG								lRevenue;						//��Ϸ˰��
	tagUserScore						ScoreModifyInfo;				//�޸Ļ���
};

//////////////////////////////////////////////////////////////////////////

//���ݿ����湳��
class CDataBaseSink : public IDataBaseSink
{
	//���ñ���
protected:
	tagDataBaseInfo						* m_pGameUserDBInfo;			//������Ϣ
	tagDataBaseInfo						* m_pGameScoreDBInfo;			//������Ϣ
	tagGameServiceAttrib				* m_pGameServiceAttrib;			//��������
	tagGameServiceOption				* m_pGameServiceOption;			//������Ϣ

	//�ӿڱ���
protected:
	IEventService						* m_pIEventService;				//�¼�����

	//�������
protected:
	CDataBaseHelper						m_GameUserDB;					//�û����ݿ�
	CDataBaseHelper						m_GameScoreDB;					//��Ϸ���ݿ�
	CQueueServiceEvent					m_AttemperEvent;				//����֪ͨ

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
	bool InitDataBaseSink(tagDataBaseSinkParameter * pDataBaseSinkParameter, IUnknownEx * pIUnknownEx);

	//������
private:
	//��¼����
	bool OnRequestLogon(const NTY_DataBaseEvent & DataBaseEvent, void * pDataBuffer, WORD wDataSize);
	//д������
	bool OnRequestWriteUserScore(const NTY_DataBaseEvent & DataBaseEvent, void * pDataBuffer, WORD wDataSize);
	//�뿪����
	bool OnRequestLeaveGameServer(const NTY_DataBaseEvent & DataBaseEvent, void * pDataBuffer, WORD wDataSize);
	//�����ʻ�
	bool OnRequestLimitAccounts(const NTY_DataBaseEvent & DataBaseEvent, void * pDataBuffer, WORD wDataSize);
	//����Ȩ��
	bool OnRequestSetUserRight(const NTY_DataBaseEvent & DataBaseEvent, void * pDataBuffer, WORD wDataSize);

	//�洢����
protected:
	//I D �洢����
	LONG SPLogonByUserID(DWORD dwUserID, LPCTSTR pszPassword, DWORD dwClientIP, LPCTSTR pszComputerID);
	//д�ִ洢����
	LONG SPWriteUserScore(DWORD dwUserID, DWORD dwPlayTimeCount, DWORD dwOnLineTimeCount, DWORD dwClientIP, LONG lRevenue, tagUserScore & UserScore);
	//�뿪�洢����
	LONG SPLeaveGameServer(DWORD dwUserID, DWORD dwPlayTimeCount, DWORD dwOnLineTimeCount, DWORD dwClientIP, LONG lRevenue, tagUserScore & UserScore);
	//���Ŵ洢����
	LONG SPCongealAccounts(DWORD dwUserID, DWORD dwMasterUserID, DWORD dwClientIP);
	//Ȩ�޴洢����
	LONG SPSetUserGameRight(DWORD dwUserID, DWORD dwUserRight, DWORD dwMasterUserID, DWORD dwClientIP);
	//Ȩ�޴洢����
	LONG SPSetUserAccountsRight(DWORD dwUserID, DWORD dwUserRight, DWORD dwMasterUserID, DWORD dwClientIP);
};

//////////////////////////////////////////////////////////////////////////

#endif