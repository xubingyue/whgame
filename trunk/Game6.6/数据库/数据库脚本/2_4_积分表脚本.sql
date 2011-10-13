USE [GameScoreDB]
GO
/****** ����:  Table [dbo].[AndroidUserInfo]    �ű�����: 12/08/2008 11:52:25 ******/
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

/****** ����:  Index [IX_AndroidUserInfo_CreateDate]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_AndroidUserInfo_CreateDate] ON [dbo].[AndroidUserInfo] 
(
	[CreateDate] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_AndroidUserInfo_KindID]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_AndroidUserInfo_KindID] ON [dbo].[AndroidUserInfo] 
(
	[KindID] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_AndroidUserInfo_ServerID]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_AndroidUserInfo_ServerID] ON [dbo].[AndroidUserInfo] 
(
	[ServerID] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_AndroidUserInfo_UserID]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_AndroidUserInfo_UserID] ON [dbo].[AndroidUserInfo] 
(
	[UserID] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û���ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AndroidUserInfo', @level2type=N'COLUMN',@level2name=N'UserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��ֹ����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AndroidUserInfo', @level2type=N'COLUMN',@level2name=N'Nullity'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���ͱ�ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AndroidUserInfo', @level2type=N'COLUMN',@level2name=N'KindID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�����ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AndroidUserInfo', @level2type=N'COLUMN',@level2name=N'ServerID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��������' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AndroidUserInfo', @level2type=N'COLUMN',@level2name=N'CreateDate'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��ע��Ϣ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AndroidUserInfo', @level2type=N'COLUMN',@level2name=N'AndroidNote'
GO
/****** ����:  Table [dbo].[ConfineAddress]    �ű�����: 12/08/2008 11:52:25 ******/
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

/****** ����:  Index [IX_ConfineAddress_CollectDate]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_ConfineAddress_CollectDate] ON [dbo].[ConfineAddress] 
(
	[CollectDate] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_ConfineAddress_EnjoinOverDate]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_ConfineAddress_EnjoinOverDate] ON [dbo].[ConfineAddress] 
(
	[EnjoinOverDate] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��ַ�ַ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'AddrString'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���Ƶ�½' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'EnjoinLogon'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'����ʱ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'EnjoinOverDate'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�ռ�����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'CollectDate'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���뱸ע' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'CollectNote'
GO
/****** ����:  Table [dbo].[ConfineMachine]    �ű�����: 12/08/2008 11:52:25 ******/
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

/****** ����:  Index [IX_MachineConfineRule_CollectDate]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_MachineConfineRule_CollectDate] ON [dbo].[ConfineMachine] 
(
	[CollectDate] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_MachineConfineRule_EnjoinOverDate]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_MachineConfineRule_EnjoinOverDate] ON [dbo].[ConfineMachine] 
(
	[EnjoinOverDate] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��������' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineMachine', @level2type=N'COLUMN',@level2name=N'MachineSerial'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���Ƶ�¼' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineMachine', @level2type=N'COLUMN',@level2name=N'EnjoinLogon'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'����ע��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineMachine', @level2type=N'COLUMN',@level2name=N'EnjoinRegister'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'����ʱ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineMachine', @level2type=N'COLUMN',@level2name=N'EnjoinOverDate'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�ռ�����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineMachine', @level2type=N'COLUMN',@level2name=N'CollectDate'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���뱸ע' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineMachine', @level2type=N'COLUMN',@level2name=N'CollectNote'
GO
/****** ����:  Table [dbo].[GameScoreInfo]    �ű�����: 12/08/2008 11:52:25 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[GameScoreInfo](
	[UserID] [int] NOT NULL,
	[Score] [bigint] NOT NULL CONSTRAINT [DF_GameScore_Score]  DEFAULT ((0)),
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
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û� ID' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'UserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û����֣����ң�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'Score'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'ʤ����Ŀ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'WinCount'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�����Ŀ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'LostCount'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�;���Ŀ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'DrawCount'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�Ӿ���Ŀ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'FleeCount'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û�Ȩ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'UserRight'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'����Ȩ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'MasterRight'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'����ȼ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'MasterOrder'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'ע�� IP' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'RegisterIP'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�ϴε�½ IP' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'LastLogonIP'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'ע��ʱ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'RegisterDate'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�ϴε�½ʱ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'LastLogonDate'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�ܵ�½����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'AllLogonTimes'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��Ϸʱ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'PlayTimeCount'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'����ʱ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameScoreInfo', @level2type=N'COLUMN',@level2name=N'OnLineTimeCount'
GO
/****** ����:  Table [dbo].[RecordGameScore]    �ű�����: 12/08/2008 11:52:25 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[RecordGameScore](
	[RecordID] [int] IDENTITY(1,1) NOT NULL,
	[KindID] [int] NOT NULL,
	[ServerID] [int] NOT NULL,
	[TableID] [int] NOT NULL,
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
) ON [PRIMARY]
) ON [PRIMARY]

GO

/****** ����:  Index [IX_GameScoreRecord_KindID]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_GameScoreRecord_KindID] ON [dbo].[RecordGameScore] 
(
	[KindID] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_GameScoreRecord_RecordDate]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_GameScoreRecord_RecordDate] ON [dbo].[RecordGameScore] 
(
	[RecordDate] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_GameScoreRecord_ServerID]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_GameScoreRecord_ServerID] ON [dbo].[RecordGameScore] 
(
	[ServerID] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_GameScoreRecord_TableID]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_GameScoreRecord_TableID] ON [dbo].[RecordGameScore] 
(
	[TableID] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_GameScoreRecord_UserID1]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_GameScoreRecord_UserID1] ON [dbo].[RecordGameScore] 
(
	[UserID1] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_GameScoreRecord_UserID2]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_GameScoreRecord_UserID2] ON [dbo].[RecordGameScore] 
(
	[UserID2] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_GameScoreRecord_UserID3]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_GameScoreRecord_UserID3] ON [dbo].[RecordGameScore] 
(
	[UserID3] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_GameScoreRecord_UserID4]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_GameScoreRecord_UserID4] ON [dbo].[RecordGameScore] 
(
	[UserID4] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_GameScoreRecord_UserID5]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_GameScoreRecord_UserID5] ON [dbo].[RecordGameScore] 
(
	[UserID5] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_GameScoreRecord_UserID6]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_GameScoreRecord_UserID6] ON [dbo].[RecordGameScore] 
(
	[UserID6] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_GameScoreRecord_UserID7]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_GameScoreRecord_UserID7] ON [dbo].[RecordGameScore] 
(
	[UserID7] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_GameScoreRecord_UserID8]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_GameScoreRecord_UserID8] ON [dbo].[RecordGameScore] 
(
	[UserID8] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��¼��ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'RecordID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���ͱ�ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'KindID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�����ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'ServerID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���Ӻ���' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'TableID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��Ϸʱ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'PlayTimeCount'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û���ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'UserID1'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��Ϸ����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'GameScore1'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û���ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'UserID2'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��Ϸ����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'GameScore2'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û���ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'UserID3'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��Ϸ����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'GameScore3'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û���ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'UserID4'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��Ϸ����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'GameScore4'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û���ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'UserID5'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��Ϸ����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'GameScore5'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û���ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'UserID6'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��Ϸ����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'GameScore6'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û���ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'UserID7'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��Ϸ����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'GameScore7'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û���ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'UserID8'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��Ϸ����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'GameScore8'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��¼ʱ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordGameScore', @level2type=N'COLUMN',@level2name=N'RecordDate'
GO
/****** ����:  Table [dbo].[RecordUserEnter]    �ű�����: 12/08/2008 11:52:25 ******/
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

/****** ����:  Index [IX_RecordUserEnter_EnterTime]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_RecordUserEnter_EnterTime] ON [dbo].[RecordUserEnter] 
(
	[EnterTime] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_RecordUserEnter_KindID]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_RecordUserEnter_KindID] ON [dbo].[RecordUserEnter] 
(
	[KindID] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_RecordUserEnter_ServerID]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_RecordUserEnter_ServerID] ON [dbo].[RecordUserEnter] 
(
	[ServerID] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_RecordUserEnter_UserID]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_RecordUserEnter_UserID] ON [dbo].[RecordUserEnter] 
(
	[UserID] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û���ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserEnter', @level2type=N'COLUMN',@level2name=N'UserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'������Ŀ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserEnter', @level2type=N'COLUMN',@level2name=N'Score'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���ͱ�ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserEnter', @level2type=N'COLUMN',@level2name=N'KindID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��¼��ַ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserEnter', @level2type=N'COLUMN',@level2name=N'ClientIP'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�����ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserEnter', @level2type=N'COLUMN',@level2name=N'ServerID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'����ʱ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserEnter', @level2type=N'COLUMN',@level2name=N'EnterTime'
GO
/****** ����:  Table [dbo].[RecordUserLeave]    �ű�����: 12/08/2008 11:52:25 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[RecordUserLeave](
	[UserID] [int] NOT NULL,
	[Score] [bigint] NOT NULL,
	[KindID] [int] NOT NULL,
	[ServerID] [int] NOT NULL,
	[PlayTimeCount] [int] NOT NULL,
	[OnLineTimeCount] [int] NOT NULL,
	[LeaveTime] [datetime] NOT NULL CONSTRAINT [DF_RecordUserLeave_LeaveTime]  DEFAULT (getdate())
) ON [PRIMARY]

GO

/****** ����:  Index [IX_RecordUserLeave_KindID]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_RecordUserLeave_KindID] ON [dbo].[RecordUserLeave] 
(
	[KindID] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_RecordUserLeave_LeaveTime]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_RecordUserLeave_LeaveTime] ON [dbo].[RecordUserLeave] 
(
	[LeaveTime] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_RecordUserLeave_ServerID]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_RecordUserLeave_ServerID] ON [dbo].[RecordUserLeave] 
(
	[ServerID] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_RecordUserLeave_UserID]    �ű�����: 12/08/2008 11:52:25 ******/
CREATE NONCLUSTERED INDEX [IX_RecordUserLeave_UserID] ON [dbo].[RecordUserLeave] 
(
	[UserID] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û���ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLeave', @level2type=N'COLUMN',@level2name=N'UserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�뿪����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLeave', @level2type=N'COLUMN',@level2name=N'Score'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���ͱ�ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLeave', @level2type=N'COLUMN',@level2name=N'KindID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�����ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLeave', @level2type=N'COLUMN',@level2name=N'ServerID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��Ϸʱ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLeave', @level2type=N'COLUMN',@level2name=N'PlayTimeCount'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'����ʱ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLeave', @level2type=N'COLUMN',@level2name=N'OnLineTimeCount'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�뿪ʱ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RecordUserLeave', @level2type=N'COLUMN',@level2name=N'LeaveTime'
GO
/****** ����:  Table [dbo].[SystemStreamInfo]    �ű�����: 12/08/2008 11:52:25 ******/
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
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���ڱ�ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'DateID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���ͱ�ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'KindID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�����ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'ServerID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'������Ŀ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'LogonCount'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�뿪��Ŀ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'LogOutCount'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'¼��ʱ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'CollectDate'