#include "Stdafx.h"
#include "GameFrame.h"
#include "GlobalUnits.h"

//////////////////////////////////////////////////////////////////////////

//宏定义
#define BORDER_WIDTH				7									//边框宽度
#define TITLE_HEIGHT				95									//标题高度

//屏幕位置
#define LESS_SCREEN_X				1024								//最小宽度
#define LESS_SCREEN_Y				720									//最小高度

//按钮标示
#define IDC_BT_MIN					1000								//最小按钮
#define IDC_BT_MAX					1001								//最小按钮
#define IDC_BT_CLOSE				1002								//关闭按钮
#define IDC_BT_BUTTON_1				1003								//功能按钮
#define IDC_BT_BUTTON_2				1004								//功能按钮
#define IDC_BT_BUTTON_3				1005								//功能按钮
#define IDC_BT_BUTTON_4				1006								//功能按钮
#define IDC_BT_BUTTON_5				1007								//功能按钮

//消息定义
#define WM_SETUP_FINISH				WM_USER+100							//安装完成

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGameFrame, CFrameWnd)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_WM_NCHITTEST()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SETTINGCHANGE()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BT_MIN, OnBnClickedMin)
	ON_BN_CLICKED(IDC_BT_MAX, OnBnClickedMax)
	ON_BN_CLICKED(IDC_BT_CLOSE, OnBnClickedClose)
	ON_MESSAGE(WM_HOTKEY,OnHotKeyMessage)
	ON_MESSAGE(WM_SETUP_FINISH,OnMessageSetupFinish)
	ON_BN_CLICKED(IDC_BT_BUTTON_1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BT_BUTTON_2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BT_BUTTON_3, OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BT_BUTTON_4, OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BT_BUTTON_5, OnBnClickedButton5)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//构造函数
CGameFrame::CGameFrame()
{
	//界面状态
	m_bMaxShow=false;
	m_rcNormalSize.SetRect(0,0,0,0);

	//加载资源
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_ImageL.SetLoadInfo(IDB_FRAME_L,hInstance);
	m_ImageR.SetLoadInfo(IDB_FRAME_R,hInstance);
	m_ImageTL.SetLoadInfo(IDB_FRAME_TL,hInstance);
	m_ImageTM.SetLoadInfo(IDB_FRAME_TM,hInstance);
	m_ImageTR.SetLoadInfo(IDB_FRAME_TR,hInstance);

	return;
}

//析构函数
CGameFrame::~CGameFrame()
{
}

//消息解释
BOOL CGameFrame::PreTranslateMessage(MSG * pMsg)
{
	m_ToolTipCtrl.RelayEvent(pMsg);
	return __super::PreTranslateMessage(pMsg);
}

//最大窗口
bool CGameFrame::MaxSizeWindow()
{
	//状态判断
	if (m_bMaxShow==false)
	{
		//默认位置
		GetWindowRect(&m_rcNormalSize);

		//设置按钮
		m_btMax.SetButtonImage(IDB_FRAME_RESORE,AfxGetInstanceHandle(),false);

		//获取位置
		CRect rcArce;
		SystemParametersInfo(SPI_GETWORKAREA,0,&rcArce,SPIF_SENDCHANGE);

		//移动窗口
		m_bMaxShow=true;
		LockWindowUpdate();
		SetWindowPos(NULL,rcArce.left-2,rcArce.top-2,rcArce.Width()+4,rcArce.Height()+4,SWP_NOZORDER);
		UnlockWindowUpdate();
	}

	return true;
}

//还原窗口
bool CGameFrame::RestoreWindow()
{
	//状态判断
	if (m_bMaxShow==true)
	{
		//设置按钮
		m_btMax.SetButtonImage(IDB_FRAME_MAX,AfxGetInstanceHandle(),false);

		//移动窗口
		m_bMaxShow=false;
		LockWindowUpdate();
		SetWindowPos(NULL,m_rcNormalSize.left,m_rcNormalSize.top,m_rcNormalSize.Width(),m_rcNormalSize.Height(),SWP_NOZORDER);
		UnlockWindowUpdate();
	}

	return true;
}

//建立消息
int CGameFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//设置属性
	ModifyStyle(WS_CAPTION|WS_BORDER,0,0);

	//设置图标
	HICON hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	SetIcon(hIcon,TRUE);
	SetIcon(hIcon,FALSE);

	//设置标题
	CString strTitle;
	strTitle.LoadString(AfxGetInstanceHandle(),IDS_MAIN_TITLE);
	SetWindowText(strTitle);

	//广告控件
	//m_BrowerAD.Create(NULL,NULL,WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),this,100,NULL);
	//m_BrowerAD.Navigate(TEXT("http://127.0.0.1/AD/GamePlazaAD.asp"),NULL,NULL,NULL,NULL);

	//创建按钮
	m_btMin.Create(NULL,WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDC_BT_MIN);
	m_btMax.Create(NULL,WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDC_BT_MAX);
	m_btClose.Create(NULL,WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDC_BT_CLOSE);
	m_btButton1.Create(TEXT(""),WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDC_BT_BUTTON_1);
	m_btButton2.Create(TEXT(""),WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDC_BT_BUTTON_2);
	m_btButton3.Create(TEXT(""),WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDC_BT_BUTTON_3);
	m_btButton4.Create(TEXT(""),WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDC_BT_BUTTON_4);
	m_btButton5.Create(TEXT(""),WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDC_BT_BUTTON_5);

	//设置图片
	m_btMin.SetButtonImage(IDB_FRAME_MIN,AfxGetInstanceHandle(),false);
	m_btMax.SetButtonImage(IDB_FRAME_RESORE,AfxGetInstanceHandle(),false);
	m_btClose.SetButtonImage(IDB_FRAME_CLOSE,AfxGetInstanceHandle(),false);
	m_btButton1.SetButtonImage(IDB_FRAME_BT_BUTTON_1,AfxGetInstanceHandle(),false);
	m_btButton2.SetButtonImage(IDB_FRAME_BT_BUTTON_2,AfxGetInstanceHandle(),false);
	m_btButton3.SetButtonImage(IDB_FRAME_BT_BUTTON_3,AfxGetInstanceHandle(),false);
	m_btButton4.SetButtonImage(IDB_FRAME_BT_BUTTON_4,AfxGetInstanceHandle(),false);
	m_btButton5.SetButtonImage(IDB_FRAME_BT_BUTTON_5,AfxGetInstanceHandle(),false);

	//建立提示控件
	m_ToolTipCtrl.Create(this);
	m_ToolTipCtrl.Activate(TRUE);
	m_ToolTipCtrl.AddTool(GetDlgItem(IDC_BT_MIN),TEXT("最小化游戏大厅"));
	m_ToolTipCtrl.AddTool(GetDlgItem(IDC_BT_CLOSE),TEXT("退出游戏大厅"));

	//创建控件
	m_DlgControlBar.Create(IDD_CONTROL_BAR,this);
	m_DlgGamePlaza.Create(IDD_GAME_PLAZA,this);
	m_DlgControlBar.ActivePlazaViewItem();
	m_DlgControlBar.ShowWindow(SW_SHOW);

	//注册热键
	g_GlobalUnits.RegisterHotKey(m_hWnd,IDI_HOT_KEY_BOSS,g_GlobalOption.m_wBossHotKey);

	//窗口位置
	CRect rcArce;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rcArce,SPIF_SENDCHANGE);

	//显示窗口
	MaxSizeWindow();
	//ShowWindow(SW_SHOW);


	//默认位置
	m_rcNormalSize.left=(rcArce.Width()-LESS_SCREEN_X)/2;
	m_rcNormalSize.top=(rcArce.Height()-LESS_SCREEN_Y)/2;
	m_rcNormalSize.right=(rcArce.Width()+LESS_SCREEN_X)/2;
	m_rcNormalSize.bottom=(rcArce.Height()+LESS_SCREEN_Y)/2;

	return 0;
}

//绘画消息
void CGameFrame::OnPaint()
{
	CPaintDC dc(this);

	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//加载资源
	int nXPos=0,nYPos=0;
	CImageHandle ImageLHandle(&m_ImageL);
	CImageHandle ImageRHandle(&m_ImageR);
	CImageHandle ImageTLHandle(&m_ImageTL);
	CImageHandle ImageTMHandle(&m_ImageTM);
	CImageHandle ImageTRHandle(&m_ImageTR);

	//绘画上边
	m_ImageTL.BitBlt(dc,0,0);
	for (nXPos=m_ImageTL.GetWidth();nXPos<rcClient.Width()-m_ImageTR.GetWidth();nXPos+=m_ImageTM.GetWidth())
	{
		m_ImageTM.BitBlt(dc,nXPos,0);
	}
	m_ImageTR.BitBlt(dc,rcClient.Width()-m_ImageTR.GetWidth(),0);

	//绘画左右
	nXPos=rcClient.Width()-m_ImageR.GetWidth();
	for (int nYPos=m_ImageTL.GetHeight();nYPos<rcClient.Height();nYPos+=m_ImageL.GetHeight()) 
	{
		m_ImageL.BitBlt(dc,0,nYPos);
		m_ImageR.BitBlt(dc,nXPos,nYPos);
	}

	return;
}

//绘画背景
BOOL CGameFrame::OnEraseBkgnd(CDC * pDC)
{
	Invalidate(FALSE);
	UpdateWindow();
	return TRUE;
}

//设置改变
void CGameFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	__super::OnSettingChange(uFlags, lpszSection);

	//调整框架大小
	CRect rcClient;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rcClient,SPIF_SENDCHANGE);
	MoveWindow(&rcClient,TRUE);

	return;
}

//关闭消息
void CGameFrame::OnClose()
{
	//关闭提示
	if (g_GlobalUnits.GetGolbalUserData().dwUserID!=0L)
	{
		int nCode=AfxMessageBox(TEXT("您确实要关闭游戏广场吗？"),MB_YESNO|MB_DEFBUTTON2|MB_ICONQUESTION);
		if (nCode!=IDYES) return;
	}

	//隐藏界面
	ShowWindow(SW_HIDE);

	//关闭房间
	g_pControlBar->CloseAllRoomViewItem();

	//保存配置
	g_GlobalOption.SaveOptionParameter();
	g_GlobalUnits.m_CompanionManager->SaveCompanion();

	__super::OnClose();
}

//功能按钮
void CGameFrame::OnBnClickedButton1()
{
	m_DlgControlBar.WebBrowse(TEXT("http://www.dreamlib.com/game/"),true);
	return;
}

//功能按钮
void CGameFrame::OnBnClickedButton2()
{
	m_DlgControlBar.WebBrowse(TEXT("http://www.dreamlib.com/home/"),true);
	return;
}

//功能按钮
void CGameFrame::OnBnClickedButton3()
{
	m_DlgControlBar.WebBrowse(TEXT("http://www.dreamlib.com/bank/"),true);
	return;
}

//功能按钮
void CGameFrame::OnBnClickedButton4()
{
	m_DlgControlBar.WebBrowse(TEXT("http://www.dreamlib.com/user/"),true);
	return;
}

//功能按钮
void CGameFrame::OnBnClickedButton5()
{
	m_DlgControlBar.WebBrowse(TEXT("http://www.dreamlib.com/bbs/"),true);
	return;
}

//获取最大位置
void CGameFrame::OnGetMinMaxInfo(MINMAXINFO FAR * lpMMI) 
{
	//设置变量
	lpMMI->ptMinTrackSize.x=LESS_SCREEN_X;
	lpMMI->ptMinTrackSize.y=LESS_SCREEN_Y;

	__super::OnGetMinMaxInfo(lpMMI);
}

//位置消息
void CGameFrame::OnSize(UINT nType, int cx, int cy) 
{
	__super::OnSize(nType, cx, cy);

	//设置控件
	m_DlgControlBar.SetViewItemRect(BORDER_WIDTH,TITLE_HEIGHT,cx-2*BORDER_WIDTH,cy-TITLE_HEIGHT-CONTROL_BAR_HEIGHT);

	//锁定屏幕
	LockWindowUpdate();

	//移动控件
	HDWP hDwp=BeginDeferWindowPos(32);
	const UINT uFlags=SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOCOPYBITS;

	//其他控件
	DeferWindowPos(hDwp,m_btMin,NULL,cx-102,3,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btMax,NULL,cx-72,3,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btClose,NULL,cx-42,3,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_DlgControlBar,NULL,0,cy-CONTROL_BAR_HEIGHT,cx,CONTROL_BAR_HEIGHT,uFlags);

	//按钮位置
	CRect rcButton;
	m_btButton1.GetWindowRect(&rcButton);

	//间隔计算
	int nEndPos=105;
	int nBeginPos=560;
	int nWindth=cx-nBeginPos-rcButton.Width()*5-nEndPos;
	int nButtonSpace=__min((cx-nBeginPos-rcButton.Width()*5-nEndPos)/4,30);

	//广告控件
	DeferWindowPos(hDwp,m_BrowerAD,NULL,300,8,250,52,uFlags);

	//导航按钮
	DeferWindowPos(hDwp,m_btButton1,NULL,cx-rcButton.Width()*5-nButtonSpace*4-nEndPos,6,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btButton2,NULL,cx-rcButton.Width()*4-nButtonSpace*3-nEndPos,6,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btButton3,NULL,cx-rcButton.Width()*3-nButtonSpace*2-nEndPos,6,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btButton4,NULL,cx-rcButton.Width()*2-nButtonSpace*1-nEndPos,6,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btButton5,NULL,cx-rcButton.Width()*1-nButtonSpace*0-nEndPos,6,0,0,uFlags|SWP_NOSIZE);

	//移动控件
	EndDeferWindowPos(hDwp);

	//解除锁定
	UnlockWindowUpdate();

	return;
}

//最小按钮
void CGameFrame::OnBnClickedMin()
{
	ShowWindow(SW_MINIMIZE);
	return;
}

//最小按钮
void CGameFrame::OnBnClickedMax()
{
	if (m_bMaxShow==true) RestoreWindow();
	else MaxSizeWindow();
	return;
}

//关闭按钮
void CGameFrame::OnBnClickedClose()
{
	g_pControlBar->CloseCurrentViewItem();
	return;
}

//按键测试
LRESULT CGameFrame::OnNcHitTest(CPoint Point)
{
	//按钮测试
	if (m_bMaxShow==false)
	{
		//获取位置
		CRect rcClient;
		GetClientRect(&rcClient);

		//转换位置
		CPoint ClientPoint=Point;
		ScreenToClient(&ClientPoint);

		//左面位置
		if (ClientPoint.x<=BORDER_WIDTH)
		{
			if (ClientPoint.y<=TITLE_HEIGHT) return HTTOPLEFT;
			if (ClientPoint.y>=(rcClient.Height()-BORDER_WIDTH)) return HTBOTTOMLEFT;
			return HTLEFT;
		}

		//右面位置
		if (ClientPoint.x>=(rcClient.Width()-BORDER_WIDTH))
		{
			if (ClientPoint.y<=TITLE_HEIGHT) return HTTOPRIGHT;
			if (ClientPoint.y>=(rcClient.Height()-BORDER_WIDTH)) return HTBOTTOMRIGHT;
			return HTRIGHT;
		}

		//上下位置
		if (ClientPoint.y<=BORDER_WIDTH) return HTTOP;
		if (ClientPoint.y>=(rcClient.Height()-BORDER_WIDTH)) return HTBOTTOM;
	}

	return __super::OnNcHitTest(Point);
}

//鼠标消息
void CGameFrame::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//模拟按标题
	if ((m_bMaxShow==false)&&(Point.y<=TITLE_HEIGHT))
	{
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(Point.x,Point.y));
	}

	return;
}

//鼠标消息
void CGameFrame::OnLButtonDblClk(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDblClk(nFlags,Point);

	//状态判断
	if (Point.y>TITLE_HEIGHT) return;

	//控制窗口
	if (m_bMaxShow==true) RestoreWindow();
	else MaxSizeWindow();
	
	return;
}

//安装完成
LRESULT CGameFrame::OnMessageSetupFinish(WPARAM wParam, LPARAM lParam)
{
	g_GlobalUnits.m_ServerListManager.UpdateGameKind((WORD)wParam);
	return 0;
}

//热键消息
LRESULT CGameFrame::OnHotKeyMessage(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case IDI_HOT_KEY_BOSS:		//老板热键
		{
			//变量定义
			bool bBossCome=(IsWindowVisible()==FALSE)?false:true;

			//隐藏窗口
			if (bBossCome==false)
			{
				//还原窗口
				ShowWindow(SW_RESTORE);
				ShowWindow(SW_SHOW);

				//置顶窗口
				SetActiveWindow();
				BringWindowToTop();
				SetForegroundWindow();
			}
			else
			{
				//隐藏窗口
				ShowWindow(SW_MINIMIZE);
				ShowWindow(SW_HIDE);
			}

			//发送消息
			for (INT_PTR i=0;i<MAX_SERVER;i++)
			{
				if (m_DlgControlBar.m_pRoomViewItem[i]!=NULL)
				{
					m_DlgControlBar.m_pRoomViewItem[i]->NotifyBossCome(bBossCome);
				}
			}

			return 0;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
