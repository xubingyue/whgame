#ifndef GLOBAL_UNITS_HEAD_FILE
#define GLOBAL_UNITS_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "DlgStatus.h"
#include "RoomViewItem.h"
#include "PlazaViewItem.h"
#include "ServerItemView.h"

//////////////////////////////////////////////////////////////////////////

//ȫ���û�����
struct tagGlobalUserData
{
	WORD								wFaceID;						//ͷ������
	BYTE								cbGender;						//�û��Ա�
	BYTE								cbMember;						//��Ա�ȼ�
	DWORD								dwUserID;						//�û� I D
	DWORD								dwGameID;						//��Ϸ I D
	DWORD								dwExperience;					//�û�����
	TCHAR								szAccounts[NAME_LEN];			//��¼�ʺ�
	TCHAR								szPassWord[PASS_LEN];			//��¼����
	TCHAR								szGroupName[GROUP_LEN];			//������Ϣ
	TCHAR								szUnderWrite[UNDER_WRITE_LEN];	//����ǩ��
};

//ȫ����Ϣ��
class CGlobalUnits
{
	//��Ϣ����
protected:
	TCHAR								m_szStationPage[32];			//վ��ҳ��
	tagGlobalUserData					m_GloblaUserData;				//�û���Ϣ

	//ϵͳ����
protected:
	DWORD								m_dwPlazaVersion;				//�����汾
	TCHAR								m_szDirSkin[MAX_PATH];			//Ƥ��Ŀ¼
	TCHAR								m_szDirWork[MAX_PATH];			//����Ŀ¼

	//�������
public:
	CServerListManager					m_ServerListManager;			//�б����

	//�������
public:
	CUserFaceResHelper					m_UserFaceRes;					//ͷ�����
	CGameRankManagerHelper				m_GameRankManager;				//��Ϸ�ȼ�
	CDownLoadServiceHelper				m_DownLoadService;				//���ط���
	CCompanionManagerHelper				m_CompanionManager;				//�رչ���
	
	//��������
public:
	//���캯��
	CGlobalUnits(void);
	//��������
	virtual ~CGlobalUnits(void);

	//���ܺ���
public:
	//��ʼ������
	bool InitGlobalUnits();
	//�����ַ�
	bool CopyToClipboard(LPCTSTR pszString);
	//��ȡ����
	void GetClientSerial(tagClientSerial & ClientSerial);
	//ע���ȼ�
	bool RegisterHotKey(HWND hWnd, UINT uKeyID, WORD wHotKey);

	//��ѯ����
public:
	//�����汾
	DWORD GetPlazaVersion() { return m_dwPlazaVersion; }
	//����Ŀ¼
	LPCTSTR GetWorkDirectory() { return m_szDirWork; }
	//����Ŀ¼
	LPCTSTR GetSkinDirectory() { return m_szDirSkin; }

	//״̬����
public:
	//������վ��ַ
	LPCTSTR SetStationPage(LPCTSTR pszStationPage);
	//��ȡ��վ��ַ
	LPCTSTR GetStationPage() { return m_szStationPage; }
	//��ȡ�û���Ϣ
	tagGlobalUserData & GetGolbalUserData() { return m_GloblaUserData; }

	//�������
public:
	//ͷ��ӿ�
	IUserFaceRes * GetUserFaceRes() { return m_UserFaceRes.GetInterface(); }

	//�ڲ�����
private:
	//������ַ
	WORD GetMACAddress(BYTE cbMacBuffer[], WORD wBufferSize);
};

//////////////////////////////////////////////////////////////////////////

//ȫ�ֵ�����
class CGlobalAttemper
{
	//�ؼ�����
protected:
	CDlgStatus							m_DlgStatus;					//״̬����
   
	//��������
public:
	//���캯��
	CGlobalAttemper(void);
	//��������
	virtual ~CGlobalAttemper(void);

	//���ܺ���
public:
	//��ʾ��ʾ
	bool ShowStatusMessage(LPCTSTR pszMessage, CWnd * pNotifyWnd);
	//�ر���ʾ
	bool DestroyStatusWnd(CWnd * pNotifyWnd);
	//������Ϸ
	bool DownLoadClient(LPCTSTR pszKindName, WORD wKindID, bool bDisplay);
};

//////////////////////////////////////////////////////////////////////////

//ȫ����Ϣ 
extern	CGlobalUnits					g_GlobalUnits;					//��Ϣ���			
extern	CGlobalAttemper					g_GlobalAttemper;				//ȫ�ֵ���

//////////////////////////////////////////////////////////////////////////

#endif