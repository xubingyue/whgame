#include "StdAfx.h"
#include "TableFrame.h"

//////////////////////////////////////////////////////////////////////////

//定时器 ID
#define IDI_OFFLINE					(IDI_MAX_TIME_ID+1)					//断线定时器

//////////////////////////////////////////////////////////////////////////

//构造函数
CTableFrame::CTableFrame()
{
	//属性变量
	m_wChairCount=0;
	m_wTableID=INVALID_TABLE;

	//状态变量
	m_bLocked=false;
	m_bGameStarted=false;

	//状态变量
	m_dwTimeStart=0L;
	m_dwTableOwnerID=0L;
	m_bGameStatus=GS_FREE;
	m_szPassword[0]=0;

	//分数信息
	m_lGameTaxScore=0L;
	memset(m_ScoreInfo,0,sizeof(m_ScoreInfo));
	memset(m_dwPlayerID,0,sizeof(m_dwPlayerID));

	//用户信息
	memset(m_pIUserItem,0,sizeof(m_pIUserItem));
	memset(m_bAllowLookon,0,sizeof(m_bAllowLookon));
	memset(m_wOffLineCount,0,sizeof(m_wOffLineCount));

	//配置变量
	m_pGameServiceAttrib=NULL;
	m_pGameServiceOption=NULL;

	//接口变量
	m_pITableFrameSink=NULL;
	m_pITableUserAction=NULL;
	m_pIGameServiceFrame=NULL;

	return;
}

//析构函数
CTableFrame::~CTableFrame()
{
	//释放对象
	if (m_pITableFrameSink!=NULL)
	{
		m_pITableFrameSink->Release();
		m_pITableFrameSink=NULL;
	}
	return;
}

//接口查询
void * __cdecl CTableFrame::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITableFrame,Guid,dwQueryVer);
	QUERYINTERFACE(ITableFrameManager,Guid,dwQueryVer);
	QUERYINTERFACE(ITableFrameControl,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITableFrameManager,Guid,dwQueryVer);
	return NULL;
}

//初始化
bool __cdecl CTableFrame::InitTableFrame(WORD wTableID, tagTableFrameParameter * pTableFrameParameter)
{
	//效验参数
	ASSERT(pTableFrameParameter!=NULL);

	//设置变量
	m_wTableID=wTableID;
	m_pGameServiceAttrib=pTableFrameParameter->pGameServiceAttrib;
	m_pGameServiceOption=pTableFrameParameter->pGameServiceOption;
	m_wChairCount=pTableFrameParameter->pGameServiceAttrib->wChairCount;

	//查询接口
	m_pIGameServiceFrame=GET_OBJECTPTR_INTERFACE(pTableFrameParameter->pIGameServiceFrame,IGameServiceFrame);
	ASSERT(m_pIGameServiceFrame!=NULL);
	if (m_pIGameServiceFrame==NULL) return false;

	//创建桌子
	IGameServiceManager * pIGameServiceManager=GET_OBJECTPTR_INTERFACE(pTableFrameParameter->pIGameServiceManager,IGameServiceManager);
	m_pITableFrameSink=(ITableFrameSink *)pIGameServiceManager->CreateTableFrameSink(IID_ITableFrameSink,VER_ITableFrameSink);
	ASSERT(m_pITableFrameSink!=NULL);
	if (m_pITableFrameSink==NULL) return false;

	//设置接口
	IUnknownEx * pIUnknownEx=GET_MYSELF_INTERFACE(IUnknownEx);
	if (m_pITableFrameSink->InitTableFrameSink(pIUnknownEx)==false) return false;

	//扩展接口
	m_pITableUserAction=GET_OBJECTPTR_INTERFACE(m_pITableFrameSink,ITableUserAction);

	return true;
}

//游戏状态
bool __cdecl CTableFrame::IsUserPlaying(IServerUserItem * pIServerUserItem)
{
	//游戏状态
	if (m_bGameStarted==false) return false;

	//用户状态
	BYTE cbUserStatus=pIServerUserItem->GetUserStatus();
	if ((cbUserStatus!=US_PLAY)&&(cbUserStatus!=US_OFFLINE)) return false;

	//逻辑判断
	WORD wChairID=pIServerUserItem->GetChairID();
	return m_pITableFrameSink->IsUserPlaying(wChairID);
}

//离开动作
bool __cdecl CTableFrame::PerformStandUpAction(IServerUserItem * pIServerUserItem)
{
	//效验参数
	ASSERT(pIServerUserItem!=NULL);
	ASSERT(pIServerUserItem->GetTableID()==m_wTableID);
	ASSERT(pIServerUserItem->GetChairID()<m_wChairCount);

	//变量定义
	tagServerUserData * pUserData=pIServerUserItem->GetUserData();
	WORD wChairID=pUserData->wChairID;
	bool bLookonUser=(pIServerUserItem->GetUserStatus()==US_LOOKON);

	//用户处理
	if (bLookonUser==true)
	{
		IServerUserItem * pILookonUserItem=NULL;
		for (INT_PTR i=0;i<m_LookonUserItemPtr.GetCount();i++)
		{
			pILookonUserItem=m_LookonUserItemPtr[i];
			ASSERT(pILookonUserItem!=NULL);
			if (pILookonUserItem==pIServerUserItem)
			{
				//设置用户
				m_LookonUserItemPtr.RemoveAt(i);
				pIServerUserItem->SetUserStatus(US_FREE,INVALID_TABLE,INVALID_CHAIR);
				m_pIGameServiceFrame->SendUserStatus(pIServerUserItem);

				//起立处理
				if (m_pITableUserAction!=NULL) m_pITableUserAction->OnActionUserStandUp(wChairID,pIServerUserItem,true);

				return true;
			}
		}
	}
	else
	{
		//变量定义
		bool bTableLocked=IsTableLocked();
		bool bGameStarted=IsGameStarted();

		//结束游戏
		if (IsUserPlaying(pIServerUserItem)==true)
		{
			m_pITableFrameSink->OnEventGameEnd(pUserData->wChairID,pIServerUserItem,GER_USER_LEFT);
			if ((pUserData->wTableID==INVALID_TABLE)||(pUserData->wChairID==INVALID_CHAIR)) return true;
		}

		//旁观设置
		m_bAllowLookon[pUserData->wChairID]=false;

		//变量定义
		CMD_GF_LookonControl LookonControl;
		ZeroMemory(&LookonControl,sizeof(LookonControl));

		//设置变量
		LookonControl.dwUserID=0L;
		LookonControl.bAllowLookon=FALSE;

		//发送消息
		for (INT_PTR i=0;i<m_LookonUserItemPtr.GetCount();i++)
		{
			//获取用户
			IServerUserItem * pILookonUserItem=m_LookonUserItemPtr[i];
			if (pILookonUserItem->GetChairID()!=pIServerUserItem->GetChairID()) continue;

			//发送消息
			m_pIGameServiceFrame->SendData(pILookonUserItem,MDM_GF_FRAME,SUB_GF_LOOKON_CONTROL,&LookonControl,sizeof(LookonControl));
		}

		//设置用户
		m_pIUserItem[pUserData->wChairID]=NULL;
		pIServerUserItem->SetUserStatus(US_FREE,INVALID_TABLE,INVALID_CHAIR);
		m_pIGameServiceFrame->SendUserStatus(pIServerUserItem);

		//设置桌主
		if (m_dwTableOwnerID==pUserData->dwUserID) m_dwTableOwnerID=0L;

		//更新密码
		WORD wUserCount=0;
		for (WORD i=0;i<m_wChairCount;i++)
		{
			if (m_pIUserItem[i]!=NULL) wUserCount++;
		}
		if (wUserCount==0)
		{
			m_bLocked=false;
			m_szPassword[0]=0;
			m_pIGameServiceFrame->SendTableStatus(m_wTableID);
		}

		//踢走旁观
		if (wUserCount==0)
		{
			for (INT_PTR i=0;i<m_LookonUserItemPtr.GetCount();i++)
			{
				SendGameMessage(m_LookonUserItemPtr[i],TEXT("此游戏桌的所有玩家已经离开了！"),SMT_CLOSE_GAME|SMT_EJECT|SMT_INFO);
			}
		}

		//设置变量
		m_bGameStarted=false;

		//发送状态
		if ((bTableLocked!=IsTableLocked())||(bGameStarted!=IsGameStarted()))
		{
			m_pIGameServiceFrame->SendTableStatus(m_wTableID);
		}

		//起立处理
		if (m_pITableUserAction!=NULL) m_pITableUserAction->OnActionUserStandUp(wChairID,pIServerUserItem,false);

		//变量定义
		bool bMatchServer=((m_pGameServiceOption->wServerType&GAME_GENRE_MATCH)!=0);
		bool bControlStart=((bMatchServer==true)&&m_pGameServiceOption->cbControlStart==TRUE);

		//开始判断
		if ((bControlStart==false)&&(StartVerdict()==true))
		{
			StartGame();
			return true;
		}

		return true;
	}

	return true;
}

//旁观动作
bool __cdecl CTableFrame::PerformLookonAction(WORD wChairID, IServerUserItem * pIServerUserItem)
{
	//变量定义
	DWORD dwUserRight=pIServerUserItem->GetUserData()->dwUserRight;
	BYTE cbMasterOrder=pIServerUserItem->GetUserData()->cbMasterOrder;

	//权限判断
	if (CUserRight::CanLookon(dwUserRight)==false)
	{
		//发送消息
		LPCTSTR pszMessage=TEXT("抱歉，你没有进行旁观游戏的权限，若需要帮助，请联系游戏客服咨询！");
		SendSitFailedPacket(pIServerUserItem,pszMessage);

		return false;
	}

	//关闭查询
	if ((cbMasterOrder==0L)&&(m_pIGameServiceFrame->IsShallClose()==true))
	{
		LPCTSTR pszDescribe=TEXT("由于此游戏房间即将暂停服务，玩家不允许再进入游戏桌！");
		SendSitFailedPacket(pIServerUserItem,pszDescribe);
		return false;
	}

	//禁止查询
	if ((cbMasterOrder==0L)&&(m_pIGameServiceFrame->IsAllowEnterGame()==false))
	{
		LPCTSTR pszDescribe=TEXT("抱歉，此游戏桌现在不允许玩家进入！");
		SendSitFailedPacket(pIServerUserItem,pszDescribe);
		return false;
	}

	//位置判断
	if (m_pIUserItem[wChairID]==NULL)
	{
		LPCTSTR pszDescribe=TEXT("所请求旁观的位置已经没有玩家了，不能旁观！");
		SendSitFailedPacket(pIServerUserItem,pszDescribe);
		return false;
	}

	//密码效验
	if (m_bLocked==true)
	{
		const tagUserRule * pUserRule=pIServerUserItem->GetUserRule();
		if ((pUserRule->bPassword==false)||(lstrcmp(m_szPassword,pUserRule->szPassword)!=0))
		{
			LPCTSTR pszDescribe=TEXT("游戏桌携带密码错误，不能旁观游戏！");
			SendSitFailedPacket(pIServerUserItem,pszDescribe);
			return false;
		}
	}

	//状态判断
	if ((m_bGameStarted==false)&&(cbMasterOrder==0L))
	{
		LPCTSTR pszDescribe=TEXT("游戏还没有开始，暂时不能旁观！");
		SendSitFailedPacket(pIServerUserItem,pszDescribe);
		return false;
	}

	//设置玩家
	m_LookonUserItemPtr.Add(pIServerUserItem);
	pIServerUserItem->SetUserStatus(US_LOOKON,m_wTableID,wChairID);
	m_pIGameServiceFrame->SendUserStatus(pIServerUserItem);

	//旁观处理
	if (m_pITableUserAction!=NULL) m_pITableUserAction->OnActionUserSitDown(wChairID,pIServerUserItem,true);

	return true;
}

//坐下动作
bool __cdecl CTableFrame::PerformSitDownAction(WORD wChairID, IServerUserItem * pIServerUserItem)
{
	//变量定义
	const tagUserScore * pUserScore=pIServerUserItem->GetUserScore();;
	const tagUserRule * pUserRule=pIServerUserItem->GetUserRule(),* pTableUserRule=NULL;
	tagServerUserData * pUserData=pIServerUserItem->GetUserData(),* pTableUserData=NULL;

	//关闭查询
	if ((pUserData->dwMasterRight==0L)&&(m_pIGameServiceFrame->IsShallClose()==true))
	{
		LPCTSTR pszDescribe=TEXT("由于此游戏房间即将暂停服务，玩家不允许再进入游戏桌！");
		SendSitFailedPacket(pIServerUserItem,pszDescribe);
		return false;
	}

	//禁止查询
	if ((pUserData->dwMasterRight==0L)&&(m_pIGameServiceFrame->IsAllowEnterGame()==false))
	{
		LPCTSTR pszDescribe=TEXT("抱歉，此游戏桌现在不允许玩家进入！");
		SendSitFailedPacket(pIServerUserItem,pszDescribe);
		return false;
	}

	//位置判断
	if (m_pIUserItem[wChairID]!=NULL)
	{
		TCHAR szDescribe[128]=TEXT("");
		pTableUserData=m_pIUserItem[wChairID]->GetUserData();
		_snprintf(szDescribe,sizeof(szDescribe),TEXT("椅子已经被 [ %s ] 捷足先登了，下次动作要快点了！"),pTableUserData->szAccounts);
		SendSitFailedPacket(pIServerUserItem,szDescribe);
		return false;
	}

	//游戏状态
	if ((m_bGameStarted==true)&&(m_pGameServiceAttrib->cbJoinInGame==FALSE))
	{
		LPCTSTR pszDescribe=TEXT("游戏已经开始了，暂时不能进入游戏桌！");
		SendSitFailedPacket(pIServerUserItem,pszDescribe);
		return false;
	}

	//比赛判断
	if (m_pGameServiceOption->wServerType&GAME_GENRE_MATCH)
	{
		//比赛权限
		if (CUserRight::IsMatchUser(pUserData->dwUserRight)==false)
		{
			TCHAR szDescribe[128]=TEXT("");
			lstrcpyn(szDescribe,TEXT("这是游戏比赛房间，你不是比赛选手，不能坐到此位置上！ "),CountArray(szDescribe));
			SendSitFailedPacket(pIServerUserItem,szDescribe);
			return false;
		}

		//地址效验
		DWORD dwUserIP=pIServerUserItem->GetClientIP();
		for (WORD i=0;i<m_wChairCount;i++)
		{
			if ((m_pIUserItem[i]!=NULL)&&(m_pIUserItem[i]->GetClientIP()==dwUserIP))
			{
				if (pUserRule->bCheckSameIP)
				{
					LPCTSTR pszDescribe=TEXT("你设置了不跟相同 IP 地址的玩家游戏，此游戏桌存在与你 IP 地址相同的玩家，不能加入游戏！");
					SendSitFailedPacket(pIServerUserItem,pszDescribe);
					return false;
				}
				else
				{
					LPCTSTR pszDescribe=TEXT("此桌设置了不跟相同 IP 地址的玩家游戏，此游戏桌存在与你 IP 地址相同的玩家，不能加入游戏！");
					SendSitFailedPacket(pIServerUserItem,pszDescribe);
					return false;
				}
			}
		}
		for (WORD i=0;i<m_wChairCount-1;i++)
		{
			if (m_pIUserItem[i]!=NULL)
			{
				for (WORD j=i+1;j<m_wChairCount;j++)
				{
					if ((m_pIUserItem[j]!=NULL)&&(m_pIUserItem[i]->GetClientIP()==m_pIUserItem[j]->GetClientIP()))
					{
						LPCTSTR pszDescribe=TEXT("你设置了不跟相同 IP 地址的玩家游戏，此游戏桌存在 IP 地址相同的玩家，不能加入游戏！");
						SendSitFailedPacket(pIServerUserItem,pszDescribe);
						return false;
					}
				}
			}
		}

		//对局局数
		if (m_pGameServiceOption->lMatchDraw>0)
		{
			LONG lPlayCount=pUserData->UserScoreInfo.lWinCount+pUserData->UserScoreInfo.lLostCount+pUserData->UserScoreInfo.lDrawCount;
			if (lPlayCount>=m_pGameServiceOption->lMatchDraw)
			{
				TCHAR szDescribe[128]=TEXT("");
				lstrcpyn(szDescribe,TEXT("恭喜您，您的比赛局数已经完成了，不需要再继续比赛，请耐心等待赛果公布！ "),CountArray(szDescribe));
				SendSitFailedPacket(pIServerUserItem,szDescribe);
				return false;
			}
		}
	}
	else
	{
		//权限判断
		if (CUserRight::CanPlay(pUserData->dwUserRight)==false)
		{
			//发送消息
			LPCTSTR pszMessage=TEXT("抱歉，你没有进行游戏的权限，若需要帮助，请联系游戏客服咨询！");
			SendSitFailedPacket(pIServerUserItem,pszMessage);

			return true;
		}

		//积分限制
		if (m_pGameServiceOption->lLessScore!=0L)
		{
			if (pUserData->UserScoreInfo.lScore<m_pGameServiceOption->lLessScore)
			{
				TCHAR szDescribe[128]=TEXT("");
				_snprintf(szDescribe,sizeof(szDescribe),TEXT("加入游戏至少需要 %ld 的游戏积分，你的积分不够，不能加入！"),m_pGameServiceOption->lLessScore);
				SendSitFailedPacket(pIServerUserItem,szDescribe);
				return false;
			}
		}

		//密码效验
		if ((m_bLocked==true)&&(pUserData->dwMasterRight==0L))
		{
			if ((pUserRule->bPassword==false)||(lstrcmp(m_szPassword,pUserRule->szPassword)!=0))
			{
				LPCTSTR pszDescribe=TEXT("携带密码错误，不能加入游戏！");
				SendSitFailedPacket(pIServerUserItem,pszDescribe);
				return false;
			}
		}

		//积分范围
		WORD wWinRate=pIServerUserItem->GetUserWinRate();
		WORD wFleeRate=pIServerUserItem->GetUserFleeRate();
		for (WORD i=0;i<m_wChairCount;i++)
		{
			if (m_pIUserItem[i]!=NULL)
			{
				//获取规则
				pTableUserRule=m_pIUserItem[i]->GetUserRule();

				//逃率效验
				if ((pTableUserRule->bLimitFlee)&&(wFleeRate>pTableUserRule->wFleeRate))
				{
					TCHAR szDescribe[128]=TEXT("");
					_snprintf(szDescribe,sizeof(szDescribe),TEXT("你的逃跑率太高，与 %s 设置的设置不符，不能加入游戏！"),m_pIUserItem[i]->GetAccounts());
					SendSitFailedPacket(pIServerUserItem,szDescribe);
					return false;
				}

				//胜率效验
				if ((pTableUserRule->bLimitWin)&&(wWinRate<pTableUserRule->wWinRate))
				{
					TCHAR szDescribe[128]=TEXT("");
					_snprintf(szDescribe,sizeof(szDescribe),TEXT("你的胜率太低，与 %s 设置的设置不符，不能加入游戏！"),m_pIUserItem[i]->GetAccounts());
					SendSitFailedPacket(pIServerUserItem,szDescribe);
					return false;
				}

				//积分效验
				if (pTableUserRule->bLimitScore==true)
				{
					if (pUserScore->lScore>pTableUserRule->lMaxScore)
					{
						TCHAR szDescribe[128]=TEXT("");
						_snprintf(szDescribe,sizeof(szDescribe),TEXT("你的积分太高，与 %s 设置的设置不符，不能加入游戏！"),m_pIUserItem[i]->GetAccounts());
						SendSitFailedPacket(pIServerUserItem,szDescribe);
						return false;
					}
					if (pUserScore->lScore<pTableUserRule->lLessScore)
					{
						TCHAR szDescribe[128]=TEXT("");
						_snprintf(szDescribe,sizeof(szDescribe),TEXT("你的积分太低，与 %s 设置的设置不符，不能加入游戏！"),m_pIUserItem[i]->GetAccounts());
						SendSitFailedPacket(pIServerUserItem,szDescribe);
						return false;
					}
				}
			}
		}

		//地址效验
		bool bCheckSameIP=pUserRule->bCheckSameIP;
		for (WORD i=0;i<m_wChairCount;i++)
		{
			if (m_pIUserItem[i]!=NULL)
			{
				pTableUserRule=m_pIUserItem[i]->GetUserRule();
				if (pTableUserRule->bCheckSameIP==true) 
				{
					bCheckSameIP=true;
					break;
				}
			}
		}
		if (bCheckSameIP==true)
		{
			DWORD dwUserIP=pIServerUserItem->GetClientIP();
			for (WORD i=0;i<m_wChairCount;i++)
			{
				if ((m_pIUserItem[i]!=NULL)&&(m_pIUserItem[i]->GetClientIP()==dwUserIP))
				{
					if (pUserRule->bCheckSameIP)
					{
						LPCTSTR pszDescribe=TEXT("你设置了不跟相同 IP 地址的玩家游戏，此游戏桌存在与你 IP 地址相同的玩家，不能加入游戏！");
						SendSitFailedPacket(pIServerUserItem,pszDescribe);
						return false;
					}
					else
					{
						LPCTSTR pszDescribe=TEXT("此桌设置了不跟相同 IP 地址的玩家游戏，此游戏桌存在与你 IP 地址相同的玩家，不能加入游戏！");
						SendSitFailedPacket(pIServerUserItem,pszDescribe);
						return false;
					}
				}
			}
			for (WORD i=0;i<m_wChairCount-1;i++)
			{
				if (m_pIUserItem[i]!=NULL)
				{
					for (WORD j=i+1;j<m_wChairCount;j++)
					{
						if ((m_pIUserItem[j]!=NULL)&&(m_pIUserItem[i]->GetClientIP()==m_pIUserItem[j]->GetClientIP()))
						{
							LPCTSTR pszDescribe=TEXT("你设置了不跟相同 IP 地址的玩家游戏，此游戏桌存在 IP 地址相同的玩家，不能加入游戏！");
							SendSitFailedPacket(pIServerUserItem,pszDescribe);
							return false;
						}
					}
				}
			}
		}
	}

	//更新密码
	WORD wUserCount=0;
	for (WORD i=0;i<m_wChairCount;i++)
	{
		if (m_pIUserItem[i]!=NULL) wUserCount++;
	}
	if (wUserCount==0)
	{
		m_bLocked=pUserRule->bPassword;
		m_dwTableOwnerID=pUserData->dwUserID;
		if (m_bLocked==true) lstrcpyn(m_szPassword,pUserRule->szPassword,CountArray(m_szPassword));
	}

	//设置玩家
	m_bAllowLookon[wChairID]=false;
	m_pIUserItem[wChairID]=pIServerUserItem;
	pIServerUserItem->SetUserStatus(US_SIT,m_wTableID,wChairID);
	m_pIGameServiceFrame->SendUserStatus(pIServerUserItem);

	//坐下处理
	if (m_pITableUserAction!=NULL) m_pITableUserAction->OnActionUserSitDown(wChairID,pIServerUserItem,false);

	return true;
}

//断线事件
bool __cdecl CTableFrame::OnUserOffLine(WORD wChairID)
{
	//设置状态
	m_pIUserItem[wChairID]->SetUserStatus(US_OFFLINE,m_wTableID,wChairID);
	m_pIGameServiceFrame->SendUserStatus(m_pIUserItem[wChairID]);

	//断线处理
	if (m_pITableUserAction!=NULL) m_pITableUserAction->OnActionUserOffLine(wChairID,m_pIUserItem[wChairID]);

	//设置定时器
	WORD wTimerID=IDI_OFFLINE+wChairID;
	WPARAM wBindParam=m_pIUserItem[wChairID]->GetUserID();
	m_pIGameServiceFrame->SetTableTimer(m_wTableID,wTimerID,90000L,1,wBindParam);

	//构造消息
	TCHAR szMessage[512]=TEXT("");
	_sntprintf(szMessage,sizeof(szMessage),TEXT("[ %s ] 断线了，请耐心等候片刻...."),m_pIUserItem[wChairID]->GetAccounts());

	//发送消息
	for (WORD i=0;i<MAX_CHAIR;i++)
	{
		if (m_pIUserItem[wChairID]!=NULL)
		{
			SendGameMessage(m_pIUserItem[wChairID],szMessage,SMT_INFO);
		}
	}

	return true;
}

//重进事件
bool __cdecl CTableFrame::OnUserReConnect(WORD wChairID)
{
	//效验状态
	ASSERT(wChairID<m_wChairCount);
	ASSERT(m_pIUserItem[wChairID]!=NULL);

	//删除定时器
	m_pIGameServiceFrame->KillTableTimer(m_wTableID,IDI_OFFLINE+wChairID);

	//设置用户
	m_pIUserItem[wChairID]->SetUserStatus(US_PLAY,m_wTableID,wChairID);
	m_pIGameServiceFrame->SendUserStatus(m_pIUserItem[wChairID]);

	return true;
}

//请求断线
bool __cdecl CTableFrame::OnUserReqOffLine(WORD wChairID)
{
	return true;
}

//定时器事件
bool __cdecl CTableFrame::OnEventTimer(WORD wTimerID, WPARAM wBindParam)
{
	//桌子定时器
	if (wTimerID>IDI_MAX_TIME_ID)
	{
		switch (wTimerID)
		{
		case IDI_OFFLINE:
		case IDI_OFFLINE+1:
		case IDI_OFFLINE+2:
		case IDI_OFFLINE+3:
		case IDI_OFFLINE+4:
		case IDI_OFFLINE+5:
		case IDI_OFFLINE+6:
		case IDI_OFFLINE+7:		//断线定时器
			{
				//效验参数
				WORD wChairID=wTimerID-IDI_OFFLINE;
				ASSERT(wChairID<m_wChairCount);

				//效验状态
				if (m_bGameStarted==false) return false;

				//断线处理
				if (m_pIUserItem[wChairID]!=NULL)
				{
					tagServerUserData * pUserData=m_pIUserItem[wChairID]->GetUserData();
					if (pUserData->dwUserID!=wBindParam) return false;
					if (pUserData->cbUserStatus!=US_OFFLINE) return false;
					m_pITableFrameSink->OnEventGameEnd(wChairID,m_pIUserItem[wChairID],GER_USER_LEFT);

					return true;
				}

				return false;
			}
		}

		return false;
	}

	//游戏定时器
	return m_pITableFrameSink->OnTimerMessage(wTimerID,wBindParam);
}

//游戏事件处理
bool __cdecl CTableFrame::OnEventSocketGame(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem)
{
	return m_pITableFrameSink->OnGameMessage(wSubCmdID,pDataBuffer,wDataSize,pIServerUserItem);
}

//框架事件处理
bool __cdecl CTableFrame::OnEventSocketFrame(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem)
{
	//效验参数
	ASSERT(pIServerUserItem!=NULL);
	ASSERT(m_pITableFrameSink!=NULL);

	//消息处理
	bool bSuccess=m_pITableFrameSink->OnFrameMessage(wSubCmdID,pDataBuffer,wDataSize,pIServerUserItem);
	if (bSuccess==false)
	{
		switch (wSubCmdID)
		{
		case SUB_GF_INFO:	//游戏信息
			{
				//效验参数
				ASSERT(wDataSize==sizeof(CMD_GF_Info));
				if (wDataSize<sizeof(CMD_GF_Info)) return false;

				//变量定义
				CMD_GF_Info * pInfo=(CMD_GF_Info *)pDataBuffer;
				tagServerUserData * pUserData=pIServerUserItem->GetUserData();
				bool bLookonUser=(pUserData->cbUserStatus==US_LOOKON);

				//效验状态
				ASSERT(pUserData->wChairID<m_wChairCount);
				if (pUserData->wChairID>=m_wChairCount) return false;

				//设置变量
				if (bLookonUser==false) m_bAllowLookon[pUserData->wChairID]=pInfo->bAllowLookon?true:false;

				//发送配置
				CMD_GF_Option Option;
				Option.bGameStatus=m_bGameStatus;
				Option.bAllowLookon=m_bAllowLookon[pUserData->wChairID]?TRUE:FALSE;
				m_pIGameServiceFrame->SendData(pIServerUserItem,MDM_GF_FRAME,SUB_GF_OPTION,&Option,sizeof(Option));

				//发送场景
				bool bSendSecret=((bLookonUser==false)||(m_bAllowLookon[pUserData->wChairID]==true));
				return m_pITableFrameSink->SendGameScene(pUserData->wChairID,pIServerUserItem,m_bGameStatus,bSendSecret);
			}
		case SUB_GF_USER_READY:	//用户同意
			{
				//变量定义
				tagServerUserData * pUserData=pIServerUserItem->GetUserData();
				bool bLookonUser=(pUserData->cbUserStatus==US_LOOKON);

				//状态效验
				ASSERT(bLookonUser==false);
				ASSERT(m_pIUserItem[pUserData->wChairID]==pIServerUserItem);
				if (bLookonUser==true) return false;
				if (pUserData->cbUserStatus>=US_PLAY) return true;

				//设置变量
				pUserData->cbUserStatus=US_READY;

				//同意处理
				if (m_pITableUserAction!=NULL) 
				{
					m_pITableUserAction->OnActionUserReady(pUserData->wChairID,m_pIUserItem[pUserData->wChairID],(VOID *)pDataBuffer,wDataSize);
				}

				//变量定义
				bool bMatchServer=((m_pGameServiceOption->wServerType&GAME_GENRE_MATCH)!=0);
				bool bControlStart=((bMatchServer==true)&&m_pGameServiceOption->cbControlStart==TRUE);

				//开始判断
				if ((bControlStart==false)&&(StartVerdict()==true))
				{
					StartGame();
					return true;
				}

				//发送状态
				m_pIGameServiceFrame->SendUserStatus(pIServerUserItem);

				return true;
			}
		case SUB_GF_USER_CHAT:	//用户聊天
			{
				//效验参数
				CMD_GF_UserChat * pUserChat=(CMD_GF_UserChat *)pDataBuffer;
				ASSERT(wDataSize>=(sizeof(CMD_GF_UserChat)-sizeof(pUserChat->szChatMessage)));
				ASSERT(wDataSize==(sizeof(CMD_GF_UserChat)-sizeof(pUserChat->szChatMessage)+pUserChat->wChatLength));
				if (wDataSize<(sizeof(CMD_GF_UserChat)-sizeof(pUserChat->szChatMessage))) return false;
				if (wDataSize!=(sizeof(CMD_GF_UserChat)-sizeof(pUserChat->szChatMessage)+pUserChat->wChatLength)) return false;

				//变量定义
				bool bMatchServer=((m_pGameServiceOption->wServerType&GAME_GENRE_MATCH)!=0);
				bool bControlStart=((bMatchServer==true)&&m_pGameServiceOption->cbControlStart==TRUE);

				//命令过虑
				const tagServerUserData * pUserData=pIServerUserItem->GetUserData();
				if (pUserData->dwMasterRight!=0L)
				{
					//比赛开始
					if ((bMatchServer==true)&&(bControlStart=true)&&(lstrcmp(pUserChat->szChatMessage,TEXT("/:StartGame"))==0))
					{
						if (StartVerdict()==true) StartGame();
						return true;
					}

					//游戏解散
					if (lstrcmp(pUserChat->szChatMessage,TEXT("/:DismissGame"))==0)
					{
						DismissGame();
						return true;
					}
				}

				//比赛旁观
				if (pUserData->dwMasterRight==0L)
				{
					if ((bMatchServer==true)&&(pIServerUserItem->GetUserStatus()==US_LOOKON))
					{
						LPCTSTR pszMessage=TEXT("为了不影响比赛选手比赛，旁观的用户禁止发言！");
						SendGameMessage(pIServerUserItem,pszMessage,SMT_EJECT|SMT_INFO);
						return true;
					}
				}

				//权限判断
				if (CUserRight::CanGameChat(pIServerUserItem->GetUserData()->dwUserRight)==false)
				{
					LPCTSTR pszMessage=TEXT("你暂时没有发送房间消息的权限，只能与管理员私聊！");
					SendGameMessage(pIServerUserItem,pszMessage,SMT_EJECT|SMT_INFO);
					return true;
				}

				//状态查询
				if ((pUserData->dwMasterRight==0L)&&(m_pIGameServiceFrame->IsAllowGameChat()==false))
				{
					LPCTSTR pszMessage=TEXT("抱歉，本游戏房间不允许发送聊天信息！");
					SendGameMessage(pIServerUserItem,pszMessage,SMT_EJECT|SMT_INFO);
					return true;
				}

				//游戏玩家
				for (WORD i=0;i<m_wChairCount;i++)
				{
					if (m_pIUserItem[i]!=NULL)
						m_pIGameServiceFrame->SendData(m_pIUserItem[i],MDM_GF_FRAME,SUB_GF_USER_CHAT,pUserChat,wDataSize);
				}

				//旁观玩家
				for (INT_PTR i=0;i<m_LookonUserItemPtr.GetCount();i++)
				{
					m_pIGameServiceFrame->SendData(m_LookonUserItemPtr[i],MDM_GF_FRAME,SUB_GF_USER_CHAT,pUserChat,wDataSize);
				}

				return true;
			}
		case SUB_GF_LOOKON_CONTROL:	//旁观控制
			{
				//效验参数
				ASSERT(wDataSize==sizeof(CMD_GF_LookonControl));
				if (wDataSize<sizeof(CMD_GF_LookonControl)) return false;

				//用户效验
				tagServerUserData * pUserData=pIServerUserItem->GetUserData();
				if (pUserData->cbUserStatus==US_LOOKON) return false;

				//变量定义
				CMD_GF_LookonControl * pLookonControl=(CMD_GF_LookonControl *)pDataBuffer;

				//旁观处理
				if (pLookonControl->dwUserID!=0L)
				{
					for (INT_PTR i=0;i<m_LookonUserItemPtr.GetCount();i++)
					{
						//获取用户
						IServerUserItem * pILookonUserItem=m_LookonUserItemPtr[i];
						if (pILookonUserItem->GetUserID()!=pLookonControl->dwUserID) continue;
						if (pILookonUserItem->GetChairID()!=pIServerUserItem->GetChairID()) continue;

						//构造消息
						CMD_GF_LookonControl LookonControl;
						LookonControl.dwUserID=pLookonControl->dwUserID;
						LookonControl.bAllowLookon=pLookonControl->bAllowLookon;

						//发送消息
						m_pIGameServiceFrame->SendData(pILookonUserItem,MDM_GF_FRAME,SUB_GF_LOOKON_CONTROL,&LookonControl,sizeof(LookonControl));

						break;
					}
				}
				else
				{
					//设置判断
					bool bAllowLookon=(pLookonControl->bAllowLookon==TRUE)?true:false;
					if (bAllowLookon==m_bAllowLookon[pUserData->wChairID]) return true;
					
					//设置变量
					m_bAllowLookon[pUserData->wChairID]=bAllowLookon;

					//构造消息
					CMD_GF_LookonControl LookonControl;
					LookonControl.dwUserID=pLookonControl->dwUserID;
					LookonControl.bAllowLookon=pLookonControl->bAllowLookon;

					//发送消息
					for (INT_PTR i=0;i<m_LookonUserItemPtr.GetCount();i++)
					{
						//获取用户
						IServerUserItem * pILookonUserItem=m_LookonUserItemPtr[i];
						if (pILookonUserItem->GetChairID()!=pIServerUserItem->GetChairID()) continue;

						//发送消息
						m_pIGameServiceFrame->SendData(pILookonUserItem,MDM_GF_FRAME,SUB_GF_LOOKON_CONTROL,&LookonControl,sizeof(LookonControl));
					}
				}

				return true;
			}
		case SUB_GF_KICK_TABLE_USER:	//踢走用户
			{
				//效验参数
				ASSERT(wDataSize==sizeof(CMD_GF_KickTableUser));
				if (wDataSize!=sizeof(CMD_GF_KickTableUser)) return false;                
			
				//效验用户
				tagServerUserData * pUserData=pIServerUserItem->GetUserData();
				if((pUserData->cbMemberOrder==0)&&(pUserData->cbMasterOrder==0)) return false;

				//变量定义
				CMD_GF_KickTableUser * pKickTableUser=(CMD_GF_KickTableUser *)pDataBuffer;

				//查找用户
				IServerUserItem * pIKickUserItem=NULL;
				for (WORD i=0;i<m_wChairCount;i++)
				{
					if ((m_pIUserItem[i]!=NULL)&&(m_pIUserItem[i]->GetUserID()==pKickTableUser->dwUserID))
					{
						pIKickUserItem=m_pIUserItem[i];
						break;
					}
				}
				if (pIKickUserItem==NULL)
				{
					IServerUserItem * pTempUserItem=NULL;
					for (INT_PTR i=0;i<m_LookonUserItemPtr.GetCount();i++)
					{
						pTempUserItem=m_LookonUserItemPtr[i];
						if (pTempUserItem->GetUserID()==pKickTableUser->dwUserID)
						{
							pIKickUserItem=pTempUserItem;
							break;
						}
					}
				}

				//踢走用户
				if (pIKickUserItem!=NULL)
				{	
					//变量定义
					tagServerUserData * pKickUserData=pIKickUserItem->GetUserData();
					tagServerUserData * pActionUserData=pIServerUserItem->GetUserData();

					//状态判断
					if (pKickUserData->cbUserStatus>=US_PLAY) return true;

					//权限判断
					bool bKickUser=false;
					if (bKickUser==false) bKickUser=(pActionUserData->cbMasterOrder>0);
					if (bKickUser==false) bKickUser=(pActionUserData->cbMemberOrder>pKickUserData->cbMemberOrder);

					//踢走用户
					if (bKickUser==true)
					{
						TCHAR szDescribe[128]=TEXT("");
						_snprintf(szDescribe,sizeof(szDescribe),TEXT("您被 [ %s ] 踢出游戏桌！"),pUserData->szAccounts);
						SendGameMessage(pIKickUserItem,szDescribe,SMT_EJECT|SMT_INFO|SMT_CLOSE_GAME);					
					}
				}    

				return true;
			}
		}
	}

	return bSuccess;
}

//视频事件处理
bool CTableFrame::OnEventSocketVideo(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem)
{
	switch (wSubCmdID)
	{
	case SUB_GF_C_VIDEO_CONFIG:		//视频配置
		{
			//效验数据
			ASSERT(wDataSize==sizeof(CMD_C_VideoConfig));
			if (wDataSize!=sizeof(CMD_C_VideoConfig)) return false;

			//变量定义
			CMD_C_VideoConfig * pVideoConfig=(CMD_C_VideoConfig *)pDataBuffer;

			//查找用户
			IServerUserItem * pIRemoteUserItem=NULL;
			for (WORD i=0;i<m_wChairCount;i++)
			{
				if ((m_pIUserItem[i]!=NULL)&&(m_pIUserItem[i]->GetUserID()==pVideoConfig->dwRemoteUserID))
				{
					pIRemoteUserItem=m_pIUserItem[i];
					break;
				}
			}

			//消息处理
			if (pIRemoteUserItem!=NULL)
			{
				//变量定义
				CMD_S_VideoConfig VideoConfig;
				ZeroMemory(&VideoConfig,sizeof(VideoConfig));

				//设置变量
				VideoConfig.wNatPort=pVideoConfig->wNatPort;
				VideoConfig.dwNatAddr=pVideoConfig->dwNatAddr;
				VideoConfig.wLocalPort=pVideoConfig->wLocalPort;
				VideoConfig.dwLocalAddr=pVideoConfig->dwLocalAddr;
				VideoConfig.dwLocalUserID=pIServerUserItem->GetUserID();

				//发送消息
				m_pIGameServiceFrame->SendData(pIRemoteUserItem,MDM_GF_VIDEO,SUB_GF_S_VIDEO_CONFIG,&VideoConfig,sizeof(VideoConfig));
			}

			return true;
		}
	}

	return true;
}

//枚举用户
IServerUserItem * __cdecl CTableFrame::EnumLookonUserItem(WORD wIndex)
{
	if (wIndex>=m_LookonUserItemPtr.GetCount()) return NULL;
	return m_LookonUserItemPtr[wIndex];
}

//获取用户
IServerUserItem * __cdecl CTableFrame::GetServerUserItem(WORD wChairID)
{
	ASSERT(wChairID<m_wChairCount);
	if (wChairID>=m_wChairCount) return NULL;
	return m_pIUserItem[wChairID];
}

//设置定时器
bool __cdecl CTableFrame::SetGameTimer(WORD wTimerID, DWORD dwElapse, DWORD dwRepeat, WPARAM wBindParam)
{
	//效验参数
	ASSERT(wTimerID<=IDI_MAX_TIME_ID);
	if (wTimerID>IDI_MAX_TIME_ID) return false;

	//设置定时器
	return m_pIGameServiceFrame->SetTableTimer(m_wTableID,wTimerID,dwElapse,dwRepeat,wBindParam);
}

//删除定时器
bool __cdecl CTableFrame::KillGameTimer(WORD wTimerID)
{
	//效验参数
	ASSERT(wTimerID<=IDI_MAX_TIME_ID);
	if (wTimerID>IDI_MAX_TIME_ID) return false;

	//删除定时器
	return m_pIGameServiceFrame->KillTableTimer(m_wTableID,wTimerID);
}

//发送数据
bool __cdecl CTableFrame::SendUserData(IServerUserItem * pIServerUserItem, WORD wSubCmdID)
{
	m_pIGameServiceFrame->SendData(pIServerUserItem,MDM_GF_GAME,wSubCmdID);
	return true;
}

//发送数据
bool __cdecl CTableFrame::SendUserData(IServerUserItem * pIServerUserItem, WORD wSubCmdID, void * pData, WORD wDataSize)
{
	m_pIGameServiceFrame->SendData(pIServerUserItem,MDM_GF_GAME,wSubCmdID,pData,wDataSize);
	return true;
}

//发送数据
bool __cdecl CTableFrame::SendTableData(WORD wChairID, WORD wSubCmdID)
{
	//群发用户
	if (wChairID==INVALID_CHAIR)
	{
		for (WORD i=0;i<m_wChairCount;i++)
		{
			if (m_pIUserItem[i]!=NULL) 
			{
				m_pIGameServiceFrame->SendData(m_pIUserItem[i],MDM_GF_GAME,wSubCmdID);
			}
		}
		return true;
	}

	//单一发送
	ASSERT(wChairID<m_wChairCount);
	if ((wChairID<m_wChairCount)&&(m_pIUserItem[wChairID]!=NULL))
	{
		m_pIGameServiceFrame->SendData(m_pIUserItem[wChairID],MDM_GF_GAME,wSubCmdID);
		return true;
	}

	return false;
}

//发送数据
bool __cdecl CTableFrame::SendTableData(WORD wChairID, WORD wSubCmdID, void * pData, WORD wDataSize)
{
	//群发用户
	if (wChairID==INVALID_CHAIR)
	{
		for (WORD i=0;i<m_wChairCount;i++)
		{
			if (m_pIUserItem[i]!=NULL) 
			{
				m_pIGameServiceFrame->SendData(m_pIUserItem[i],MDM_GF_GAME,wSubCmdID,pData,wDataSize);
			}
		}
		return true;
	}

	//单一发送
	ASSERT(wChairID<m_wChairCount);
	if ((wChairID<m_wChairCount)&&(m_pIUserItem[wChairID]!=NULL))
	{
		m_pIGameServiceFrame->SendData(m_pIUserItem[wChairID],MDM_GF_GAME,wSubCmdID,pData,wDataSize);
		return true;
	}

	return false;
}

//发送数据
bool __cdecl CTableFrame::SendLookonData(WORD wChairID, WORD wSubCmdID)
{
	tagServerUserData * pUserData=NULL;
	IServerUserItem * pIServerUserItem=NULL;
	for (INT_PTR i=0;i<m_LookonUserItemPtr.GetCount();i++)
	{
		pIServerUserItem=m_LookonUserItemPtr[i];
		ASSERT(pIServerUserItem!=NULL);
		if (wChairID<m_wChairCount)
		{
			pUserData=pIServerUserItem->GetUserData();
			if (pUserData->wChairID==wChairID) m_pIGameServiceFrame->SendData(pIServerUserItem,MDM_GF_GAME,wSubCmdID);
		}
		else m_pIGameServiceFrame->SendData(pIServerUserItem,MDM_GF_GAME,wSubCmdID);
	}

	return true;
}

//发送数据
bool __cdecl CTableFrame::SendLookonData(WORD wChairID, WORD wSubCmdID, void * pData, WORD wDataSize)
{
	tagServerUserData * pUserData=NULL;
	IServerUserItem * pIServerUserItem=NULL;
	for (INT_PTR i=0;i<m_LookonUserItemPtr.GetCount();i++)
	{
		pIServerUserItem=m_LookonUserItemPtr[i];
		ASSERT(pIServerUserItem!=NULL);
		if (wChairID<m_wChairCount)
		{
			pUserData=pIServerUserItem->GetUserData();
			if (pUserData->wChairID==wChairID) m_pIGameServiceFrame->SendData(pIServerUserItem,MDM_GF_GAME,wSubCmdID,pData,wDataSize);
		}
		else m_pIGameServiceFrame->SendData(pIServerUserItem,MDM_GF_GAME,wSubCmdID,pData,wDataSize);
	}

	return true;
}

//发送房间消息
bool __cdecl CTableFrame::SendRoomMessage(IServerUserItem * pIServerUserItem, LPCTSTR lpszMessage, WORD wMessageType)
{
	//构造数据包
	CMD_GR_Message Message;
	Message.wMessageType=wMessageType;
	lstrcpyn(Message.szContent,lpszMessage,CountArray(Message.szContent));
	Message.wMessageLength=CountString(Message.szContent);

	//发送数据
	WORD wSendSize=sizeof(Message)-sizeof(Message.szContent)+Message.wMessageLength*sizeof(TCHAR);
	m_pIGameServiceFrame->SendData(pIServerUserItem,MDM_GR_SYSTEM,SUB_GR_MESSAGE,&Message,wSendSize);

	return true;
}

//发送游戏消息
bool __cdecl CTableFrame::SendGameMessage(IServerUserItem * pIServerUserItem, LPCTSTR lpszMessage, WORD wMessageType)
{
	//构造数据包
	CMD_GF_Message Message;
	Message.wMessageType=wMessageType;
	lstrcpyn(Message.szContent,lpszMessage,CountArray(Message.szContent));
	Message.wMessageLength=CountString(Message.szContent);

	//发送数据
	WORD wSendSize=sizeof(Message)-sizeof(Message.szContent)+Message.wMessageLength*sizeof(TCHAR);
	m_pIGameServiceFrame->SendData(pIServerUserItem,MDM_GF_FRAME,SUB_GF_MESSAGE,&Message,wSendSize);

	return true;
}

//解散游戏
bool __cdecl CTableFrame::DismissGame()
{
	//状态判断
	ASSERT(m_bGameStarted==true);
	if (m_bGameStarted==false) return false;

	//结束游戏
	if ((m_bGameStarted==true)&&(m_pITableFrameSink->OnEventGameEnd(INVALID_CHAIR,NULL,GER_DISMISS)==false))
	{
		ASSERT(FALSE);
		return false;
	}

	//设置状态
	if (m_bGameStarted==false)
	{
		//设置变量
		m_bGameStarted=false;

		//发送状态
		m_pIGameServiceFrame->SendTableStatus(m_wTableID);
	}

	return true;
}

//结束游戏
bool __cdecl CTableFrame::ConcludeGame()
{
	//设置变量
	m_dwTimeStart=0L;
	m_lGameTaxScore=0L;
	m_bGameStarted=false;
	memset(m_ScoreInfo,0,sizeof(m_ScoreInfo));
	memset(m_dwPlayerID,0,sizeof(m_dwPlayerID));
	memset(m_wOffLineCount,0,sizeof(m_wOffLineCount));

	//设置状态
	m_bGameStarted=false;
	m_bGameStatus=GS_FREE;

	//重置桌子
	m_pITableFrameSink->RepositTableFrameSink();

	//设置用户
	tagServerUserData * pUserData=NULL;
	for (WORD i=0;i<m_wChairCount;i++)
	{
		if (m_pIUserItem[i]!=NULL)
		{
			pUserData=m_pIUserItem[i]->GetUserData();
			if (pUserData->cbUserStatus!=US_OFFLINE) pUserData->cbUserStatus=US_SIT;
		}
	}

	//断线处理
	for (WORD i=0;i<m_wChairCount;i++)
	{
		if (m_pIUserItem[i]!=NULL)
		{
			//获取用户
			IServerUserItem * pIServerUserItem=m_pIUserItem[i];
			if (pIServerUserItem->GetUserStatus()!=US_OFFLINE) continue;
			
			//删除定时器
			WORD wTimerID=IDI_OFFLINE+i;
			m_pIGameServiceFrame->KillTableTimer(m_wTableID,wTimerID);

			//用户离开
			PerformStandUpAction(pIServerUserItem);

			//清理用户资料
			m_pIGameServiceFrame->DeleteUserItem(pIServerUserItem);
		}
	}

	//赛局判断
	if ((m_pGameServiceOption->wServerType&GAME_GENRE_MATCH)&&(m_pGameServiceOption->lMatchDraw>0))
	{
		for (WORD i=0;i<m_wChairCount;i++)
		{
			if (m_pIUserItem[i]!=NULL)
			{
				//获取用户
				IServerUserItem * pIServerUserItem=m_pIUserItem[i];
				tagServerUserData * pUserData=pIServerUserItem->GetUserData();

				//比赛判断
				LONG lPlayCount=pUserData->UserScoreInfo.lWinCount+pUserData->UserScoreInfo.lLostCount+pUserData->UserScoreInfo.lDrawCount;
				if (lPlayCount>=m_pGameServiceOption->lMatchDraw)
				{
					TCHAR szDescribe[256]=TEXT("");
					lstrcpyn(szDescribe,TEXT("恭喜你，你的比赛局数已经完成了，不需要再继续比赛，请耐心等待赛果公布！ "),CountArray(szDescribe));
					SendGameMessage(pIServerUserItem,szDescribe,SMT_EJECT|SMT_INFO|SMT_CLOSE_GAME);
					PerformStandUpAction(pIServerUserItem);
				}
			}
		}
	}

	//检测积分
	if (m_pGameServiceOption->lLessScore!=0L)
	{
		for (WORD i=0;i<m_wChairCount;i++)
		{
			if (m_pIUserItem[i]!=NULL)
			{
				//获取用户
				IServerUserItem * pIServerUserItem=m_pIUserItem[i];
				tagServerUserData * pUserData=pIServerUserItem->GetUserData();

				//判断积分
				LONG lLessScore=m_pGameServiceOption->lLessScore;
				if ((lLessScore!=0L)&&(pUserData->UserScoreInfo.lScore<lLessScore))
				{
					TCHAR szDescribe[256]=TEXT("");
					_snprintf(szDescribe,sizeof(szDescribe),TEXT("你的游戏积分少于 %ld，不能继续游戏！"),lLessScore);
					SendGameMessage(pIServerUserItem,szDescribe,SMT_EJECT|SMT_INFO|SMT_CLOSE_GAME);
					PerformStandUpAction(pIServerUserItem);
				}
			}
		}
	}

	//关闭判断
	if ((m_pIGameServiceFrame->IsAllowEnterGame()==false)||(m_pIGameServiceFrame->IsShallClose()==true))
	{
		for (WORD i=0;i<m_wChairCount;i++)
		{
			if (m_pIUserItem[i]!=NULL)
			{
				//获取用户
				IServerUserItem * pIServerUserItem=m_pIUserItem[i];
				tagServerUserData * pUserData=pIServerUserItem->GetUserData();

				//用户判断
				if (pUserData->dwMasterRight==0L)
				{
					//用户起立
					LPCTSTR pszMessage=TEXT("请注意，游戏房间即将关闭或者不允许玩家进入，请你离开游戏桌子！");
					SendGameMessage(pIServerUserItem,pszMessage,SMT_EJECT|SMT_INFO|SMT_CLOSE_GAME);
					PerformStandUpAction(pIServerUserItem);

					continue;
				}
			}
		}
	}

	//用户状态
	for (WORD i=0;i<m_wChairCount;i++)
	{
		if (m_pIUserItem[i]!=NULL)
		{
			m_pIGameServiceFrame->SendUserStatus(m_pIUserItem[i]);
		}
	}

	//发送状态
	m_pIGameServiceFrame->SendTableStatus(m_wTableID);

	return true;
}

//写入积分
bool __cdecl CTableFrame::WriteUserScore(WORD wChairID, LONG lScore, LONG lRevenue, enScoreKind ScoreKind)
{
	//效验参数
	ASSERT(wChairID<m_wChairCount);
	ASSERT(m_pIUserItem[wChairID]!=NULL);
	if (wChairID>=m_wChairCount) return false;
	if (m_pIUserItem[wChairID]==NULL) return false;

	//设置变量
	m_ScoreInfo[wChairID].lScore=lScore;
	m_ScoreInfo[wChairID].lRevenue=lRevenue;
	m_ScoreInfo[wChairID].ScoreKind=ScoreKind;

	//写入积分
	WriteUserScore(m_pIUserItem[wChairID],lScore,lRevenue,ScoreKind);

	return true;
}

//写入积分
bool __cdecl CTableFrame::WriteUserScore(IServerUserItem * pIServerUserItem, LONG lScore, LONG lRevenue, enScoreKind ScoreKind)
{
	//效验参数
	ASSERT(pIServerUserItem!=NULL);
	if (pIServerUserItem==NULL) return false;

	//变量定义
	tagScoreInfo ScoreInfo;
	ZeroMemory(&ScoreInfo,sizeof(ScoreInfo));

	//设置变量
	ScoreInfo.lScore=lScore;
	ScoreInfo.lRevenue=lRevenue;
	ScoreInfo.ScoreKind=ScoreKind;

	//修改积分
	pIServerUserItem->WriteScore(ScoreInfo,(DWORD)time(NULL)-m_dwTimeStart);

	//发送信息
	m_pIGameServiceFrame->SendUserScore(pIServerUserItem);

	//存储积分
	if ((m_pGameServiceOption->wServerType==GAME_GENRE_GOLD)&&(m_pGameServiceOption->lRestrictScore>0L))
	{
		//还原积分
		tagServerUserData * pServerUserData=pIServerUserItem->GetUserData();
		pServerUserData->UserScoreInfo.lScore+=pServerUserData->lStorageScore;
		pServerUserData->lStorageScore=0L;

		//存储积分
		if (pServerUserData->UserScoreInfo.lScore>m_pGameServiceOption->lRestrictScore)
		{
			LONG lUserScore=pServerUserData->UserScoreInfo.lScore;
			pServerUserData->UserScoreInfo.lScore=m_pGameServiceOption->lRestrictScore;
			pServerUserData->lStorageScore=lUserScore-m_pGameServiceOption->lRestrictScore;
		}
	}

	return true;
}

//发送场景
bool __cdecl CTableFrame::SendGameScene(IServerUserItem * pIServerUserItem, void * pData, WORD wDataSize)
{
	//系统消息
	TCHAR szMessage[256]=TEXT("");
	if (m_pGameServiceOption->wServerType&GAME_GENRE_MATCH)
	{
		_snprintf(szMessage,sizeof(szMessage),TEXT("亲爱的用户，欢迎您来到“%s”比赛游戏房间，祝比赛选手赛出水平，取得好的成绩！"),m_pGameServiceAttrib->szKindName);
		SendGameMessage(pIServerUserItem,szMessage,SMT_INFO);
	}
	else
	{
		_snprintf(szMessage,sizeof(szMessage),TEXT("亲爱的用户，欢迎您来到“%s”，欢迎你多提宝贵建议！"),m_pGameServiceAttrib->szKindName);
		SendGameMessage(pIServerUserItem,szMessage,SMT_INFO);
	}

	//安全提示
	if ((pIServerUserItem->GetUserStatus()!=US_LOOKON)&&(m_bAllowLookon[pIServerUserItem->GetChairID()]==true))
	{
		_snprintf(szMessage,sizeof(szMessage),TEXT("请注意，您设置了允许所有玩家观看您游戏。"),m_pGameServiceAttrib->szKindName);
		SendGameMessage(pIServerUserItem,szMessage,SMT_INFO);
	}

	//发送场景
	m_pIGameServiceFrame->SendData(pIServerUserItem,MDM_GF_FRAME,SUB_GF_SCENE,pData,wDataSize);

	return true;
}

//开始游戏
bool __cdecl CTableFrame::StartGame()
{
	//效验状态
	ASSERT(m_bGameStarted==false);
	if (m_bGameStarted==true) return false;

	//设置变量
	m_bGameStarted=true;
	m_dwTimeStart=(DWORD)time(NULL);
	memset(m_wOffLineCount,0,sizeof(m_wOffLineCount));

	//记录分数
	m_lGameTaxScore=0L;
	memset(m_ScoreInfo,0,sizeof(m_ScoreInfo));
	memset(m_dwPlayerID,0,sizeof(m_dwPlayerID));

	//设置玩家
	tagServerUserData * pUserData=NULL;
	for (WORD i=0;i<m_wChairCount;i++)
	{
		if (m_pIUserItem[i]!=NULL)
		{
			pUserData=m_pIUserItem[i]->GetUserData();
			pUserData->cbUserStatus=US_PLAY;
			m_dwPlayerID[i]=pUserData->dwUserID;
		}
	}

	//发送状态
	m_pIGameServiceFrame->SendTableStatus(m_wTableID);

	//用户状态
	for (WORD i=0;i<m_wChairCount;i++)
	{
		if (m_pIUserItem[i]!=NULL)
		{
			m_pIGameServiceFrame->SendUserStatus(m_pIUserItem[i]);
		}
	}

	//通知事件
	m_pITableFrameSink->OnEventGameStart();

	return true;
}

//判断开始
bool __cdecl CTableFrame::StartVerdict()
{
	//比赛判断
	if (m_bGameStarted==true) return false;

	//时间模式
	enStartMode StartMode=m_pITableFrameSink->GetGameStartMode();
	if (StartMode==enStartMode_TimeControl) return false;

	//准备人数
	WORD wReadyUserCount=0;
	tagServerUserData * pUserData=NULL;
	for (WORD i=0;i<m_wChairCount;i++) 
	{
		if (m_pIUserItem[i]!=NULL)
		{
			wReadyUserCount++;
			pUserData=m_pIUserItem[i]->GetUserData();
			if (pUserData->cbUserStatus!=US_READY) return false;
		}
	}

	//条件判断
	if (wReadyUserCount>1L)
	{
		if (StartMode==enStartMode_Symmetry)
		{
			if ((wReadyUserCount%2)!=0) return false;
			if (wReadyUserCount==m_wChairCount) return true;
			WORD wHalfCount=m_wChairCount/2;
			for (WORD i=0;i<wHalfCount;i++)
			{
				if ((m_pIUserItem[i]==NULL)&&(m_pIUserItem[i+wHalfCount]!=NULL)) return false;
				if ((m_pIUserItem[i]!=NULL)&&(m_pIUserItem[i+wHalfCount]==NULL)) return false;
			}
			return true;
		}
		else 
		{
			if (StartMode==enStartMode_FullReady) return (wReadyUserCount==m_wChairCount);
			if (StartMode==enStartMode_AllReady) return true;
		}
	}

	return false;
}

//获取空位
WORD CTableFrame::GetNullChairID()
{
	//椅子搜索
	for (WORD i=0;i<m_wChairCount;i++)
	{
		if (m_pIUserItem[i]==NULL)
		{
			return i;
		}
	}

	return INVALID_CHAIR;
}

//发送坐下失败
void CTableFrame::SendSitFailedPacket(IServerUserItem * pIServerUserItem, LPCTSTR pszFailedDescribe)
{
	//构造数据
	CMD_GR_SitFailed SitFailed;
	memset(&SitFailed,0,sizeof(SitFailed));
	lstrcpyn(SitFailed.szFailedDescribe,pszFailedDescribe,CountArray(SitFailed.szFailedDescribe));

	//发送数据
	WORD wSendSize=sizeof(SitFailed)-sizeof(SitFailed.szFailedDescribe)+CountString(SitFailed.szFailedDescribe);
	m_pIGameServiceFrame->SendData(pIServerUserItem,MDM_GR_USER,SUB_GR_SIT_FAILED,&SitFailed,wSendSize);

	return;
}

//////////////////////////////////////////////////////////////////////////
