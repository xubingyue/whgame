#ifndef CMD_VIDEO_HEAD_FILE
#define CMD_VIDEO_HEAD_FILE

//////////////////////////////////////////////////////////////////////////

#define MDM_GF_VIDEO				200									//��Ƶͨ��

#define SUB_GF_C_VIDEO_CONFIG		1									//��Ƶ����

#define SUB_GF_S_VIDEO_CONFIG		100									//��Ƶ����

//////////////////////////////////////////////////////////////////////////

//��Ƶ����
struct CMD_C_VideoConfig
{
	//������Ϣ
	WORD							wNatPort;							//����˿�
	WORD							wLocalPort;							//����˿�
	DWORD							dwNatAddr;							//�����ַ
	DWORD							dwLocalAddr;						//���ص�ַ

	//�û���ʶ
	DWORD							dwRemoteUserID;						//Զ���û�
};

//��Ƶ����
struct CMD_S_VideoConfig
{
	//������Ϣ
	WORD							wNatPort;							//����˿�
	WORD							wLocalPort;							//����˿�
	DWORD							dwNatAddr;							//�����ַ
	DWORD							dwLocalAddr;						//���ص�ַ

	//�û���ʶ
	DWORD							dwLocalUserID;						//�����û�
};

//////////////////////////////////////////////////////////////////////////

#endif