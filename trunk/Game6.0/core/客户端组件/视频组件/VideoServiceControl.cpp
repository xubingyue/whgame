#include "Stdafx.h"
#include "Resource.h"
#include "VideoServiceControl.h"

//////////////////////////////////////////////////////////////////////////

//窗口标识
#define IDC_VIDEO_SNED				100									//发送窗口
#define IDC_VIDEO_RCEC				100									//接收窗口
#define IDC_VIDEO_SR				100									//视频窗口

//按钮标识
#define IDC_FLOWER					103									//送花按钮
#define IDC_VIDEO					104									//视频按钮
#define IDC_AUDIO					105									//音频按钮
#define IDC_CLONE					106									//克隆按钮
#define IDC_MORE					107									//更多按钮


//位置标识
#define X_SMALL_POS					4									//起始坐标
#define Y_SMALL_POS					4									//起始坐标
#define X_LARGE_POS					5									//起始坐标
#define Y_LARGE_POS					5									//起始坐标

//宽度标识
#define W_SMALL_POS					80									//宽度坐标
#define H_SMALL_POS					60									//高度坐标
#define W_LARGE_POS					160									//宽度坐标
#define H_LARGE_POS					120									//高度坐标

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

//静态变量
CVideoServiceManager * CVideoServiceManager::m_pVideoServiceManager=NULL;//管理对象

//////////////////////////////////////////////////////////////////////////

//构造函数
CVideoServiceControl::CVideoServiceControl()
{
	//内核变量
	m_bInitVideo=false;

	//控制变量
	m_bSmallMode=false;
	m_bLocalMode=false;
	m_bEnableVideo=true;
	m_bEnableAudio=true;

	//设备标志
	m_bVidicon=false;
	m_bMicrophone=false;

	//用户信息
	m_dwUserID=0L;
	ZeroMemory(m_szAccounts,sizeof(m_szAccounts));

	//加载资源
	HINSTANCE hResInstance=GetModuleHandle(VIDEO_SERVICE_DLL_NAME);
	m_ImageSmallPhoto.SetLoadInfo(IDB_SMALL_PHOTO,hResInstance,false);
	m_ImageLargePhoto.SetLoadInfo(IDB_LARGE_PHOTO,hResInstance,false);
	m_ImageSmallFrame.SetLoadInfo(IDB_SMALL_FRAME,hResInstance,false);
	m_ImageLargeFrame.SetLoadInfo(IDB_LARGE_FRAME,hResInstance,false);

	return;
}

//析构函数
CVideoServiceControl::~CVideoServiceControl()
{
}

//消息解释
BOOL CVideoServiceControl::PreTranslateMessage(MSG * pMsg)
{
	//提示消息
	if (m_ToolTipCtrl.m_hWnd!=NULL)
	{
		m_ToolTipCtrl.RelayEvent(pMsg);
	}

	return __super::PreTranslateMessage(pMsg);
}

//大小模式
bool CVideoServiceControl::SetSmallMode(bool bSmallMode)
{
	//设置变量
	if (m_bSmallMode!=bSmallMode)
	{
		//设置变量
		m_bSmallMode=bSmallMode;

		//调整窗口
		RectifyControl();
	}

	return true;
}

//音频控制
bool CVideoServiceControl::EnableAudio(bool bEnable)
{
	return true;
}

//视频控制
bool CVideoServiceControl::EnableVideo(bool bEnable)
{
	return true;
}

//设置用户
bool CVideoServiceControl::SetVideoUserInfo(DWORD dwUserID, LPCTSTR pszAccounts)
{
	//设置变量
	m_dwUserID=dwUserID;
	lstrcpyn(m_szAccounts,pszAccounts,CountArray(m_szAccounts));

	//刷新窗口
	if (m_hWnd!=NULL) Invalidate(FALSE);

	return true;
}

//配置视频
bool CVideoServiceControl::InitVideoService(bool bLocalMode, bool bSmallMode)
{
	//效验状态
	ASSERT((m_hWnd!=NULL)&&(m_bInitVideo==false));
	if ((m_hWnd==NULL)||(m_bInitVideo==true)) return false;

	//获取对象
	ASSERT(CVideoServiceManager::GetInstance()!=NULL);
	CVideoServiceManager * pVideoServiceManager=CVideoServiceManager::GetInstance();

	//旁观判断
	if ( pVideoServiceManager != NULL && pVideoServiceManager->m_pIClientKernel != NULL && pVideoServiceManager->m_pIClientKernel->IsLookonMode() ) return false;

	//设置变量
	m_bInitVideo=true;
	m_bSmallMode=bSmallMode;
	m_bLocalMode=bLocalMode;

	//设置按钮
	HINSTANCE hResInstance=GetModuleHandle(VIDEO_SERVICE_DLL_NAME);
	m_btMore.SetButtonImage(m_bSmallMode?IDB_BT_SMALL_MORE:IDB_BT_BIG_MORE,hResInstance,false);
	m_btVideo.SetButtonImage(m_bSmallMode?IDB_BT_SMALL_SEE:IDB_BT_BIG_SEE,hResInstance,false);
	m_btAudio.SetButtonImage(m_bSmallMode?IDB_BT_SMALL_TALK:IDB_BT_BIG_TALK,hResInstance,false);
	m_btClone.SetButtonImage(m_bSmallMode?IDB_BT_SMALL_RESORE:IDB_BT_BIG_RESORE,hResInstance,false);
	m_btFlower.SetButtonImage(m_bSmallMode?IDB_BT_SMALL_FLOWER:IDB_BT_BIG_FLOWER,hResInstance,false);

	//创建窗口
	if (m_bLocalMode==true)
	{
		//创建视频
		CRect rcCreate(0,0,0,0);
		m_VideoSend.Create(NULL,NULL,WS_CHILD,rcCreate,this,IDC_VIDEO_SNED);

		//设置设备
		if ((m_VideoSend.m_hWnd!=NULL)&&(m_VideoSend.HasVideoDrv()!=FALSE))
		{
			//设置变量
			m_bVidicon=true;
			m_bMicrophone=true;

			//设置设备
			m_VideoSend.SetVideoMode(2);
			m_VideoSend.SetVideoRate(3);
		}
	}
	else
	{
		//创建视频
		CRect rcCreate(0,0,0,0);
		m_VideoRece.Create(NULL,NULL,WS_CHILD,rcCreate,this,IDC_VIDEO_RCEC);
	}

	//调整窗口
	RectifyControl();

	return true;
}

//显示视频
bool CVideoServiceControl::OnShowLocalVD(bool bShow)
{
	//显示界面
	if ( bShow )
	{
		if ( m_bLocalMode )
		{
			//显示视频
			m_VideoSend.OpenSend();

			return true;
		}
	}
	else
	{
		if ( m_bLocalMode )
		{
			//关闭视频
			m_VideoSend.CloseSend();
			m_VideoSend.ShowWindow(SW_HIDE);
			
			//禁止按钮
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

//界面重置
bool CVideoServiceControl::OnEventGameReset()
{
	//设置变量
	m_dwUserID=0L;
	ZeroMemory(m_szAccounts,sizeof(m_szAccounts));

	//设置控件
	if (m_VideoRece.m_hWnd!=NULL)
	{
		m_VideoRece.CloseRece();
		m_VideoRece.ShowWindow(SW_HIDE);

		//禁止按钮
		m_btMore.EnableWindow(FALSE);
		m_btVideo.EnableWindow(FALSE);
		m_btAudio.EnableWindow(FALSE);
		m_btClone.EnableWindow(FALSE);
		m_btFlower.EnableWindow(FALSE);
	}

	//关闭通道
	if (m_VideoSend.m_hWnd!=NULL)
	{
	}

	return true;
}

//用户离开
bool CVideoServiceControl::OnEventUserLeave(DWORD dwRemoteUserID)
{
	//状态效验
	ASSERT(m_bInitVideo==true);
	if (m_bInitVideo==false) return false;

	//本地模式
	if ((m_bLocalMode==true)&&(m_bVidicon==true))
	{
		//状态效验
		if (m_VideoSend.m_hWnd==NULL) return false;

		//删除通道
		m_VideoSend.DeleteP2PSocket(dwRemoteUserID);

		return true;
	}

	//远程模式
	if ((m_bLocalMode==false)&&(m_dwUserID==dwRemoteUserID))
	{
		//状态效验
		if (m_VideoRece.m_hWnd==NULL) return false;

		//关闭视频
		m_VideoRece.CloseRece();

		//隐藏窗口
		if (m_VideoRece.m_hWnd!=NULL) m_VideoRece.ShowWindow(SW_HIDE);

		//设置用户
		SetVideoUserInfo(0L,TEXT(""));

		//使能按钮
		m_btMore.EnableWindow(FALSE);
		m_btVideo.EnableWindow(FALSE);
		m_btAudio.EnableWindow(FALSE);
		m_btClone.EnableWindow(FALSE);
		m_btFlower.EnableWindow(FALSE);

		return true;
	}

	return false;
}

//用户进入
bool CVideoServiceControl::OnEventUserEnter(DWORD dwRemoteUserID)
{
	//状态效验
	ASSERT(m_bInitVideo==true);
	if (m_bInitVideo==false) return false;

	//本地模式
	if ((m_bLocalMode==true)&&(m_bVidicon==true))
	{
		//获取对象
		ASSERT(CVideoServiceManager::GetInstance()!=NULL);
		CVideoServiceManager * pVideoServiceManager=CVideoServiceManager::GetInstance();

		//创建通道
		m_VideoSend.InsertP2PSocket(pVideoServiceManager->m_dwLocalUserID,dwRemoteUserID,pVideoServiceManager->m_dwVideoServer,
			pVideoServiceManager->m_wVideoPort);

		//网络信息
		WORD wNatPort=0,wLocalPort=0;
		DWORD dwNatAddr=0L,dwLocalAddr=0L;
		if (m_VideoSend.m_hWnd!=NULL) m_VideoSend.GetP2PInfo(dwRemoteUserID,&dwLocalAddr,&wLocalPort,&dwNatAddr,&wNatPort);

		//效验数据
 		if ((wNatPort==0L)||(dwNatAddr==0L)) return false;
		if ((wLocalPort==0L)||(dwLocalAddr==0L)) return false;

		//发送请求
		if ((pVideoServiceManager!=NULL)&&(pVideoServiceManager->m_pIClientKernel!=NULL))
		{
			//变量定义
			CMD_C_VideoConfig VideoConfig;
			ZeroMemory(&VideoConfig,sizeof(VideoConfig));

			//设置变量
			VideoConfig.wNatPort=wNatPort;
			VideoConfig.dwNatAddr=dwNatAddr;
			VideoConfig.wLocalPort=wLocalPort;
			VideoConfig.dwLocalAddr=dwLocalAddr;
			VideoConfig.dwRemoteUserID=dwRemoteUserID;

			//发送数据
			IClientKernel * pIClientKernel=pVideoServiceManager->m_pIClientKernel;
			pIClientKernel->SendSocketData(MDM_GF_VIDEO,SUB_GF_C_VIDEO_CONFIG,&VideoConfig,sizeof(VideoConfig));

			return true;
		}

		//错误断言
		ASSERT(FALSE);

		return false;
	}

	return true;
}

//用户配置
bool CVideoServiceControl::OnEventUserConfig(DWORD dwRemoteUserID, tagVideoNetwordInfo * pVideoNetwordInfo)
{
	//状态效验
	ASSERT(m_bInitVideo==true);
	if (m_bInitVideo==false) return false;

	//获取对象
	ASSERT(CVideoServiceManager::GetInstance()!=NULL);
	CVideoServiceManager * pVideoServiceManager=CVideoServiceManager::GetInstance();

	//远程模式
	if ((m_bLocalMode==false)&&(m_dwUserID==dwRemoteUserID))
	{
		//窗口效验
		ASSERT(m_VideoRece.m_hWnd!=NULL);
		if (m_VideoRece.IsWindowVisible()) return true;

		//打开视频
		m_VideoRece.OpenRece();

		//创建通道
		m_VideoRece.CreateP2P(pVideoServiceManager->m_dwLocalUserID,dwRemoteUserID,pVideoServiceManager->m_dwVideoServer,
			pVideoServiceManager->m_wVideoPort,pVideoNetwordInfo->dwLocalAddr,pVideoNetwordInfo->wLocalPort,pVideoNetwordInfo->dwNatAddr,
			pVideoNetwordInfo->wNatPort);

		return true;
	}

	//错误断言
	ASSERT(FALSE);

	return false;
}

//调整窗口
VOID CVideoServiceControl::RectifyControl()
{
	//窗口判断
	if (m_hWnd==NULL) return;

	//调整窗口
	if (m_bInitVideo==true)
	{
		//加载资源
		CImageHandle HandleFrame;
		if (m_bSmallMode==true) HandleFrame.AttachResource(&m_ImageSmallFrame);
		if (m_bSmallMode==false) HandleFrame.AttachResource(&m_ImageLargeFrame);

		//调整窗口
		INT nFrameWidth=HandleFrame->GetWidth();
		INT nFrameHeight=HandleFrame->GetHeight();
		SetWindowPos(NULL,0,0,nFrameWidth,nFrameHeight,SWP_NOZORDER|SWP_NOMOVE|SWP_NOCOPYBITS);

		//移动控件
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

		//变量定义
		INT nSpace=m_bSmallMode?3:10;
		INT nXCenterPos=HandleFrame->GetWidth()/2;
		INT nYPos=m_bSmallMode?H_SMALL_POS+8:H_LARGE_POS+11;
		const UINT uFlags=SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOSIZE;

		//按钮位置
		CRect rcButton;
		m_btFlower.GetWindowRect(&rcButton);

		//移动按钮
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
		//缩小窗口
		SetWindowPos(NULL,0,0,0,0,SWP_NOZORDER|SWP_NOMOVE|SWP_NOCOPYBITS);
	}

	//重画窗口
	Invalidate(TRUE);

	return;
}

//重画函数
VOID CVideoServiceControl::OnPaint()
{
	CPaintDC dc(this);

	//配置判断
	ASSERT(m_bInitVideo==true);
	if (m_bInitVideo==false) return;

	//绘画背景
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

	//视频标识
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

//绘画背景
BOOL CVideoServiceControl::OnEraseBkgnd(CDC * pDC)
{
	Invalidate(FALSE);
	UpdateWindow();

	return TRUE;
}

//创建函数
INT CVideoServiceControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//修改窗口属性
	ModifyStyle(0,WS_CLIPCHILDREN);

	//创建按钮
	CRect rcCreate(0,0,0,0);
	m_btMore.Create(TEXT(""),WS_CHILD|WS_DISABLED|WS_VISIBLE,rcCreate,this,IDC_MORE);
	m_btVideo.Create(TEXT(""),WS_CHILD|WS_DISABLED|WS_VISIBLE,rcCreate,this,IDC_VIDEO);
	m_btAudio.Create(TEXT(""),WS_CHILD|WS_DISABLED|WS_VISIBLE,rcCreate,this,IDC_AUDIO);
	m_btClone.Create(TEXT(""),WS_CHILD|WS_DISABLED|WS_VISIBLE,rcCreate,this,IDC_CLONE);
	m_btFlower.Create(TEXT(""),WS_CHILD|WS_DISABLED|WS_VISIBLE,rcCreate,this,IDC_FLOWER);

	//建立提示
	m_ToolTipCtrl.Create(this);
	m_ToolTipCtrl.Activate(TRUE);

	//调整窗口
	RectifyControl();

	return 0;
}

//送花按钮
VOID CVideoServiceControl::OnBnClickedFlower()
{
	return;
}

//视频按钮
VOID CVideoServiceControl::OnBnClickedVideo()
{
	//设置变量
	m_bEnableVideo=!m_bEnableVideo;

	//设置按钮
	HINSTANCE hInstance=GetModuleHandle(VIDEO_SERVICE_DLL_NAME);
	if (m_bSmallMode==false) m_btVideo.SetButtonImage((m_bEnableVideo==true)?IDB_BT_BIG_SEE:IDB_BT_BIG_NOSEE,hInstance,false);
	if (m_bSmallMode==true) m_btVideo.SetButtonImage((m_bEnableVideo==true)?IDB_BT_SMALL_SEE:IDB_BT_SMALL_NOSEE,hInstance,false);

	//控制设备
	if (m_VideoSend.m_hWnd!=NULL)
	{
		m_VideoSend.EnableVideo(m_bEnableVideo);
		m_VideoSend.ShowWindow(m_bEnableVideo?SW_SHOW:SW_HIDE);
	}

	//控制设备
	if (m_VideoRece.m_hWnd!=NULL)
	{
		m_VideoRece.EnableVideo(m_bEnableVideo);
		m_VideoRece.ShowWindow(m_bEnableVideo?SW_SHOW:SW_HIDE);
	}

	//重画控件
	Invalidate(FALSE);

	return;
}

//音频按钮
VOID CVideoServiceControl::OnBnClickedAudio()
{
	//设置变量
	m_bEnableAudio=!m_bEnableAudio;

	//设置按钮
	HINSTANCE hInstance=GetModuleHandle(VIDEO_SERVICE_DLL_NAME);
	if (m_bSmallMode==false) m_btAudio.SetButtonImage((m_bEnableAudio==true)?IDB_BT_BIG_TALK:IDB_BT_BIG_NOTALK,hInstance,false);
	if (m_bSmallMode==true) m_btAudio.SetButtonImage((m_bEnableAudio==true)?IDB_BT_SMALL_TALK:IDB_BT_SMALL_NOTALK,hInstance,false);

	//控制设备
	if (m_VideoSend.m_hWnd!=NULL) m_VideoSend.EnableAudio(m_bEnableAudio);
	if (m_VideoRece.m_hWnd!=NULL) m_VideoRece.EnableAudio(m_bEnableAudio);

	return;
}

//克隆按钮
VOID CVideoServiceControl::OnBnClickedClone()
{
	//本地模式
	if (m_bLocalMode==true)
	{
		ASSERT(m_VideoSend.m_hWnd!=NULL);
		if (m_VideoSend.m_hWnd!=NULL) m_VideoSend.ScaleVideo();
	}

	//远程模式
	if (m_bLocalMode==false)
	{
		ASSERT(m_VideoRece.m_hWnd!=NULL);
		if (m_VideoRece.m_hWnd!=NULL) m_VideoRece.ScaleVideo();
	}

	return;
}

//更多按钮
VOID CVideoServiceControl::OnBnClickedMore()
{
	return;
}

//使能通知
VOID CVideoServiceControl::OnEventVideoEnable()
{
	//设置按钮
	m_btMore.EnableWindow(FALSE);
	m_btVideo.EnableWindow(TRUE);
	m_btAudio.EnableWindow(TRUE);
	m_btClone.EnableWindow(TRUE);
	m_btFlower.EnableWindow(FALSE);

	//本地模式
	if (m_VideoSend.m_hWnd!=NULL) m_VideoSend.ShowWindow(SW_SHOW);
	if (m_VideoRece.m_hWnd!=NULL) m_VideoRece.ShowWindow(SW_SHOW);

	return;
}

//////////////////////////////////////////////////////////////////////////

//构造函数
CVideoServiceManager::CVideoServiceManager()
{
	//视频信息
	m_wVideoPort=0;
	m_dwVideoServer=0L;
	m_dwLocalUserID=0L;
	ZeroMemory( m_bOffLine, sizeof( m_bOffLine ) );

	//组件变量
	m_pIClientKernel=NULL;
	ZeroMemory(m_VideoServiceControl,sizeof(m_VideoServiceControl));

	//设置对象
	ASSERT(m_pVideoServiceManager==NULL);
	if (m_pVideoServiceManager==NULL) m_pVideoServiceManager=this;

	return;
}

//析构函数
CVideoServiceManager::~CVideoServiceManager()
{
}

//设置接口
bool CVideoServiceManager::SetClientKernel(IUnknownEx * pIUnknownEx)
{
	//设置接口
	if (pIUnknownEx!=NULL)
	{
		//查询接口
		ASSERT(GET_OBJECTPTR_INTERFACE(pIUnknownEx,IClientKernel)!=NULL);
		m_pIClientKernel=GET_OBJECTPTR_INTERFACE(pIUnknownEx,IClientKernel);

		//成功判断
		if (m_pIClientKernel==NULL) return false;
	}
	else m_pIClientKernel=NULL;

	return true;
}

//服务信息
bool CVideoServiceManager::SetVideoServiceInfo(DWORD dwLoaclUserID, DWORD dwVideoServer, WORD wVideoPort)
{
	//设置变量
	m_wVideoPort=wVideoPort;
	m_dwVideoServer=dwVideoServer;
	m_dwLocalUserID=dwLoaclUserID;

	return true;
}

//设置对象
bool CVideoServiceManager::SetVideoServiceControl(WORD wVideoIndex, CVideoServiceControl * pVideoServiceControl)
{
	//获取对象
	ASSERT(wVideoIndex<MAX_CHAIR);
	if (wVideoIndex>=MAX_CHAIR) return false;

	//设置对象
	m_VideoServiceControl[wVideoIndex]=pVideoServiceControl;

	return true;
}

//界面重置
bool CVideoServiceManager::OnEventGameReset()
{
	//界面重置
	for (WORD i=0;i<MAX_CHAIR;i++)
	{
		if (m_VideoServiceControl[i]!=NULL)
		{
			m_VideoServiceControl[i]->OnEventGameReset();
		}
	}

	return true;
}

//用户离开
bool CVideoServiceManager::OnEventUserLeave(WORD wVideoIndex, DWORD dwRemoteUserID)
{
	//事件通知
	ASSERT(wVideoIndex<MAX_CHAIR);
	if (wVideoIndex>=MAX_CHAIR) return false;

	//效验参数
	ASSERT(m_VideoServiceControl[wVideoIndex]!=NULL);
	ASSERT(m_VideoServiceControl[wVideoIndex]->GetVideoUserID()==dwRemoteUserID);

	//发送组件
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

//用户进入
bool CVideoServiceManager::OnEventUserEnter(WORD wVideoIndex, DWORD dwRemoteUserID)
{
	//事件通知
	ASSERT(wVideoIndex<MAX_CHAIR);
 	if (wVideoIndex>=MAX_CHAIR) return false;

	//效验参数
	ASSERT(m_VideoServiceControl[wVideoIndex]!=NULL);
	ASSERT(m_VideoServiceControl[wVideoIndex]->GetVideoUserID()==0L);

	//设置用户
	if (m_VideoServiceControl[wVideoIndex]!=NULL)
	{
		m_VideoServiceControl[wVideoIndex]->SetVideoUserInfo(dwRemoteUserID,TEXT("视频用户"));
	}

	//增加用户
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
						//设置变量
						m_bOffLine[wVideoIndex] = false;
						break;
					}
			}
		}
	}

	return true;
}

//用户配置
bool CVideoServiceManager::OnEventUserConfig(WORD wVideoIndex, DWORD dwRemoteUserID, tagVideoNetwordInfo * pVideoNetwordInfo)
{
	//事件通知
	ASSERT(wVideoIndex<MAX_CHAIR);
	if (wVideoIndex>=MAX_CHAIR) return false;

	//效验参数
	ASSERT(m_VideoServiceControl[wVideoIndex]!=NULL);
	ASSERT(m_VideoServiceControl[wVideoIndex]->GetVideoUserID()==dwRemoteUserID);

	//设置用户
	if (m_VideoServiceControl[wVideoIndex]!=NULL)
	{
		m_VideoServiceControl[wVideoIndex]->OnEventUserConfig(dwRemoteUserID, pVideoNetwordInfo);
	}

	return true;
}

//显示视频
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

//更新用户
bool CVideoServiceManager::OnUpdateUserItem( WORD wVideoIndex, BYTE cbUserStatus, DWORD dwRemoteUserID )
{
	//参数效验
	ASSERT(wVideoIndex<MAX_CHAIR);
	ASSERT(m_VideoServiceControl[wVideoIndex]!=NULL);

	//参数效验
	if (wVideoIndex>=MAX_CHAIR) return false;
	if (m_VideoServiceControl[wVideoIndex]==NULL) return false;	

	if (cbUserStatus==US_OFFLINE )
	{
		//设置变量
		m_bOffLine[wVideoIndex]=true;
		return OnEventUserLeave(wVideoIndex,dwRemoteUserID);
	}
	else if (cbUserStatus==US_PLAY)
	{
		//断线判断
		if (m_bOffLine[wVideoIndex]) OnEventUserEnter(wVideoIndex,dwRemoteUserID);

	}

	return false;
}
//////////////////////////////////////////////////////////////////////////
