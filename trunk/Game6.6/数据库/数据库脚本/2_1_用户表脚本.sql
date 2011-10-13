USE [GameUserDB]
GO
/****** ����:  Table [dbo].[AccountsInfo]    �ű�����: 12/08/2008 11:51:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[AccountsInfo](
	[UserID] [int] IDENTITY(1,1) NOT NULL,
	[GameID] [int] NOT NULL CONSTRAINT [DF_AccountsInfo_GameID]  DEFAULT ((0)),
	[ProtectID] [int] NOT NULL CONSTRAINT [DF_UserAccounts_ProtectID]  DEFAULT ((0)),
	[Accounts] [nvarchar](31) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[RegAccounts] [nvarchar](31) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[UnderWrite] [nvarchar](63) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_UserAccounts_UnderWrite]  DEFAULT (''),
	[LogonPass] [nchar](32) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[InsurePass] [nchar](32) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[SpreaderID] [nvarchar](31) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_AccountsInfo_SpreaderID]  DEFAULT (N''),
	[FaceID] [smallint] NOT NULL CONSTRAINT [DF_UserAccounts_FaceID]  DEFAULT ((0)),
	[Experience] [int] NOT NULL CONSTRAINT [DF_UserAccounts_Experience]  DEFAULT ((0)),
	[UserRight] [int] NOT NULL CONSTRAINT [DF_AccountsInfo_UserRight]  DEFAULT ((0)),
	[MasterRight] [int] NOT NULL CONSTRAINT [DF_AccountsInfo_MasterRight]  DEFAULT ((0)),
	[ServiceRight] [int] NOT NULL CONSTRAINT [DF_AccountsInfo_ServiceRight]  DEFAULT ((0)),
	[MasterOrder] [tinyint] NOT NULL CONSTRAINT [DF_AccountsInfo_MasterOrder]  DEFAULT ((0)),
	[MemberOrder] [tinyint] NOT NULL CONSTRAINT [DF_UserAccounts_MemberOrder]  DEFAULT ((0)),
	[MemberOverDate] [datetime] NOT NULL CONSTRAINT [DF_UserAccounts_MemberOverDate]  DEFAULT (((1980)-(1))-(1)),
	[Loveliness] [int] NOT NULL CONSTRAINT [DF_AccountsInfo_Loveliness]  DEFAULT ((0)),
	[Gender] [tinyint] NOT NULL CONSTRAINT [DF_UserAccounts_Gender]  DEFAULT ((0)),
	[Nullity] [bit] NOT NULL CONSTRAINT [DF_UserAccounts_ServiceNullity]  DEFAULT ((0)),
	[StunDown] [bit] NOT NULL CONSTRAINT [DF_AccountsInfo_CloseDown]  DEFAULT ((0)),
	[MoorMachine] [tinyint] NOT NULL CONSTRAINT [DF_AccountsInfo_MoorMachine]  DEFAULT ((0)),
	[MachineSerial] [nchar](32) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_AccountsInfo_MachineSerial]  DEFAULT (''),
	[WebLogonTimes] [int] NOT NULL CONSTRAINT [DF_AccountsInfo_WebLogonTimes]  DEFAULT ((0)),
	[GameLogonTimes] [int] NOT NULL CONSTRAINT [DF_UserAccounts_AllLogonTimes]  DEFAULT ((0)),
	[RegisterIP] [nvarchar](15) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[LastLogonIP] [nvarchar](15) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[RegisterDate] [datetime] NOT NULL CONSTRAINT [DF_UserAccounts_RegisterDate]  DEFAULT (getdate()),
	[LastLogonDate] [datetime] NOT NULL CONSTRAINT [DF_UserAccounts_LastLogonDate]  DEFAULT (getdate()),
	[CustomFaceVer] [tinyint] NULL CONSTRAINT [DF_AccountsInfo_CustomFaceVer]  DEFAULT ((0)),
 CONSTRAINT [PK_AccountsInfo_UserID] PRIMARY KEY CLUSTERED 
(
	[UserID] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO

/****** ����:  Index [IX_AccountsInfo_Accounts]    �ű�����: 12/08/2008 11:51:08 ******/
CREATE UNIQUE NONCLUSTERED INDEX [IX_AccountsInfo_Accounts] ON [dbo].[AccountsInfo] 
(
	[Accounts] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_AccountsInfo_GameID]    �ű�����: 12/08/2008 11:51:08 ******/
CREATE NONCLUSTERED INDEX [IX_AccountsInfo_GameID] ON [dbo].[AccountsInfo] 
(
	[GameID] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_AccountsInfo_GameLogonTimes]    �ű�����: 12/08/2008 11:51:08 ******/
CREATE NONCLUSTERED INDEX [IX_AccountsInfo_GameLogonTimes] ON [dbo].[AccountsInfo] 
(
	[GameLogonTimes] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_AccountsInfo_LastLogonDate]    �ű�����: 12/08/2008 11:51:08 ******/
CREATE NONCLUSTERED INDEX [IX_AccountsInfo_LastLogonDate] ON [dbo].[AccountsInfo] 
(
	[LastLogonDate] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_AccountsInfo_LastLogonIP]    �ű�����: 12/08/2008 11:51:08 ******/
CREATE NONCLUSTERED INDEX [IX_AccountsInfo_LastLogonIP] ON [dbo].[AccountsInfo] 
(
	[LastLogonIP] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_AccountsInfo_MemberOrder]    �ű�����: 12/08/2008 11:51:08 ******/
CREATE NONCLUSTERED INDEX [IX_AccountsInfo_MemberOrder] ON [dbo].[AccountsInfo] 
(
	[MemberOrder] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_AccountsInfo_MemberOverDate]    �ű�����: 12/08/2008 11:51:08 ******/
CREATE NONCLUSTERED INDEX [IX_AccountsInfo_MemberOverDate] ON [dbo].[AccountsInfo] 
(
	[MemberOverDate] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_AccountsInfo_RegisterDate]    �ű�����: 12/08/2008 11:51:08 ******/
CREATE NONCLUSTERED INDEX [IX_AccountsInfo_RegisterDate] ON [dbo].[AccountsInfo] 
(
	[RegisterDate] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_AccountsInfo_RegisterIP]    �ű�����: 12/08/2008 11:51:08 ******/
CREATE NONCLUSTERED INDEX [IX_AccountsInfo_RegisterIP] ON [dbo].[AccountsInfo] 
(
	[RegisterIP] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û���ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'UserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��Ϸ��ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'GameID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�ܱ���ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'ProtectID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û��ʺ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'Accounts'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'ע���ʺ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'RegAccounts'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'����ǩ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'UnderWrite'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��¼����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'LogonPass'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��ȫ����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'InsurePass'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�Ƽ��˱�ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'SpreaderID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'ͷ���ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'FaceID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'������ֵ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'Experience'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û�Ȩ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'UserRight'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'����Ȩ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'MasterRight'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'����Ȩ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'ServiceRight'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'����ȼ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'MasterOrder'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��Ա�ȼ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'MemberOrder'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��������' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'MemberOverDate'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û��Ա�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'Gender'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��ֹ����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'Nullity'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�رձ�־' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'StunDown'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�̶�����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'MoorMachine'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��������' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'MachineSerial'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��¼����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'WebLogonTimes'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��¼����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'GameLogonTimes'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'ע���ַ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'RegisterIP'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��¼��ַ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'LastLogonIP'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'ע��ʱ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'RegisterDate'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��¼ʱ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'LastLogonDate'
GO
/****** ����:  Table [dbo].[ConfineAddress]    �ű�����: 12/08/2008 11:51:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ConfineAddress](
	[AddrString] [nvarchar](15) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[EnjoinLogon] [bit] NOT NULL CONSTRAINT [DF_AddrConfineRule_EnjoinLogon]  DEFAULT ((0)),
	[EnjoinRegister] [bit] NOT NULL CONSTRAINT [DF_AddrConfineRule_EnjoinRegister]  DEFAULT ((0)),
	[EnjoinOverDate] [datetime] NOT NULL,
	[CollectDate] [datetime] NOT NULL CONSTRAINT [DF_AddrConfineRule_CollectDate]  DEFAULT (getdate()),
	[CollectNote] [nvarchar](32) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_AddrConfineRule_CollectNote]  DEFAULT (''),
 CONSTRAINT [PK_ConfineAddress_AddrString] PRIMARY KEY CLUSTERED 
(
	[AddrString] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO

/****** ����:  Index [IX_ConfineAddress_CollectDate]    �ű�����: 12/08/2008 11:51:08 ******/
CREATE NONCLUSTERED INDEX [IX_ConfineAddress_CollectDate] ON [dbo].[ConfineAddress] 
(
	[CollectDate] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_ConfineAddress_EnjoinOverDate]    �ű�����: 12/08/2008 11:51:08 ******/
CREATE NONCLUSTERED INDEX [IX_ConfineAddress_EnjoinOverDate] ON [dbo].[ConfineAddress] 
(
	[EnjoinOverDate] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��ַ�ַ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'AddrString'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���Ƶ�¼' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'EnjoinLogon'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'����ע��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'EnjoinRegister'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'����ʱ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'EnjoinOverDate'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�ռ�����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'CollectDate'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���뱸ע' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'CollectNote'
GO
/****** ����:  Table [dbo].[ConfineContent]    �ű�����: 12/08/2008 11:51:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ConfineContent](
	[String] [nvarchar](31) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[CollectDate] [datetime] NOT NULL CONSTRAINT [DF_ReserveCharacter_ModifyDate]  DEFAULT (getdate()),
 CONSTRAINT [PK_ConfineContent_String] PRIMARY KEY CLUSTERED 
(
	[String] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO

/****** ����:  Index [IX_ConfineContent_CollectDate]    �ű�����: 12/08/2008 11:51:08 ******/
CREATE NONCLUSTERED INDEX [IX_ConfineContent_CollectDate] ON [dbo].[ConfineContent] 
(
	[CollectDate] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�����ַ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineContent', @level2type=N'COLUMN',@level2name=N'String'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'¼������' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineContent', @level2type=N'COLUMN',@level2name=N'CollectDate'
GO
/****** ����:  Table [dbo].[ConfineMachine]    �ű�����: 12/08/2008 11:51:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[ConfineMachine](
	[MachineSerial] [char](32) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[EnjoinLogon] [bit] NOT NULL CONSTRAINT [DF_MachineConfineRule_EnjoinLogon]  DEFAULT ((0)),
	[EnjoinRegister] [bit] NOT NULL CONSTRAINT [DF_MachineConfineRule_EnjoinRegister]  DEFAULT ((0)),
	[EnjoinOverDate] [datetime] NOT NULL,
	[CollectDate] [datetime] NOT NULL CONSTRAINT [DF_MachineConfineRule_CollectDate]  DEFAULT (getdate()),
	[CollectNote] [nvarchar](32) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_MachineConfineRule_CollectNote]  DEFAULT (''),
 CONSTRAINT [PK_ConfineMachine_MachineSerial] PRIMARY KEY CLUSTERED 
(
	[MachineSerial] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO

/****** ����:  Index [IX_ConfineMachine_CollectDate]    �ű�����: 12/08/2008 11:51:08 ******/
CREATE NONCLUSTERED INDEX [IX_ConfineMachine_CollectDate] ON [dbo].[ConfineMachine] 
(
	[CollectDate] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_ConfineMachine_EnjoinOverDate]    �ű�����: 12/08/2008 11:51:08 ******/
CREATE NONCLUSTERED INDEX [IX_ConfineMachine_EnjoinOverDate] ON [dbo].[ConfineMachine] 
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
/****** ����:  Table [dbo].[CustomFaceInfo]    �ű�����: 12/08/2008 11:51:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[CustomFaceInfo](
	[UserID] [int] NOT NULL,
	[CustomFaceImage] [varbinary](MAX) NOT NULL CONSTRAINT [DF_CustomFaceInfo_CustomFaceImage]  DEFAULT ((0)),
 CONSTRAINT [PK_CustomFaceInfo] PRIMARY KEY CLUSTERED 
(
	[UserID] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û���ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'CustomFaceInfo', @level2type=N'COLUMN',@level2name=N'UserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�Զ���ͷ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'CustomFaceInfo', @level2type=N'COLUMN',@level2name=N'CustomFaceImage'
GO
/****** ����:  Table [dbo].[GameIdentifier]    �ű�����: 12/08/2008 11:51:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[GameIdentifier](
	[UserID] [int] IDENTITY(1,1) NOT NULL,
	[GameID] [int] NOT NULL,
	[IDLevel] [int] NOT NULL CONSTRAINT [DF_GameIdentifiers_IDLevel]  DEFAULT ((0)),
 CONSTRAINT [PK_GameIdentifier_UserID] PRIMARY KEY CLUSTERED 
(
	[UserID] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO

/****** ����:  Index [IX_GameIdentifier_GameID]    �ű�����: 12/08/2008 11:51:08 ******/
CREATE UNIQUE NONCLUSTERED INDEX [IX_GameIdentifier_GameID] ON [dbo].[GameIdentifier] 
(
	[GameID] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_GameIdentifier_IDLevel]    �ű�����: 12/08/2008 11:51:08 ******/
CREATE NONCLUSTERED INDEX [IX_GameIdentifier_IDLevel] ON [dbo].[GameIdentifier] 
(
	[IDLevel] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û���ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameIdentifier', @level2type=N'COLUMN',@level2name=N'UserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��Ϸ��ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameIdentifier', @level2type=N'COLUMN',@level2name=N'GameID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��ʶ�ȼ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameIdentifier', @level2type=N'COLUMN',@level2name=N'IDLevel'
GO
/****** ����:  Table [dbo].[IndividualDatum]    �ű�����: 12/08/2008 11:51:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[IndividualDatum](
	[UserID] [int] NOT NULL,
	[Compellation] [nvarchar](16) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_IndividualDatum_Compellation]  DEFAULT (''),
	[QQ] [nvarchar](16) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[EMail] [nvarchar](32) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[SeatPhone] [nvarchar](32) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_IndividualDatum_SeatPhone]  DEFAULT (''),
	[MobilePhone] [nvarchar](16) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_IndividualDatum_MobilePhone]  DEFAULT (''),
	[DwellingPlace] [nvarchar](128) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_IndividualDatum_DwellingPlace]  DEFAULT (''),
	[PostalCode] [nvarchar](8) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_IndividualDatum_PostalCode]  DEFAULT (''),
	[CollectDate] [datetime] NOT NULL CONSTRAINT [DF_IndividualDatum_CollectDate]  DEFAULT (getdate()),
	[UserNote] [nvarchar](256) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_IndividualDatum_UserNote]  DEFAULT (''),
 CONSTRAINT [PK_IndividualDatum_UserID] PRIMARY KEY CLUSTERED 
(
	[UserID] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO

/****** ����:  Index [IX_IndividualDatum_CollectDate]    �ű�����: 12/08/2008 11:51:08 ******/
CREATE NONCLUSTERED INDEX [IX_IndividualDatum_CollectDate] ON [dbo].[IndividualDatum] 
(
	[UserID] ASC,
	[CollectDate] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_IndividualDatum_Compellation]    �ű�����: 12/08/2008 11:51:08 ******/
CREATE NONCLUSTERED INDEX [IX_IndividualDatum_Compellation] ON [dbo].[IndividualDatum] 
(
	[Compellation] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_IndividualDatum_EMail]    �ű�����: 12/08/2008 11:51:08 ******/
CREATE NONCLUSTERED INDEX [IX_IndividualDatum_EMail] ON [dbo].[IndividualDatum] 
(
	[EMail] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_IndividualDatum_MobilePhone]    �ű�����: 12/08/2008 11:51:08 ******/
CREATE NONCLUSTERED INDEX [IX_IndividualDatum_MobilePhone] ON [dbo].[IndividualDatum] 
(
	[MobilePhone] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_IndividualDatum_SeatPhone]    �ű�����: 12/08/2008 11:51:08 ******/
CREATE NONCLUSTERED INDEX [IX_IndividualDatum_SeatPhone] ON [dbo].[IndividualDatum] 
(
	[SeatPhone] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û���ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'IndividualDatum', @level2type=N'COLUMN',@level2name=N'UserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��ʵ����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'IndividualDatum', @level2type=N'COLUMN',@level2name=N'Compellation'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�̶��绰' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'IndividualDatum', @level2type=N'COLUMN',@level2name=N'SeatPhone'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�ֻ�����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'IndividualDatum', @level2type=N'COLUMN',@level2name=N'MobilePhone'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��ϸסַ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'IndividualDatum', @level2type=N'COLUMN',@level2name=N'DwellingPlace'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��������' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'IndividualDatum', @level2type=N'COLUMN',@level2name=N'PostalCode'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�ռ�����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'IndividualDatum', @level2type=N'COLUMN',@level2name=N'CollectDate'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û���ע' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'IndividualDatum', @level2type=N'COLUMN',@level2name=N'UserNote'
GO
/****** ����:  Table [dbo].[MemberInfo]    �ű�����: 12/08/2008 11:51:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[MemberInfo](
	[UserID] [int] NOT NULL,
	[MemberOrder] [tinyint] NOT NULL,
	[MemberOverDate] [datetime] NOT NULL CONSTRAINT [DF_MemberInfo_MemberOverDate]  DEFAULT (getdate()),
 CONSTRAINT [PK_MemberInfo] PRIMARY KEY CLUSTERED 
(
	[UserID] ASC,
	[MemberOrder] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO

/****** ����:  Index [IX_OverDate]    �ű�����: 12/08/2008 11:51:08 ******/
CREATE NONCLUSTERED INDEX [IX_OverDate] ON [dbo].[MemberInfo] 
(
	[MemberOverDate] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_UserID]    �ű�����: 12/08/2008 11:51:08 ******/
CREATE NONCLUSTERED INDEX [IX_UserID] ON [dbo].[MemberInfo] 
(
	[UserID] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û���ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'MemberInfo', @level2type=N'COLUMN',@level2name=N'UserID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��Ա��ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'MemberInfo', @level2type=N'COLUMN',@level2name=N'MemberOrder'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��Ա����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'MemberInfo', @level2type=N'COLUMN',@level2name=N'MemberOverDate'
GO
/****** ����:  Table [dbo].[ReserveIdentifier]    �ű�����: 12/08/2008 11:51:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ReserveIdentifier](
	[GameID] [int] NOT NULL,
	[IDLevel] [int] NOT NULL CONSTRAINT [DF_Table1_IDLevel]  DEFAULT ((0)),
	[Distribute] [bit] NOT NULL CONSTRAINT [DF_ReserveIdentifiers_Distribute]  DEFAULT ((0)),
 CONSTRAINT [PK_ReserveIdentifier_GameID] PRIMARY KEY CLUSTERED 
(
	[GameID] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO

/****** ����:  Index [IX_ReserveIdentifier_IDLevel]    �ű�����: 12/08/2008 11:51:08 ******/
CREATE NONCLUSTERED INDEX [IX_ReserveIdentifier_IDLevel] ON [dbo].[ReserveIdentifier] 
(
	[IDLevel] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��Ϸ��ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ReserveIdentifier', @level2type=N'COLUMN',@level2name=N'GameID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��ʶ�ȼ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ReserveIdentifier', @level2type=N'COLUMN',@level2name=N'IDLevel'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�����־' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ReserveIdentifier', @level2type=N'COLUMN',@level2name=N'Distribute'
GO
/****** ����:  Table [dbo].[SystemStreamInfo]    �ű�����: 12/08/2008 11:51:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[SystemStreamInfo](
	[DateID] [int] NOT NULL,
	[WebLogonSuccess] [int] NOT NULL CONSTRAINT [DF_SystemLogonInfo_WebLogonSuccess]  DEFAULT ((0)),
	[WebRegisterSuccess] [int] NOT NULL CONSTRAINT [DF_SystemLogonInfo_WebRegisterSuccess]  DEFAULT ((0)),
	[GameLogonSuccess] [int] NOT NULL CONSTRAINT [DF_TABLE1_LogonCount]  DEFAULT ((0)),
	[GameRegisterSuccess] [int] NOT NULL CONSTRAINT [DF_TABLE1_RegisterCount]  DEFAULT ((0)),
	[CollectDate] [datetime] NOT NULL CONSTRAINT [DF_TABLE1_RecordDate]  DEFAULT (getdate()),
 CONSTRAINT [PK_SystemStreamInfo_DateID] PRIMARY KEY CLUSTERED 
(
	[DateID] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO

/****** ����:  Index [IX_SystemStreamInfo_CollectDate]    �ű�����: 12/08/2008 11:51:08 ******/
CREATE NONCLUSTERED INDEX [IX_SystemStreamInfo_CollectDate] ON [dbo].[SystemStreamInfo] 
(
	[CollectDate] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���ڱ�ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'DateID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��¼�ɹ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'WebLogonSuccess'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'ע��ɹ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'WebRegisterSuccess'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��¼�ɹ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'GameLogonSuccess'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'ע��ɹ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'GameRegisterSuccess'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'¼��ʱ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'CollectDate'