#ifndef VIDEO_SERVICE_CONTROL_HEAD_FILE
#define VIDEO_SERVICE_CONTROL_HEAD_FILE

#pragma once

#include "VideoSend.h"
#include "VideoRece.h"
#include "VideoServiceModule.h"

//////////////////////////////////////////////////////////////////////////

//视频窗口
class VIDEO_SERVICE_CLASS CVideoServiceControl : public CWnd
{
	//友元定义
	friend class CVideoServiceManager;

	//内核变量
private:
	bool							m_bInitVideo;						//配置标志

	//用户信息
private:
	DWORD							m_dwUserID;							//用户标识
	TCHAR							m_szAccounts[NAME_LEN];				//用户帐号

	//设备标志
private:
	bool							m_bVidicon;							//视频设备
	bool							m_bMicrophone;						//音频设备

	//控制变量
private:
	bool							m_bSmallMode;						//小型模式
	bool							m_bLocalMode;						//本地标志
	bool							m_bEnableVideo;						//是否视频
	bool							m_bEnableAudio;						//是否音频

	//控钮控件
private:
	CSkinButton						m_btMore;							//更多按钮
	CSkinButton						m_btVideo;							//视频按钮
	CSkinButton						m_btAudio;							//音频按钮
	CSkinButton						m_btClone;							//克隆按钮
	CSkinButton						m_btFlower;							//送花按钮

	//控件变量
protected:
	CVideoSend						m_VideoSend;						//发送组件
	CVideoRece						m_VideoRece;						//接受组件
	CToolTipCtrl					m_ToolTipCtrl;						//提示控件

	//图片资源
private:
	CSkinImage						m_ImageSmallPhoto;					//缩小头像
	CSkinImage						m_ImageLargePhoto;					//放大头像
	CSkinImage						m_ImageSmallFrame;					//缩小框架
	CSkinImage						m_ImageLargeFrame;					//放大框架

	//函数定义
public:
	//构造函数
	CVideoServiceControl();
	//析构函数
	virtual ~CVideoServiceControl();

	//重载函数
protected:
	//消息解释
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	//大小模式
public:
	//大小模式
	bool SetSmallMode(bool bSmallMode);
	//大小模式
	bool IsSamllMode() { return m_bSmallMode; }

	//远程用户
public:
	//远程用户
	DWORD GetVideoUserID() { return m_dwUserID; }
	//远程用户
	bool SetVideoUserInfo(DWORD dwUserID, LPCTSTR pszAccounts);

	//设备属性
public:
	//视频设备
	bool HaveVidicon() { return m_bVidicon; }
	//音频设备
	bool HaveMicrophone() { return m_bMicrophone; }

	//控制函数
public:
	//音频控制
	bool EnableAudio(bool bEnable);
	//视频控制
	bool EnableVideo(bool bEnable);
	//配置视频
	bool InitVideoService(bool bLocalMode, bool bSmallMode);

	//事件函数
public:
	//界面重置
	bool OnEventGameReset();
	//用户离开
	bool OnEventUserLeave(DWORD dwRemoteUserID);
	//用户进入
	bool OnEventUserEnter(DWORD dwRemoteUserID);
	//用户配置
	bool OnEventUserConfig(DWORD dwRemoteUserID, tagVideoNetwordInfo * pVideoNetwordInfo);
	//显示视频
	bool OnShowLocalVD(bool bShow);

	//内部函数
protected:
	//调整窗口
	VOID RectifyControl();

	//消息映射
protected:
	//重画函数
	VOID OnPaint();
	//使能通知
	VOID OnEventVideoEnable();
	//绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	//创建函数
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);

	//按钮消息
protected:
	//更多按钮
	VOID OnBnClickedMore();
	//视频按钮
	VOID OnBnClickedVideo();
	//音频按钮
	VOID OnBnClickedAudio();
	//克隆按钮
	VOID OnBnClickedClone();
	//送花按钮
	VOID OnBnClickedFlower();

	//消息宏
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP() 
};

//////////////////////////////////////////////////////////////////////////

//视频管理
class VIDEO_SERVICE_CLASS CVideoServiceManager
{
	//友元定义
	friend class CVideoServiceControl;

	//视频信息
protected:
	WORD							m_wVideoPort;						//视频端口
	DWORD							m_dwVideoServer;					//视频地址
	DWORD							m_dwLocalUserID;					//本地用户
	bool							m_bOffLine[MAX_CHAIR];				//玩家断线

	//组件变量
protected:
	IClientKernel *					m_pIClientKernel;					//内核接口
	CVideoServiceControl *			m_VideoServiceControl[MAX_CHAIR];	//视频数组

	//静态变量
protected:
	static CVideoServiceManager *	m_pVideoServiceManager;				//管理对象

	//函数定义
public:
	//构造函数
	CVideoServiceManager();
	//析构函数
	virtual ~CVideoServiceManager();

	//配置函数
public:
	//设置接口
	bool SetClientKernel(IUnknownEx * pIUnknownEx);
	//服务信息
	bool SetVideoServiceInfo(DWORD dwLoaclUserID, DWORD dwVideoServer, WORD wVideoPort);
	//设置对象
	bool SetVideoServiceControl(WORD wVideoIndex, CVideoServiceControl * pVideoServiceControl);

	//事件接口
public:
	//界面重置
	bool OnEventGameReset();
	//用户离开
	bool OnEventUserLeave(WORD wVideoIndex, DWORD dwRemoteUserID);
	//用户进入
	bool OnEventUserEnter(WORD wVideoIndex, DWORD dwRemoteUserID);
	//用户配置
	bool OnEventUserConfig(WORD wVideoIndex, DWORD dwRemoteUserID, tagVideoNetwordInfo * pVideoNetwordInfo);
	//显示视频
	bool OnShowLocalVD(bool bShow);
	//更新用户
	bool OnUpdateUserItem( WORD wVideoIndex, BYTE cbUserStatus, DWORD dwRemoteUserID );

	//静态函数
public:
	//获取实例
	static CVideoServiceManager * GetInstance() { return m_pVideoServiceManager; }
};

//////////////////////////////////////////////////////////////////////////

#endif
