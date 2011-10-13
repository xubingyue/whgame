#ifndef VIDEO_SERVICE_CONTROL_HEAD_FILE
#define VIDEO_SERVICE_CONTROL_HEAD_FILE

#pragma once

#include "VideoSend.h"
#include "VideoRece.h"
#include "VideoServiceModule.h"

//////////////////////////////////////////////////////////////////////////

//��Ƶ����
class VIDEO_SERVICE_CLASS CVideoServiceControl : public CWnd
{
	//��Ԫ����
	friend class CVideoServiceManager;

	//�ں˱���
private:
	bool							m_bInitVideo;						//���ñ�־

	//�û���Ϣ
private:
	DWORD							m_dwUserID;							//�û���ʶ
	TCHAR							m_szAccounts[NAME_LEN];				//�û��ʺ�

	//�豸��־
private:
	bool							m_bVidicon;							//��Ƶ�豸
	bool							m_bMicrophone;						//��Ƶ�豸

	//���Ʊ���
private:
	bool							m_bSmallMode;						//С��ģʽ
	bool							m_bLocalMode;						//���ر�־
	bool							m_bEnableVideo;						//�Ƿ���Ƶ
	bool							m_bEnableAudio;						//�Ƿ���Ƶ

	//��ť�ؼ�
private:
	CSkinButton						m_btMore;							//���ఴť
	CSkinButton						m_btVideo;							//��Ƶ��ť
	CSkinButton						m_btAudio;							//��Ƶ��ť
	CSkinButton						m_btClone;							//��¡��ť
	CSkinButton						m_btFlower;							//�ͻ���ť

	//�ؼ�����
protected:
	CVideoSend						m_VideoSend;						//�������
	CVideoRece						m_VideoRece;						//�������
	CToolTipCtrl					m_ToolTipCtrl;						//��ʾ�ؼ�

	//ͼƬ��Դ
private:
	CSkinImage						m_ImageSmallPhoto;					//��Сͷ��
	CSkinImage						m_ImageLargePhoto;					//�Ŵ�ͷ��
	CSkinImage						m_ImageSmallFrame;					//��С���
	CSkinImage						m_ImageLargeFrame;					//�Ŵ���

	//��������
public:
	//���캯��
	CVideoServiceControl();
	//��������
	virtual ~CVideoServiceControl();

	//���غ���
protected:
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	//��Сģʽ
public:
	//��Сģʽ
	bool SetSmallMode(bool bSmallMode);
	//��Сģʽ
	bool IsSamllMode() { return m_bSmallMode; }

	//Զ���û�
public:
	//Զ���û�
	DWORD GetVideoUserID() { return m_dwUserID; }
	//Զ���û�
	bool SetVideoUserInfo(DWORD dwUserID, LPCTSTR pszAccounts);

	//�豸����
public:
	//��Ƶ�豸
	bool HaveVidicon() { return m_bVidicon; }
	//��Ƶ�豸
	bool HaveMicrophone() { return m_bMicrophone; }

	//���ƺ���
public:
	//��Ƶ����
	bool EnableAudio(bool bEnable);
	//��Ƶ����
	bool EnableVideo(bool bEnable);
	//������Ƶ
	bool InitVideoService(bool bLocalMode, bool bSmallMode);

	//�¼�����
public:
	//��������
	bool OnEventGameReset();
	//�û��뿪
	bool OnEventUserLeave(DWORD dwRemoteUserID);
	//�û�����
	bool OnEventUserEnter(DWORD dwRemoteUserID);
	//�û�����
	bool OnEventUserConfig(DWORD dwRemoteUserID, tagVideoNetwordInfo * pVideoNetwordInfo);
	//��ʾ��Ƶ
	bool OnShowLocalVD(bool bShow);

	//�ڲ�����
protected:
	//��������
	VOID RectifyControl();

	//��Ϣӳ��
protected:
	//�ػ�����
	VOID OnPaint();
	//ʹ��֪ͨ
	VOID OnEventVideoEnable();
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//��������
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);

	//��ť��Ϣ
protected:
	//���ఴť
	VOID OnBnClickedMore();
	//��Ƶ��ť
	VOID OnBnClickedVideo();
	//��Ƶ��ť
	VOID OnBnClickedAudio();
	//��¡��ť
	VOID OnBnClickedClone();
	//�ͻ���ť
	VOID OnBnClickedFlower();

	//��Ϣ��
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP() 
};

//////////////////////////////////////////////////////////////////////////

//��Ƶ����
class VIDEO_SERVICE_CLASS CVideoServiceManager
{
	//��Ԫ����
	friend class CVideoServiceControl;

	//��Ƶ��Ϣ
protected:
	WORD							m_wVideoPort;						//��Ƶ�˿�
	DWORD							m_dwVideoServer;					//��Ƶ��ַ
	DWORD							m_dwLocalUserID;					//�����û�
	bool							m_bOffLine[MAX_CHAIR];				//��Ҷ���

	//�������
protected:
	IClientKernel *					m_pIClientKernel;					//�ں˽ӿ�
	CVideoServiceControl *			m_VideoServiceControl[MAX_CHAIR];	//��Ƶ����

	//��̬����
protected:
	static CVideoServiceManager *	m_pVideoServiceManager;				//�������

	//��������
public:
	//���캯��
	CVideoServiceManager();
	//��������
	virtual ~CVideoServiceManager();

	//���ú���
public:
	//���ýӿ�
	bool SetClientKernel(IUnknownEx * pIUnknownEx);
	//������Ϣ
	bool SetVideoServiceInfo(DWORD dwLoaclUserID, DWORD dwVideoServer, WORD wVideoPort);
	//���ö���
	bool SetVideoServiceControl(WORD wVideoIndex, CVideoServiceControl * pVideoServiceControl);

	//�¼��ӿ�
public:
	//��������
	bool OnEventGameReset();
	//�û��뿪
	bool OnEventUserLeave(WORD wVideoIndex, DWORD dwRemoteUserID);
	//�û�����
	bool OnEventUserEnter(WORD wVideoIndex, DWORD dwRemoteUserID);
	//�û�����
	bool OnEventUserConfig(WORD wVideoIndex, DWORD dwRemoteUserID, tagVideoNetwordInfo * pVideoNetwordInfo);
	//��ʾ��Ƶ
	bool OnShowLocalVD(bool bShow);
	//�����û�
	bool OnUpdateUserItem( WORD wVideoIndex, BYTE cbUserStatus, DWORD dwRemoteUserID );

	//��̬����
public:
	//��ȡʵ��
	static CVideoServiceManager * GetInstance() { return m_pVideoServiceManager; }
};

//////////////////////////////////////////////////////////////////////////

#endif
