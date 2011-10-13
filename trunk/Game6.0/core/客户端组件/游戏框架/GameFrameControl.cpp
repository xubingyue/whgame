#include "Stdafx.h"
#include "Resource.h"
#include "GlobalOption.h"
#include "GameFrameControl.h"

//////////////////////////////////////////////////////////////////////////

//列表区域
#define	LIST_TOP					127									//列表头高
#define	LIST_LEFT					10									//列表左宽
#define	LIST_RIGHT					7									//列表右宽
#define	LIST_BOTTOM					61									//列表底高

//聊天区域
#define	CHAT_TOP					0									//聊天头高
#define	CHAT_LEFT					10									//聊天左宽
#define	CHAT_RIGHT					7									//聊天右宽
#define	CHAT_BOTTOM					64									//聊天底高

//菜单命令
#define	IDM_UM_COPY_NAME			WM_USER+100							//拷贝名字
#define	IDM_UM_SET_CHAT				WM_USER+101							//设置聊天
#define	IDM_UM_CANECL_CHAT			WM_USER+102							//取消聊天
#define	IDM_UM_ALLOW_LOOKON			WM_USER+103							//旁观控制
#define	IDM_UM_ENJOIN_LOOKON		WM_USER+104							//旁观控制
#define	IDM_UM_KICK_TABLE_USER		WM_USER+105							//踢走用户

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGameFrameControl, CDialog)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_HIT_EXPMESSTION,OnHitExpression)
	ON_BN_CLICKED(IDC_GAME_RULE, OnBnClickedRule)
	ON_BN_CLICKED(IDC_SOUND, OnBnClickedSound)
	ON_BN_CLICKED(IDC_LOOKON, OnBnClickedLookon)
	ON_BN_CLICKED(IDC_GAME_OPTION, OnBnClickedOption)
	ON_BN_CLICKED(IDC_SEND_CHAT, OnBnClickedSendChat)
	ON_BN_CLICKED(IDC_EXPRESSION, OnBnClickedExpression)
	ON_BN_CLICKED(IDC_COLOR_SET, OnBnClickedColorSet)
	ON_BN_CLICKED(IDC_CLEAN_SCREEN, OnBnClickedCleanScreen)
	ON_NOTIFY(NM_RCLICK, IDC_USER_LIST, OnNMRclickUserList)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//构造函数
CGameFrameControl::CGameFrameControl(CGameFrameDlg * pGameFrameDlg) : CDialog(IDD_FRAME_CONTROL), m_pGameFrameDlg(pGameFrameDlg)
{
	//设置变量
	m_bRectify=false;
	m_bInitDialog=false;

	//接口指针
	m_pUserData=NULL;
	m_pIClientKernel=NULL;

	//加载资源
	HINSTANCE hInstance=GetModuleHandle(GAME_FRAME_DLL_NAME);
	m_ImageLeftViewLM.SetLoadInfo(IDB_LEFT_VIEW_LM,hInstance);
	m_ImageLeftViewMM.SetLoadInfo(IDB_LEFT_VIEW_MM,hInstance);
	m_ImageLeftViewRM.SetLoadInfo(IDB_LEFT_VIEW_RM,hInstance);
	m_ImageLeftViewLTM.SetLoadInfo(IDB_LEFT_VIEW_LTM,hInstance);
	m_ImageLeftViewRTM.SetLoadInfo(IDB_LEFT_VIEW_RTM,hInstance);
	m_ImageLeftViewLT.SetLoadInfo(IDB_LEFT_VIEW_LT,hInstance);
	m_ImageLeftViewMT.SetLoadInfo(IDB_LEFT_VIEW_MT,hInstance);
	m_ImageLeftViewRT.SetLoadInfo(IDB_LEFT_VIEW_RT,hInstance);
	m_ImageLeftViewLB.SetLoadInfo(IDB_LEFT_VIEW_LB,hInstance);
	m_ImageLeftViewMB.SetLoadInfo(IDB_LEFT_VIEW_MB,hInstance);
	m_ImageLeftViewRB.SetLoadInfo(IDB_LEFT_VIEW_RB,hInstance);
	m_ImageLeftViewLBM.SetLoadInfo(IDB_LEFT_VIEW_LBM,hInstance);
	m_ImageLeftViewRBM.SetLoadInfo(IDB_LEFT_VIEW_RBM,hInstance);

	return;
}

//析构函数
CGameFrameControl::~CGameFrameControl()
{
}

//控件绑定
void CGameFrameControl::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PHRASE, m_btPhrase);
	DDX_Control(pDX, IDC_COLOR_SET, m_btColorSet);
	DDX_Control(pDX, IDC_SEND_CHAT, m_btSendChat);
	DDX_Control(pDX, IDC_EXPRESSION, m_btExpression);
	DDX_Control(pDX, IDC_CLEAN_SCREEN, m_btCleanScreen);
	DDX_Control(pDX, IDC_CHAT_INPUT, m_ChatInput);
	DDX_Control(pDX, IDC_CHAT_MESSAGE, m_ChatMessage);
	DDX_Control(pDX, IDC_USER_LIST, m_UserListView);
	DDX_Control(pDX, IDC_SOUND, m_btSound);
	DDX_Control(pDX, IDC_LOOKON, m_btLookOn);
	DDX_Control(pDX, IDC_GAME_RULE, m_btGameRule);
	DDX_Control(pDX, IDC_GAME_OPTION, m_btGameOption);
	DDX_Control(pDX, IDC_CHAT_OBJECT, m_ChatObject);
}

//初始化函数
BOOL CGameFrameControl::OnInitDialog()
{
	__super::OnInitDialog();

	//设置控件
	m_UserListView.InitUserListView();
	m_ChatMessage.SetBackgroundColor(FALSE,RGB(230,249,255));

	//广告控件
	m_BrowerAD.Create(NULL,NULL,WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),this,100,NULL);
	m_BrowerAD.Navigate(TEXT("http://www.dreamlib.com/game/gameAd.html"),NULL,NULL,NULL,NULL);

	//设置按钮
	HINSTANCE hInstance=GetModuleHandle(GAME_FRAME_DLL_NAME);
	m_btPhrase.SetButtonImage(IDB_BT_EXPESSION,hInstance,false);
	m_btExpression.SetButtonImage(IDB_BT_EXPESSION,hInstance,false);
	m_btColorSet.SetButtonImage(IDB_BT_COLOR_SET,hInstance,false);
	m_btCleanScreen.SetButtonImage(IDB_BT_CLEAN_SCREEN,hInstance,false);
	m_btSendChat.SetButtonImage(IDB_BT_SEND_CHAT,hInstance,false);

	//游戏规则
	m_btSound.SetButtonImage(IDB_BT_SOUND,hInstance,false);
	m_btLookOn.SetButtonImage(IDB_BT_LOOKON,hInstance,false);
	m_btGameRule.SetButtonImage(IDB_BT_GAME_RULE,hInstance,false);
	m_btGameOption.SetButtonImage(IDB_BT_GAME_OPTION,hInstance,false);

	//聊天短语
	m_ChatInput.AddString(TEXT("快点吧我等的花儿也谢了"));
	m_ChatInput.AddString(TEXT("大家好，很高兴见到各位！"));
	m_ChatInput.AddString(TEXT("怎么又断线了，网络太差了..."));
	m_ChatInput.AddString(TEXT("不要走，决战到天亮。"));
	m_ChatInput.AddString(TEXT("和你合作真是太愉快了..."));
	m_ChatInput.AddString(TEXT("我们交个朋友，能告诉我你的联系方式吗？"));
	m_ChatInput.AddString(TEXT("你是MM,还是GG?"));
	m_ChatInput.AddString(TEXT("快点，花儿都凋谢了！"));
	m_ChatInput.AddString(TEXT("痛快，痛快，来十斤牛肉，八碗好酒！"));
	m_ChatInput.AddString(TEXT("不要吵了，有什么好吵的..."));
	m_ChatInput.AddString(TEXT("再见了，我会想念大家的！BYE"));

	//建立提示控件
	m_ToolTipCtrl.Create(this);
	m_ToolTipCtrl.Activate(TRUE);
	m_ToolTipCtrl.AddTool(GetDlgItem(IDC_EXPRESSION),TEXT("表情"));
	m_ToolTipCtrl.AddTool(GetDlgItem(IDC_COLOR_SET),TEXT("颜色"));
	m_ToolTipCtrl.AddTool(GetDlgItem(IDC_CLEAN_SCREEN),TEXT("清屏"));
	m_ToolTipCtrl.AddTool(GetDlgItem(IDC_SEND_CHAT),TEXT("发送"));

	//聊天对象
	m_ChatObject.AddString(TEXT("所有人"));
	m_ChatObject.SetCurSel(0);

	//设置变量
	m_bInitDialog=true;

	return TRUE;
}

//消息过虑
BOOL CGameFrameControl::PreTranslateMessage(MSG * pMsg)
{
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_RETURN))
	{
		OnBnClickedSendChat();
		return TRUE;
	}
	m_ToolTipCtrl.RelayEvent(pMsg);
	return __super::PreTranslateMessage(pMsg);
}

//菜单命令
BOOL CGameFrameControl::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDM_UM_COPY_NAME:		//拷贝名字
		{
			//寻找玩家
			if ((m_pUserData==NULL)||(m_pUserData->dwUserID==0)) return TRUE;

			//打开剪切板
			if (OpenClipboard()==FALSE) return TRUE;
			if (EmptyClipboard()==FALSE) 
			{
				CloseClipboard();
				return TRUE;
			}

			//复制数据
			HANDLE hData=GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT,NAME_LEN);
			if (hData==NULL) 
			{
				CloseClipboard();
				return TRUE;
			}
			LPTSTR szMemName=(LPTSTR)GlobalLock(hData);
			lstrcpy(szMemName,m_pUserData->szName);
			SetClipboardData(CF_TEXT,hData);
			GlobalUnlock(hData);
			CloseClipboard();

			//显示名字
			m_ChatInput.Paste();
			m_ChatInput.SetFocus();

			return TRUE;
		}
	case IDM_UM_SET_CHAT:		//设置聊天
		{
			//寻找玩家
			if ((m_pUserData==NULL)||(m_pUserData->dwUserID==0)) return TRUE;

			int nCount=m_ChatObject.GetCount();
			for (int i=1;i<nCount;i++)
			{
				if (m_ChatObject.GetItemData(i)==m_pUserData->dwUserID)
				{
					m_ChatObject.SetCurSel(i);
					break;
				}
			}
			m_ChatInput.SetFocus();

			return TRUE;
		}
	case IDM_UM_CANECL_CHAT:		//取消聊天
		{
			//寻找玩家
			if ((m_pUserData==NULL)||(m_pUserData->dwUserID==0)) return TRUE;

			if (m_ChatObject.GetCurSel()!=LB_ERR)
			{
				DWORD dwUserID=(DWORD)m_ChatObject.GetItemData(m_ChatObject.GetCurSel());
				if (dwUserID==m_pUserData->dwUserID)
				{
					m_ChatObject.SetCurSel(0);
					break;
				}
			}
			m_ChatInput.SetFocus();

			return TRUE;
		}
	case IDM_UM_ALLOW_LOOKON:		//允许旁观
	case IDM_UM_ENJOIN_LOOKON:		//禁止旁观
		{
			//寻找玩家
			if ((m_pUserData==NULL)||(m_pUserData->dwUserID==0)) return TRUE;

			//设置控制
			bool bAllowLookon=(LOWORD(wParam)==IDM_UM_ALLOW_LOOKON);
			m_pIClientKernel->AllowUserLookon(m_pUserData->dwUserID,bAllowLookon);

			return TRUE;
		}
	case IDM_UM_KICK_TABLE_USER:	//踢走用户
		{
			//寻找玩家
			if ((m_pUserData==NULL)||(m_pUserData->dwUserID==0)) return TRUE;

			//发送消息
			CMD_GF_KickTableUser KickTableUser;
			KickTableUser.dwUserID=m_pUserData->dwUserID;
			m_pGameFrameDlg->m_ClientKernelHelper->SendSocketData(MDM_GF_FRAME,SUB_GF_KICK_TABLE_USER,&KickTableUser,sizeof(KickTableUser));

			return TRUE;
		}
	}

	return __super::OnCommand(wParam,lParam);
}

//设置内核
void CGameFrameControl::SetClientKernel(IClientKernel * pIClientKernel)
{
	m_pIClientKernel=pIClientKernel;
	return;
}

//重置控制
void CGameFrameControl::ResetGameFrameControl()
{
	//聊天对象
	int nChatCount=m_ChatObject.GetCount();
	for (int i=1;i<nChatCount;i++) m_ChatObject.DeleteString(1);

	//清理列表
	m_UserListView.DeleteAllItems();

	return;
}

//加入用户
bool CGameFrameControl::InsertUserItem(tagUserData * pUserData)
{
	return m_UserListView.InsertUserItem(pUserData);
}

//更新用户
bool CGameFrameControl::UpdateUserItem(tagUserData * pUserData)
{
	return m_UserListView.UpdateUserItem(pUserData);
}

//删除用户
bool CGameFrameControl::DeleteUserItem(tagUserData * pUserData)
{
	return m_UserListView.DeleteUserItem(pUserData);
}

//绘画消息
void CGameFrameControl::OnPaint()
{
	CPaintDC dc(this);

	//绘画背景
	DrawLeftViewFrame(&dc);

	return;
}

//设置按钮
void CGameFrameControl::OnBnClickedOption()
{
	m_pGameFrameDlg->OnGameOptionSet();
	return;
}

//游戏规则
void CGameFrameControl::OnBnClickedRule()
{
	TCHAR szRuleUrl[128];
	_snprintf(szRuleUrl,sizeof(szRuleUrl),TEXT("http://game.dreamlib.com/game/rules/rule%ld.html"),m_UserListView.m_wKindID);
	ShellExecute(NULL,TEXT("open"),szRuleUrl,NULL,NULL,SW_SHOWDEFAULT);

	return;
}

//游戏声音
void CGameFrameControl::OnBnClickedSound()
{
	if (m_pGameFrameDlg->IsEnableSound()==true)
	{
		m_pGameFrameDlg->EnableSound(false);
	}
	else
	{
		m_pGameFrameDlg->EnableSound(true);
	}

	return;
}

//游戏旁观
void CGameFrameControl::OnBnClickedLookon()
{
	if (m_pGameFrameDlg->IsAllowUserLookon()==true)
	{
		m_pGameFrameDlg->AllowUserLookon(0L,false);
	}
	else
	{
		m_pGameFrameDlg->AllowUserLookon(0L,true);
	}

	return;
}

//绘画背景
BOOL CGameFrameControl::OnEraseBkgnd(CDC * pDC)
{
	return TRUE;
}

//位置消息
void CGameFrameControl::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	//调整控件
	RectifyControl(cx,cy);

	return;
}

//表情消息
LRESULT CGameFrameControl::OnHitExpression(WPARAM wParam, LPARAM lParam)
{
	CExpressionItem * pExpressionItem=m_Expression.GetExpressItem((WORD)wParam);
	if (pExpressionItem!=NULL)
	{
		CString strBuffer;
		m_ChatInput.GetWindowText(strBuffer);
		strBuffer+=pExpressionItem->m_szTrancelate;
		m_ChatInput.SetWindowText(strBuffer);
		m_ChatInput.SetFocus();
		m_ChatInput.SetEditSel(strBuffer.GetLength(),strBuffer.GetLength());
	}

	return 0;
}

//发送按钮
void CGameFrameControl::OnBnClickedSendChat()
{
	//聊天信息
	TCHAR szChatMessage[MAX_CHAT_LEN]=TEXT("");
	m_ChatInput.GetWindowText(szChatMessage,CountArray(szChatMessage));
	if (szChatMessage[0]!=0)
	{
		DWORD dwTargetUserID=0L;
		int nItem=m_ChatObject.GetCurSel();
		if ((nItem!=LB_ERR)&&(nItem!=0)) 
		{
			dwTargetUserID=(DWORD)m_ChatObject.GetItemData(nItem);
		}
		m_ChatInput.SetWindowText(TEXT(""));
		m_pIClientKernel->SendChatMessage(dwTargetUserID,szChatMessage,g_GlobalOption.m_crChatTX);
	}

	//设置界面
	m_ChatInput.SetFocus();

	return;
}

//表情按钮
void CGameFrameControl::OnBnClickedExpression()
{
	//建立表情窗口
	if (m_Expression.GetSafeHwnd()==NULL) m_Expression.CreateExpression(this);

	//移动窗口
	CRect rcButton;
	CSize ExpressSize;
	m_Expression.GetFixSize(ExpressSize);
	m_btExpression.GetWindowRect(&rcButton);
	m_Expression.MoveWindow(rcButton.right-ExpressSize.cx,rcButton.top-ExpressSize.cy,ExpressSize.cx,ExpressSize.cy);
	m_Expression.ShowWindow(SW_SHOW);
	m_Expression.SetFocus();

	return;
}

//颜色按钮
void CGameFrameControl::OnBnClickedColorSet()
{
	//设置颜色
	CColorDialog ColorDialog(g_GlobalOption.m_crChatTX,CC_FULLOPEN);
	if (ColorDialog.DoModal()==IDOK) g_GlobalOption.m_crChatTX=ColorDialog.GetColor();

	//设置界面
	m_ChatInput.SetFocus();

	return;
}

//清屏按钮
void CGameFrameControl::OnBnClickedCleanScreen()
{
	m_ChatMessage.CleanScreen();
	return;
}

//左视图区
void CGameFrameControl::DrawLeftViewFrame(CDC * pDC)
{
	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//变量定义
	HDC hDC=pDC->m_hDC;
	int nXPos=0,nYPos=0;
	int nComminutePos=rcClient.Height()*3/7;

	CBrush brClient;
	brClient.CreateSolidBrush(RGB(161,212,226));
	pDC->SelectObject(brClient);
	pDC->Rectangle(&rcClient);

	return;

	//加载资源
	CImageHandle ImageLeftViewLMHandle(&m_ImageLeftViewLM);
	CImageHandle ImageLeftViewMMHandle(&m_ImageLeftViewMM);
	CImageHandle ImageLeftViewRMHandle(&m_ImageLeftViewRM);
	CImageHandle ImageLeftViewLTMHandle(&m_ImageLeftViewLTM);
	CImageHandle ImageLeftViewRTMHandle(&m_ImageLeftViewRTM);
	CImageHandle ImageLeftViewLTHandle(&m_ImageLeftViewLT);
	CImageHandle ImageLeftViewMTHandle(&m_ImageLeftViewMT);
	CImageHandle ImageLeftViewRTHandle(&m_ImageLeftViewRT);
	CImageHandle ImageLeftViewLBHandle(&m_ImageLeftViewLB);
	CImageHandle ImageLeftViewMBHandle(&m_ImageLeftViewMB);
	CImageHandle ImageLeftViewRBHandle(&m_ImageLeftViewRB);
	CImageHandle ImageLeftViewLBMHandle(&m_ImageLeftViewLBM);
	CImageHandle ImageLeftViewRBMHandle(&m_ImageLeftViewRBM);

	//绘画上框
	m_ImageLeftViewLT.BitBlt(hDC,0,0);
	for (nXPos=m_ImageLeftViewLT.GetWidth();nXPos<rcClient.Width();nXPos+=m_ImageLeftViewMT.GetWidth())
	{
		m_ImageLeftViewMT.BitBlt(hDC,nXPos,0);
	}
	m_ImageLeftViewRT.BitBlt(hDC,rcClient.Width()-m_ImageLeftViewRT.GetWidth(),0);

	//绘画左右
	nXPos=rcClient.Width()-m_ImageLeftViewRTM.GetWidth();
	for (nYPos=m_ImageLeftViewLT.GetHeight();nYPos<nComminutePos-m_ImageLeftViewLM.GetHeight();nYPos+=m_ImageLeftViewLTM.GetHeight())
	{
		m_ImageLeftViewLTM.BitBlt(hDC,0,nYPos);
		m_ImageLeftViewRTM.BitBlt(hDC,nXPos,nYPos);
	}

	//绘画中间
	m_ImageLeftViewLM.BitBlt(hDC,0,nComminutePos-m_ImageLeftViewLM.GetHeight());
	for (nXPos=m_ImageLeftViewLM.GetWidth();nXPos<rcClient.Width();nXPos+=m_ImageLeftViewMM.GetWidth())
	{
		m_ImageLeftViewMM.BitBlt(hDC,nXPos,nComminutePos-m_ImageLeftViewMM.GetHeight());
	}
	m_ImageLeftViewRM.BitBlt(hDC,rcClient.Width()-m_ImageLeftViewRM.GetWidth(),nComminutePos-m_ImageLeftViewRM.GetHeight());

	//绘画左右
	nXPos=rcClient.Width()-m_ImageLeftViewRBM.GetWidth();
	for (nYPos=nComminutePos;nYPos<rcClient.Height()-m_ImageLeftViewLB.GetHeight();nYPos+=m_ImageLeftViewLBM.GetHeight())
	{
		m_ImageLeftViewLBM.BitBlt(hDC,0,nYPos);
		m_ImageLeftViewRBM.BitBlt(hDC,nXPos,nYPos);
	}

	//绘画下框
	nYPos=rcClient.Height()-m_ImageLeftViewMB.GetHeight();
	m_ImageLeftViewLB.BitBlt(hDC,0,rcClient.Height()-m_ImageLeftViewLB.GetHeight());
	for (nXPos=m_ImageLeftViewLB.GetWidth();nXPos<rcClient.Width()-m_ImageLeftViewRB.GetWidth();nXPos+=m_ImageLeftViewMB.GetWidth())
	{
		m_ImageLeftViewMB.BitBlt(hDC,nXPos,nYPos);
	}
	m_ImageLeftViewRB.BitBlt(hDC,rcClient.Width()-m_ImageLeftViewRB.GetWidth(),rcClient.Height()-m_ImageLeftViewRB.GetHeight());

	return;
}

//调整控件
void CGameFrameControl::RectifyControl(int nWidth, int nHeight)
{
	//状态判断
	if (m_bInitDialog==false) return;
	if ((nWidth==0)||(nHeight==0)) return;

	//变量定义
	const int nComminutePos=nHeight*3/7;
	const UINT uFlags=SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOCOPYBITS;

	//移动控件
	HDWP hDwp=BeginDeferWindowPos(20);

	//广告区域
	DeferWindowPos(hDwp,m_BrowerAD,NULL,LIST_LEFT,7,nWidth-LIST_LEFT-LIST_RIGHT,115,uFlags);

	//列表区域
	DeferWindowPos(hDwp,m_UserListView,NULL,LIST_LEFT,LIST_TOP,nWidth-LIST_LEFT-LIST_RIGHT,nComminutePos-LIST_TOP-LIST_BOTTOM,uFlags);

	

	//聊天区域
	DeferWindowPos(hDwp,m_ChatMessage,NULL,CHAT_LEFT,nComminutePos+CHAT_TOP,nWidth-CHAT_RIGHT-CHAT_LEFT,
		nHeight-nComminutePos-CHAT_TOP-CHAT_BOTTOM,uFlags);

	//聊天区域
	CRect rcButton;
	m_btPhrase.GetWindowRect(&rcButton);
	CButton * pButtonArray[]={&m_btExpression,&m_btColorSet,&m_btCleanScreen};
	for (int i=0;i<CountArray(pButtonArray);i++)
	{
		DeferWindowPos(hDwp,pButtonArray[i]->m_hWnd,NULL,CHAT_LEFT+(rcButton.Width()+5)*i,nHeight-61,rcButton.Width(),rcButton.Height(),uFlags);
	}
	m_btSendChat.GetWindowRect(&rcButton);
	DeferWindowPos(hDwp,m_btSendChat,NULL,nWidth-rcButton.Width()-8,nHeight-33,rcButton.Width(),rcButton.Height(),uFlags);
	DeferWindowPos(hDwp,m_ChatObject,NULL,8,nHeight-33,70,200,uFlags);
	DeferWindowPos(hDwp,m_ChatInput,NULL,81,nHeight-33,nWidth-rcButton.Width()-93,19,uFlags);

	//功能按钮
	m_btSound.GetWindowRect(&rcButton);
	int nBeginPos=22,nEndPos=nWidth-17;
	int nButtonSpace=(nEndPos-nBeginPos-4*rcButton.Width())/3,nYPosButton=nComminutePos-rcButton.Height()-7;
	DeferWindowPos(hDwp,m_btSound,NULL,nBeginPos,nYPosButton,rcButton.Width(),rcButton.Height(),uFlags);
	DeferWindowPos(hDwp,m_btLookOn,NULL,nBeginPos+nButtonSpace+rcButton.Width(),nYPosButton,rcButton.Width(),rcButton.Height(),uFlags);
	DeferWindowPos(hDwp,m_btGameRule,NULL,nBeginPos+nButtonSpace*2+rcButton.Width()*2,nYPosButton,rcButton.Width(),rcButton.Height(),uFlags);
	DeferWindowPos(hDwp,m_btGameOption,NULL,nBeginPos+nButtonSpace*3+rcButton.Width()*3,nYPosButton,rcButton.Width(),rcButton.Height(),uFlags);

	EndDeferWindowPos(hDwp);

	//重画界面
	Invalidate(FALSE);
	UpdateWindow();

	return;
}

//右键列表
void CGameFrameControl::OnNMRclickUserList(NMHDR * pNMHDR, LRESULT * pResult)
{
	NMITEMACTIVATE * pListNotify=(NMITEMACTIVATE *)pNMHDR;
	if (pListNotify->iItem!=-1)
	{
		//获取位置
		CPoint MousePoint;
		GetCursorPos(&MousePoint);

		//获取用户
		TCHAR szBuffer[512]=TEXT("");
		m_pUserData=(tagUserData *)m_UserListView.GetItemData(pListNotify->iItem);
		if(m_pUserData==NULL) return;

		//预先计算
		double dFleeRate=0.0;
		LONG lPlayCount=m_pUserData->lWinCount+m_pUserData->lLostCount+m_pUserData->lDrawCount+m_pUserData->lFleeCount;
		if (m_pUserData->lFleeCount>0)
		{
			dFleeRate=(double)(m_pUserData->lFleeCount*100)/(double)lPlayCount;
			if (dFleeRate<0.01) dFleeRate=0.0;
		}

		//构造菜单
		CMenu UserInfoMenu;
		UserInfoMenu.CreatePopupMenu();

		//功能菜单
		UserInfoMenu.AppendMenu(0,IDM_UM_COPY_NAME,TEXT("拷贝用户名"));
		UserInfoMenu.AppendMenu(MF_SEPARATOR);
		
		//用户称谓
		LPCTSTR pszMemberOrder[]={TEXT("普通会员"),TEXT("中级会员"),TEXT("高级贵宾")};
		if ((m_pUserData->cbMemberOrder>0)&&(m_pUserData->cbMemberOrder<CountArray(pszMemberOrder)))
		{
			_snprintf(szBuffer,sizeof(szBuffer),TEXT("用户名：%s [ %s ]"),m_pUserData->szName,pszMemberOrder[m_pUserData->cbMemberOrder]);
		}
		else _snprintf(szBuffer,sizeof(szBuffer),TEXT("用户名：%s"),m_pUserData->szName);
		UserInfoMenu.AppendMenu(0,0,szBuffer);

		//用户 ID
		_snprintf(szBuffer,sizeof(szBuffer),TEXT("游戏 ID：%ld"),m_pUserData->dwGameID);
		UserInfoMenu.AppendMenu(0,0,szBuffer);

		//用户经验
		_snprintf(szBuffer,sizeof(szBuffer),TEXT("经验值：%ld"),m_pUserData->lExperience);
		UserInfoMenu.AppendMenu(0,0,szBuffer);

		//用户积分
		_snprintf(szBuffer,sizeof(szBuffer),TEXT("积分：%ld  总局数：%ld  逃跑率：%5.2f%%"),m_pUserData->lScore,lPlayCount,dFleeRate);
		UserInfoMenu.AppendMenu(0,0,szBuffer);

		//获取用户
		DWORD dwCurUserID=0L;
		const tagUserData * pMeUserData=m_pIClientKernel->GetMeUserInfo();
		if (m_ChatObject.GetCurSel()!=LB_ERR)
		{
			dwCurUserID=(DWORD)m_ChatObject.GetItemData(m_ChatObject.GetCurSel());
		}

		//聊天对象
		if (pMeUserData->dwUserID!=m_pUserData->dwUserID) UserInfoMenu.AppendMenu(MF_SEPARATOR);
		if ((dwCurUserID!=m_pUserData->dwUserID)&&(dwCurUserID!=pMeUserData->dwUserID)&&(pMeUserData->dwUserID!=m_pUserData->dwUserID))
		{
			_snprintf(szBuffer,sizeof(szBuffer),TEXT("与 [ %s ] 聊天"),m_pUserData->szName);
			UserInfoMenu.AppendMenu(0,IDM_UM_SET_CHAT,szBuffer);
		}
		if (dwCurUserID==m_pUserData->dwUserID)
		{
			_snprintf(szBuffer,sizeof(szBuffer),TEXT("取消与 [ %s ] 的聊天"),m_pUserData->szName);
			UserInfoMenu.AppendMenu(0,IDM_UM_CANECL_CHAT,szBuffer);
		}

		//旁观控制
		if ((pMeUserData!=m_pUserData)&&(pMeUserData->cbUserStatus!=US_LOOKON)&&(m_pUserData->wChairID==pMeUserData->wChairID))
		{
			//分隔菜单
			UserInfoMenu.AppendMenu(MF_SEPARATOR);

			//允许旁观
			_snprintf(szBuffer,sizeof(szBuffer),TEXT("允许 [ %s ] 观看您游戏"),m_pUserData->szName);
			UserInfoMenu.AppendMenu(0,IDM_UM_ALLOW_LOOKON,szBuffer);

			//禁止旁观
			_snprintf(szBuffer,sizeof(szBuffer),TEXT("禁止 [ %s ] 观看您游戏"),m_pUserData->szName);
			UserInfoMenu.AppendMenu(0,IDM_UM_ENJOIN_LOOKON,szBuffer);
		}

		//踢人菜单
		if (m_pIClientKernel->GetMeUserInfo()->dwUserID!=m_pUserData->dwUserID)
		{
			//控制菜单
			bool bEnable=false;
			if (bEnable==false) bEnable=(pMeUserData->cbMasterOrder>0);
			if (bEnable==false) bEnable=(pMeUserData->cbMemberOrder>m_pUserData->cbMemberOrder);

			//插入菜单
			_snprintf(szBuffer,sizeof(szBuffer),TEXT("把 [ %s ] 踢出游戏房间"),m_pUserData->szName);
			UserInfoMenu.AppendMenu((bEnable==true)?MF_ENABLED:MF_GRAYED,IDM_UM_KICK_TABLE_USER,szBuffer);
		}
	
		//显示菜单
		UserInfoMenu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,MousePoint.x,MousePoint.y,this);
	}

	return;
}

//////////////////////////////////////////////////////////////////////////
