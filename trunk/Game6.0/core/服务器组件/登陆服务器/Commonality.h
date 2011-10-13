#ifndef COMMONALITY_HEAD_FILE
#define COMMONALITY_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////
//����ͷ�ļ�

//�������ļ�
#include "..\..\��Ϣ����\CMD_Plaza.h"
#include "..\..\��Ϣ����\CMD_Center.h"

//ȫ��ͷ�ļ�
#include "..\..\�����ļ�\GlobalField.h"
#include "..\..\�����ļ�\GlobalService.h"

//////////////////////////////////////////////////////////////////////////
//���ݿ������

//���ݿ������ʶ
#define	DBR_GP_LOGON_BY_ACCOUNTS	1									//�ʺŵ�¼
#define	DBR_GP_LOGON_BY_USERID		2									//I D ��¼
#define DBR_GP_REGISTER_ACCOUNTS	3									//ע���ʺ�

//���ݿ������ʶ
#define DBR_GP_LOGON_SUCCESS		100									//��¼�ɹ�
#define DBR_GP_LOGON_ERROR			101									//��¼ʧ��

//�ʺŵ�¼
struct DBR_GP_LogonByAccounts
{
	DWORD							dwClientIP;							//���ӵ�ַ
	TCHAR							szAccounts[NAME_LEN];				//��¼�ʺ�
	TCHAR							szPassWord[PASS_LEN];				//��¼����
	TCHAR							szComputerID[COMPUTER_ID_LEN];		//��������
};

//ID ��¼
struct DBR_GP_LogonByUserID
{
	DWORD							dwClientIP;							//���ӵ�ַ
	DWORD							dwUserID;							//�û� I D
	TCHAR							szPassWord[PASS_LEN];				//��¼����
	TCHAR							szComputerID[COMPUTER_ID_LEN];		//��������
};

//�ʺ�ע��
struct DBR_GP_RegisterAccounts
{
	WORD							wFaceID;							//ע��ͷ��
	BYTE							cbGender;							//�û��Ա�
	DWORD							dwClientIP;							//���ӵ�ַ
	TCHAR							szSpreader[NAME_LEN];				//�Ƽ�����
	TCHAR							szAccounts[NAME_LEN];				//��¼�ʺ�
	TCHAR							szPassWord[PASS_LEN];				//��¼����
	TCHAR							szComputerID[COMPUTER_ID_LEN];		//��������
};

//��¼�ɹ�
struct DBR_GP_LogonSuccess
{
	//��������
	DWORD							dwUserID;							//�û���ʶ
	DWORD							dwGameID;							//��Ϸ��ʶ
	DWORD							dwExperience;						//������ֵ
	TCHAR							szPassword[PASS_LEN];				//��¼����
	TCHAR							szAccounts[NAME_LEN];				//��¼�ʺ�
	TCHAR							szGroupName[GROUP_LEN];				//��������

	//�û�����
	WORD							wFaceID;							//ͷ���ʶ
	BYTE							cbGender;							//�û��Ա�
	BYTE							cbMember;							//��Ա�ȼ�
	TCHAR							szUnderWrite[UNDER_WRITE_LEN];		//����ǩ��

	//������Ϣ
	TCHAR							szDescribeString[128];				//������Ϣ
};

//��¼ʧ��
struct DBR_GP_LogonError
{
	LONG							lErrorCode;							//�������
	TCHAR							szErrorDescribe[128];				//������Ϣ
};

//////////////////////////////////////////////////////////////////////////

#endif