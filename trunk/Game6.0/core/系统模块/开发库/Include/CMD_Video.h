#ifndef CMD_VIDEO_HEAD_FILE
#define CMD_VIDEO_HEAD_FILE

//////////////////////////////////////////////////////////////////////////

#define MDM_GF_VIDEO				200									//视频通道

#define SUB_GF_C_VIDEO_CONFIG		1									//视频配置

#define SUB_GF_S_VIDEO_CONFIG		100									//视频配置

//////////////////////////////////////////////////////////////////////////

//视频配置
struct CMD_C_VideoConfig
{
	//连接信息
	WORD							wNatPort;							//网络端口
	WORD							wLocalPort;							//网络端口
	DWORD							dwNatAddr;							//网络地址
	DWORD							dwLocalAddr;						//本地地址

	//用户标识
	DWORD							dwRemoteUserID;						//远程用户
};

//视频配置
struct CMD_S_VideoConfig
{
	//连接信息
	WORD							wNatPort;							//网络端口
	WORD							wLocalPort;							//网络端口
	DWORD							dwNatAddr;							//网络地址
	DWORD							dwLocalAddr;						//本地地址

	//用户标识
	DWORD							dwLocalUserID;						//本地用户
};

//////////////////////////////////////////////////////////////////////////

#endif