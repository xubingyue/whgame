USE [master]
GO
/****** 对象:  Database [GameTreasureDB]    脚本日期: 01/23/2008 14:58:13 ******/
IF NOT EXISTS (SELECT name FROM master.dbo.sysdatabases WHERE name = N'GameTreasureDB')
BEGIN
CREATE DATABASE [GameTreasureDB]
END

GO
ALTER DATABASE [GameTreasureDB] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [GameTreasureDB] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [GameTreasureDB] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [GameTreasureDB] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [GameTreasureDB] SET ARITHABORT OFF 
GO
ALTER DATABASE [GameTreasureDB] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [GameTreasureDB] SET AUTO_CREATE_STATISTICS ON 
GO
ALTER DATABASE [GameTreasureDB] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [GameTreasureDB] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [GameTreasureDB] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [GameTreasureDB] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [GameTreasureDB] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [GameTreasureDB] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [GameTreasureDB] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [GameTreasureDB] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [GameTreasureDB] SET  READ_WRITE 
GO
ALTER DATABASE [GameTreasureDB] SET RECOVERY FULL 
GO
ALTER DATABASE [GameTreasureDB] SET  MULTI_USER 
GO
if ( ((@@microsoftversion / power(2, 24) = 8) and (@@microsoftversion & 0xffff >= 760)) or 
		(@@microsoftversion / power(2, 24) >= 9) )begin 
	exec dbo.sp_dboption @dbname =  N'GameTreasureDB', @optname = 'db chaining', @optvalue = 'OFF'
 end

USE [GameTreasureDB]
GO
/****** 对象:  Table [dbo].[AndroidUserInfo]    脚本日期: 01/23/2008 14:58:23 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[dbo].[AndroidUserInfo]') AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
BEGIN
CREATE TABLE [dbo].[AndroidUserInfo](
	[UserID] [int] NOT NULL,
	[Nullity] [bit] NOT NULL CONSTRAINT [DF_AndroidUserInfo_Nullity]  DEFAULT ((0)),
	[KindID] [int] NOT NULL CONSTRAINT [DF_AndroidUserInfo_KindID]  DEFAULT ((0)),
	[ServerID] [int] NOT NULL CONSTRAINT [DF_AndroidUserInfo_ServerID]  DEFAULT ((0)),
	[CreateDate] [datetime] NOT NULL CONSTRAINT [DF_AndroidUserInfo_CreateDate]  DEFAULT (getdate()),
	[AndroidNote] [nvarchar](32) NOT NULL CONSTRAINT [DF_AndroidUserInfo_AndroidNote]  DEFAULT (''),
 CONSTRAINT [PK_AndroidUserInfo] PRIMARY KEY CLUSTERED 
(
	[UserID] ASC,
	[KindID] ASC,
	[ServerID] ASC
)
)
END
GO

/****** 对象:  Index [IX_AndroidUserInfo_CreateDate]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[AndroidUserInfo]') AND name = N'IX_AndroidUserInfo_CreateDate')
CREATE NONCLUSTERED INDEX [IX_AndroidUserInfo_CreateDate] ON [dbo].[AndroidUserInfo] 
(
	[CreateDate] ASC
)
GO

/****** 对象:  Index [IX_AndroidUserInfo_KindID]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[AndroidUserInfo]') AND name = N'IX_AndroidUserInfo_KindID')
CREATE NONCLUSTERED INDEX [IX_AndroidUserInfo_KindID] ON [dbo].[AndroidUserInfo] 
(
	[KindID] ASC
)
GO

/****** 对象:  Index [IX_AndroidUserInfo_ServerID]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[AndroidUserInfo]') AND name = N'IX_AndroidUserInfo_ServerID')
CREATE NONCLUSTERED INDEX [IX_AndroidUserInfo_ServerID] ON [dbo].[AndroidUserInfo] 
(
	[ServerID] ASC
)
GO

/****** 对象:  Index [IX_AndroidUserInfo_UserID]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[AndroidUserInfo]') AND name = N'IX_AndroidUserInfo_UserID')
CREATE NONCLUSTERED INDEX [IX_AndroidUserInfo_UserID] ON [dbo].[AndroidUserInfo] 
(
	[UserID] ASC
)
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AndroidUserInfo', N'COLUMN',N'UserID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AndroidUserInfo', @level2type=N'COLUMN',@level2name=N'UserID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AndroidUserInfo', N'COLUMN',N'Nullity'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'禁止服务' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AndroidUserInfo', @level2type=N'COLUMN',@level2name=N'Nullity'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AndroidUserInfo', N'COLUMN',N'KindID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'类型标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AndroidUserInfo', @level2type=N'COLUMN',@level2name=N'KindID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AndroidUserInfo', N'COLUMN',N'ServerID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'房间标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AndroidUserInfo', @level2type=N'COLUMN',@level2name=N'ServerID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AndroidUserInfo', N'COLUMN',N'CreateDate'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'创建日期' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AndroidUserInfo', @level2type=N'COLUMN',@level2name=N'CreateDate'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AndroidUserInfo', N'COLUMN',N'AndroidNote'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'备注信息' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AndroidUserInfo', @level2type=N'COLUMN',@level2name=N'AndroidNote'
GO
/****** 对象:  Table [dbo].[ConfineAddress]    脚本日期: 01/23/2008 14:58:23 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[dbo].[ConfineAddress]') AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
BEGIN
CREATE TABLE [dbo].[ConfineAddress](
	[AddrString] [nvarchar](15) NOT NULL,
	[EnjoinLogon] [bit] NOT NULL CONSTRAINT [DF_AddrConfineRule_EnjoinLogon]  DEFAULT ((0)),
	[EnjoinOverDate] [datetime] NOT NULL,
	[CollectDate] [datetime] NOT NULL CONSTRAINT [DF_AddrConfineRule_CollectDate]  DEFAULT (getdate()),
	[CollectNote] [nvarchar](32) NOT NULL CONSTRAINT [DF_AddrConfineRule_CollectNote]  DEFAULT (''),
 CONSTRAINT [PK_ConfineAddress_AddrString] PRIMARY KEY CLUSTERED 
(
	[AddrString] ASC
)
)
END
GO

/****** 对象:  Index [IX_ConfineAddress_CollectDate]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[ConfineAddress]') AND name = N'IX_ConfineAddress_CollectDate')
CREATE NONCLUSTERED INDEX [IX_ConfineAddress_CollectDate] ON [dbo].[ConfineAddress] 
(
	[CollectDate] ASC
)
GO

/****** 对象:  Index [IX_ConfineAddress_EnjoinOverDate]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[ConfineAddress]') AND name = N'IX_ConfineAddress_EnjoinOverDate')
CREATE NONCLUSTERED INDEX [IX_ConfineAddress_EnjoinOverDate] ON [dbo].[ConfineAddress] 
(
	[EnjoinOverDate] ASC
)
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ConfineAddress', N'COLUMN',N'AddrString'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'地址字符' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'AddrString'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ConfineAddress', N'COLUMN',N'EnjoinLogon'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'限制登陆' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'EnjoinLogon'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ConfineAddress', N'COLUMN',N'EnjoinOverDate'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'过期时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'EnjoinOverDate'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ConfineAddress', N'COLUMN',N'CollectDate'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'收集日期' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'CollectDate'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ConfineAddress', N'COLUMN',N'CollectNote'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'输入备注' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'CollectNote'
GO
/****** 对象:  Table [dbo].[ConfineMachine]    脚本日期: 01/23/2008 14:58:23 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[dbo].[ConfineMachine]') AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
BEGIN
CREATE TABLE [dbo].[ConfineMachine](
	[MachineSerial] [nchar](32) NOT NULL,
	[EnjoinLogon] [bit] NOT NULL CONSTRAINT [DF_MachineConfineRule_EnjoinLogon]  DEFAULT ((0)),
	[EnjoinRegister] [bit] NOT NULL CONSTRAINT [DF_MachineConfineRule_EnjoinRegister]  DEFAULT ((0)),
	[EnjoinOverDate] [datetime] NOT NULL,
	[CollectDate] [datetime] NOT NULL CONSTRAINT [DF_MachineConfineRule_CollectDate]  DEFAULT (getdate()),
	[CollectNote] [nvarchar](32) NOT NULL CONSTRAINT [DF_MachineConfineRule_CollectNote]  DEFAULT (''),
 CONSTRAINT [PK_MachineConfineRule_MachineSerial] PRIMARY KEY CLUSTERED 
(
	[MachineSerial] ASC
)
)
END
GO

/****** 对象:  Index [IX_MachineConfineRule_CollectDate]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[ConfineMachine]') AND name = N'IX_MachineConfineRule_CollectDate')
CREATE NONCLUSTERED INDEX [IX_MachineConfineRule_CollectDate] ON [dbo].[ConfineMachine] 
(
	[CollectDate] ASC
)
GO

/****** 对象:  Index [IX_MachineConfineRule_EnjoinOverDate]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[ConfineMachine]') AND name = N'IX_MachineConfineRule_EnjoinOverDate')
CREATE NONCLUSTERED INDEX [IX_MachineConfineRule_EnjoinOverDate] ON [dbo].[ConfineMachine] 
(
	[EnjoinOverDate] ASC
)
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ConfineMachine', N'COLUMN',N'MachineSerial'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'机器序列' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineMachine', @level2type=N'COLUMN',@level2name=N'MachineSerial'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ConfineMachine', N'COLUMN',N'EnjoinLogon'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'限制登录' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineMachine', @level2type=N'COLUMN',@level2name=N'EnjoinLogon'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ConfineMachine', N'COLUMN',N'EnjoinRegister'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'限制注册' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineMachine', @level2type=N'COLUMN',@level2name=N'EnjoinRegister'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ConfineMachine', N'COLUMN',N'EnjoinOverDate'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'过期时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineMachine', @level2type=N'COLUMN',@level2name=N'EnjoinOverDate'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ConfineMachine', N'COLUMN',N'CollectDate'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'收集日期' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineMachine', @level2type=N'COLUMN',@level2name=N'CollectDate'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ConfineMachine', N'COLUMN',N'CollectNote'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'输入备注' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineMachine', @level2type=N'COLUMN',@level2name=N'CollectNote'
GO
/****** 对象:  Table [dbo].[GameScoreInfo]    脚本日期: 01/23/2008 14:58:23 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[dbo].[GameScoreInfo]') AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
BEGIN
CREATE TABLE [dbo].[GameScoreInfo](
	[UserID] [int] NOT NULL,
	[Score] [bigint] NOT NULL CONSTRAINT [DF_GameScore_Score]  DEFAULT ((100000)),
	[Revenue] [bigint] NOT NULL CONSTRAINT [DF_GameScoreInfo_GameTax]  DEFAULT ((0)),
	[InsureScore] [bigint] NOT NULL CONSTRAINT [DF_GameScoreInfo_InsureScore]  DEFAULT ((0)),
	[WinCount] [int] NOT NULL CONSTRAINT [DF_GameScore_WinCount]  DEFAULT ((0)),
	[LostCount] [int] NOT NULL CONSTRAINT [DF_GameScore_LostCount]  DEFAULT ((0)),
	[DrawCount] [int] NOT NULL CONSTRAINT [DF_GameScore_DrawCount]  DEFAULT ((0)),
	[FleeCount] [int] NOT NULL CONSTRAINT [DF_GameScore_FleeCount]  DEFAULT ((0)),
	[UserRight] [int] NOT NULL CONSTRAINT [DF_GameScoreInfo_UserRight]  DEFAULT ((0)),
	[MasterRight] [int] NOT NULL CONSTRAINT [DF_GameScoreInfo_MasterRight]  DEFAULT ((0)),
	[MasterOrder] [tinyint] NOT NULL CONSTRAINT [DF_GameScoreInfo_MasterOrder]  DEFAULT ((0)),
	[RegisterIP] [nvarchar](15) NOT NULL,
	[LastLogonIP] [nvarchar](15) NOT NULL,
	[RegisterDate] [datetime] NOT NULL CONSTRAINT [DF_GameScore_RegisterDate]  DEFAULT (getdate()),
	[LastLogonDate] [datetime] NOT NULL CONSTRAINT [DF_GameScore_LastLogonDate]  DEFAULT (getdate()),
	[AllLogonTimes] [int] NOT NULL CONSTRAINT [DF_GameScore_AllLogonTimes]  DEFAULT ((0)),
	[PlayTimeCount] [int] NOT NULL CONSTRAINT [DF_GameScore_PlayTimeCount_1]  DEFAULT ((0)),
	[OnLineTimeCount] [int] NOT NULL CONSTRAINT [DF_GameScore_OnLineTimeCount]  DEFAULT ((0)),
 CONSTRAINT [PK_GameScore] PRIMARY KEY CLUSTERED 
(
	[UserID] ASC
)
)
END
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameScoreInfo', N'COLUMN',N'UserID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户 ID' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'UserID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameScoreInfo', N'COLUMN',N'Score'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户积分（货币）' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'Score'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameScoreInfo', N'COLUMN',N'Revenue'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'游戏税收' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'Revenue'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameScoreInfo', N'COLUMN',N'InsureScore'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'银行金币' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'InsureScore'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameScoreInfo', N'COLUMN',N'WinCount'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'胜局数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'WinCount'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameScoreInfo', N'COLUMN',N'LostCount'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'输局数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'LostCount'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameScoreInfo', N'COLUMN',N'DrawCount'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'和局数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'DrawCount'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameScoreInfo', N'COLUMN',N'FleeCount'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'逃局数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'FleeCount'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameScoreInfo', N'COLUMN',N'UserRight'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户权限' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'UserRight'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameScoreInfo', N'COLUMN',N'MasterRight'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'管理权限' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'MasterRight'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameScoreInfo', N'COLUMN',N'MasterOrder'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'管理等级' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'MasterOrder'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameScoreInfo', N'COLUMN',N'RegisterIP'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'注册 IP' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'RegisterIP'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameScoreInfo', N'COLUMN',N'LastLogonIP'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'上次登陆 IP' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'LastLogonIP'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameScoreInfo', N'COLUMN',N'RegisterDate'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'注册时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'RegisterDate'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameScoreInfo', N'COLUMN',N'LastLogonDate'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'上次登陆时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'LastLogonDate'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameScoreInfo', N'COLUMN',N'AllLogonTimes'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'总登陆次数' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'AllLogonTimes'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameScoreInfo', N'COLUMN',N'PlayTimeCount'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'游戏时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'PlayTimeCount'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameScoreInfo', N'COLUMN',N'OnLineTimeCount'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'在线时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'OnLineTimeCount'
GO
/****** 对象:  Table [dbo].[GameScoreLocker]    脚本日期: 01/23/2008 14:58:23 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[dbo].[GameScoreLocker]') AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
BEGIN
CREATE TABLE [dbo].[GameScoreLocker](
	[UserID] [int] NOT NULL,
	[KindID] [int] NOT NULL,
	[ServerID] [int] NOT NULL,
	[CollectDate] [datetime] NOT NULL CONSTRAINT [DF_GameScoreLocker_CollectDate]  DEFAULT (getdate()),
 CONSTRAINT [PK_GameScoreLocker] PRIMARY KEY CLUSTERED 
(
	[UserID] ASC,
	[ServerID] ASC,
	[KindID] ASC
)
)
END
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameScoreLocker', N'COLUMN',N'UserID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户索引' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreLocker', @level2type=N'COLUMN',@level2name=N'UserID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameScoreLocker', N'COLUMN',N'KindID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'类型标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreLocker', @level2type=N'COLUMN',@level2name=N'KindID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameScoreLocker', N'COLUMN',N'ServerID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'房间索引' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreLocker', @level2type=N'COLUMN',@level2name=N'ServerID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameScoreLocker', N'COLUMN',N'CollectDate'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'录入日期' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreLocker', @level2type=N'COLUMN',@level2name=N'CollectDate'
GO
/****** 对象:  Table [dbo].[RecordGameScore]    脚本日期: 01/23/2008 14:58:23 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[dbo].[RecordGameScore]') AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
BEGIN
CREATE TABLE [dbo].[RecordGameScore](
	[RecordID] [int] IDENTITY(1,1) NOT NULL,
	[KindID] [int] NOT NULL,
	[ServerID] [int] NOT NULL,
	[TableID] [int] NOT NULL,
	[WasteCount] [bigint] NOT NULL,
	[RevenueCount] [bigint] NOT NULL,
	[PlayTimeCount] [int] NOT NULL,
	[UserID1] [int] NOT NULL CONSTRAINT [DF_GameScoreRecord_UserID1]  DEFAULT ((0)),
	[GameScore1] [bigint] NOT NULL CONSTRAINT [DF_GameScoreRecord_GameScore1]  DEFAULT ((0)),
	[UserID2] [int] NOT NULL CONSTRAINT [DF_GameScoreRecord_UserID2]  DEFAULT ((0)),
	[GameScore2] [bigint] NOT NULL CONSTRAINT [DF_GameScoreRecord_GameScore2]  DEFAULT ((0)),
	[UserID3] [int] NOT NULL CONSTRAINT [DF_GameScoreRecord_UserID3]  DEFAULT ((0)),
	[GameScore3] [bigint] NOT NULL CONSTRAINT [DF_GameScoreRecord_GameScore3]  DEFAULT ((0)),
	[UserID4] [int] NOT NULL CONSTRAINT [DF_GameScoreRecord_UserID4]  DEFAULT ((0)),
	[GameScore4] [bigint] NOT NULL CONSTRAINT [DF_GameScoreRecord_GameScore4]  DEFAULT ((0)),
	[UserID5] [int] NOT NULL CONSTRAINT [DF_GameScoreRecord_UserID5]  DEFAULT ((0)),
	[GameScore5] [bigint] NOT NULL CONSTRAINT [DF_GameScoreRecord_GameScore5]  DEFAULT ((0)),
	[UserID6] [int] NOT NULL CONSTRAINT [DF_GameScoreRecord_UserID6]  DEFAULT ((0)),
	[GameScore6] [bigint] NOT NULL CONSTRAINT [DF_GameScoreRecord_GameScore6]  DEFAULT ((0)),
	[UserID7] [int] NOT NULL CONSTRAINT [DF_GameScoreRecord_UserID7]  DEFAULT ((0)),
	[GameScore7] [bigint] NOT NULL CONSTRAINT [DF_GameScoreRecord_GameScore7]  DEFAULT ((0)),
	[UserID8] [int] NOT NULL CONSTRAINT [DF_GameScoreRecord_UserID8]  DEFAULT ((0)),
	[GameScore8] [bigint] NOT NULL CONSTRAINT [DF_GameScoreRecord_GameScore8]  DEFAULT ((0)),
	[RecordDate] [datetime] NOT NULL CONSTRAINT [DF_GameScoreRecord_RecordDate]  DEFAULT (getdate()),
 CONSTRAINT [PK_GameScoreRecord_RecordID] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
)
)
END
GO

/****** 对象:  Index [IX_GameScoreRecord_KindID]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[RecordGameScore]') AND name = N'IX_GameScoreRecord_KindID')
CREATE NONCLUSTERED INDEX [IX_GameScoreRecord_KindID] ON [dbo].[RecordGameScore] 
(
	[KindID] ASC
)
GO

/****** 对象:  Index [IX_GameScoreRecord_RecordDate]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[RecordGameScore]') AND name = N'IX_GameScoreRecord_RecordDate')
CREATE NONCLUSTERED INDEX [IX_GameScoreRecord_RecordDate] ON [dbo].[RecordGameScore] 
(
	[RecordDate] ASC
)
GO

/****** 对象:  Index [IX_GameScoreRecord_ServerID]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[RecordGameScore]') AND name = N'IX_GameScoreRecord_ServerID')
CREATE NONCLUSTERED INDEX [IX_GameScoreRecord_ServerID] ON [dbo].[RecordGameScore] 
(
	[ServerID] ASC
)
GO

/****** 对象:  Index [IX_GameScoreRecord_TableID]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[RecordGameScore]') AND name = N'IX_GameScoreRecord_TableID')
CREATE NONCLUSTERED INDEX [IX_GameScoreRecord_TableID] ON [dbo].[RecordGameScore] 
(
	[TableID] ASC
)
GO

/****** 对象:  Index [IX_GameScoreRecord_UserID1]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[RecordGameScore]') AND name = N'IX_GameScoreRecord_UserID1')
CREATE NONCLUSTERED INDEX [IX_GameScoreRecord_UserID1] ON [dbo].[RecordGameScore] 
(
	[UserID1] ASC
)
GO

/****** 对象:  Index [IX_GameScoreRecord_UserID2]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[RecordGameScore]') AND name = N'IX_GameScoreRecord_UserID2')
CREATE NONCLUSTERED INDEX [IX_GameScoreRecord_UserID2] ON [dbo].[RecordGameScore] 
(
	[UserID2] ASC
)
GO

/****** 对象:  Index [IX_GameScoreRecord_UserID3]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[RecordGameScore]') AND name = N'IX_GameScoreRecord_UserID3')
CREATE NONCLUSTERED INDEX [IX_GameScoreRecord_UserID3] ON [dbo].[RecordGameScore] 
(
	[UserID3] ASC
)
GO

/****** 对象:  Index [IX_GameScoreRecord_UserID4]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[RecordGameScore]') AND name = N'IX_GameScoreRecord_UserID4')
CREATE NONCLUSTERED INDEX [IX_GameScoreRecord_UserID4] ON [dbo].[RecordGameScore] 
(
	[UserID4] ASC
)
GO

/****** 对象:  Index [IX_GameScoreRecord_UserID5]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[RecordGameScore]') AND name = N'IX_GameScoreRecord_UserID5')
CREATE NONCLUSTERED INDEX [IX_GameScoreRecord_UserID5] ON [dbo].[RecordGameScore] 
(
	[UserID5] ASC
)
GO

/****** 对象:  Index [IX_GameScoreRecord_UserID6]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[RecordGameScore]') AND name = N'IX_GameScoreRecord_UserID6')
CREATE NONCLUSTERED INDEX [IX_GameScoreRecord_UserID6] ON [dbo].[RecordGameScore] 
(
	[UserID6] ASC
)
GO

/****** 对象:  Index [IX_GameScoreRecord_UserID7]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[RecordGameScore]') AND name = N'IX_GameScoreRecord_UserID7')
CREATE NONCLUSTERED INDEX [IX_GameScoreRecord_UserID7] ON [dbo].[RecordGameScore] 
(
	[UserID7] ASC
)
GO

/****** 对象:  Index [IX_GameScoreRecord_UserID8]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[RecordGameScore]') AND name = N'IX_GameScoreRecord_UserID8')
CREATE NONCLUSTERED INDEX [IX_GameScoreRecord_UserID8] ON [dbo].[RecordGameScore] 
(
	[UserID8] ASC
)
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordGameScore', N'COLUMN',N'RecordID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'记录标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'RecordID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordGameScore', N'COLUMN',N'KindID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'类型标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'KindID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordGameScore', N'COLUMN',N'ServerID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'房间标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'ServerID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordGameScore', N'COLUMN',N'TableID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'桌子号码' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'TableID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordGameScore', N'COLUMN',N'WasteCount'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'损耗数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'WasteCount'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordGameScore', N'COLUMN',N'RevenueCount'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'税收数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'RevenueCount'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordGameScore', N'COLUMN',N'PlayTimeCount'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'游戏时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'PlayTimeCount'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordGameScore', N'COLUMN',N'UserID1'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'UserID1'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordGameScore', N'COLUMN',N'GameScore1'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'游戏积分' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'GameScore1'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordGameScore', N'COLUMN',N'UserID2'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'UserID2'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordGameScore', N'COLUMN',N'GameScore2'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'游戏积分' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'GameScore2'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordGameScore', N'COLUMN',N'UserID3'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'UserID3'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordGameScore', N'COLUMN',N'GameScore3'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'游戏积分' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'GameScore3'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordGameScore', N'COLUMN',N'UserID4'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'UserID4'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordGameScore', N'COLUMN',N'GameScore4'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'游戏积分' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'GameScore4'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordGameScore', N'COLUMN',N'UserID5'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'UserID5'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordGameScore', N'COLUMN',N'GameScore5'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'游戏积分' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'GameScore5'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordGameScore', N'COLUMN',N'UserID6'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'UserID6'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordGameScore', N'COLUMN',N'GameScore6'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'游戏积分' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'GameScore6'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordGameScore', N'COLUMN',N'UserID7'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'UserID7'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordGameScore', N'COLUMN',N'GameScore7'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'游戏积分' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'GameScore7'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordGameScore', N'COLUMN',N'UserID8'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'UserID8'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordGameScore', N'COLUMN',N'GameScore8'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'游戏积分' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'GameScore8'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordGameScore', N'COLUMN',N'RecordDate'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'记录时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'RecordDate'
GO
/****** 对象:  Table [dbo].[RecordUserEnter]    脚本日期: 01/23/2008 14:58:23 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[dbo].[RecordUserEnter]') AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
BEGIN
CREATE TABLE [dbo].[RecordUserEnter](
	[UserID] [int] NOT NULL,
	[Score] [bigint] NOT NULL,
	[KindID] [int] NOT NULL,
	[ClientIP] [nvarchar](15) NOT NULL,
	[ServerID] [int] NOT NULL,
	[EnterTime] [datetime] NOT NULL CONSTRAINT [DF_RecordUserEnter_EnterTime]  DEFAULT (getdate())
)
END
GO

/****** 对象:  Index [IX_RecordUserEnter_EnterTime]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[RecordUserEnter]') AND name = N'IX_RecordUserEnter_EnterTime')
CREATE NONCLUSTERED INDEX [IX_RecordUserEnter_EnterTime] ON [dbo].[RecordUserEnter] 
(
	[EnterTime] ASC
)
GO

/****** 对象:  Index [IX_RecordUserEnter_KindID]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[RecordUserEnter]') AND name = N'IX_RecordUserEnter_KindID')
CREATE NONCLUSTERED INDEX [IX_RecordUserEnter_KindID] ON [dbo].[RecordUserEnter] 
(
	[KindID] ASC
)
GO

/****** 对象:  Index [IX_RecordUserEnter_ServerID]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[RecordUserEnter]') AND name = N'IX_RecordUserEnter_ServerID')
CREATE NONCLUSTERED INDEX [IX_RecordUserEnter_ServerID] ON [dbo].[RecordUserEnter] 
(
	[ServerID] ASC
)
GO

/****** 对象:  Index [IX_RecordUserEnter_UserID]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[RecordUserEnter]') AND name = N'IX_RecordUserEnter_UserID')
CREATE NONCLUSTERED INDEX [IX_RecordUserEnter_UserID] ON [dbo].[RecordUserEnter] 
(
	[UserID] ASC
)
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordUserEnter', N'COLUMN',N'UserID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserEnter', @level2type=N'COLUMN',@level2name=N'UserID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordUserEnter', N'COLUMN',N'Score'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'积分数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserEnter', @level2type=N'COLUMN',@level2name=N'Score'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordUserEnter', N'COLUMN',N'KindID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'类型标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserEnter', @level2type=N'COLUMN',@level2name=N'KindID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordUserEnter', N'COLUMN',N'ClientIP'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'登录地址' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserEnter', @level2type=N'COLUMN',@level2name=N'ClientIP'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordUserEnter', N'COLUMN',N'ServerID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'房间标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserEnter', @level2type=N'COLUMN',@level2name=N'ServerID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordUserEnter', N'COLUMN',N'EnterTime'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'进入时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserEnter', @level2type=N'COLUMN',@level2name=N'EnterTime'
GO
/****** 对象:  Table [dbo].[RecordUserLeave]    脚本日期: 01/23/2008 14:58:23 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[dbo].[RecordUserLeave]') AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
BEGIN
CREATE TABLE [dbo].[RecordUserLeave](
	[UserID] [int] NOT NULL,
	[Score] [bigint] NOT NULL,
	[Revenue] [bigint] NOT NULL,
	[KindID] [int] NOT NULL,
	[ServerID] [int] NOT NULL,
	[PlayTimeCount] [int] NOT NULL,
	[OnLineTimeCount] [int] NOT NULL,
	[LeaveTime] [datetime] NOT NULL CONSTRAINT [DF_RecordUserLeave_LeaveTime]  DEFAULT (getdate())
)
END
GO

/****** 对象:  Index [IX_RecordUserLeave_KindID]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[RecordUserLeave]') AND name = N'IX_RecordUserLeave_KindID')
CREATE NONCLUSTERED INDEX [IX_RecordUserLeave_KindID] ON [dbo].[RecordUserLeave] 
(
	[KindID] ASC
)
GO

/****** 对象:  Index [IX_RecordUserLeave_LeaveTime]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[RecordUserLeave]') AND name = N'IX_RecordUserLeave_LeaveTime')
CREATE NONCLUSTERED INDEX [IX_RecordUserLeave_LeaveTime] ON [dbo].[RecordUserLeave] 
(
	[LeaveTime] ASC
)
GO

/****** 对象:  Index [IX_RecordUserLeave_ServerID]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[RecordUserLeave]') AND name = N'IX_RecordUserLeave_ServerID')
CREATE NONCLUSTERED INDEX [IX_RecordUserLeave_ServerID] ON [dbo].[RecordUserLeave] 
(
	[ServerID] ASC
)
GO

/****** 对象:  Index [IX_RecordUserLeave_UserID]    脚本日期: 01/23/2008 14:58:23 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[RecordUserLeave]') AND name = N'IX_RecordUserLeave_UserID')
CREATE NONCLUSTERED INDEX [IX_RecordUserLeave_UserID] ON [dbo].[RecordUserLeave] 
(
	[UserID] ASC
)
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordUserLeave', N'COLUMN',N'UserID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLeave', @level2type=N'COLUMN',@level2name=N'UserID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordUserLeave', N'COLUMN',N'Score'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'离开积分' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLeave', @level2type=N'COLUMN',@level2name=N'Score'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordUserLeave', N'COLUMN',N'Revenue'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'税收数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLeave', @level2type=N'COLUMN',@level2name=N'Revenue'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordUserLeave', N'COLUMN',N'KindID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'类型标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLeave', @level2type=N'COLUMN',@level2name=N'KindID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordUserLeave', N'COLUMN',N'ServerID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'房间标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLeave', @level2type=N'COLUMN',@level2name=N'ServerID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordUserLeave', N'COLUMN',N'PlayTimeCount'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'游戏时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLeave', @level2type=N'COLUMN',@level2name=N'PlayTimeCount'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordUserLeave', N'COLUMN',N'OnLineTimeCount'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'在线时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLeave', @level2type=N'COLUMN',@level2name=N'OnLineTimeCount'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'RecordUserLeave', N'COLUMN',N'LeaveTime'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'离开时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLeave', @level2type=N'COLUMN',@level2name=N'LeaveTime'
GO
/****** 对象:  Table [dbo].[SystemStreamInfo]    脚本日期: 01/23/2008 14:58:23 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[dbo].[SystemStreamInfo]') AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
BEGIN
CREATE TABLE [dbo].[SystemStreamInfo](
	[DateID] [int] NOT NULL,
	[KindID] [int] NOT NULL,
	[ServerID] [int] NOT NULL,
	[LogonCount] [int] NOT NULL CONSTRAINT [DF_TABLE1_LogonCount]  DEFAULT ((0)),
	[LogOutCount] [int] NOT NULL CONSTRAINT [DF_GameEnterInfo_LogonCount1]  DEFAULT ((0)),
	[CollectDate] [datetime] NOT NULL CONSTRAINT [DF_TABLE1_RecordDate]  DEFAULT (getdate()),
 CONSTRAINT [PK_SystemStreamInfo_ID] PRIMARY KEY CLUSTERED 
(
	[DateID] ASC,
	[KindID] ASC,
	[ServerID] ASC
)
)
END
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'SystemStreamInfo', N'COLUMN',N'DateID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'日期标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'DateID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'SystemStreamInfo', N'COLUMN',N'KindID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'类型标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'KindID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'SystemStreamInfo', N'COLUMN',N'ServerID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'房间标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'ServerID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'SystemStreamInfo', N'COLUMN',N'LogonCount'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'进入数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'LogonCount'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'SystemStreamInfo', N'COLUMN',N'LogOutCount'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'离开数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'LogOutCount'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'SystemStreamInfo', N'COLUMN',N'CollectDate'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'录入时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'CollectDate'