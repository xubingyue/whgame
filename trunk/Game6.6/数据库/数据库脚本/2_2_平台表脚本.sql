USE [GameServerInfoDB]
GO
/****** ����:  Table [dbo].[DataBaseInfo]    �ű�����: 12/08/2008 11:51:42 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[DataBaseInfo](
	[DBAddr] [nvarchar](15) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[DBPort] [int] NOT NULL CONSTRAINT [DF_TABLE1_DataBasePort]  DEFAULT ((1433)),
	[DBUser] [nvarchar](512) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[DBPassword] [nvarchar](512) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[Information] [nvarchar](128) COLLATE Chinese_PRC_CI_AS NOT NULL CONSTRAINT [DF_SQLConnectInfo_NoteInfo]  DEFAULT (''),
 CONSTRAINT [PK_DataBaseInfo_DBAddr] PRIMARY KEY CLUSTERED 
(
	[DBAddr] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���ݿ��ַ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'DataBaseInfo', @level2type=N'COLUMN',@level2name=N'DBAddr'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���ݿ�˿�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'DataBaseInfo', @level2type=N'COLUMN',@level2name=N'DBPort'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���ݿ��û�' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'DataBaseInfo', @level2type=N'COLUMN',@level2name=N'DBUser'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���ݿ�����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'DataBaseInfo', @level2type=N'COLUMN',@level2name=N'DBPassword'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��ע��Ϣ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'DataBaseInfo', @level2type=N'COLUMN',@level2name=N'Information'
GO
/****** ����:  Table [dbo].[GameKindItem]    �ű�����: 12/08/2008 11:51:42 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[GameKindItem](
	[KindID] [int] NOT NULL,
	[TypeID] [int] NOT NULL,
	[JoinID] [int] NOT NULL CONSTRAINT [DF_GameKindItem_JoinID]  DEFAULT ((0)),
	[SortID] [int] NOT NULL CONSTRAINT [DF_GameKindItem_SortID]  DEFAULT ((1000)),
	[KindName] [nvarchar](32) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[ProcessName] [nvarchar](32) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[MaxVersion] [int] NOT NULL CONSTRAINT [DF_GameKindItem_MaxVersion]  DEFAULT ((65542)),
	[DataBaseName] [nvarchar](32) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[Nullity] [bit] NOT NULL CONSTRAINT [DF_GameKindItem_Nullity]  DEFAULT ((0)),
 CONSTRAINT [PK_GameKindItem] PRIMARY KEY CLUSTERED 
(
	[KindID] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO

/****** ����:  Index [IX_GameKindItem_JoinID]    �ű�����: 12/08/2008 11:51:42 ******/
CREATE NONCLUSTERED INDEX [IX_GameKindItem_JoinID] ON [dbo].[GameKindItem] 
(
	[JoinID] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_GameKindItem_SortID]    �ű�����: 12/08/2008 11:51:42 ******/
CREATE NONCLUSTERED INDEX [IX_GameKindItem_SortID] ON [dbo].[GameKindItem] 
(
	[SortID] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_GameKindItem_TypeID]    �ű�����: 12/08/2008 11:51:42 ******/
CREATE NONCLUSTERED INDEX [IX_GameKindItem_TypeID] ON [dbo].[GameKindItem] 
(
	[TypeID] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���ͱ�ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'KindID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�����ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'TypeID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�ҽӱ�ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'JoinID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�����ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'SortID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��������' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'KindName'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��������' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'ProcessName'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�汾����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'MaxVersion'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���ݿ�����' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'DataBaseName'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��Ч��־' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'Nullity'
GO
/****** ����:  Table [dbo].[GameNodeItem]    �ű�����: 12/08/2008 11:51:42 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[GameNodeItem](
	[NodeID] [int] NOT NULL,
	[KindID] [int] NOT NULL,
	[JoinID] [int] NOT NULL CONSTRAINT [DF_GameStationItem_JoinID]  DEFAULT ((0)),
	[SortID] [int] NOT NULL CONSTRAINT [DF_GameStationItem_SortID]  DEFAULT ((1000)),
	[NodeName] [nvarchar](32) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[Nullity] [bit] NOT NULL CONSTRAINT [DF_GameStationItem_Nullity]  DEFAULT ((0)),
 CONSTRAINT [PK_GameNodeItem] PRIMARY KEY CLUSTERED 
(
	[NodeID] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO

/****** ����:  Index [IX_GameStationItem_JoinID]    �ű�����: 12/08/2008 11:51:42 ******/
CREATE NONCLUSTERED INDEX [IX_GameStationItem_JoinID] ON [dbo].[GameNodeItem] 
(
	[JoinID] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_GameStationItem_KindID]    �ű�����: 12/08/2008 11:51:42 ******/
CREATE NONCLUSTERED INDEX [IX_GameStationItem_KindID] ON [dbo].[GameNodeItem] 
(
	[KindID] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_GameStationItem_SortID]    �ű�����: 12/08/2008 11:51:42 ******/
CREATE NONCLUSTERED INDEX [IX_GameStationItem_SortID] ON [dbo].[GameNodeItem] 
(
	[SortID] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�ڵ��ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameNodeItem', @level2type=N'COLUMN',@level2name=N'NodeID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���ͱ�ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameNodeItem', @level2type=N'COLUMN',@level2name=N'KindID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�ҽӱ�ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameNodeItem', @level2type=N'COLUMN',@level2name=N'JoinID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�����ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameNodeItem', @level2type=N'COLUMN',@level2name=N'SortID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'վ������' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameNodeItem', @level2type=N'COLUMN',@level2name=N'NodeName'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��Ч��־' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameNodeItem', @level2type=N'COLUMN',@level2name=N'Nullity'
GO
/****** ����:  Table [dbo].[GameTypeItem]    �ű�����: 12/08/2008 11:51:42 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[GameTypeItem](
	[TypeID] [int] NOT NULL,
	[JoinID] [int] NOT NULL CONSTRAINT [DF_GameTypeItem_JoinID]  DEFAULT ((0)),
	[SortID] [int] NOT NULL CONSTRAINT [DF_GameTypeItem_SortID]  DEFAULT ((1000)),
	[TypeName] [nvarchar](32) COLLATE Chinese_PRC_CI_AS NOT NULL,
	[Nullity] [bit] NOT NULL CONSTRAINT [DF_GameTypeItem_Nullity]  DEFAULT ((0)),
 CONSTRAINT [PK_GameTypeItem_TypeID] PRIMARY KEY CLUSTERED 
(
	[TypeID] ASC
) ON [PRIMARY]
) ON [PRIMARY]

GO

/****** ����:  Index [IX_GameTypeItem_JoinID]    �ű�����: 12/08/2008 11:51:42 ******/
CREATE NONCLUSTERED INDEX [IX_GameTypeItem_JoinID] ON [dbo].[GameTypeItem] 
(
	[JoinID] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_GameTypeItem_SortID]    �ű�����: 12/08/2008 11:51:42 ******/
CREATE NONCLUSTERED INDEX [IX_GameTypeItem_SortID] ON [dbo].[GameTypeItem] 
(
	[SortID] ASC
) ON [PRIMARY]
GO

/****** ����:  Index [IX_GameTypeItem_TypeName]    �ű�����: 12/08/2008 11:51:42 ******/
CREATE NONCLUSTERED INDEX [IX_GameTypeItem_TypeName] ON [dbo].[GameTypeItem] 
(
	[TypeName] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'���ͱ�ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameTypeItem', @level2type=N'COLUMN',@level2name=N'TypeID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�ҽӱ�ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameTypeItem', @level2type=N'COLUMN',@level2name=N'JoinID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'�����ʶ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameTypeItem', @level2type=N'COLUMN',@level2name=N'SortID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��������' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameTypeItem', @level2type=N'COLUMN',@level2name=N'TypeName'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'��Ч��־' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameTypeItem', @level2type=N'COLUMN',@level2name=N'Nullity'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'������Ϣ' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameTypeItem'