#ifndef DATA_BASE_SINK_HEAD_FILE
#define DATA_BASE_SINK_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "GameServiceExport.h"

//////////////////////////////////////////////////////////////////////////
//结构定义

//数据库参数
struct tagDataBaseSinkParameter
{
	tagDataBaseInfo						* pGameUserDBInfo;				//连接信息
	tagDataBaseInfo						* pGameScoreDBInfo;				//连接信息
	tagGameServiceAttrib				* pGameServiceAttrib;			//服务属性
	tagGameServiceOption				* pGameServiceOption;			//配置信息
};

//////////////////////////////////////////////////////////////////////////
//数据库请求数据包

//数据库请求标识
#define	DBR_GR_LOGON_BY_USERID			1								//I D 登录
#define DBR_GR_WRITE_GAME_SCORE			2								//离开房间
#define DBR_GR_LEAVE_GAME_SERVER		3								//修改积分
#define DBR_GR_GAME_SCORE_RECORD		4								//积分记录
#define DBR_GR_LOAD_ANDROID				5								//加载用户
#define DBR_GR_LIMIT_ACCOUNTS			6								//禁用帐户
#define DBR_GR_SET_USER_RIGHT			7								//设置权限

//数据库输出标识
#define DBR_GR_LOGON_SUCCESS			100								//登录成功
#define DBR_GR_LOGON_ERROR				101								//登录失败
#define DBR_GR_ANDROID_USER				102								//机器信息

//ID 登录
struct DBR_GR_LogonByUserID
{
	DWORD								dwUserID;						//用户 I D
	DWORD								dwClientIP;						//连接地址
	TCHAR								szPassWord[PASS_LEN];			//登录密码
	TCHAR								szComputerID[COMPUTER_ID_LEN];	//机器序列
};

//禁用帐户
struct DBR_GR_LimitAccounts
{
	DWORD								dwUserID;						//用户 I D
	DWORD								dwMasterUserID;					//管理 I D
	DWORD								dwMasterClientIP;				//连接地址
};

//设置权限
struct DBR_GR_SetUserRight
{
	//权限范围
	BYTE								cbGame;							//设置游戏
	BYTE								cbAccounts;						//设置帐号

	//权限信息
	DWORD								dwUserID;						//用户 I D
	DWORD								dwUserRight;					//用户权限
	DWORD								dwMasterUserID;					//管理 I D
	DWORD								dwMasterClientIP;				//连接地址
};

//机器用户
struct DBO_GR_AndroidUser
{
	LONG								lResultCode;					//结果代码
	WORD								wAndroidCount;					//用户数目
	DWORD								dwAndroidID[MAX_ANDROID];		//用户 I D
};

//登录成功
struct DBR_GR_LogonSuccess
{
	//基本信息
	WORD								wFaceID;						//头像索引
	DWORD								dwUserID;						//用户 I D
	DWORD								dwGameID;						//用户 I D
	DWORD								dwGroupID;						//社团索引
	DWORD								dwUserRight;					//用户等级
	DWORD								dwMasterRight;					//管理权限
	TCHAR								szAccounts[NAME_LEN];			//登录帐号
	TCHAR								szPassWord[PASS_LEN];			//登录密码
	TCHAR								szGroupName[GROUP_LEN];			//社团名字
	TCHAR								szUnderWrite[UNDER_WRITE_LEN];	//个性签名

	//用户属性
	BYTE								cbGender;						//用户性别
	BYTE								cbMemberOrder;					//会员等级
	BYTE								cbMasterOrder;					//管理等级

	//积分信息
	LONG								lScore;							//用户分数
	LONG								lWinCount;						//胜利盘数
	LONG								lLostCount;						//失败盘数
	LONG								lDrawCount;						//和局盘数
	LONG								lFleeCount;						//断线数目
	LONG								lExperience;					//用户经验
};

//登录失败
struct DBR_GR_LogonError
{
	LONG								lErrorCode;						//错误代码
	TCHAR								szErrorDescribe[128];			//错误消息
};

//修改积分
struct DBR_GR_WriteUserScore
{
	//用户属性
	DWORD								dwUserID;						//用户地址
	DWORD								dwClientIP;						//连接地址
	DWORD								dwPlayTimeCount;				//游戏时间
	DWORD								dwOnlineTimeCount;				//在线时间

	//积分信息
	LONG								lRevenue;						//游戏税收
	tagUserScore						ScoreModifyInfo;				//修改积分
};

//离开房间
struct DBR_GR_LeaveGameServer
{
	//用户属性
	DWORD								dwUserID;						//用户地址
	DWORD								dwClientIP;						//连接地址
	DWORD								dwPlayTimeCount;				//游戏时间
	DWORD								dwOnlineTimeCount;				//在线时间

	//积分信息
	LONG								lRevenue;						//游戏税收
	tagUserScore						ScoreModifyInfo;				//修改积分
};

//////////////////////////////////////////////////////////////////////////

//数据库引擎钩子
class CDataBaseSink : public IDataBaseSink
{
	//配置变量
protected:
	tagDataBaseInfo						* m_pGameUserDBInfo;			//连接信息
	tagDataBaseInfo						* m_pGameScoreDBInfo;			//连接信息
	tagGameServiceAttrib				* m_pGameServiceAttrib;			//服务属性
	tagGameServiceOption				* m_pGameServiceOption;			//配置信息

	//接口变量
protected:
	IEventService						* m_pIEventService;				//事件服务

	//组件变量
protected:
	CDataBaseHelper						m_GameUserDB;					//用户数据库
	CDataBaseHelper						m_GameScoreDB;					//游戏数据库
	CQueueServiceEvent					m_AttemperEvent;				//调度通知

	//函数定义
public:
	//构造函数
	CDataBaseSink();
	//析构函数
	virtual ~CDataBaseSink();

	//基础接口
public:
	//释放对象
	virtual bool __cdecl Release() { if (IsValid()) delete this; return true; }
	//是否有效
	virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CDataBaseSink))?true:false; }
	//接口查询
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//调度接口
public:
	//调度模块启动
	virtual bool __cdecl BeginService(IUnknownEx * pIUnknownEx);
	//调度模块关闭
	virtual bool __cdecl EndService(IUnknownEx * pIUnknownEx);
	//数据操作处理
	virtual bool __cdecl OnDataBaseRequest(const NTY_DataBaseEvent & DataBaseEvent, void * pDataBuffer, WORD wDataSize);

	//配置函数 
public:
	//设置事件
	bool SetEventService(IUnknownEx * pIUnknownEx);
	//配置函数
	bool InitDataBaseSink(tagDataBaseSinkParameter * pDataBaseSinkParameter, IUnknownEx * pIUnknownEx);

	//处理函数
private:
	//登录请求
	bool OnRequestLogon(const NTY_DataBaseEvent & DataBaseEvent, void * pDataBuffer, WORD wDataSize);
	//写分请求
	bool OnRequestWriteUserScore(const NTY_DataBaseEvent & DataBaseEvent, void * pDataBuffer, WORD wDataSize);
	//离开房间
	bool OnRequestLeaveGameServer(const NTY_DataBaseEvent & DataBaseEvent, void * pDataBuffer, WORD wDataSize);
	//禁用帐户
	bool OnRequestLimitAccounts(const NTY_DataBaseEvent & DataBaseEvent, void * pDataBuffer, WORD wDataSize);
	//设置权限
	bool OnRequestSetUserRight(const NTY_DataBaseEvent & DataBaseEvent, void * pDataBuffer, WORD wDataSize);

	//存储过程
protected:
	//I D 存储过程
	LONG SPLogonByUserID(DWORD dwUserID, LPCTSTR pszPassword, DWORD dwClientIP, LPCTSTR pszComputerID);
	//写分存储过程
	LONG SPWriteUserScore(DWORD dwUserID, DWORD dwPlayTimeCount, DWORD dwOnLineTimeCount, DWORD dwClientIP, LONG lRevenue, tagUserScore & UserScore);
	//离开存储过程
	LONG SPLeaveGameServer(DWORD dwUserID, DWORD dwPlayTimeCount, DWORD dwOnLineTimeCount, DWORD dwClientIP, LONG lRevenue, tagUserScore & UserScore);
	//禁号存储过程
	LONG SPCongealAccounts(DWORD dwUserID, DWORD dwMasterUserID, DWORD dwClientIP);
	//权限存储过程
	LONG SPSetUserGameRight(DWORD dwUserID, DWORD dwUserRight, DWORD dwMasterUserID, DWORD dwClientIP);
	//权限存储过程
	LONG SPSetUserAccountsRight(DWORD dwUserID, DWORD dwUserRight, DWORD dwMasterUserID, DWORD dwClientIP);
};

//////////////////////////////////////////////////////////////////////////

#endif