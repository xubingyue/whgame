#include "Stdafx.h"
#include "Resource.h"
#include "VideoServiceControl.h"

//////////////////////////////////////////////////////////////////////////

//���ڱ�ʶ
#define IDC_VIDEO_SNED				100									//���ʹ���
#define IDC_VIDEO_RCEC				100									//���մ���
#define IDC_VIDEO_SR				100									//��Ƶ����

//��ť��ʶ
#define IDC_FLOWER					103									//�ͻ���ť
#define IDC_VIDEO					104									//��Ƶ��ť
#define IDC_AUDIO					105									//��Ƶ��ť
#define IDC_CLONE					106									//��¡��ť
#define IDC_MORE					107									//���ఴť


//λ�ñ�ʶ
#define X_SMALL_POS					4									//��ʼ����
#define Y_SMALL_POS					4									//��ʼ����
#define X_LARGE_POS					5									//��ʼ����
#define Y_LARGE_POS					5									//��ʼ����

//��ȱ�ʶ
#define W_SMALL_POS					80									//�������
#define H_SMALL_POS					60									//�߶�����
#define W_LARGE_POS					160									//�������
#define H_LARGE_POS					120									//�߶�����

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CVideoServiceControl, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_FLOWER,OnBnClickedFlower)
	ON_BN_CLICKED(IDC_VIDEO,OnBnClickedVideo)
	ON_BN_CLICKED(IDC_AUDIO,OnBnClickedAudio)
	ON_BN_CLICKED(IDC_CLONE,OnBnClickedClone)
	ON_BN_CLICKED(IDC_MORE,OnBnClickedMore)
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CVideoServiceControl, CWnd)
	ON_EVENT(CVideoServiceControl, IDC_VIDEO_SR, 202, OnEventVideoEnable, VTS_NONE)
END_EVENTSINK_MAP()

//////////////////////////////////////////////////////////////////////////

//��̬����
CVideoServiceManager * CVideoServiceManager::m_pVideoServiceManager=NULL;//�������

//////////////////////////////////////////////////////////////////////////

//���캯��
CVideoServiceControl::CVideoServiceControl()
{
	//�ں˱���
	m_bInitVideo=false;

	//���Ʊ���
	m_bSmallMode=false;
	m_bLocalMode=false;
	m_bEnableVideo=true;
	m_bEnableAudio=true;

	//�豸��־
	m_bVidicon=false;
	m_bMicrophone=false;

	//�û���Ϣ
	m_dwUserID=0L;
	ZeroMemory(m_szAccounts,sizeof(m_szAccounts));

	//������Դ
	HINSTANCE hResInstance=GetModuleHandle(VIDEO_SERVICE_DLL_NAME);
	m_ImageSmallPhoto.SetLoadInfo(IDB_SMALL_PHOTO,hResInstance,false);
	m_ImageLargePhoto.SetLoadInfo(IDB_LARGE_PHOTO,hResInstance,false);
	m_ImageSmallFrame.SetLoadInfo(IDB_SMALL_FRAME,hResInstance,false);
	m_ImageLargeFrame.SetLoadInfo(IDB_LARGE_FRAME,hResInstance,false);

	return;
}

//��������
CVideoServiceControl::~CVideoServiceControl()
{
}

//��Ϣ����
BOOL CVideoServiceControl::PreTranslateMessage(MSG * pMsg)
{
	//��ʾ��Ϣ
	if (m_ToolTipCtrl.m_hWnd!=NULL)
	{
		m_ToolTipCtrl.RelayEvent(pMsg);
	}

	return __super::PreTranslateMessage(pMsg);
}

//��Сģʽ
bool CVideoServiceControl::SetSmallMode(bool bSmallMode)
{
	//���ñ���
	if (m_bSmallMode!=bSmallMode)
	{
		//���ñ���
		m_bSmallMode=bSmallMode;

		//��������
		RectifyControl();
	}

	return true;
}

//��Ƶ����
bool CVideoServiceControl::EnableAudio(bool bEnable)
{
	return true;
}

//��Ƶ����
bool CVideoServiceControl::EnableVideo(bool bEnable)
{
	return true;
}

//�����û�
bool CVideoServiceControl::SetVideoUserInfo(DWORD dwUserID, LPCTSTR pszAccounts)
{
	//���ñ���
	m_dwUserID=dwUserID;
	lstrcpyn(m_szAccounts,pszAccounts,CountArray(m_szAccounts));

	//ˢ�´���
	if (m_hWnd!=NULL) Invalidate(FALSE);

	return true;
}

//������Ƶ
bool CVideoServiceControl::InitVideoService(bool bLocalMode, bool bSmallMode)
{
	//Ч��״̬
	ASSERT((m_hWnd!=NULL)&&(m_bInitVideo==false));
	if ((m_hWnd==NULL)||(m_bInitVideo==true)) return false;

	//��ȡ����
	ASSERT(CVideoServiceManager::GetInstance()!=NULL);
	CVideoServiceManager * pVideoServiceManager=CVideoServiceManager::GetInstance();

	//�Թ��ж�
	if ( pVideoServiceManager != NULL && pVideoServiceManager->m_pIClientKernel != NULL && pVideoServiceManager->m_pIClientKernel->IsLookonMode() ) return false;

	//���ñ���
	m_bInitVideo=true;
	m_bSmallMode=bSmallMode;
	m_bLocalMode=bLocalMode;

	//���ð�ť
	HINSTANCE hResInstance=GetModuleHandle(VIDEO_SERVICE_DLL_NAME);
	m_btMore.SetButtonImage(m_bSmallMode?IDB_BT_SMALL_MORE:IDB_BT_BIG_MORE,hResInstance,false);
	m_btVideo.SetButtonImage(m_bSmallMode?IDB_BT_SMALL_SEE:IDB_BT_BIG_SEE,hResInstance,false);
	m_btAudio.SetButtonImage(m_bSmallMode?IDB_BT_SMALL_TALK:IDB_BT_BIG_TALK,hResInstance,false);
	m_btClone.SetButtonImage(m_bSmallMode?IDB_BT_SMALL_RESORE:IDB_BT_BIG_RESORE,hResInstance,false);
	m_btFlower.SetButtonImage(m_bSmallMode?IDB_BT_SMALL_FLOWER:IDB_BT_BIG_FLOWER,hResInstance,false);

	//��������
	if (m_bLocalMode==true)
	{
		//������Ƶ
		CRect rcCreate(0,0,0,0);
		m_VideoSend.Create(NULL,NULL,WS_CHILD,rcCreate,this,IDC_VIDEO_SNED);

		//�����豸
		if ((m_VideoSend.m_hWnd!=NULL)&&(m_VideoSend.HasVideoDrv()!=FALSE))
		{
			//���ñ���
			m_bVidicon=true;
			m_bMicrophone=true;

			//�����豸
			m_VideoSend.SetVideoMode(2);
			m_VideoSend.SetVideoRate(3);
		}
	}
	else
	{
		//������Ƶ
		CRect rcCreate(0,0,0,0);
		m_VideoRece.Create(NULL,NULL,WS_CHILD,rcCreate,this,IDC_VIDEO_RCEC);
	}

	//��������
	RectifyControl();

	return true;
}

//��ʾ��Ƶ
bool CVideoServiceControl::OnShowLocalVD(bool bShow)
{
	//��ʾ����
	if ( bShow )
	{
		if ( m_bLocalMode )
		{
			//��ʾ��Ƶ
			m_VideoSend.OpenSend();

			return true;
		}
	}
	else
	{
		if ( m_bLocalMode )
		{
			//�ر���Ƶ
			m_VideoSend.CloseSend();
			m_VideoSend.ShowWindow(SW_HIDE);
			
			//��ֹ��ť
			m_btMore.EnableWindow(FALSE);
			m_btVideo.EnableWindow(FALSE);
			m_btAudio.EnableWindow(FALSE);
			m_btClone.EnableWindow(FALSE);
			m_btFlower.EnableWindow(FALSE);

			return true;
		}
	}

	return false;
}

//��������
bool CVideoServiceControl::OnEventGameReset()
{
	//���ñ���
	m_dwUserID=0L;
	ZeroMemory(m_szAccounts,sizeof(m_szAccounts));

	//���ÿؼ�
	if (m_VideoRece.m_hWnd!=NULL)
	{
		m_VideoRece.CloseRece();
		m_VideoRece.ShowWindow(SW_HIDE);

		//��ֹ��ť
		m_btMore.EnableWindow(FALSE);
		m_btVideo.EnableWindow(FALSE);
		m_btAudio.EnableWindow(FALSE);
		m_btClone.EnableWindow(FALSE);
		m_btFlower.EnableWindow(FALSE);
	}

	//�ر�ͨ��
	if (m_VideoSend.m_hWnd!=NULL)
	{
	}

	return true;
}

//�û��뿪
bool CVideoServiceControl::OnEventUserLeave(DWORD dwRemoteUserID)
{
	//״̬Ч��
	ASSERT(m_bInitVideo==true);
	if (m_bInitVideo==false) return false;

	//����ģʽ
	if ((m_bLocalMode==true)&&(m_bVidicon==true))
	{
		//״̬Ч��
		if (m_VideoSend.m_hWnd==NULL) return false;

		//ɾ��ͨ��
		m_VideoSend.DeleteP2PSocket(dwRemoteUserID);

		return true;
	}

	//Զ��ģʽ
	if ((m_bLocalMode==false)&&(m_dwUserID==dwRemoteUserID))
	{
		//״̬Ч��
		if (m_VideoRece.m_hWnd==NULL) return false;

		//�ر���Ƶ
		m_VideoRece.CloseRece();

		//���ش���
		if (m_VideoRece.m_hWnd!=NULL) m_VideoRece.ShowWindow(SW_HIDE);

		//�����û�
		SetVideoUserInfo(0L,TEXT(""));

		//ʹ�ܰ�ť
		m_btMore.EnableWindow(FALSE);
		m_btVideo.EnableWindow(FALSE);
		m_btAudio.EnableWindow(FALSE);
		m_btClone.EnableWindow(FALSE);
		m_btFlower.EnableWindow(FALSE);

		return true;
	}

	return false;
}

//�û�����
bool CVideoServiceControl::OnEventUserEnter(DWORD dwRemoteUserID)
{
	//״̬Ч��
	ASSERT(m_bInitVideo==true);
	if (m_bInitVideo==false) return false;

	//����ģʽ
	if ((m_bLocalMode==true)&&(m_bVidicon==true))
	{
		//��ȡ����
		ASSERT(CVideoServiceManager::GetInstance()!=NULL);
		CVideoServiceManager * pVideoServiceManager=CVideoServiceManager::GetInstance();

		//����ͨ��
		m_VideoSend.InsertP2PSocket(pVideoServiceManager->m_dwLocalUserID,dwRemoteUserID,pVideoServiceManager->m_dwVideoServer,
			pVideoServiceManager->m_wVideoPort);

		//������Ϣ
		WORD wNatPort=0,wLocalPort=0;
		DWORD dwNatAddr=0L,dwLocalAddr=0L;
		if (m_VideoSend.m_hWnd!=NULL) m_VideoSend.GetP2PInfo(dwRemoteUserID,&dwLocalAddr,&wLocalPort,&dwNatAddr,&wNatPort);

		//Ч������
 		if ((wNatPort==0L)||(dwNatAddr==0L)) return false;
		if ((wLocalPort==0L)||(dwLocalAddr==0L)) return false;

		//��������
		if ((pVideoServiceManager!=NULL)&&(pVideoServiceManager->m_pIClientKernel!=NULL))
		{
			//��������
			CMD_C_VideoConfig VideoConfig;
			ZeroMemory(&VideoConfig,sizeof(VideoConfig));

			//���ñ���
			VideoConfig.wNatPort=wNatPort;
			VideoConfig.dwNatAddr=dwNatAddr;
			VideoConfig.wLocalPort=wLocalPort;
			VideoConfig.dwLocalAddr=dwLocalAddr;
			VideoConfig.dwRemoteUserID=dwRemoteUserID;

			//��������
			IClientKernel * pIClientKernel=pVideoServiceManager->m_pIClientKernel;
			pIClientKernel->SendSocketData(MDM_GF_VIDEO,SUB_GF_C_VIDEO_CONFIG,&VideoConfig,sizeof(VideoConfig));

			return true;
		}

		//�������
		ASSERT(FALSE);

		return false;
	}

	return true;
}

//�û�����
bool CVideoServiceControl::OnEventUserConfig(DWORD dwRemoteUserID, tagVideoNetwordInfo * pVideoNetwordInfo)
{
	//״̬Ч��
	ASSERT(m_bInitVideo==true);
	if (m_bInitVideo==false) return false;

	//��ȡ����
	ASSERT(CVideoServiceManager::GetInstance()!=NULL);
	CVideoServiceManager * pVideoServiceManager=CVideoServiceManager::GetInstance();

	//Զ��ģʽ
	if ((m_bLocalMode==false)&&(m_dwUserID==dwRemoteUserID))
	{
		//����Ч��
		ASSERT(m_VideoRece.m_hWnd!=NULL);
		if (m_VideoRece.IsWindowVisible()) return true;

		//����Ƶ
		m_VideoRece.OpenRece();

		//����ͨ��
		m_VideoRece.CreateP2P(pVideoServiceManager->m_dwLocalUserID,dwRemoteUserID,pVideoServiceManager->m_dwVideoServer,
			pVideoServiceManager->m_wVideoPort,pVideoNetwordInfo->dwLocalAddr,pVideoNetwordInfo->wLocalPort,pVideoNetwordInfo->dwNatAddr,
			pVideoNetwordInfo->wNatPort);

		return true;
	}

	//�������
	ASSERT(FALSE);

	return false;
}

//��������
VOID CVideoServiceControl::RectifyControl()
{
	//�����ж�
	if (m_hWnd==NULL) return;

	//��������
	if (m_bInitVideo==true)
	{
		//������Դ
		CImageHandle HandleFrame;
		if (m_bSmallMode==true) HandleFrame.AttachResource(&m_ImageSmallFrame);
		if (m_bSmallMode==false) HandleFrame.AttachResource(&m_ImageLargeFrame);

		//��������
		INT nFrameWidth=HandleFrame->GetWidth();
		INT nFrameHeight=HandleFrame->GetHeight();
		SetWindowPos(NULL,0,0,nFrameWidth,nFrameHeight,SWP_NOZORDER|SWP_NOMOVE|SWP_NOCOPYBITS);

		//�ƶ��ؼ�
		if (m_bSmallMode==true)
		{
			if (m_VideoSend.m_hWnd!=NULL) m_VideoSend.SetWindowPos(NULL,X_SMALL_POS,Y_SMALL_POS,W_SMALL_POS,H_SMALL_POS,SWP_NOZORDER|SWP_NOACTIVATE);
			if (m_VideoRece.m_hWnd!=NULL) m_VideoRece.SetWindowPos(NULL,X_SMALL_POS,Y_SMALL_POS,W_SMALL_POS,H_SMALL_POS,SWP_NOZORDER|SWP_NOACTIVATE);
		}
		else
		{
			if (m_VideoSend.m_hWnd!=NULL) m_VideoSend.SetWindowPos(NULL,X_LARGE_POS,Y_LARGE_POS,W_LARGE_POS,H_LARGE_POS,SWP_NOZORDER|SWP_NOACTIVATE);
			if (m_VideoRece.m_hWnd!=NULL) m_VideoRece.SetWindowPos(NULL,X_LARGE_POS,Y_LARGE_POS,W_LARGE_POS,H_LARGE_POS,SWP_NOZORDER|SWP_NOACTIVATE);
		}

		//��������
		INT nSpace=m_bSmallMode?3:10;
		INT nXCenterPos=HandleFrame->GetWidth()/2;
		INT nYPos=m_bSmallMode?H_SMALL_POS+8:H_LARGE_POS+11;
		const UINT uFlags=SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOSIZE;

		//��ťλ��
		CRect rcButton;
		m_btFlower.GetWindowRect(&rcButton);

		//�ƶ���ť
		HDWP hDwp=BeginDeferWindowPos(32);
		DeferWindowPos(hDwp,m_btFlower,NULL,nXCenterPos-rcButton.Width()*5/2-nSpace*2,nYPos,0,0,uFlags);
		DeferWindowPos(hDwp,m_btVideo,NULL,nXCenterPos-rcButton.Width()*3/2-nSpace,nYPos,0,0,uFlags);
		DeferWindowPos(hDwp,m_btAudio,NULL,nXCenterPos-rcButton.Width()/2,nYPos,0,0,uFlags);
		DeferWindowPos(hDwp,m_btClone,NULL,nXCenterPos+rcButton.Width()/2+nSpace,nYPos,0,0,uFlags);
		DeferWindowPos(hDwp,m_btMore,NULL,nXCenterPos+rcButton.Width()*3/2+nSpace*2,nYPos,0,0,uFlags);
		EndDeferWindowPos(hDwp);
	}
	else
	{
		//��С����
		SetWindowPos(NULL,0,0,0,0,SWP_NOZORDER|SWP_NOMOVE|SWP_NOCOPYBITS);
	}

	//�ػ�����
	Invalidate(TRUE);

	return;
}

//�ػ�����
VOID CVideoServiceControl::OnPaint()
{
	CPaintDC dc(this);

	//�����ж�
	ASSERT(m_bInitVideo==true);
	if (m_bInitVideo==false) return;

	//�滭����
	if (m_bSmallMode==true)
	{
		CImageHandle HandleFrame(&m_ImageSmallFrame);
		m_ImageSmallFrame.BitBlt(dc,0,0);
	}
	else
	{
		CImageHandle HandleFrame(&m_ImageLargeFrame);
		m_ImageLargeFrame.BitBlt(dc,0,0);
	}

	//��Ƶ��ʶ
	if (m_bVidicon==false)
	{
		if (m_bSmallMode==true)
		{
			CImageHandle HandlePhoto(&m_ImageSmallPhoto);
			m_ImageSmallPhoto.BitBlt(dc,X_SMALL_POS+(W_SMALL_POS-m_ImageSmallPhoto.GetWidth())/2,Y_SMALL_POS-(H_SMALL_POS-m_ImageSmallPhoto.GetHeight())/2);
		}
		else
		{
			CImageHandle HandlePhoto(&m_ImageLargePhoto);
			m_ImageLargePhoto.BitBlt(dc,X_LARGE_POS+(W_LARGE_POS-m_ImageLargePhoto.GetWidth())/2,Y_LARGE_POS+(H_LARGE_POS-m_ImageLargePhoto.GetHeight())/2);
		}
	}

	return;
}

//�滭����
BOOL CVideoServiceControl::OnEraseBkgnd(CDC * pDC)
{
	Invalidate(FALSE);
	UpdateWindow();

	return TRUE;
}

//��������
INT CVideoServiceControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//�޸Ĵ�������
	ModifyStyle(0,WS_CLIPCHILDREN);

	//������ť
	CRect rcCreate(0,0,0,0);
	m_btMore.Create(TEXT(""),WS_CHILD|WS_DISABLED|WS_VISIBLE,rcCreate,this,IDC_MORE);
	m_btVideo.Create(TEXT(""),WS_CHILD|WS_DISABLED|WS_VISIBLE,rcCreate,this,IDC_VIDEO);
	m_btAudio.Create(TEXT(""),WS_CHILD|WS_DISABLED|WS_VISIBLE,rcCreate,this,IDC_AUDIO);
	m_btClone.Create(TEXT(""),WS_CHILD|WS_DISABLED|WS_VISIBLE,rcCreate,this,IDC_CLONE);
	m_btFlower.Create(TEXT(""),WS_CHILD|WS_DISABLED|WS_VISIBLE,rcCreate,this,IDC_FLOWER);

	//������ʾ
	m_ToolTipCtrl.Create(this);
	m_ToolTipCtrl.Activate(TRUE);

	//��������
	RectifyControl();

	return 0;
}

//�ͻ���ť
VOID CVideoServiceControl::OnBnClickedFlower()
{
	return;
}

//��Ƶ��ť
VOID CVideoServiceControl::OnBnClickedVideo()
{
	//���ñ���
	m_bEnableVideo=!m_bEnableVideo;

	//���ð�ť
	HINSTANCE hInstance=GetModuleHandle(VIDEO_SERVICE_DLL_NAME);
	if (m_bSmallMode==false) m_btVideo.SetButtonImage((m_bEnableVideo==true)?IDB_BT_BIG_SEE:IDB_BT_BIG_NOSEE,hInstance,false);
	if (m_bSmallMode==true) m_btVideo.SetButtonImage((m_bEnableVideo==true)?IDB_BT_SMALL_SEE:IDB_BT_SMALL_NOSEE,hInstance,false);

	//�����豸
	if (m_VideoSend.m_hWnd!=NULL)
	{
		m_VideoSend.EnableVideo(m_bEnableVideo);
		m_VideoSend.ShowWindow(m_bEnableVideo?SW_SHOW:SW_HIDE);
	}

	//�����豸
	if (m_VideoRece.m_hWnd!=NULL)
	{
		m_VideoRece.EnableVideo(m_bEnableVideo);
		m_VideoRece.ShowWindow(m_bEnableVideo?SW_SHOW:SW_HIDE);
	}

	//�ػ��ؼ�
	Invalidate(FALSE);

	return;
}

//��Ƶ��ť
VOID CVideoServiceControl::OnBnClickedAudio()
{
	//���ñ���
	m_bEnableAudio=!m_bEnableAudio;

	//���ð�ť
	HINSTANCE hInstance=GetModuleHandle(VIDEO_SERVICE_DLL_NAME);
	if (m_bSmallMode==false) m_btAudio.SetButtonImage((m_bEnableAudio==true)?IDB_BT_BIG_TALK:IDB_BT_BIG_NOTALK,hInstance,false);
	if (m_bSmallMode==true) m_btAudio.SetButtonImage((m_bEnableAudio==true)?IDB_BT_SMALL_TALK:IDB_BT_SMALL_NOTALK,hInstance,false);

	//�����豸
	if (m_VideoSend.m_hWnd!=NULL) m_VideoSend.EnableAudio(m_bEnableAudio);
	if (m_VideoRece.m_hWnd!=NULL) m_VideoRece.EnableAudio(m_bEnableAudio);

	return;
}

//��¡��ť
VOID CVideoServiceControl::OnBnClickedClone()
{
	//����ģʽ
	if (m_bLocalMode==true)
	{
		ASSERT(m_VideoSend.m_hWnd!=NULL);
		if (m_VideoSend.m_hWnd!=NULL) m_VideoSend.ScaleVideo();
	}

	//Զ��ģʽ
	if (m_bLocalMode==false)
	{
		ASSERT(m_VideoRece.m_hWnd!=NULL);
		if (m_VideoRece.m_hWnd!=NULL) m_VideoRece.ScaleVideo();
	}

	return;
}

//���ఴť
VOID CVideoServiceControl::OnBnClickedMore()
{
	return;
}

//ʹ��֪ͨ
VOID CVideoServiceControl::OnEventVideoEnable()
{
	//���ð�ť
	m_btMore.EnableWindow(FALSE);
	m_btVideo.EnableWindow(TRUE);
	m_btAudio.EnableWindow(TRUE);
	m_btClone.EnableWindow(TRUE);
	m_btFlower.EnableWindow(FALSE);

	//����ģʽ
	if (m_VideoSend.m_hWnd!=NULL) m_VideoSend.ShowWindow(SW_SHOW);
	if (m_VideoRece.m_hWnd!=NULL) m_VideoRece.ShowWindow(SW_SHOW);

	return;
}

//////////////////////////////////////////////////////////////////////////

//���캯��
CVideoServiceManager::CVideoServiceManager()
{
	//��Ƶ��Ϣ
	m_wVideoPort=0;
	m_dwVideoServer=0L;
	m_dwLocalUserID=0L;
	ZeroMemory( m_bOffLine, sizeof( m_bOffLine ) );

	//�������
	m_pIClientKernel=NULL;
	ZeroMemory(m_VideoServiceControl,sizeof(m_VideoServiceControl));

	//���ö���
	ASSERT(m_pVideoServiceManager==NULL);
	if (m_pVideoServiceManager==NULL) m_pVideoServiceManager=this;

	return;
}

//��������
CVideoServiceManager::~CVideoServiceManager()
{
}

//���ýӿ�
bool CVideoServiceManager::SetClientKernel(IUnknownEx * pIUnknownEx)
{
	//���ýӿ�
	if (pIUnknownEx!=NULL)
	{
		//��ѯ�ӿ�
		ASSERT(GET_OBJECTPTR_INTERFACE(pIUnknownEx,IClientKernel)!=NULL);
		m_pIClientKernel=GET_OBJECTPTR_INTERFACE(pIUnknownEx,IClientKernel);

		//�ɹ��ж�
		if (m_pIClientKernel==NULL) return false;
	}
	else m_pIClientKernel=NULL;

	return true;
}

//������Ϣ
bool CVideoServiceManager::SetVideoServiceInfo(DWORD dwLoaclUserID, DWORD dwVideoServer, WORD wVideoPort)
{
	//���ñ���
	m_wVideoPort=wVideoPort;
	m_dwVideoServer=dwVideoServer;
	m_dwLocalUserID=dwLoaclUserID;

	return true;
}

//���ö���
bool CVideoServiceManager::SetVideoServiceControl(WORD wVideoIndex, CVideoServiceControl * pVideoServiceControl)
{
	//��ȡ����
	ASSERT(wVideoIndex<MAX_CHAIR);
	if (wVideoIndex>=MAX_CHAIR) return false;

	//���ö���
	m_VideoServiceControl[wVideoIndex]=pVideoServiceControl;

	return true;
}

//��������
bool CVideoServiceManager::OnEventGameReset()
{
	//��������
	for (WORD i=0;i<MAX_CHAIR;i++)
	{
		if (m_VideoServiceControl[i]!=NULL)
		{
			m_VideoServiceControl[i]->OnEventGameReset();
		}
	}

	return true;
}

//�û��뿪
bool CVideoServiceManager::OnEventUserLeave(WORD wVideoIndex, DWORD dwRemoteUserID)
{
	//�¼�֪ͨ
	ASSERT(wVideoIndex<MAX_CHAIR);
	if (wVideoIndex>=MAX_CHAIR) return false;

	//Ч�����
	ASSERT(m_VideoServiceControl[wVideoIndex]!=NULL);
	ASSERT(m_VideoServiceControl[wVideoIndex]->GetVideoUserID()==dwRemoteUserID);

	//�������
	for (WORD i=0;i<MAX_CHAIR;i++)
	{
		if (m_VideoServiceControl[i]!=NULL)
		{
			DWORD dwVideoUserID=m_VideoServiceControl[i]->GetVideoUserID();
			if ((dwVideoUserID==m_dwLocalUserID)||(dwVideoUserID==dwRemoteUserID))
			{
				m_VideoServiceControl[i]->OnEventUserLeave(dwRemoteUserID);
			}
		}
	}

	return true;
}

//�û�����
bool CVideoServiceManager::OnEventUserEnter(WORD wVideoIndex, DWORD dwRemoteUserID)
{
	//�¼�֪ͨ
	ASSERT(wVideoIndex<MAX_CHAIR);
 	if (wVideoIndex>=MAX_CHAIR) return false;

	//Ч�����
	ASSERT(m_VideoServiceControl[wVideoIndex]!=NULL);
	ASSERT(m_VideoServiceControl[wVideoIndex]->GetVideoUserID()==0L);

	//�����û�
	if (m_VideoServiceControl[wVideoIndex]!=NULL)
	{
		m_VideoServiceControl[wVideoIndex]->SetVideoUserInfo(dwRemoteUserID,TEXT("��Ƶ�û�"));
	}

	//�����û�
	if (dwRemoteUserID!=m_dwLocalUserID)
	{
		for (WORD i=0;i<MAX_CHAIR;i++)
		{
			if (m_VideoServiceControl[i]!=NULL)
			{
				DWORD dwVideoUserID=m_VideoServiceControl[i]->GetVideoUserID();
				if (dwVideoUserID==m_dwLocalUserID)
					if ( m_VideoServiceControl[i]->OnEventUserEnter(dwRemoteUserID) )
					{
						//���ñ���
						m_bOffLine[wVideoIndex] = false;
						break;
					}
			}
		}
	}

	return true;
}

//�û�����
bool CVideoServiceManager::OnEventUserConfig(WORD wVideoIndex, DWORD dwRemoteUserID, tagVideoNetwordInfo * pVideoNetwordInfo)
{
	//�¼�֪ͨ
	ASSERT(wVideoIndex<MAX_CHAIR);
	if (wVideoIndex>=MAX_CHAIR) return false;

	//Ч�����
	ASSERT(m_VideoServiceControl[wVideoIndex]!=NULL);
	ASSERT(m_VideoServiceControl[wVideoIndex]->GetVideoUserID()==dwRemoteUserID);

	//�����û�
	if (m_VideoServiceControl[wVideoIndex]!=NULL)
	{
		m_VideoServiceControl[wVideoIndex]->OnEventUserConfig(dwRemoteUserID, pVideoNetwordInfo);
	}

	return true;
}

//��ʾ��Ƶ
bool CVideoServiceManager::OnShowLocalVD(bool bShow)
{
	for (WORD i=0;i<MAX_CHAIR;i++)
	{
		if (m_VideoServiceControl[i]!=NULL)
		{
			m_VideoServiceControl[i]->OnShowLocalVD(bShow);
		}
	}

	return false;
}

//�����û�
bool CVideoServiceManager::OnUpdateUserItem( WORD wVideoIndex, BYTE cbUserStatus, DWORD dwRemoteUserID )
{
	//����Ч��
	ASSERT(wVideoIndex<MAX_CHAIR);
	ASSERT(m_VideoServiceControl[wVideoIndex]!=NULL);

	//����Ч��
	if (wVideoIndex>=MAX_CHAIR) return false;
	if (m_VideoServiceControl[wVideoIndex]==NULL) return false;	

	if (cbUserStatus==US_OFFLINE )
	{
		//���ñ���
		m_bOffLine[wVideoIndex]=true;
		return OnEventUserLeave(wVideoIndex,dwRemoteUserID);
	}
	else if (cbUserStatus==US_PLAY)
	{
		//�����ж�
		if (m_bOffLine[wVideoIndex]) OnEventUserEnter(wVideoIndex,dwRemoteUserID);

	}

	return false;
}
//////////////////////////////////////////////////////////////////////////
