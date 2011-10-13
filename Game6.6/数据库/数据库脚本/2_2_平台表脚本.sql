USE [GameServerInfoDB]
GO
/****** 对象:  Table [dbo].[DataBaseInfo]    脚本日期: 12/08/2008 11:51:42 ******/
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
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'数据库地址' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'DataBaseInfo', @level2type=N'COLUMN',@level2name=N'DBAddr'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'数据库端口' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'DataBaseInfo', @level2type=N'COLUMN',@level2name=N'DBPort'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'数据库用户' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'DataBaseInfo', @level2type=N'COLUMN',@level2name=N'DBUser'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'数据库密码' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'DataBaseInfo', @level2type=N'COLUMN',@level2name=N'DBPassword'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'备注信息' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'DataBaseInfo', @level2type=N'COLUMN',@level2name=N'Information'
GO
/****** 对象:  Table [dbo].[GameKindItem]    脚本日期: 12/08/2008 11:51:42 ******/
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

/****** 对象:  Index [IX_GameKindItem_JoinID]    脚本日期: 12/08/2008 11:51:42 ******/
CREATE NONCLUSTERED INDEX [IX_GameKindItem_JoinID] ON [dbo].[GameKindItem] 
(
	[JoinID] ASC
) ON [PRIMARY]
GO

/****** 对象:  Index [IX_GameKindItem_SortID]    脚本日期: 12/08/2008 11:51:42 ******/
CREATE NONCLUSTERED INDEX [IX_GameKindItem_SortID] ON [dbo].[GameKindItem] 
(
	[SortID] ASC
) ON [PRIMARY]
GO

/****** 对象:  Index [IX_GameKindItem_TypeID]    脚本日期: 12/08/2008 11:51:42 ******/
CREATE NONCLUSTERED INDEX [IX_GameKindItem_TypeID] ON [dbo].[GameKindItem] 
(
	[TypeID] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'类型标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'KindID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'种类标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'TypeID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'挂接标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'JoinID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'排序标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'SortID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'类型名字' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'KindName'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'进程名字' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'ProcessName'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'版本号码' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'MaxVersion'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'数据库名字' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'DataBaseName'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'无效标志' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'Nullity'
GO
/****** 对象:  Table [dbo].[GameNodeItem]    脚本日期: 12/08/2008 11:51:42 ******/
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

/****** 对象:  Index [IX_GameStationItem_JoinID]    脚本日期: 12/08/2008 11:51:42 ******/
CREATE NONCLUSTERED INDEX [IX_GameStationItem_JoinID] ON [dbo].[GameNodeItem] 
(
	[JoinID] ASC
) ON [PRIMARY]
GO

/****** 对象:  Index [IX_GameStationItem_KindID]    脚本日期: 12/08/2008 11:51:42 ******/
CREATE NONCLUSTERED INDEX [IX_GameStationItem_KindID] ON [dbo].[GameNodeItem] 
(
	[KindID] ASC
) ON [PRIMARY]
GO

/****** 对象:  Index [IX_GameStationItem_SortID]    脚本日期: 12/08/2008 11:51:42 ******/
CREATE NONCLUSTERED INDEX [IX_GameStationItem_SortID] ON [dbo].[GameNodeItem] 
(
	[SortID] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'节点标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameNodeItem', @level2type=N'COLUMN',@level2name=N'NodeID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'类型标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameNodeItem', @level2type=N'COLUMN',@level2name=N'KindID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'挂接标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameNodeItem', @level2type=N'COLUMN',@level2name=N'JoinID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'排序标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameNodeItem', @level2type=N'COLUMN',@level2name=N'SortID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'站点名字' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameNodeItem', @level2type=N'COLUMN',@level2name=N'NodeName'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'无效标志' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameNodeItem', @level2type=N'COLUMN',@level2name=N'Nullity'
GO
/****** 对象:  Table [dbo].[GameTypeItem]    脚本日期: 12/08/2008 11:51:42 ******/
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

/****** 对象:  Index [IX_GameTypeItem_JoinID]    脚本日期: 12/08/2008 11:51:42 ******/
CREATE NONCLUSTERED INDEX [IX_GameTypeItem_JoinID] ON [dbo].[GameTypeItem] 
(
	[JoinID] ASC
) ON [PRIMARY]
GO

/****** 对象:  Index [IX_GameTypeItem_SortID]    脚本日期: 12/08/2008 11:51:42 ******/
CREATE NONCLUSTERED INDEX [IX_GameTypeItem_SortID] ON [dbo].[GameTypeItem] 
(
	[SortID] ASC
) ON [PRIMARY]
GO

/****** 对象:  Index [IX_GameTypeItem_TypeName]    脚本日期: 12/08/2008 11:51:42 ******/
CREATE NONCLUSTERED INDEX [IX_GameTypeItem_TypeName] ON [dbo].[GameTypeItem] 
(
	[TypeName] ASC
) ON [PRIMARY]
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'类型标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameTypeItem', @level2type=N'COLUMN',@level2name=N'TypeID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'挂接标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameTypeItem', @level2type=N'COLUMN',@level2name=N'JoinID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'排序标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameTypeItem', @level2type=N'COLUMN',@level2name=N'SortID'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'类型名字' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameTypeItem', @level2type=N'COLUMN',@level2name=N'TypeName'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'无效标志' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameTypeItem', @level2type=N'COLUMN',@level2name=N'Nullity'
GO
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'类型信息' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameTypeItem'