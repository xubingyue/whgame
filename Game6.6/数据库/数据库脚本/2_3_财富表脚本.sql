USE [GameTreasureDB]
GO
/****** 对象:  Table [dbo].[AndroidUserInfo]    脚本日期: 12/08/2008 11:52:02 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[AndroidUserInfo](
	[UserID] [int] NOT NULL,
	[Nullity] [bit] NOT NULL CONSTRAINT [DF_AndroidUserInfo_Nullity]  DEFAULT ((0)),
	[KindID] [int] NOT NULL CONSTRAINT [DF_AndroidUserInfo_KindID]  DEFAULT ((0)),
	[ServerID] [int] NOT NULL CONSTRAINT [DF_AndroidUserInfo_ServerID]  DEFAULT ((0)),
	[CreateDate] [datetime] NOT NULL CONSTRAINT [DF_AndroidUserInfo_CreateDate]  DEFAULT (getdate()),
	[AndroidNote] [nvarchar](32) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_AndroidUserInfo_AndroidNote]  DEFAULT (''),
 CONSTRAINT [PK_AndroidUserInfo] PRIMARY KEY CLUSTERED 
(
	[UserID] ASC,
	[KindID] ASC,
	[ServerID] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO

/****** 对象:  Index [IX_AndroidUserInfo_CreateDate]    脚本日期: 12/08/2008 11:52:02 ******/
CREATE NONCLUSTERED INDEX [IX_AndroidUserInfo_CreateDate] ON [dbo].[AndroidUserInfo] 
(
	[CreateDate] ASC
) ON [PRIMARY]
GO

/****** 对象:  Index [IX_AndroidUserInfo_KindID]    脚本日期: 12/08/2008 11:52:02 ******/
CREATE NONCLUSTERED INDEX [IX_AndroidUserInfo_KindID] ON [dbo].[AndroidUserInfo] 
(
	[KindID] ASC
) ON [PRIMARY]
GO

/****** 对象:  Index [IX_AndroidUserInfo_ServerID]    脚本日期: 12/08/2008 11:52:02 ******/
CREATE NONCLUSTERED INDEX [IX_AndroidUserInfo_ServerID] ON [dbo].[AndroidUserInfo] 
(
	[ServerID] ASC
) ON [PRIMARY]
GO

/****** 对象:  Index [IX_AndroidUserInfo_UserID]    脚本日期: 12/08/2008 11:52:02 ******/
CREATE NONCLUSTERED INDEX [IX_AndroidUserInfo_UserID] ON [dbo].[AndroidUserInfo] 
(
	[UserID] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AndroidUserInfo', @level2type=N'COLUMN',@level2name=N'UserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'禁止服务' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AndroidUserInfo', @level2type=N'COLUMN',@level2name=N'Nullity'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'类型标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AndroidUserInfo', @level2type=N'COLUMN',@level2name=N'KindID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'房间标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AndroidUserInfo', @level2type=N'COLUMN',@level2name=N'ServerID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'创建日期' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AndroidUserInfo', @level2type=N'COLUMN',@level2name=N'CreateDate'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'备注信息' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AndroidUserInfo', @level2type=N'COLUMN',@level2name=N'AndroidNote'
GO
/****** 对象:  Table [dbo].[ConfineAddress]    脚本日期: 12/08/2008 11:52:02 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ConfineAddress](
	[AddrString] [nvarchar](15) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[EnjoinLogon] [bit] NOT NULL CONSTRAINT [DF_AddrConfineRule_EnjoinLogon]  DEFAULT ((0)),
	[EnjoinOverDate] [datetime] NOT NULL,
	[CollectDate] [datetime] NOT NULL CONSTRAINT [DF_AddrConfineRule_CollectDate]  DEFAULT (getdate()),
	[CollectNote] [nvarchar](32) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_AddrConfineRule_CollectNote]  DEFAULT (''),
 CONSTRAINT [PK_ConfineAddress_AddrString] PRIMARY KEY CLUSTERED 
(
	[AddrString] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO

/****** 对象:  Index [IX_ConfineAddress_CollectDate]    脚本日期: 12/08/2008 11:52:02 ******/
CREATE NONCLUSTERED INDEX [IX_ConfineAddress_CollectDate] ON [dbo].[ConfineAddress] 
(
	[CollectDate] ASC
) ON [PRIMARY]
GO

/****** 对象:  Index [IX_ConfineAddress_EnjoinOverDate]    脚本日期: 12/08/2008 11:52:02 ******/
CREATE NONCLUSTERED INDEX [IX_ConfineAddress_EnjoinOverDate] ON [dbo].[ConfineAddress] 
(
	[EnjoinOverDate] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'地址字符' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'AddrString'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'限制登陆' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'EnjoinLogon'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'过期时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'EnjoinOverDate'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'收集日期' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'CollectDate'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'输入备注' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'CollectNote'
GO
/****** 对象:  Table [dbo].[ConfineMachine]    脚本日期: 12/08/2008 11:52:02 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ConfineMachine](
	[MachineSerial] [nchar](32) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[EnjoinLogon] [bit] NOT NULL CONSTRAINT [DF_MachineConfineRule_EnjoinLogon]  DEFAULT ((0)),
	[EnjoinRegister] [bit] NOT NULL CONSTRAINT [DF_MachineConfineRule_EnjoinRegister]  DEFAULT ((0)),
	[EnjoinOverDate] [datetime] NOT NULL,
	[CollectDate] [datetime] NOT NULL CONSTRAINT [DF_MachineConfineRule_CollectDate]  DEFAULT (getdate()),
	[CollectNote] [nvarchar](32) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_MachineConfineRule_CollectNote]  DEFAULT (''),
 CONSTRAINT [PK_MachineConfineRule_MachineSerial] PRIMARY KEY CLUSTERED 
(
	[MachineSerial] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO

/****** 对象:  Index [IX_MachineConfineRule_CollectDate]    脚本日期: 12/08/2008 11:52:02 ******/
CREATE NONCLUSTERED INDEX [IX_MachineConfineRule_CollectDate] ON [dbo].[ConfineMachine] 
(
	[CollectDate] ASC
) ON [PRIMARY]
GO

/****** 对象:  Index [IX_MachineConfineRule_EnjoinOverDate]    脚本日期: 12/08/2008 11:52:02 ******/
CREATE NONCLUSTERED INDEX [IX_MachineConfineRule_EnjoinOverDate] ON [dbo].[ConfineMachine] 
(
	[EnjoinOverDate] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'机器序列' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineMachine', @level2type=N'COLUMN',@level2name=N'MachineSerial'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'限制登录' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineMachine', @level2type=N'COLUMN',@level2name=N'EnjoinLogon'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'限制注册' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineMachine', @level2type=N'COLUMN',@level2name=N'EnjoinRegister'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'过期时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineMachine', @level2type=N'COLUMN',@level2name=N'EnjoinOverDate'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'收集日期' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineMachine', @level2type=N'COLUMN',@level2name=N'CollectDate'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'输入备注' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineMachine', @level2type=N'COLUMN',@level2name=N'CollectNote'
GO
/****** 对象:  Table [dbo].[FlowerCate]    脚本日期: 12/08/2008 11:52:02 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[FlowerCate](
	[ID] [int] NOT NULL,
	[Name] [nvarchar](32) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[Price] [int] NOT NULL CONSTRAINT [DF_FlowerCate_Price]  DEFAULT ((0)),
	[SendUserCharm] [int] NOT NULL CONSTRAINT [DF_FlowerCate_SendUserCharm]  DEFAULT ((0)),
	[RcvUserCharm] [int] NOT NULL CONSTRAINT [DF_FlowerCate_RcvUserCharm]  DEFAULT ((0)),
	[Discount] [int] NOT NULL CONSTRAINT [DF_FlowerCate_Discount]  DEFAULT ((0)),
	[Nullity] [bit] NOT NULL CONSTRAINT [DF_FlowerCate_Nullity]  DEFAULT ((0)),
 CONSTRAINT [PK_FlowerCate] PRIMARY KEY CLUSTERED 
(
	[ID] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'鲜花ID' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'FlowerCate', @level2type=N'COLUMN',@level2name=N'ID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'鲜花名称' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'FlowerCate', @level2type=N'COLUMN',@level2name=N'Name'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'鲜花价格' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'FlowerCate', @level2type=N'COLUMN',@level2name=N'Price'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'赠送魅力' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'FlowerCate', @level2type=N'COLUMN',@level2name=N'SendUserCharm'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'接受魅力' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'FlowerCate', @level2type=N'COLUMN',@level2name=N'RcvUserCharm'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'会员折扣' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'FlowerCate', @level2type=N'COLUMN',@level2name=N'Discount'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'禁止标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'FlowerCate', @level2type=N'COLUMN',@level2name=N'Nullity'
GO
/****** 对象:  Table [dbo].[GameScoreInfo]    脚本日期: 12/08/2008 11:52:02 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
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
	[RegisterIP] [nvarchar](15) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[LastLogonIP] [nvarchar](15) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[RegisterDate] [datetime] NOT NULL CONSTRAINT [DF_GameScore_RegisterDate]  DEFAULT (getdate()),
	[LastLogonDate] [datetime] NOT NULL CONSTRAINT [DF_GameScore_LastLogonDate]  DEFAULT (getdate()),
	[AllLogonTimes] [int] NOT NULL CONSTRAINT [DF_GameScore_AllLogonTimes]  DEFAULT ((0)),
	[PlayTimeCount] [int] NOT NULL CONSTRAINT [DF_GameScore_PlayTimeCount_1]  DEFAULT ((0)),
	[OnLineTimeCount] [int] NOT NULL CONSTRAINT [DF_GameScore_OnLineTimeCount]  DEFAULT ((0)),
 CONSTRAINT [PK_GameScore] PRIMARY KEY CLUSTERED 
(
	[UserID] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户 ID' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'UserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户积分（货币）' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'Score'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'游戏税收' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'Revenue'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'银行金币' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'InsureScore'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'胜局数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'WinCount'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'输局数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'LostCount'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'和局数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'DrawCount'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'逃局数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'FleeCount'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户权限' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'UserRight'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'管理权限' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'MasterRight'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'管理等级' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'MasterOrder'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'注册 IP' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'RegisterIP'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'上次登陆 IP' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'LastLogonIP'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'注册时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'RegisterDate'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'上次登陆时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'LastLogonDate'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'总登陆次数' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'AllLogonTimes'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'游戏时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'PlayTimeCount'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'在线时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'OnLineTimeCount'
GO
/****** 对象:  Table [dbo].[GameScoreLocker]    脚本日期: 12/08/2008 11:52:02 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
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
) ON [PRIMARY]
) ON [PRIMARY]

GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户索引' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreLocker', @level2type=N'COLUMN',@level2name=N'UserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'类型标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreLocker', @level2type=N'COLUMN',@level2name=N'KindID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'房间索引' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreLocker', @level2type=N'COLUMN',@level2name=N'ServerID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'录入日期' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreLocker', @level2type=N'COLUMN',@level2name=N'CollectDate'
GO
/****** 对象:  Table [dbo].[GameShopCate]    脚本日期: 12/08/2008 11:52:02 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[GameShopCate](
	[CateID] [int] NOT NULL,
	[CateName] [nvarchar](32) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[PropCount1] [int] NOT NULL CONSTRAINT [DF_GameShopCate_PropCount1]  DEFAULT ((0)),
	[PropCount2] [int] NOT NULL CONSTRAINT [DF_GameShopCate_PropCount2]  DEFAULT ((0)),
	[PropCount3] [int] NOT NULL CONSTRAINT [DF_GameShopCate_PropCount3]  DEFAULT ((0)),
	[PropCount4] [int] NOT NULL CONSTRAINT [DF_GameShopCate_PropCount4]  DEFAULT ((0)),
	[PropCount5] [int] NOT NULL CONSTRAINT [DF_GameShopCate_PropCount5]  DEFAULT ((0)),
	[PropCount6] [int] NOT NULL CONSTRAINT [DF_GameShopCate_PropCount6]  DEFAULT ((0)),
	[PropCount7] [int] NOT NULL CONSTRAINT [DF_GameShopCate_PropCount7]  DEFAULT ((0)),
	[PropCount8] [int] NOT NULL CONSTRAINT [DF_GameShopCate_PropCount8]  DEFAULT ((0)),
	[PropCount9] [int] NOT NULL CONSTRAINT [DF_GameShopCate_PropCount9]  DEFAULT ((0)),
	[PropCount10] [int] NOT NULL CONSTRAINT [DF_GameShopCate_PropCount10]  DEFAULT ((0)),
	[Price1] [int] NOT NULL CONSTRAINT [DF_GameShopCate_Price1]  DEFAULT ((0)),
	[Price2] [int] NOT NULL CONSTRAINT [DF_GameShopCate_Price2]  DEFAULT ((0)),
	[Price3] [int] NOT NULL CONSTRAINT [DF_GameShopCate_Price3]  DEFAULT ((0)),
	[Price4] [int] NOT NULL CONSTRAINT [DF_GameShopCate_Price4]  DEFAULT ((0)),
	[Price5] [int] NOT NULL CONSTRAINT [DF_GameShopCate_Price5]  DEFAULT ((0)),
	[Price6] [int] NOT NULL CONSTRAINT [DF_GameShopCate_Price6]  DEFAULT ((0)),
	[Price7] [int] NOT NULL CONSTRAINT [DF_GameShopCate_Price7]  DEFAULT ((0)),
	[Price8] [int] NOT NULL CONSTRAINT [DF_GameShopCate_Price8]  DEFAULT ((0)),
	[Price9] [int] NOT NULL CONSTRAINT [DF_GameShopCate_Price9]  DEFAULT ((0)),
	[Price10] [int] NOT NULL CONSTRAINT [DF_GameShopCate_Price10]  DEFAULT ((0)),
	[Discount] [int] NOT NULL CONSTRAINT [DF_GameShopCate_Discount]  DEFAULT ((0)),
	[CateNote] [nvarchar](32) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_GameShopCate_CateNote]  DEFAULT (N''),
	[Nullity] [bit] NOT NULL CONSTRAINT [DF_GameShopCate_Nullity]  DEFAULT ((0)),
 CONSTRAINT [PK_GameShopCate] PRIMARY KEY CLUSTERED 
(
	[CateID] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'道具ID' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameShopCate', @level2type=N'COLUMN',@level2name=N'CateID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'道具名称' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameShopCate', @level2type=N'COLUMN',@level2name=N'CateName'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'道具数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameShopCate', @level2type=N'COLUMN',@level2name=N'PropCount1'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'道具数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameShopCate', @level2type=N'COLUMN',@level2name=N'PropCount2'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'道具数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameShopCate', @level2type=N'COLUMN',@level2name=N'PropCount3'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'道具数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameShopCate', @level2type=N'COLUMN',@level2name=N'PropCount4'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'道具数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameShopCate', @level2type=N'COLUMN',@level2name=N'PropCount5'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'道具数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameShopCate', @level2type=N'COLUMN',@level2name=N'PropCount6'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'道具数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameShopCate', @level2type=N'COLUMN',@level2name=N'PropCount7'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'道具数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameShopCate', @level2type=N'COLUMN',@level2name=N'PropCount8'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'道具数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameShopCate', @level2type=N'COLUMN',@level2name=N'PropCount9'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'道具数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameShopCate', @level2type=N'COLUMN',@level2name=N'PropCount10'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'道具价格' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameShopCate', @level2type=N'COLUMN',@level2name=N'Price1'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'道具价格' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameShopCate', @level2type=N'COLUMN',@level2name=N'Price2'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'道具价格' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameShopCate', @level2type=N'COLUMN',@level2name=N'Price3'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'道具价格' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameShopCate', @level2type=N'COLUMN',@level2name=N'Price4'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'道具价格' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameShopCate', @level2type=N'COLUMN',@level2name=N'Price5'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'道具价格' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameShopCate', @level2type=N'COLUMN',@level2name=N'Price6'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'道具价格' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameShopCate', @level2type=N'COLUMN',@level2name=N'Price7'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'道具价格' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameShopCate', @level2type=N'COLUMN',@level2name=N'Price8'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'道具价格' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameShopCate', @level2type=N'COLUMN',@level2name=N'Price9'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'道具价格' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameShopCate', @level2type=N'COLUMN',@level2name=N'Price10'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'会员折扣' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameShopCate', @level2type=N'COLUMN',@level2name=N'Discount'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'备注信息' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameShopCate', @level2type=N'COLUMN',@level2name=N'CateNote'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'禁止标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameShopCate', @level2type=N'COLUMN',@level2name=N'Nullity'
GO
/****** 对象:  Table [dbo].[GameUserShelf]    脚本日期: 12/08/2008 11:52:02 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[GameUserShelf](
	[UserID] [int] NOT NULL,
	[CateID] [int] NOT NULL CONSTRAINT [DF_GameUserShelf_CateID]  DEFAULT ((0)),
	[KindID] [int] NOT NULL CONSTRAINT [DF_GameUserShelf_KindID]  DEFAULT ((0)),
	[PropCount] [bigint] NOT NULL CONSTRAINT [DF_GameUserShelf_UseableTime]  DEFAULT ((0)),
	[UsedFlag] [tinyint] NOT NULL CONSTRAINT [DF_GameUserShelf_UsedFlag]  DEFAULT ((0)),
	[WriteDate] [datetime] NOT NULL CONSTRAINT [DF_GameUserShelf_WriteDate]  DEFAULT (getdate()),
	[ClientIP] [nvarchar](15) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_GameUserShelf_ClientIP]  DEFAULT (N'000.000.000.000')
) ON [PRIMARY]

GO

/****** 对象:  Index [IX_CateID]    脚本日期: 12/08/2008 11:52:02 ******/
CREATE NONCLUSTERED INDEX [IX_CateID] ON [dbo].[GameUserShelf] 
(
	[CateID] ASC
) ON [PRIMARY]
GO

/****** 对象:  Index [IX_UserCateID]    脚本日期: 12/08/2008 11:52:02 ******/
CREATE NONCLUSTERED INDEX [IX_UserCateID] ON [dbo].[GameUserShelf] 
(
	[UserID] ASC,
	[CateID] ASC
) ON [PRIMARY]
GO

/****** 对象:  Index [IX_UserID]    脚本日期: 12/08/2008 11:52:02 ******/
CREATE NONCLUSTERED INDEX [IX_UserID] ON [dbo].[GameUserShelf] 
(
	[UserID] ASC
) ON [PRIMARY]
GO

/****** 对象:  Index [IX_UserPropUsedFlag]    脚本日期: 12/08/2008 11:52:02 ******/
CREATE NONCLUSTERED INDEX [IX_UserPropUsedFlag] ON [dbo].[GameUserShelf] 
(
	[UserID] ASC,
	[UsedFlag] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameUserShelf', @level2type=N'COLUMN',@level2name=N'UserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'类别标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameUserShelf', @level2type=N'COLUMN',@level2name=N'CateID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'使用标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameUserShelf', @level2type=N'COLUMN',@level2name=N'UsedFlag'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'写入时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameUserShelf', @level2type=N'COLUMN',@level2name=N'WriteDate'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'写入地址' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameUserShelf', @level2type=N'COLUMN',@level2name=N'ClientIP'
GO
/****** 对象:  Table [dbo].[RecordExchangeLoveliness]    脚本日期: 12/08/2008 11:52:02 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[RecordExchangeLoveliness](
	[RecordID] [int] IDENTITY(1,1) NOT NULL,
	[UserID] [int] NOT NULL,
	[KindID] [int] NOT NULL,
	[ServerID] [int] NOT NULL,
	[Loveliness] [bigint] NOT NULL CONSTRAINT [DF_RecordExchangeCharmValue_CharmValue]  DEFAULT ((0)),
	[InsureScore] [bigint] NOT NULL CONSTRAINT [DF_RecordExchangeCharmValue_GoldValue]  DEFAULT ((0)),
	[ExchangeDate] [datetime] NOT NULL CONSTRAINT [DF_RecordExchangeCharmValue_ExchangeDate]  DEFAULT (getdate()),
	[ClientIP] [nvarchar](15) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_RecordExchangeCharmValue_ClientIP]  DEFAULT (N'000.000.000.000'),
 CONSTRAINT [PK_RecordExchangeCharmValue] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'记录标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordExchangeLoveliness', @level2type=N'COLUMN',@level2name=N'RecordID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordExchangeLoveliness', @level2type=N'COLUMN',@level2name=N'UserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'游戏标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordExchangeLoveliness', @level2type=N'COLUMN',@level2name=N'KindID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'房间标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordExchangeLoveliness', @level2type=N'COLUMN',@level2name=N'ServerID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户魅力' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordExchangeLoveliness', @level2type=N'COLUMN',@level2name=N'Loveliness'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'兑换金币' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordExchangeLoveliness', @level2type=N'COLUMN',@level2name=N'InsureScore'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'兑换日期' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordExchangeLoveliness', @level2type=N'COLUMN',@level2name=N'ExchangeDate'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'兑换地址' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordExchangeLoveliness', @level2type=N'COLUMN',@level2name=N'ClientIP'
GO
/****** 对象:  Table [dbo].[RecordFlowerGrant]    脚本日期: 12/08/2008 11:52:02 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[RecordFlowerGrant](
	[RecordID] [int] IDENTITY(1,1) NOT NULL,
	[SendUserID] [int] NOT NULL,
	[RcvUserID] [int] NOT NULL,
	[KindID] [int] NOT NULL CONSTRAINT [DF_RecordFlowerGrant_KindID]  DEFAULT ((0)),
	[ServerID] [int] NOT NULL CONSTRAINT [DF_RecordFlowerGrant_ServerID]  DEFAULT ((0)),
	[FlowerName] [nvarchar](32) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[FlowerCount] [int] NOT NULL CONSTRAINT [DF_RecordGiftGrant_FlowerCount]  DEFAULT ((0)),
	[FlowerPay] [bigint] NOT NULL CONSTRAINT [DF_RecordFlowerGrant_GiftPay]  DEFAULT ((0)),
	[SendUserLoveliness] [int] NOT NULL CONSTRAINT [DF_RecordFlowerGrant_SendUserCharm]  DEFAULT ((0)),
	[RcvUserLoveliness] [int] NOT NULL CONSTRAINT [DF_RecordFlowerGrant_RcvUserCharm]  DEFAULT ((0)),
	[GrantIP] [nvarchar](15) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_RecordFlowerGrant_GrantIP]  DEFAULT ('000.000.000.000'),
	[GrantDate] [datetime] NOT NULL CONSTRAINT [DF_RecordFlowerGrant_GrantDate]  DEFAULT (getdate()),
 CONSTRAINT [PK_RecordFlowerGrant] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'流水标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordFlowerGrant', @level2type=N'COLUMN',@level2name=N'RecordID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'赠送者标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordFlowerGrant', @level2type=N'COLUMN',@level2name=N'SendUserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'接受者标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordFlowerGrant', @level2type=N'COLUMN',@level2name=N'RcvUserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'游戏标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordFlowerGrant', @level2type=N'COLUMN',@level2name=N'KindID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'房间标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordFlowerGrant', @level2type=N'COLUMN',@level2name=N'ServerID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'赠送礼物' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordFlowerGrant', @level2type=N'COLUMN',@level2name=N'FlowerName'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'赠送付费' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordFlowerGrant', @level2type=N'COLUMN',@level2name=N'FlowerPay'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'赠送魅力' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordFlowerGrant', @level2type=N'COLUMN',@level2name=N'SendUserLoveliness'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'接受魅力' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordFlowerGrant', @level2type=N'COLUMN',@level2name=N'RcvUserLoveliness'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'赠送地址' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordFlowerGrant', @level2type=N'COLUMN',@level2name=N'GrantIP'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'赠送日期' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordFlowerGrant', @level2type=N'COLUMN',@level2name=N'GrantDate'
GO
/****** 对象:  Table [dbo].[RecordGiftGrant]    脚本日期: 12/08/2008 11:52:02 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[RecordGiftGrant](
	[RecordID] [int] IDENTITY(1,1) NOT NULL,
	[SendUserID] [int] NOT NULL,
	[RcvUserID] [int] NOT NULL,
	[KindID] [int] NOT NULL CONSTRAINT [DF_RecordGoodsGrant_KindID]  DEFAULT ((0)),
	[ServerID] [int] NOT NULL CONSTRAINT [DF_RecordGoodsGrant_ServerID]  DEFAULT ((0)),
	[Gift] [varchar](64) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[GiftPay] [bigint] NOT NULL CONSTRAINT [DF_RecordGoodsGrant_GiftPay]  DEFAULT ((0)),
	[GrantIP] [varchar](15) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_RecordGoodsGrant_GrantIP]  DEFAULT ('000.000.000.000'),
	[GrantDate] [datetime] NOT NULL CONSTRAINT [DF_RecordGoodsGrant_GrantDate]  DEFAULT (getdate()),
 CONSTRAINT [PK_RecordGiftGrant] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'流水标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGiftGrant', @level2type=N'COLUMN',@level2name=N'RecordID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'赠送者标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGiftGrant', @level2type=N'COLUMN',@level2name=N'SendUserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'接受者标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGiftGrant', @level2type=N'COLUMN',@level2name=N'RcvUserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'游戏标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGiftGrant', @level2type=N'COLUMN',@level2name=N'KindID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'房间标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGiftGrant', @level2type=N'COLUMN',@level2name=N'ServerID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'赠送礼物' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGiftGrant', @level2type=N'COLUMN',@level2name=N'Gift'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'赠送付费' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGiftGrant', @level2type=N'COLUMN',@level2name=N'GiftPay'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'赠送地址' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGiftGrant', @level2type=N'COLUMN',@level2name=N'GrantIP'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'赠送日期' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGiftGrant', @level2type=N'COLUMN',@level2name=N'GrantDate'
GO
/****** 对象:  Table [dbo].[RecordInsure]    脚本日期: 12/08/2008 11:52:02 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[RecordInsure](
	[InsureID] [int] IDENTITY(1,1) NOT NULL,
	[KindID] [int] NOT NULL CONSTRAINT [DF_RecordInsure_KindID]  DEFAULT ((0)),
	[ServerID] [int] NOT NULL CONSTRAINT [DF_RecordInsure_ServerID]  DEFAULT ((0)),
	[SourceUserID] [int] NOT NULL CONSTRAINT [DF_InsureTankRecord_SourceUserID_1]  DEFAULT ((0)),
	[SourceGameID] [int] NOT NULL CONSTRAINT [DF_InsureTankRecord_SourceUserID]  DEFAULT ((0)),
	[SourceAccounts] [nvarchar](31) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_InsureTankRecord_SourceAccounts]  DEFAULT (''),
	[TargetUserID] [int] NOT NULL CONSTRAINT [DF_InsureTankRecord_TargetUserID_1]  DEFAULT ((0)),
	[TargetGameID] [int] NOT NULL CONSTRAINT [DF_InsureTankRecord_TargetUserID]  DEFAULT ((0)),
	[TargetAccounts] [nvarchar](31) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_InsureTankRecord_TargetAccounts]  DEFAULT (''),
	[InsureScore] [bigint] NOT NULL CONSTRAINT [DF_InsureTankRecord_CurrentScore]  DEFAULT ((0)),
	[SwapScore] [bigint] NOT NULL CONSTRAINT [DF_InsureTankRecord_TransferScore]  DEFAULT ((0)),
	[Revenue] [bigint] NOT NULL CONSTRAINT [DF_InsureTankRecord_Taxation]  DEFAULT ((0)),
	[TradeType] [tinyint] NOT NULL,
	[ClientIP] [nvarchar](15) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_InsureTankRecord_ClientIP]  DEFAULT ('000.000.000.000'),
	[CollectDate] [datetime] NOT NULL CONSTRAINT [DF_InsureTankRecord_CollectDate]  DEFAULT (getdate()),
	[CollectNote] [nvarchar](63) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_InsureTankRecord_CollectNote]  DEFAULT (''),
 CONSTRAINT [PK_RecordInsure] PRIMARY KEY CLUSTERED 
(
	[InsureID] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO

/****** 对象:  Index [IX_RecordInsure_CollectDate]    脚本日期: 12/08/2008 11:52:02 ******/
CREATE NONCLUSTERED INDEX [IX_RecordInsure_CollectDate] ON [dbo].[RecordInsure] 
(
	[CollectDate] ASC
) ON [PRIMARY]
GO

/****** 对象:  Index [IX_RecordInsure_SourceUserID]    脚本日期: 12/08/2008 11:52:02 ******/
CREATE NONCLUSTERED INDEX [IX_RecordInsure_SourceUserID] ON [dbo].[RecordInsure] 
(
	[SourceUserID] ASC
) ON [PRIMARY]
GO

/****** 对象:  Index [IX_RecordInsure_TargetAccounts]    脚本日期: 12/08/2008 11:52:02 ******/
CREATE NONCLUSTERED INDEX [IX_RecordInsure_TargetAccounts] ON [dbo].[RecordInsure] 
(
	[TargetAccounts] ASC
) ON [PRIMARY]
GO

/****** 对象:  Index [IX_RecordInsure_TargetGameID]    脚本日期: 12/08/2008 11:52:02 ******/
CREATE NONCLUSTERED INDEX [IX_RecordInsure_TargetGameID] ON [dbo].[RecordInsure] 
(
	[TargetGameID] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'流水标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordInsure', @level2type=N'COLUMN',@level2name=N'InsureID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'游戏种类' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordInsure', @level2type=N'COLUMN',@level2name=N'KindID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'房间标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordInsure', @level2type=N'COLUMN',@level2name=N'ServerID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'源用户ID' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordInsure', @level2type=N'COLUMN',@level2name=N'SourceUserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'源用户游戏ID' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordInsure', @level2type=N'COLUMN',@level2name=N'SourceGameID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'源用户帐号' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordInsure', @level2type=N'COLUMN',@level2name=N'SourceAccounts'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'目标用户ID' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordInsure', @level2type=N'COLUMN',@level2name=N'TargetUserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'目标人游戏ID' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordInsure', @level2type=N'COLUMN',@level2name=N'TargetGameID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'目标人帐户' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordInsure', @level2type=N'COLUMN',@level2name=N'TargetAccounts'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'源用户拥有金币数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordInsure', @level2type=N'COLUMN',@level2name=N'InsureScore'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'流通金币数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordInsure', @level2type=N'COLUMN',@level2name=N'SwapScore'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'税收数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordInsure', @level2type=N'COLUMN',@level2name=N'Revenue'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'交易类别,存 1,取 2,转 3' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordInsure', @level2type=N'COLUMN',@level2name=N'TradeType'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'连接地址' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordInsure', @level2type=N'COLUMN',@level2name=N'ClientIP'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'录入时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordInsure', @level2type=N'COLUMN',@level2name=N'CollectDate'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'备注' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordInsure', @level2type=N'COLUMN',@level2name=N'CollectNote'
GO
/****** 对象:  Table [dbo].[RecordPurchaseProp]    脚本日期: 12/08/2008 11:52:02 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[RecordPurchaseProp](
	[RecordID] [int] IDENTITY(1,1) NOT NULL,
	[SendUserID] [int] NOT NULL CONSTRAINT [DF_RecordPurchaseProp_SendUserID]  DEFAULT ((0)),
	[RcvUserID] [int] NOT NULL CONSTRAINT [DF_RecordPurchaseProp_RcvUserID]  DEFAULT ((0)),
	[KindID] [int] NOT NULL CONSTRAINT [DF_RecordPurchaseProp_KindID]  DEFAULT ((0)),
	[ServerID] [int] NOT NULL CONSTRAINT [DF_RecordPurchaseProp_ServerID]  DEFAULT ((0)),
	[CateID] [int] NOT NULL CONSTRAINT [DF_RecordPurchaseProp_CateID]  DEFAULT ((0)),
	[CurCount] [int] NOT NULL CONSTRAINT [DF_RecordPurchaseProp_CurCount]  DEFAULT ((0)),
	[OnceCount] [int] NOT NULL CONSTRAINT [DF_RecordPurchaseProp_OnceCount]  DEFAULT ((0)),
	[PachurseCount] [int] NOT NULL CONSTRAINT [DF_RecordPurchaseProp_PachurseCount]  DEFAULT ((0)),
	[SpendScore] [int] NOT NULL CONSTRAINT [DF_RecordPurchaseProp_SpendScore]  DEFAULT ((0)),
	[ClientIP] [nvarchar](15) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_RecordPurchaseProp_ClientIP]  DEFAULT (N'000.000.000.000'),
	[PurchaseDate] [datetime] NOT NULL CONSTRAINT [DF_RecordPurchaseProp_PurchaseDate]  DEFAULT (getdate()),
 CONSTRAINT [PK_RecordPurchaseProp] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'记录标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordPurchaseProp', @level2type=N'COLUMN',@level2name=N'RecordID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'赠送者ID' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordPurchaseProp', @level2type=N'COLUMN',@level2name=N'SendUserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'接受者ID' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordPurchaseProp', @level2type=N'COLUMN',@level2name=N'RcvUserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'游戏标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordPurchaseProp', @level2type=N'COLUMN',@level2name=N'KindID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'房间标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordPurchaseProp', @level2type=N'COLUMN',@level2name=N'ServerID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'道具类别' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordPurchaseProp', @level2type=N'COLUMN',@level2name=N'CateID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'当前数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordPurchaseProp', @level2type=N'COLUMN',@level2name=N'CurCount'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'单次数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordPurchaseProp', @level2type=N'COLUMN',@level2name=N'OnceCount'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'购买数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordPurchaseProp', @level2type=N'COLUMN',@level2name=N'PachurseCount'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'购买价格' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordPurchaseProp', @level2type=N'COLUMN',@level2name=N'SpendScore'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'购买日期' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordPurchaseProp', @level2type=N'COLUMN',@level2name=N'PurchaseDate'
GO
/****** 对象:  Table [dbo].[RecordUserEnter]    脚本日期: 12/08/2008 11:52:02 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[RecordUserEnter](
	[UserID] [int] NOT NULL,
	[Score] [bigint] NOT NULL,
	[KindID] [int] NOT NULL,
	[ClientIP] [nvarchar](15) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[ServerID] [int] NOT NULL,
	[EnterTime] [datetime] NOT NULL CONSTRAINT [DF_RecordUserEnter_EnterTime]  DEFAULT (getdate())
) ON [PRIMARY]

GO

/****** 对象:  Index [IX_RecordUserEnter_EnterTime]    脚本日期: 12/08/2008 11:52:02 ******/
CREATE NONCLUSTERED INDEX [IX_RecordUserEnter_EnterTime] ON [dbo].[RecordUserEnter] 
(
	[EnterTime] ASC
) ON [PRIMARY]
GO

/****** 对象:  Index [IX_RecordUserEnter_KindID]    脚本日期: 12/08/2008 11:52:02 ******/
CREATE NONCLUSTERED INDEX [IX_RecordUserEnter_KindID] ON [dbo].[RecordUserEnter] 
(
	[KindID] ASC
) ON [PRIMARY]
GO

/****** 对象:  Index [IX_RecordUserEnter_ServerID]    脚本日期: 12/08/2008 11:52:02 ******/
CREATE NONCLUSTERED INDEX [IX_RecordUserEnter_ServerID] ON [dbo].[RecordUserEnter] 
(
	[ServerID] ASC
) ON [PRIMARY]
GO

/****** 对象:  Index [IX_RecordUserEnter_UserID]    脚本日期: 12/08/2008 11:52:02 ******/
CREATE NONCLUSTERED INDEX [IX_RecordUserEnter_UserID] ON [dbo].[RecordUserEnter] 
(
	[UserID] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserEnter', @level2type=N'COLUMN',@level2name=N'UserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'积分数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserEnter', @level2type=N'COLUMN',@level2name=N'Score'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'类型标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserEnter', @level2type=N'COLUMN',@level2name=N'KindID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'登录地址' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserEnter', @level2type=N'COLUMN',@level2name=N'ClientIP'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'房间标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserEnter', @level2type=N'COLUMN',@level2name=N'ServerID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'进入时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserEnter', @level2type=N'COLUMN',@level2name=N'EnterTime'
GO
/****** 对象:  Table [dbo].[RecordUserLeave]    脚本日期: 12/08/2008 11:52:02 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[RecordUserLeave](
	[UserID] [int] NOT NULL,
	[Score] [bigint] NOT NULL,
	[Revenue] [bigint] NOT NULL,
	[KindID] [int] NOT NULL,
	[ServerID] [int] NOT NULL,
	[PlayTimeCount] [int] NOT NULL,
	[OnLineTimeCount] [int] NOT NULL,
	[LeaveTime] [datetime] NOT NULL CONSTRAINT [DF_RecordUserLeave_LeaveTime]  DEFAULT (getdate())
) ON [PRIMARY]

GO

/****** 对象:  Index [IX_RecordUserLeave_KindID]    脚本日期: 12/08/2008 11:52:02 ******/
CREATE NONCLUSTERED INDEX [IX_RecordUserLeave_KindID] ON [dbo].[RecordUserLeave] 
(
	[KindID] ASC
) ON [PRIMARY]
GO

/****** 对象:  Index [IX_RecordUserLeave_LeaveTime]    脚本日期: 12/08/2008 11:52:02 ******/
CREATE NONCLUSTERED INDEX [IX_RecordUserLeave_LeaveTime] ON [dbo].[RecordUserLeave] 
(
	[LeaveTime] ASC
) ON [PRIMARY]
GO

/****** 对象:  Index [IX_RecordUserLeave_ServerID]    脚本日期: 12/08/2008 11:52:02 ******/
CREATE NONCLUSTERED INDEX [IX_RecordUserLeave_ServerID] ON [dbo].[RecordUserLeave] 
(
	[ServerID] ASC
) ON [PRIMARY]
GO

/****** 对象:  Index [IX_RecordUserLeave_UserID]    脚本日期: 12/08/2008 11:52:02 ******/
CREATE NONCLUSTERED INDEX [IX_RecordUserLeave_UserID] ON [dbo].[RecordUserLeave] 
(
	[UserID] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLeave', @level2type=N'COLUMN',@level2name=N'UserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'离开积分' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLeave', @level2type=N'COLUMN',@level2name=N'Score'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'税收数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLeave', @level2type=N'COLUMN',@level2name=N'Revenue'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'类型标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLeave', @level2type=N'COLUMN',@level2name=N'KindID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'房间标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLeave', @level2type=N'COLUMN',@level2name=N'ServerID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'游戏时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLeave', @level2type=N'COLUMN',@level2name=N'PlayTimeCount'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'在线时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLeave', @level2type=N'COLUMN',@level2name=N'OnLineTimeCount'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'离开时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLeave', @level2type=N'COLUMN',@level2name=N'LeaveTime'
GO
/****** 对象:  Table [dbo].[RecordUserLoveliness]    脚本日期: 12/08/2008 11:52:02 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[RecordUserLoveliness](
	[RecordID] [int] IDENTITY(1,1) NOT NULL,
	[UserID] [int] NOT NULL CONSTRAINT [DF_RecordUserCharm_UserID]  DEFAULT ((0)),
	[KindID] [int] NOT NULL CONSTRAINT [DF_RecordUserCharm_KindID]  DEFAULT ((0)),
	[ServerID] [int] NOT NULL CONSTRAINT [DF_RecordUserCharm_ServerID]  DEFAULT ((0)),
	[Loveliness] [int] NOT NULL CONSTRAINT [DF_RecordUserCharm_CharmValue]  DEFAULT ((0)),
	[WriteDate] [datetime] NOT NULL CONSTRAINT [DF_RecordUserCharm_WriteDate]  DEFAULT (getdate()),
	[ClientIP] [nvarchar](15) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_RecordUserCharm_ClientIP]  DEFAULT (N'000.000.000.000'),
 CONSTRAINT [PK_RecordUserCharm] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'记录标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLoveliness', @level2type=N'COLUMN',@level2name=N'RecordID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLoveliness', @level2type=N'COLUMN',@level2name=N'UserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'游戏标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLoveliness', @level2type=N'COLUMN',@level2name=N'KindID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'房间标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLoveliness', @level2type=N'COLUMN',@level2name=N'ServerID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户魅力' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLoveliness', @level2type=N'COLUMN',@level2name=N'Loveliness'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'写入时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLoveliness', @level2type=N'COLUMN',@level2name=N'WriteDate'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'写入地址' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLoveliness', @level2type=N'COLUMN',@level2name=N'ClientIP'
GO
/****** 对象:  Table [dbo].[RecordUserProp]    脚本日期: 12/08/2008 11:52:02 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[RecordUserProp](
	[RecordID] [int] IDENTITY(1,1) NOT NULL,
	[UserID] [int] NOT NULL CONSTRAINT [DF_RecordUserProp_UserID]  DEFAULT ((0)),
	[KindID] [int] NOT NULL CONSTRAINT [DF_RecordUserProp_KindID]  DEFAULT ((0)),
	[CateID] [int] NOT NULL CONSTRAINT [DF_RecordUserProp_CateID]  DEFAULT ((0)),
	[PropCount] [bigint] NOT NULL CONSTRAINT [DF_RecordUserProp_PropCount]  DEFAULT ((0)),
	[WriteDate] [datetime] NOT NULL CONSTRAINT [DF_RecordUserProp_WriteDate]  DEFAULT (getdate()),
	[ClientIP] [nvarchar](15) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_RecordUserProp_ClientIP]  DEFAULT (N'000.000.000.000'),
 CONSTRAINT [PK_RecordUserProp] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'记录标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserProp', @level2type=N'COLUMN',@level2name=N'RecordID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'用户标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserProp', @level2type=N'COLUMN',@level2name=N'UserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'游戏标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserProp', @level2type=N'COLUMN',@level2name=N'KindID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'道具类别' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserProp', @level2type=N'COLUMN',@level2name=N'CateID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'道具数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserProp', @level2type=N'COLUMN',@level2name=N'PropCount'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'写入时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserProp', @level2type=N'COLUMN',@level2name=N'WriteDate'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'写入地址' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserProp', @level2type=N'COLUMN',@level2name=N'ClientIP'
GO
/****** 对象:  Table [dbo].[SystemStreamInfo]    脚本日期: 12/08/2008 11:52:02 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
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
) ON [PRIMARY]
) ON [PRIMARY]

GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'日期标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'DateID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'类型标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'KindID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'房间标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'ServerID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'进入数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'LogonCount'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'离开数目' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'LogOutCount'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'录入时间' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'CollectDate'