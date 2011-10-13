#ifndef GLOBAL_DEF_HEAD_FILE
#define GLOBAL_DEF_HEAD_FILE

#pragma once

/////////////////////////////////////////////////////////////////////////////////////////
//��������

const TCHAR	szProductName[]=TEXT("������Ϸ����");							//��Ʒ����
const TCHAR szSystemRegKey[]=TEXT("dreamGame");								//ע������
const TCHAR szStationPage[]=TEXT("http://www.dreamlib.com/game");								//��Ϸ��ҳ

/////////////////////////////////////////////////////////////////////////////////////////
//�궨��

#define MAX_CHAIR						100									//�����Ϸ��
#define MAX_ANDROID						256									//������
#define MAX_CHAIR_NORMAL				8									//�����Ϸ��

#define MAX_CHAT_LEN					512									//���쳤��
#define INVALID_TABLE					((WORD)(-1))						//��Ч���Ӻ�
#define INVALID_CHAIR					((WORD)(-1))						//��Ч���Ӻ�
#define MAIN_DLG_CLASSNAME				TEXT("dreamGamePlaza")				//����ע����

//�˿ڶ���
#define PORT_LOGON_SERVER				7788								//��½������
#define PORT_CENTER_SERVER				6677								//���ķ�����
#define PORT_VIDEO_SERVER				5566								//��Ƶ������

//�������ݶ���
#define SOCKET_VER						65									//���ݰ��汾
#define SOCKET_PACKAGE					2046								//��������
#define SOCKET_BUFFER					(sizeof(CMD_Head)+SOCKET_PACKAGE+2*sizeof(DWORD))

//����ģʽ
#define DISTRIBUTE_MODE_NONE			0									//���ɷ���
#define DISTRIBUTE_MODE_RAND			1									//�������
#define DISTRIBUTE_MODE_PLAN			2									//��λ����

/////////////////////////////////////////////////////////////////////////////////////////

//���ݰ��ṹ��Ϣ
struct CMD_Info
{
	WORD								wDataSize;							//���ݴ�С
	BYTE								cbCheckCode;						//Ч���ֶ�
	BYTE								cbMessageVer;						//�汾��ʶ
};

//���ݰ�������Ϣ
struct CMD_Command
{
	WORD								wMainCmdID;							//��������
	WORD								wSubCmdID;							//��������
};

//���ݰ����ݰ�ͷ
struct CMD_Head
{
	CMD_Info							CmdInfo;							//�����ṹ
	CMD_Command							CommandInfo;						//������Ϣ
};

//�������ݰ�����
struct CMD_Buffer
{
	CMD_Head							Head;								//���ݰ�ͷ
	BYTE								cbBuffer[SOCKET_PACKAGE];			//���ݻ���
};

//�ں�������
#define MDM_KN_COMMAND					0									//�ں�����
#define SUB_KN_DETECT_SOCKET			1									//�������

//���ṹ��Ϣ
struct CMD_KN_DetectSocket
{
	DWORD								dwSendTickCount;					//����ʱ��
	DWORD								dwRecvTickCount;					//����ʱ��
};

/////////////////////////////////////////////////////////////////////////////////////////

//IPC ���ݶ���
#define IPC_VER							0x0001								//IPC �汾
#define IPC_IDENTIFIER					0x0001								//��ʶ����
#define IPC_PACKAGE						4096								//��� IPC ��
#define IPC_BUFFER						(sizeof(IPC_Head)+IPC_PACKAGE)		//���峤��

//IPC ���ݰ�ͷ
struct IPC_Head
{
	WORD								wVersion;							//IPC �汾
	WORD								wDataSize;							//���ݴ�С
	WORD								wMainCmdID;							//��������
	WORD								wSubCmdID;							//��������
};

//IPC ����ṹ
struct IPC_Buffer
{
	IPC_Head							Head;								//���ݰ�ͷ
	BYTE								cbBuffer[IPC_PACKAGE];				//���ݻ���
};

//////////////////////////////////////////////////////////////////////////

//���Ⱥ궨��
#define TYPE_LEN						32									//���೤��
#define KIND_LEN						32									//���ͳ���
#define STATION_LEN						32									//վ�㳤��
#define SERVER_LEN						32									//���䳤��
#define MODULE_LEN						32									//���̳���

//�Ա���
#define GENDER_NULL						0									//δ֪�Ա�
#define GENDER_BOY						1									//�����Ա�
#define GENDER_GIRL						2									//Ů���Ա�

//��Ϸ����
#define GAME_GENRE_SCORE				0x0001								//��ֵ����
#define GAME_GENRE_GOLD					0x0002								//�������
#define GAME_GENRE_MATCH				0x0004								//��������
#define GAME_GENRE_EDUCATE				0x0008								//ѵ������

//��Ϸ���ͽṹ
struct tagGameType
{
	WORD								wSortID;							//�������
	WORD								wTypeID;							//�������
	TCHAR								szTypeName[TYPE_LEN];				//��������
};

//��Ϸ���ƽṹ
struct tagGameKind
{
	WORD								wSortID;							//�������
	WORD								wTypeID;							//���ͺ���
	WORD								wKindID;							//���ƺ���
	DWORD								dwMaxVersion;						//���°汾
	DWORD								dwOnLineCount;						//������Ŀ
	TCHAR								szKindName[KIND_LEN];				//��Ϸ����
	TCHAR								szProcessName[MODULE_LEN];			//��������
};

//��Ϸ���̽ṹ
struct tagGameProcess
{
	WORD								wSortID;							//�������
	WORD								wTypeID;							//���ͺ���
	WORD								wKindID;							//���ƺ���
	WORD								wServerPort;						//����˿�
	DWORD								dwServerAddr;						//�����ַ
	DWORD								dwMaxVersion;						//���°汾
	DWORD								dwOnLineCount;						//������Ŀ
	TCHAR								szKindName[KIND_LEN];				//��Ϸ����
	TCHAR								szProcessName[MODULE_LEN];			//��������
};

//��Ϸվ��ṹ
struct tagGameStation
{
	WORD								wSortID;							//�������
	WORD								wKindID;							//���ƺ���
	WORD								wJoinID;							//�ҽӺ���
	WORD								wStationID;							//վ�����
	TCHAR								szStationName[STATION_LEN];			//վ������
};

//��Ϸ�����б�ṹ
struct tagGameServer
{
	WORD								wSortID;							//�������
	WORD								wKindID;							//���ƺ���
	WORD								wServerID;							//�������
	WORD								wStationID;							//վ�����
	WORD								wServerPort;						//����˿�
	DWORD								dwServerAddr;						//�����ַ
	DWORD								dwOnLineCount;						//��������
	TCHAR								szServerName[SERVER_LEN];			//��������
};

//////////////////////////////////////////////////////////////////////////

//�û�״̬����
#define US_NULL							0x00								//û��״̬
#define US_FREE							0x01								//վ��״̬
#define US_SIT							0x02								//����״̬
#define US_READY						0x03								//ͬ��״̬
#define US_LOOKON						0x04								//�Թ�״̬
#define US_PLAY							0x05								//��Ϸ״̬
#define US_OFFLINE						0x06								//����״̬

//���Ⱥ궨��
#define NAME_LEN						32									//���ֳ���
#define PASS_LEN						33									//���볤��
#define EMAIL_LEN						32									//���䳤��
#define GROUP_LEN						32									//���ų���
#define COMPUTER_ID_LEN					33									//��������
#define UNDER_WRITE_LEN					32									//����ǩ��

//�û�������Ϣ
struct tagUserScore
{
	LONG								lScore;								//�û�����
	LONG								lWinCount;							//ʤ������
	LONG								lLostCount;							//ʧ������
	LONG								lDrawCount;							//�;�����
	LONG								lFleeCount;							//������Ŀ
	LONG								lExperience;						//�û�����
};

//�û�״̬��Ϣ
struct tagUserStatus
{
	WORD								wTableID;							//���Ӻ���
	WORD								wChairID;							//����λ��
	BYTE								cbUserStatus;						//�û�״̬
};

//�û�������Ϣ�ṹ
struct tagUserInfoHead
{
	//�û�����
	WORD								wFaceID;							//ͷ������
	DWORD								dwUserID;							//�û� I D
	DWORD								dwGameID;							//��Ϸ I D
	DWORD								dwGroupID;							//��������
	DWORD								dwUserRight;						//�û��ȼ�
	DWORD								dwMasterRight;						//����Ȩ��

	//�û�����
	BYTE								cbGender;							//�û��Ա�
	BYTE								cbMemberOrder;						//��Ա�ȼ�
	BYTE								cbMasterOrder;						//����ȼ�

	//�û�״̬
	WORD								wTableID;							//���Ӻ���
	WORD								wChairID;							//����λ��
	BYTE								cbUserStatus;						//�û�״̬

	//�û�����
	tagUserScore						UserScoreInfo;						//������Ϣ
};

//�û���Ϣ�ṹ
struct tagUserData
{
	//�û�����
	WORD								wFaceID;							//ͷ������
	DWORD								dwUserID;							//�û� I D
	DWORD								dwGroupID;							//��������
	DWORD								dwGameID;							//�û� I D
	DWORD								dwUserRight;						//�û��ȼ�
	DWORD								dwMasterRight;						//����Ȩ��
	TCHAR								szName[NAME_LEN];					//�û�����
	TCHAR								szGroupName[GROUP_LEN];				//��������
	TCHAR								szUnderWrite[UNDER_WRITE_LEN];		//����ǩ��

	//�û�����
	BYTE								cbGender;							//�û��Ա�
	BYTE								cbMemberOrder;						//��Ա�ȼ�
	BYTE								cbMasterOrder;						//����ȼ�

	//�û�����
	LONG								lScore;								//�û�����
	LONG								lWinCount;							//ʤ������
	LONG								lLostCount;							//ʧ������
	LONG								lDrawCount;							//�;�����
	LONG								lFleeCount;							//������Ŀ
	LONG								lExperience;						//�û�����

	//�û�״̬
	WORD								wTableID;							//���Ӻ���
	WORD								wChairID;							//����λ��
	BYTE								cbUserStatus;						//�û�״̬

	//������Ϣ
	BYTE								cbCompanion;						//�û���ϵ
};

//////////////////////////////////////////////////////////////////////////

//�������кŽṹ
struct tagClientSerial
{
	DWORD								dwSystemVer;						//ϵͳ�汾
	DWORD								dwComputerID[3];					//��������
};

//���û���ṹ
struct tagOptionBuffer
{
	BYTE								cbBufferLen;						//���ݳ���
	BYTE								cbOptionBuf[32];					//���û���
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif