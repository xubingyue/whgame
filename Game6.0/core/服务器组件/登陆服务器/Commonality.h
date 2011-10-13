#ifndef COMMONALITY_HEAD_FILE
#define COMMONALITY_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////
//定义头文件

//命令码文件
#include "..\..\消息定义\CMD_Plaza.h"
#include "..\..\消息定义\CMD_Center.h"

//全局头文件
#include "..\..\公共文件\GlobalField.h"
#include "..\..\公共文件\GlobalService.h"

//////////////////////////////////////////////////////////////////////////
//数据库对象定义

//数据库请求标识
#define	DBR_GP_LOGON_BY_ACCOUNTS	1									//帐号登录
#define	DBR_GP_LOGON_BY_USERID		2									//I D 登录
#define DBR_GP_REGISTER_ACCOUNTS	3									//注册帐号

//数据库输出标识
#define DBR_GP_LOGON_SUCCESS		100									//登录成功
#define DBR_GP_LOGON_ERROR			101									//登录失败

//帐号登录
struct DBR_GP_LogonByAccounts
{
	DWORD							dwClientIP;							//连接地址
	TCHAR							szAccounts[NAME_LEN];				//登录帐号
	TCHAR							szPassWord[PASS_LEN];				//登录密码
	TCHAR							szComputerID[COMPUTER_ID_LEN];		//机器序列
};

//ID 登录
struct DBR_GP_LogonByUserID
{
	DWORD							dwClientIP;							//连接地址
	DWORD							dwUserID;							//用户 I D
	TCHAR							szPassWord[PASS_LEN];				//登录密码
	TCHAR							szComputerID[COMPUTER_ID_LEN];		//机器序列
};

//帐号注册
struct DBR_GP_RegisterAccounts
{
	WORD							wFaceID;							//注册头像
	BYTE							cbGender;							//用户性别
	DWORD							dwClientIP;							//连接地址
	TCHAR							szSpreader[NAME_LEN];				//推荐人名
	TCHAR							szAccounts[NAME_LEN];				//登录帐号
	TCHAR							szPassWord[PASS_LEN];				//登录密码
	TCHAR							szComputerID[COMPUTER_ID_LEN];		//机器序列
};

//登录成功
struct DBR_GP_LogonSuccess
{
	//属性资料
	DWORD							dwUserID;							//用户标识
	DWORD							dwGameID;							//游戏标识
	DWORD							dwExperience;						//经验数值
	TCHAR							szPassword[PASS_LEN];				//登录密码
	TCHAR							szAccounts[NAME_LEN];				//登录帐号
	TCHAR							szGroupName[GROUP_LEN];				//社团名字

	//用户资料
	WORD							wFaceID;							//头像标识
	BYTE							cbGender;							//用户性别
	BYTE							cbMember;							//会员等级
	TCHAR							szUnderWrite[UNDER_WRITE_LEN];		//个性签名

	//描述信息
	TCHAR							szDescribeString[128];				//描述消息
};

//登录失败
struct DBR_GP_LogonError
{
	LONG							lErrorCode;							//错误代码
	TCHAR							szErrorDescribe[128];				//错误消息
};

//////////////////////////////////////////////////////////////////////////

#endif