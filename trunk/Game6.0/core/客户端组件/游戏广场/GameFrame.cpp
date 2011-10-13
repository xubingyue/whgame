#include "Stdafx.h"
#include "GameFrame.h"
#include "GlobalUnits.h"

//////////////////////////////////////////////////////////////////////////

//�궨��
#define BORDER_WIDTH				7									//�߿���
#define TITLE_HEIGHT				95									//����߶�

//��Ļλ��
#define LESS_SCREEN_X				1024								//��С���
#define LESS_SCREEN_Y				720									//��С�߶�

//��ť��ʾ
#define IDC_BT_MIN					1000								//��С��ť
#define IDC_BT_MAX					1001								//��С��ť
#define IDC_BT_CLOSE				1002								//�رհ�ť
#define IDC_BT_BUTTON_1				1003								//���ܰ�ť
#define IDC_BT_BUTTON_2				1004								//���ܰ�ť
#define IDC_BT_BUTTON_3				1005								//���ܰ�ť
#define IDC_BT_BUTTON_4				1006								//���ܰ�ť
#define IDC_BT_BUTTON_5				1007								//���ܰ�ť

//��Ϣ����
#define WM_SETUP_FINISH				WM_USER+100							//��װ���

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

//���캯��
CGameFrame::CGameFrame()
{
	//����״̬
	m_bMaxShow=false;
	m_rcNormalSize.SetRect(0,0,0,0);

	//������Դ
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_ImageL.SetLoadInfo(IDB_FRAME_L,hInstance);
	m_ImageR.SetLoadInfo(IDB_FRAME_R,hInstance);
	m_ImageTL.SetLoadInfo(IDB_FRAME_TL,hInstance);
	m_ImageTM.SetLoadInfo(IDB_FRAME_TM,hInstance);
	m_ImageTR.SetLoadInfo(IDB_FRAME_TR,hInstance);

	return;
}

//��������
CGameFrame::~CGameFrame()
{
}

//��Ϣ����
BOOL CGameFrame::PreTranslateMessage(MSG * pMsg)
{
	m_ToolTipCtrl.RelayEvent(pMsg);
	return __super::PreTranslateMessage(pMsg);
}

//��󴰿�
bool CGameFrame::MaxSizeWindow()
{
	//״̬�ж�
	if (m_bMaxShow==false)
	{
		//Ĭ��λ��
		GetWindowRect(&m_rcNormalSize);

		//���ð�ť
		m_btMax.SetButtonImage(IDB_FRAME_RESORE,AfxGetInstanceHandle(),false);

		//��ȡλ��
		CRect rcArce;
		SystemParametersInfo(SPI_GETWORKAREA,0,&rcArce,SPIF_SENDCHANGE);

		//�ƶ�����
		m_bMaxShow=true;
		LockWindowUpdate();
		SetWindowPos(NULL,rcArce.left-2,rcArce.top-2,rcArce.Width()+4,rcArce.Height()+4,SWP_NOZORDER);
		UnlockWindowUpdate();
	}

	return true;
}

//��ԭ����
bool CGameFrame::RestoreWindow()
{
	//״̬�ж�
	if (m_bMaxShow==true)
	{
		//���ð�ť
		m_btMax.SetButtonImage(IDB_FRAME_MAX,AfxGetInstanceHandle(),false);

		//�ƶ�����
		m_bMaxShow=false;
		LockWindowUpdate();
		SetWindowPos(NULL,m_rcNormalSize.left,m_rcNormalSize.top,m_rcNormalSize.Width(),m_rcNormalSize.Height(),SWP_NOZORDER);
		UnlockWindowUpdate();
	}

	return true;
}

//������Ϣ
int CGameFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//��������
	ModifyStyle(WS_CAPTION|WS_BORDER,0,0);

	//����ͼ��
	HICON hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	SetIcon(hIcon,TRUE);
	SetIcon(hIcon,FALSE);

	//���ñ���
	CString strTitle;
	strTitle.LoadString(AfxGetInstanceHandle(),IDS_MAIN_TITLE);
	SetWindowText(strTitle);

	//���ؼ�
	//m_BrowerAD.Create(NULL,NULL,WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),this,100,NULL);
	//m_BrowerAD.Navigate(TEXT("http://127.0.0.1/AD/GamePlazaAD.asp"),NULL,NULL,NULL,NULL);

	//������ť
	m_btMin.Create(NULL,WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDC_BT_MIN);
	m_btMax.Create(NULL,WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDC_BT_MAX);
	m_btClose.Create(NULL,WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDC_BT_CLOSE);
	m_btButton1.Create(TEXT(""),WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDC_BT_BUTTON_1);
	m_btButton2.Create(TEXT(""),WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDC_BT_BUTTON_2);
	m_btButton3.Create(TEXT(""),WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDC_BT_BUTTON_3);
	m_btButton4.Create(TEXT(""),WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDC_BT_BUTTON_4);
	m_btButton5.Create(TEXT(""),WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDC_BT_BUTTON_5);

	//����ͼƬ
	m_btMin.SetButtonImage(IDB_FRAME_MIN,AfxGetInstanceHandle(),false);
	m_btMax.SetButtonImage(IDB_FRAME_RESORE,AfxGetInstanceHandle(),false);
	m_btClose.SetButtonImage(IDB_FRAME_CLOSE,AfxGetInstanceHandle(),false);
	m_btButton1.SetButtonImage(IDB_FRAME_BT_BUTTON_1,AfxGetInstanceHandle(),false);
	m_btButton2.SetButtonImage(IDB_FRAME_BT_BUTTON_2,AfxGetInstanceHandle(),false);
	m_btButton3.SetButtonImage(IDB_FRAME_BT_BUTTON_3,AfxGetInstanceHandle(),false);
	m_btButton4.SetButtonImage(IDB_FRAME_BT_BUTTON_4,AfxGetInstanceHandle(),false);
	m_btButton5.SetButtonImage(IDB_FRAME_BT_BUTTON_5,AfxGetInstanceHandle(),false);

	//������ʾ�ؼ�
	m_ToolTipCtrl.Create(this);
	m_ToolTipCtrl.Activate(TRUE);
	m_ToolTipCtrl.AddTool(GetDlgItem(IDC_BT_MIN),TEXT("��С����Ϸ����"));
	m_ToolTipCtrl.AddTool(GetDlgItem(IDC_BT_CLOSE),TEXT("�˳���Ϸ����"));

	//�����ؼ�
	m_DlgControlBar.Create(IDD_CONTROL_BAR,this);
	m_DlgGamePlaza.Create(IDD_GAME_PLAZA,this);
	m_DlgControlBar.ActivePlazaViewItem();
	m_DlgControlBar.ShowWindow(SW_SHOW);

	//ע���ȼ�
	g_GlobalUnits.RegisterHotKey(m_hWnd,IDI_HOT_KEY_BOSS,g_GlobalOption.m_wBossHotKey);

	//����λ��
	CRect rcArce;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rcArce,SPIF_SENDCHANGE);

	//��ʾ����
	MaxSizeWindow();
	//ShowWindow(SW_SHOW);


	//Ĭ��λ��
	m_rcNormalSize.left=(rcArce.Width()-LESS_SCREEN_X)/2;
	m_rcNormalSize.top=(rcArce.Height()-LESS_SCREEN_Y)/2;
	m_rcNormalSize.right=(rcArce.Width()+LESS_SCREEN_X)/2;
	m_rcNormalSize.bottom=(rcArce.Height()+LESS_SCREEN_Y)/2;

	return 0;
}

//�滭��Ϣ
void CGameFrame::OnPaint()
{
	CPaintDC dc(this);

	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//������Դ
	int nXPos=0,nYPos=0;
	CImageHandle ImageLHandle(&m_ImageL);
	CImageHandle ImageRHandle(&m_ImageR);
	CImageHandle ImageTLHandle(&m_ImageTL);
	CImageHandle ImageTMHandle(&m_ImageTM);
	CImageHandle ImageTRHandle(&m_ImageTR);

	//�滭�ϱ�
	m_ImageTL.BitBlt(dc,0,0);
	for (nXPos=m_ImageTL.GetWidth();nXPos<rcClient.Width()-m_ImageTR.GetWidth();nXPos+=m_ImageTM.GetWidth())
	{
		m_ImageTM.BitBlt(dc,nXPos,0);
	}
	m_ImageTR.BitBlt(dc,rcClient.Width()-m_ImageTR.GetWidth(),0);

	//�滭����
	nXPos=rcClient.Width()-m_ImageR.GetWidth();
	for (int nYPos=m_ImageTL.GetHeight();nYPos<rcClient.Height();nYPos+=m_ImageL.GetHeight()) 
	{
		m_ImageL.BitBlt(dc,0,nYPos);
		m_ImageR.BitBlt(dc,nXPos,nYPos);
	}

	return;
}

//�滭����
BOOL CGameFrame::OnEraseBkgnd(CDC * pDC)
{
	Invalidate(FALSE);
	UpdateWindow();
	return TRUE;
}

//���øı�
void CGameFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	__super::OnSettingChange(uFlags, lpszSection);

	//������ܴ�С
	CRect rcClient;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rcClient,SPIF_SENDCHANGE);
	MoveWindow(&rcClient,TRUE);

	return;
}

//�ر���Ϣ
void CGameFrame::OnClose()
{
	//�ر���ʾ
	if (g_GlobalUnits.GetGolbalUserData().dwUserID!=0L)
	{
		int nCode=AfxMessageBox(TEXT("��ȷʵҪ�ر���Ϸ�㳡��"),MB_YESNO|MB_DEFBUTTON2|MB_ICONQUESTION);
		if (nCode!=IDYES) return;
	}

	//���ؽ���
	ShowWindow(SW_HIDE);

	//�رշ���
	g_pControlBar->CloseAllRoomViewItem();

	//��������
	g_GlobalOption.SaveOptionParameter();
	g_GlobalUnits.m_CompanionManager->SaveCompanion();

	__super::OnClose();
}

//���ܰ�ť
void CGameFrame::OnBnClickedButton1()
{
	m_DlgControlBar.WebBrowse(TEXT("http://www.dreamlib.com/game/"),true);
	return;
}

//���ܰ�ť
void CGameFrame::OnBnClickedButton2()
{
	m_DlgControlBar.WebBrowse(TEXT("http://www.dreamlib.com/home/"),true);
	return;
}

//���ܰ�ť
void CGameFrame::OnBnClickedButton3()
{
	m_DlgControlBar.WebBrowse(TEXT("http://www.dreamlib.com/bank/"),true);
	return;
}

//���ܰ�ť
void CGameFrame::OnBnClickedButton4()
{
	m_DlgControlBar.WebBrowse(TEXT("http://www.dreamlib.com/user/"),true);
	return;
}

//���ܰ�ť
void CGameFrame::OnBnClickedButton5()
{
	m_DlgControlBar.WebBrowse(TEXT("http://www.dreamlib.com/bbs/"),true);
	return;
}

//��ȡ���λ��
void CGameFrame::OnGetMinMaxInfo(MINMAXINFO FAR * lpMMI) 
{
	//���ñ���
	lpMMI->ptMinTrackSize.x=LESS_SCREEN_X;
	lpMMI->ptMinTrackSize.y=LESS_SCREEN_Y;

	__super::OnGetMinMaxInfo(lpMMI);
}

//λ����Ϣ
void CGameFrame::OnSize(UINT nType, int cx, int cy) 
{
	__super::OnSize(nType, cx, cy);

	//���ÿؼ�
	m_DlgControlBar.SetViewItemRect(BORDER_WIDTH,TITLE_HEIGHT,cx-2*BORDER_WIDTH,cy-TITLE_HEIGHT-CONTROL_BAR_HEIGHT);

	//������Ļ
	LockWindowUpdate();

	//�ƶ��ؼ�
	HDWP hDwp=BeginDeferWindowPos(32);
	const UINT uFlags=SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOCOPYBITS;

	//�����ؼ�
	DeferWindowPos(hDwp,m_btMin,NULL,cx-102,3,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btMax,NULL,cx-72,3,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btClose,NULL,cx-42,3,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_DlgControlBar,NULL,0,cy-CONTROL_BAR_HEIGHT,cx,CONTROL_BAR_HEIGHT,uFlags);

	//��ťλ��
	CRect rcButton;
	m_btButton1.GetWindowRect(&rcButton);

	//�������
	int nEndPos=105;
	int nBeginPos=560;
	int nWindth=cx-nBeginPos-rcButton.Width()*5-nEndPos;
	int nButtonSpace=__min((cx-nBeginPos-rcButton.Width()*5-nEndPos)/4,30);

	//���ؼ�
	DeferWindowPos(hDwp,m_BrowerAD,NULL,300,8,250,52,uFlags);

	//������ť
	DeferWindowPos(hDwp,m_btButton1,NULL,cx-rcButton.Width()*5-nButtonSpace*4-nEndPos,6,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btButton2,NULL,cx-rcButton.Width()*4-nButtonSpace*3-nEndPos,6,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btButton3,NULL,cx-rcButton.Width()*3-nButtonSpace*2-nEndPos,6,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btButton4,NULL,cx-rcButton.Width()*2-nButtonSpace*1-nEndPos,6,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btButton5,NULL,cx-rcButton.Width()*1-nButtonSpace*0-nEndPos,6,0,0,uFlags|SWP_NOSIZE);

	//�ƶ��ؼ�
	EndDeferWindowPos(hDwp);

	//�������
	UnlockWindowUpdate();

	return;
}

//��С��ť
void CGameFrame::OnBnClickedMin()
{
	ShowWindow(SW_MINIMIZE);
	return;
}

//��С��ť
void CGameFrame::OnBnClickedMax()
{
	if (m_bMaxShow==true) RestoreWindow();
	else MaxSizeWindow();
	return;
}

//�رհ�ť
void CGameFrame::OnBnClickedClose()
{
	g_pControlBar->CloseCurrentViewItem();
	return;
}

//��������
LRESULT CGameFrame::OnNcHitTest(CPoint Point)
{
	//��ť����
	if (m_bMaxShow==false)
	{
		//��ȡλ��
		CRect rcClient;
		GetClientRect(&rcClient);

		//ת��λ��
		CPoint ClientPoint=Point;
		ScreenToClient(&ClientPoint);

		//����λ��
		if (ClientPoint.x<=BORDER_WIDTH)
		{
			if (ClientPoint.y<=TITLE_HEIGHT) return HTTOPLEFT;
			if (ClientPoint.y>=(rcClient.Height()-BORDER_WIDTH)) return HTBOTTOMLEFT;
			return HTLEFT;
		}

		//����λ��
		if (ClientPoint.x>=(rcClient.Width()-BORDER_WIDTH))
		{
			if (ClientPoint.y<=TITLE_HEIGHT) return HTTOPRIGHT;
			if (ClientPoint.y>=(rcClient.Height()-BORDER_WIDTH)) return HTBOTTOMRIGHT;
			return HTRIGHT;
		}

		//����λ��
		if (ClientPoint.y<=BORDER_WIDTH) return HTTOP;
		if (ClientPoint.y>=(rcClient.Height()-BORDER_WIDTH)) return HTBOTTOM;
	}

	return __super::OnNcHitTest(Point);
}

//�����Ϣ
void CGameFrame::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//ģ�ⰴ����
	if ((m_bMaxShow==false)&&(Point.y<=TITLE_HEIGHT))
	{
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(Point.x,Point.y));
	}

	return;
}

//�����Ϣ
void CGameFrame::OnLButtonDblClk(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDblClk(nFlags,Point);

	//״̬�ж�
	if (Point.y>TITLE_HEIGHT) return;

	//���ƴ���
	if (m_bMaxShow==true) RestoreWindow();
	else MaxSizeWindow();
	
	return;
}

//��װ���
LRESULT CGameFrame::OnMessageSetupFinish(WPARAM wParam, LPARAM lParam)
{
	g_GlobalUnits.m_ServerListManager.UpdateGameKind((WORD)wParam);
	return 0;
}

//�ȼ���Ϣ
LRESULT CGameFrame::OnHotKeyMessage(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case IDI_HOT_KEY_BOSS:		//�ϰ��ȼ�
		{
			//��������
			bool bBossCome=(IsWindowVisible()==FALSE)?false:true;

			//���ش���
			if (bBossCome==false)
			{
				//��ԭ����
				ShowWindow(SW_RESTORE);
				ShowWindow(SW_SHOW);

				//�ö�����
				SetActiveWindow();
				BringWindowToTop();
				SetForegroundWindow();
			}
			else
			{
				//���ش���
				ShowWindow(SW_MINIMIZE);
				ShowWindow(SW_HIDE);
			}

			//������Ϣ
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
