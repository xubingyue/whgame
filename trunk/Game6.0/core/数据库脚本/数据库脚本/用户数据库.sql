USE [master]
GO
/****** ����:  Database [UserDB]    �ű�����: 01/23/2008 14:54:42 ******/
IF NOT EXISTS (SELECT name FROM master.dbo.sysdatabases WHERE name = N'UserDB')
BEGIN
CREATE DATABASE [UserDB]
END

GO
ALTER DATABASE [UserDB] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [UserDB] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [UserDB] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [UserDB] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [UserDB] SET ARITHABORT OFF 
GO
ALTER DATABASE [UserDB] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [UserDB] SET AUTO_CREATE_STATISTICS ON 
GO
ALTER DATABASE [UserDB] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [UserDB] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [UserDB] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [UserDB] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [UserDB] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [UserDB] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [UserDB] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [UserDB] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [UserDB] SET  READ_WRITE 
GO
ALTER DATABASE [UserDB] SET RECOVERY FULL 
GO
ALTER DATABASE [UserDB] SET  MULTI_USER 
GO
if ( ((@@microsoftversion / power(2, 24) = 8) and (@@microsoftversion & 0xffff >= 760)) or 
		(@@microsoftversion / power(2, 24) >= 9) )begin 
	exec dbo.sp_dboption @dbname =  N'UserDB', @optname = 'db chaining', @optvalue = 'OFF'
 end

USE [UserDB]
GO
/****** ����:  Table [dbo].[AccountsInfo]    �ű�����: 01/23/2008 14:55:03 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[dbo].[AccountsInfo]') AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
BEGIN
CREATE TABLE [dbo].[AccountsInfo](
	[UserID] [int] IDENTITY(1,1) NOT NULL,
	[GameID] [int] NOT NULL CONSTRAINT [DF_AccountsInfo_GameID]  DEFAULT ((0)),
	[ProtectID] [int] NOT NULL CONSTRAINT [DF_UserAccounts_ProtectID]  DEFAULT ((0)),
	[Accounts] [nvarchar](31) NOT NULL,
	[RegAccounts] [nvarchar](31) NOT NULL,
	[UnderWrite] [nvarchar](63) NOT NULL CONSTRAINT [DF_UserAccounts_UnderWrite]  DEFAULT (''),
	[LogonPass] [nchar](32) NOT NULL,
	[InsurePass] [nchar](32) NOT NULL,
	[EMail] [nvarchar](31) NOT NULL CONSTRAINT [DF_AccountsInfo_EMail]  DEFAULT (N''),
	[FaceID] [smallint] NOT NULL CONSTRAINT [DF_UserAccounts_FaceID]  DEFAULT ((0)),
	[Experience] [int] NOT NULL CONSTRAINT [DF_UserAccounts_Experience]  DEFAULT ((0)),
	[UserRight] [int] NOT NULL CONSTRAINT [DF_AccountsInfo_UserRight]  DEFAULT ((0)),
	[MasterRight] [int] NOT NULL CONSTRAINT [DF_AccountsInfo_MasterRight]  DEFAULT ((0)),
	[ServiceRight] [int] NOT NULL CONSTRAINT [DF_AccountsInfo_ServiceRight]  DEFAULT ((0)),
	[MasterOrder] [tinyint] NOT NULL CONSTRAINT [DF_AccountsInfo_MasterOrder]  DEFAULT ((0)),
	[MemberOrder] [tinyint] NOT NULL CONSTRAINT [DF_UserAccounts_MemberOrder]  DEFAULT ((0)),
	[MemberOverDate] [datetime] NOT NULL CONSTRAINT [DF_UserAccounts_MemberOverDate]  DEFAULT (((1980)-(1))-(1)),
	[Gender] [tinyint] NOT NULL CONSTRAINT [DF_UserAccounts_Gender]  DEFAULT ((0)),
	[Nullity] [bit] NOT NULL CONSTRAINT [DF_UserAccounts_ServiceNullity]  DEFAULT ((0)),
	[StunDown] [bit] NOT NULL CONSTRAINT [DF_AccountsInfo_CloseDown]  DEFAULT ((0)),
	[MoorMachine] [tinyint] NOT NULL CONSTRAINT [DF_AccountsInfo_MoorMachine]  DEFAULT ((0)),
	[MachineSerial] [nchar](32) NOT NULL CONSTRAINT [DF_AccountsInfo_MachineSerial]  DEFAULT (''),
	[WebLogonTimes] [int] NOT NULL CONSTRAINT [DF_AccountsInfo_WebLogonTimes]  DEFAULT ((0)),
	[GameLogonTimes] [int] NOT NULL CONSTRAINT [DF_UserAccounts_AllLogonTimes]  DEFAULT ((0)),
	[RegisterIP] [nvarchar](15) NOT NULL,
	[LastLogonIP] [nvarchar](15) NOT NULL,
	[RegisterDate] [datetime] NOT NULL CONSTRAINT [DF_UserAccounts_RegisterDate]  DEFAULT (getdate()),
	[LastLogonDate] [datetime] NOT NULL CONSTRAINT [DF_UserAccounts_LastLogonDate]  DEFAULT (getdate()),
 CONSTRAINT [PK_AccountsInfo_UserID] PRIMARY KEY CLUSTERED 
(
	[UserID] ASC
)
)
END
GO

/****** ����:  Index [IX_AccountsInfo_Accounts]    �ű�����: 01/23/2008 14:55:03 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[AccountsInfo]') AND name = N'IX_AccountsInfo_Accounts')
CREATE UNIQUE NONCLUSTERED INDEX [IX_AccountsInfo_Accounts] ON [dbo].[AccountsInfo] 
(
	[Accounts] ASC
)
GO

/****** ����:  Index [IX_AccountsInfo_GameID]    �ű�����: 01/23/2008 14:55:03 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[AccountsInfo]') AND name = N'IX_AccountsInfo_GameID')
CREATE NONCLUSTERED INDEX [IX_AccountsInfo_GameID] ON [dbo].[AccountsInfo] 
(
	[GameID] ASC
)
GO

/****** ����:  Index [IX_AccountsInfo_GameLogonTimes]    �ű�����: 01/23/2008 14:55:03 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[AccountsInfo]') AND name = N'IX_AccountsInfo_GameLogonTimes')
CREATE NONCLUSTERED INDEX [IX_AccountsInfo_GameLogonTimes] ON [dbo].[AccountsInfo] 
(
	[GameLogonTimes] ASC
)
GO

/****** ����:  Index [IX_AccountsInfo_LastLogonDate]    �ű�����: 01/23/2008 14:55:03 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[AccountsInfo]') AND name = N'IX_AccountsInfo_LastLogonDate')
CREATE NONCLUSTERED INDEX [IX_AccountsInfo_LastLogonDate] ON [dbo].[AccountsInfo] 
(
	[LastLogonDate] ASC
)
GO

/****** ����:  Index [IX_AccountsInfo_LastLogonIP]    �ű�����: 01/23/2008 14:55:03 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[AccountsInfo]') AND name = N'IX_AccountsInfo_LastLogonIP')
CREATE NONCLUSTERED INDEX [IX_AccountsInfo_LastLogonIP] ON [dbo].[AccountsInfo] 
(
	[LastLogonIP] ASC
)
GO

/****** ����:  Index [IX_AccountsInfo_MemberOrder]    �ű�����: 01/23/2008 14:55:03 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[AccountsInfo]') AND name = N'IX_AccountsInfo_MemberOrder')
CREATE NONCLUSTERED INDEX [IX_AccountsInfo_MemberOrder] ON [dbo].[AccountsInfo] 
(
	[MemberOrder] ASC
)
GO

/****** ����:  Index [IX_AccountsInfo_MemberOverDate]    �ű�����: 01/23/2008 14:55:03 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[AccountsInfo]') AND name = N'IX_AccountsInfo_MemberOverDate')
CREATE NONCLUSTERED INDEX [IX_AccountsInfo_MemberOverDate] ON [dbo].[AccountsInfo] 
(
	[MemberOverDate] ASC
)
GO

/****** ����:  Index [IX_AccountsInfo_RegisterDate]    �ű�����: 01/23/2008 14:55:03 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[AccountsInfo]') AND name = N'IX_AccountsInfo_RegisterDate')
CREATE NONCLUSTERED INDEX [IX_AccountsInfo_RegisterDate] ON [dbo].[AccountsInfo] 
(
	[RegisterDate] ASC
)
GO

/****** ����:  Index [IX_AccountsInfo_RegisterIP]    �ű�����: 01/23/2008 14:55:03 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[AccountsInfo]') AND name = N'IX_AccountsInfo_RegisterIP')
CREATE NONCLUSTERED INDEX [IX_AccountsInfo_RegisterIP] ON [dbo].[AccountsInfo] 
(
	[RegisterIP] ASC
)
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'UserID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û���ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'UserID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'GameID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��Ϸ��ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'GameID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'ProtectID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�ܱ���ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'ProtectID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'Accounts'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û��ʺ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'Accounts'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'RegAccounts'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'ע���ʺ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'RegAccounts'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'UnderWrite'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'����ǩ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'UnderWrite'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'LogonPass'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��¼����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'LogonPass'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'InsurePass'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��ȫ����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'InsurePass'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'EMail'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�����ʼ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'EMail'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'FaceID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'ͷ���ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'FaceID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'Experience'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'������ֵ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'Experience'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'UserRight'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û�Ȩ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'UserRight'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'MasterRight'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'����Ȩ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'MasterRight'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'ServiceRight'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'����Ȩ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'ServiceRight'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'MasterOrder'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'����ȼ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'MasterOrder'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'MemberOrder'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��Ա�ȼ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'MemberOrder'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'MemberOverDate'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��������' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'MemberOverDate'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'Gender'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û��Ա�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'Gender'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'Nullity'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��ֹ����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'Nullity'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'StunDown'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�رձ�־' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'StunDown'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'MoorMachine'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�̶�����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'MoorMachine'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'MachineSerial'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��������' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'MachineSerial'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'WebLogonTimes'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��¼����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'WebLogonTimes'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'GameLogonTimes'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��¼����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'GameLogonTimes'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'RegisterIP'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'ע���ַ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'RegisterIP'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'LastLogonIP'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��¼��ַ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'LastLogonIP'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'RegisterDate'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'ע��ʱ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'RegisterDate'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'AccountsInfo', N'COLUMN',N'LastLogonDate'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��¼ʱ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'AccountsInfo', @level2type=N'COLUMN',@level2name=N'LastLogonDate'
GO
/****** ����:  Table [dbo].[ConfineAddress]    �ű�����: 01/23/2008 14:55:03 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[dbo].[ConfineAddress]') AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
BEGIN
CREATE TABLE [dbo].[ConfineAddress](
	[AddrString] [nvarchar](15) NOT NULL,
	[EnjoinLogon] [bit] NOT NULL CONSTRAINT [DF_AddrConfineRule_EnjoinLogon]  DEFAULT ((0)),
	[EnjoinRegister] [bit] NOT NULL CONSTRAINT [DF_AddrConfineRule_EnjoinRegister]  DEFAULT ((0)),
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

/****** ����:  Index [IX_ConfineAddress_CollectDate]    �ű�����: 01/23/2008 14:55:03 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[ConfineAddress]') AND name = N'IX_ConfineAddress_CollectDate')
CREATE NONCLUSTERED INDEX [IX_ConfineAddress_CollectDate] ON [dbo].[ConfineAddress] 
(
	[CollectDate] ASC
)
GO

/****** ����:  Index [IX_ConfineAddress_EnjoinOverDate]    �ű�����: 01/23/2008 14:55:03 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[ConfineAddress]') AND name = N'IX_ConfineAddress_EnjoinOverDate')
CREATE NONCLUSTERED INDEX [IX_ConfineAddress_EnjoinOverDate] ON [dbo].[ConfineAddress] 
(
	[EnjoinOverDate] ASC
)
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ConfineAddress', N'COLUMN',N'AddrString'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��ַ�ַ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'AddrString'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ConfineAddress', N'COLUMN',N'EnjoinLogon'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���Ƶ�¼' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'EnjoinLogon'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ConfineAddress', N'COLUMN',N'EnjoinRegister'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'����ע��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'EnjoinRegister'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ConfineAddress', N'COLUMN',N'EnjoinOverDate'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'����ʱ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'EnjoinOverDate'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ConfineAddress', N'COLUMN',N'CollectDate'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�ռ�����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'CollectDate'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ConfineAddress', N'COLUMN',N'CollectNote'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���뱸ע' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineAddress', @level2type=N'COLUMN',@level2name=N'CollectNote'
GO
/****** ����:  Table [dbo].[ConfineContent]    �ű�����: 01/23/2008 14:55:03 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[dbo].[ConfineContent]') AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
BEGIN
CREATE TABLE [dbo].[ConfineContent](
	[String] [nvarchar](31) NOT NULL,
	[CollectDate] [datetime] NOT NULL CONSTRAINT [DF_ReserveCharacter_ModifyDate]  DEFAULT (getdate()),
 CONSTRAINT [PK_ConfineContent_String] PRIMARY KEY CLUSTERED 
(
	[String] ASC
)
)
END
GO

/****** ����:  Index [IX_ConfineContent_CollectDate]    �ű�����: 01/23/2008 14:55:03 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[ConfineContent]') AND name = N'IX_ConfineContent_CollectDate')
CREATE NONCLUSTERED INDEX [IX_ConfineContent_CollectDate] ON [dbo].[ConfineContent] 
(
	[CollectDate] ASC
)
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ConfineContent', N'COLUMN',N'String'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�����ַ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineContent', @level2type=N'COLUMN',@level2name=N'String'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ConfineContent', N'COLUMN',N'CollectDate'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'¼������' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineContent', @level2type=N'COLUMN',@level2name=N'CollectDate'
GO
/****** ����:  Table [dbo].[ConfineMachine]    �ű�����: 01/23/2008 14:55:03 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
IF NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[dbo].[ConfineMachine]') AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
BEGIN
CREATE TABLE [dbo].[ConfineMachine](
	[MachineSerial] [char](32) NOT NULL,
	[EnjoinLogon] [bit] NOT NULL CONSTRAINT [DF_MachineConfineRule_EnjoinLogon]  DEFAULT ((0)),
	[EnjoinRegister] [bit] NOT NULL CONSTRAINT [DF_MachineConfineRule_EnjoinRegister]  DEFAULT ((0)),
	[EnjoinOverDate] [datetime] NOT NULL,
	[CollectDate] [datetime] NOT NULL CONSTRAINT [DF_MachineConfineRule_CollectDate]  DEFAULT (getdate()),
	[CollectNote] [nvarchar](32) NOT NULL CONSTRAINT [DF_MachineConfineRule_CollectNote]  DEFAULT (''),
 CONSTRAINT [PK_ConfineMachine_MachineSerial] PRIMARY KEY CLUSTERED 
(
	[MachineSerial] ASC
)
)
END
GO
SET ANSI_PADDING OFF
GO

/****** ����:  Index [IX_ConfineMachine_CollectDate]    �ű�����: 01/23/2008 14:55:03 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[ConfineMachine]') AND name = N'IX_ConfineMachine_CollectDate')
CREATE NONCLUSTERED INDEX [IX_ConfineMachine_CollectDate] ON [dbo].[ConfineMachine] 
(
	[CollectDate] ASC
)
GO

/****** ����:  Index [IX_ConfineMachine_EnjoinOverDate]    �ű�����: 01/23/2008 14:55:03 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[ConfineMachine]') AND name = N'IX_ConfineMachine_EnjoinOverDate')
CREATE NONCLUSTERED INDEX [IX_ConfineMachine_EnjoinOverDate] ON [dbo].[ConfineMachine] 
(
	[EnjoinOverDate] ASC
)
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ConfineMachine', N'COLUMN',N'MachineSerial'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��������' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineMachine', @level2type=N'COLUMN',@level2name=N'MachineSerial'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ConfineMachine', N'COLUMN',N'EnjoinLogon'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���Ƶ�¼' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineMachine', @level2type=N'COLUMN',@level2name=N'EnjoinLogon'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ConfineMachine', N'COLUMN',N'EnjoinRegister'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'����ע��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineMachine', @level2type=N'COLUMN',@level2name=N'EnjoinRegister'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ConfineMachine', N'COLUMN',N'EnjoinOverDate'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'����ʱ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineMachine', @level2type=N'COLUMN',@level2name=N'EnjoinOverDate'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ConfineMachine', N'COLUMN',N'CollectDate'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�ռ�����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineMachine', @level2type=N'COLUMN',@level2name=N'CollectDate'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ConfineMachine', N'COLUMN',N'CollectNote'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���뱸ע' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ConfineMachine', @level2type=N'COLUMN',@level2name=N'CollectNote'
GO
/****** ����:  Table [dbo].[GameIdentifier]    �ű�����: 01/23/2008 14:55:03 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[dbo].[GameIdentifier]') AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
BEGIN
CREATE TABLE [dbo].[GameIdentifier](
	[UserID] [int] IDENTITY(1,1) NOT NULL,
	[GameID] [int] NOT NULL,
	[IDLevel] [int] NOT NULL CONSTRAINT [DF_GameIdentifiers_IDLevel]  DEFAULT ((0)),
 CONSTRAINT [PK_GameIdentifier_UserID] PRIMARY KEY CLUSTERED 
(
	[UserID] ASC
)
)
END
GO

/****** ����:  Index [IX_GameIdentifier_GameID]    �ű�����: 01/23/2008 14:55:03 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[GameIdentifier]') AND name = N'IX_GameIdentifier_GameID')
CREATE UNIQUE NONCLUSTERED INDEX [IX_GameIdentifier_GameID] ON [dbo].[GameIdentifier] 
(
	[GameID] ASC
)
GO

/****** ����:  Index [IX_GameIdentifier_IDLevel]    �ű�����: 01/23/2008 14:55:03 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[GameIdentifier]') AND name = N'IX_GameIdentifier_IDLevel')
CREATE NONCLUSTERED INDEX [IX_GameIdentifier_IDLevel] ON [dbo].[GameIdentifier] 
(
	[IDLevel] ASC
)
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameIdentifier', N'COLUMN',N'UserID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û���ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameIdentifier', @level2type=N'COLUMN',@level2name=N'UserID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameIdentifier', N'COLUMN',N'GameID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��Ϸ��ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameIdentifier', @level2type=N'COLUMN',@level2name=N'GameID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameIdentifier', N'COLUMN',N'IDLevel'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��ʶ�ȼ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameIdentifier', @level2type=N'COLUMN',@level2name=N'IDLevel'
GO
/****** ����:  Table [dbo].[IndividualDatum]    �ű�����: 01/23/2008 14:55:03 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[dbo].[IndividualDatum]') AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
BEGIN
CREATE TABLE [dbo].[IndividualDatum](
	[UserID] [int] NOT NULL,
	[Compellation] [nvarchar](16) NOT NULL CONSTRAINT [DF_IndividualDatum_Compellation]  DEFAULT (''),
	[QQ] [nvarchar](16) NOT NULL,
	[EMail] [nvarchar](32) NOT NULL,
	[SeatPhone] [nvarchar](32) NOT NULL CONSTRAINT [DF_IndividualDatum_SeatPhone]  DEFAULT (''),
	[MobilePhone] [nvarchar](16) NOT NULL CONSTRAINT [DF_IndividualDatum_MobilePhone]  DEFAULT (''),
	[DwellingPlace] [nvarchar](128) NOT NULL CONSTRAINT [DF_IndividualDatum_DwellingPlace]  DEFAULT (''),
	[PostalCode] [nvarchar](8) NOT NULL CONSTRAINT [DF_IndividualDatum_PostalCode]  DEFAULT (''),
	[CollectDate] [datetime] NOT NULL CONSTRAINT [DF_IndividualDatum_CollectDate]  DEFAULT (getdate()),
	[UserNote] [nvarchar](256) NOT NULL CONSTRAINT [DF_IndividualDatum_UserNote]  DEFAULT (''),
 CONSTRAINT [PK_IndividualDatum_UserID] PRIMARY KEY CLUSTERED 
(
	[UserID] ASC
)
)
END
GO

/****** ����:  Index [IX_IndividualDatum_CollectDate]    �ű�����: 01/23/2008 14:55:03 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[IndividualDatum]') AND name = N'IX_IndividualDatum_CollectDate')
CREATE NONCLUSTERED INDEX [IX_IndividualDatum_CollectDate] ON [dbo].[IndividualDatum] 
(
	[UserID] ASC,
	[CollectDate] ASC
)
GO

/****** ����:  Index [IX_IndividualDatum_Compellation]    �ű�����: 01/23/2008 14:55:03 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[IndividualDatum]') AND name = N'IX_IndividualDatum_Compellation')
CREATE NONCLUSTERED INDEX [IX_IndividualDatum_Compellation] ON [dbo].[IndividualDatum] 
(
	[Compellation] ASC
)
GO

/****** ����:  Index [IX_IndividualDatum_EMail]    �ű�����: 01/23/2008 14:55:03 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[IndividualDatum]') AND name = N'IX_IndividualDatum_EMail')
CREATE NONCLUSTERED INDEX [IX_IndividualDatum_EMail] ON [dbo].[IndividualDatum] 
(
	[EMail] ASC
)
GO

/****** ����:  Index [IX_IndividualDatum_MobilePhone]    �ű�����: 01/23/2008 14:55:03 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[IndividualDatum]') AND name = N'IX_IndividualDatum_MobilePhone')
CREATE NONCLUSTERED INDEX [IX_IndividualDatum_MobilePhone] ON [dbo].[IndividualDatum] 
(
	[MobilePhone] ASC
)
GO

/****** ����:  Index [IX_IndividualDatum_SeatPhone]    �ű�����: 01/23/2008 14:55:03 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[IndividualDatum]') AND name = N'IX_IndividualDatum_SeatPhone')
CREATE NONCLUSTERED INDEX [IX_IndividualDatum_SeatPhone] ON [dbo].[IndividualDatum] 
(
	[SeatPhone] ASC
)
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'IndividualDatum', N'COLUMN',N'UserID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û���ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'IndividualDatum', @level2type=N'COLUMN',@level2name=N'UserID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'IndividualDatum', N'COLUMN',N'Compellation'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��ʵ����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'IndividualDatum', @level2type=N'COLUMN',@level2name=N'Compellation'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'IndividualDatum', N'COLUMN',N'SeatPhone'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�̶��绰' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'IndividualDatum', @level2type=N'COLUMN',@level2name=N'SeatPhone'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'IndividualDatum', N'COLUMN',N'MobilePhone'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�ֻ�����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'IndividualDatum', @level2type=N'COLUMN',@level2name=N'MobilePhone'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'IndividualDatum', N'COLUMN',N'DwellingPlace'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��ϸסַ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'IndividualDatum', @level2type=N'COLUMN',@level2name=N'DwellingPlace'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'IndividualDatum', N'COLUMN',N'PostalCode'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��������' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'IndividualDatum', @level2type=N'COLUMN',@level2name=N'PostalCode'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'IndividualDatum', N'COLUMN',N'CollectDate'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�ռ�����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'IndividualDatum', @level2type=N'COLUMN',@level2name=N'CollectDate'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'IndividualDatum', N'COLUMN',N'UserNote'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�û���ע' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'IndividualDatum', @level2type=N'COLUMN',@level2name=N'UserNote'
GO
/****** ����:  Table [dbo].[ReserveIdentifier]    �ű�����: 01/23/2008 14:55:03 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[dbo].[ReserveIdentifier]') AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
BEGIN
CREATE TABLE [dbo].[ReserveIdentifier](
	[GameID] [int] NOT NULL,
	[IDLevel] [int] NOT NULL CONSTRAINT [DF_Table1_IDLevel]  DEFAULT ((0)),
	[Distribute] [bit] NOT NULL CONSTRAINT [DF_ReserveIdentifiers_Distribute]  DEFAULT ((0)),
 CONSTRAINT [PK_ReserveIdentifier_GameID] PRIMARY KEY CLUSTERED 
(
	[GameID] ASC
)
)
END
GO

/****** ����:  Index [IX_ReserveIdentifier_IDLevel]    �ű�����: 01/23/2008 14:55:03 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[ReserveIdentifier]') AND name = N'IX_ReserveIdentifier_IDLevel')
CREATE NONCLUSTERED INDEX [IX_ReserveIdentifier_IDLevel] ON [dbo].[ReserveIdentifier] 
(
	[IDLevel] ASC
)
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ReserveIdentifier', N'COLUMN',N'GameID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��Ϸ��ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ReserveIdentifier', @level2type=N'COLUMN',@level2name=N'GameID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ReserveIdentifier', N'COLUMN',N'IDLevel'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��ʶ�ȼ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ReserveIdentifier', @level2type=N'COLUMN',@level2name=N'IDLevel'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'ReserveIdentifier', N'COLUMN',N'Distribute'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�����־' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'ReserveIdentifier', @level2type=N'COLUMN',@level2name=N'Distribute'
GO
/****** ����:  Table [dbo].[SystemStreamInfo]    �ű�����: 01/23/2008 14:55:03 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[dbo].[SystemStreamInfo]') AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
BEGIN
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
)
)
END
GO

/****** ����:  Index [IX_SystemStreamInfo_CollectDate]    �ű�����: 01/23/2008 14:55:03 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[SystemStreamInfo]') AND name = N'IX_SystemStreamInfo_CollectDate')
CREATE NONCLUSTERED INDEX [IX_SystemStreamInfo_CollectDate] ON [dbo].[SystemStreamInfo] 
(
	[CollectDate] ASC
)
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'SystemStreamInfo', N'COLUMN',N'DateID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���ڱ�ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'DateID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'SystemStreamInfo', N'COLUMN',N'WebLogonSuccess'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��¼�ɹ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'WebLogonSuccess'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'SystemStreamInfo', N'COLUMN',N'WebRegisterSuccess'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'ע��ɹ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'WebRegisterSuccess'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'SystemStreamInfo', N'COLUMN',N'GameLogonSuccess'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��¼�ɹ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'GameLogonSuccess'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'SystemStreamInfo', N'COLUMN',N'GameRegisterSuccess'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'ע��ɹ�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'GameRegisterSuccess'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'SystemStreamInfo', N'COLUMN',N'CollectDate'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'¼��ʱ��' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'SystemStreamInfo', @level2type=N'COLUMN',@level2name=N'CollectDate'