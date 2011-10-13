USE [master]
GO
/****** 对象:  Database [GameServerInfoDB]    脚本日期: 01/23/2008 14:57:41 ******/
IF NOT EXISTS (SELECT name FROM master.dbo.sysdatabases WHERE name = N'GameServerInfoDB')
BEGIN
CREATE DATABASE [GameServerInfoDB]
END

GO
ALTER DATABASE [GameServerInfoDB] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [GameServerInfoDB] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [GameServerInfoDB] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [GameServerInfoDB] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [GameServerInfoDB] SET ARITHABORT OFF 
GO
ALTER DATABASE [GameServerInfoDB] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [GameServerInfoDB] SET AUTO_CREATE_STATISTICS ON 
GO
ALTER DATABASE [GameServerInfoDB] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [GameServerInfoDB] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [GameServerInfoDB] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [GameServerInfoDB] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [GameServerInfoDB] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [GameServerInfoDB] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [GameServerInfoDB] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [GameServerInfoDB] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [GameServerInfoDB] SET  READ_WRITE 
GO
ALTER DATABASE [GameServerInfoDB] SET RECOVERY FULL 
GO
ALTER DATABASE [GameServerInfoDB] SET  MULTI_USER 
GO
if ( ((@@microsoftversion / power(2, 24) = 8) and (@@microsoftversion & 0xffff >= 760)) or 
		(@@microsoftversion / power(2, 24) >= 9) )begin 
	exec dbo.sp_dboption @dbname =  N'GameServerInfoDB', @optname = 'db chaining', @optvalue = 'OFF'
 end

USE [GameServerInfoDB]
GO
/****** 对象:  Table [dbo].[DataBaseInfo]    脚本日期: 01/23/2008 14:57:55 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[dbo].[DataBaseInfo]') AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
BEGIN
CREATE TABLE [dbo].[DataBaseInfo](
	[DBAddr] [nvarchar](15) NOT NULL,
	[DBPort] [int] NOT NULL CONSTRAINT [DF_TABLE1_DataBasePort]  DEFAULT ((1433)),
	[DBUser] [nvarchar](512) NOT NULL,
	[DBPassword] [nvarchar](512) NOT NULL,
	[Information] [nvarchar](128) NOT NULL CONSTRAINT [DF_SQLConnectInfo_NoteInfo]  DEFAULT (''),
 CONSTRAINT [PK_DataBaseInfo_DBAddr] PRIMARY KEY CLUSTERED 
(
	[DBAddr] ASC
)
)
END
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'DataBaseInfo', N'COLUMN',N'DBAddr'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'数据库地址' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'DataBaseInfo', @level2type=N'COLUMN',@level2name=N'DBAddr'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'DataBaseInfo', N'COLUMN',N'DBPort'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'数据库端口' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'DataBaseInfo', @level2type=N'COLUMN',@level2name=N'DBPort'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'DataBaseInfo', N'COLUMN',N'DBUser'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'数据库用户' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'DataBaseInfo', @level2type=N'COLUMN',@level2name=N'DBUser'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'DataBaseInfo', N'COLUMN',N'DBPassword'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'数据库密码' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'DataBaseInfo', @level2type=N'COLUMN',@level2name=N'DBPassword'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'DataBaseInfo', N'COLUMN',N'Information'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'备注信息' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'DataBaseInfo', @level2type=N'COLUMN',@level2name=N'Information'
GO
/****** 对象:  Table [dbo].[GameKindItem]    脚本日期: 01/23/2008 14:57:55 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[dbo].[GameKindItem]') AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
BEGIN
CREATE TABLE [dbo].[GameKindItem](
	[KindID] [int] NOT NULL,
	[TypeID] [int] NOT NULL,
	[JoinID] [int] NOT NULL CONSTRAINT [DF_GameKindItem_JoinID]  DEFAULT ((0)),
	[SortID] [int] NOT NULL CONSTRAINT [DF_GameKindItem_SortID]  DEFAULT ((1000)),
	[KindName] [nvarchar](32) NOT NULL,
	[ProcessName] [nvarchar](32) NOT NULL,
	[MaxVersion] [int] NOT NULL CONSTRAINT [DF_GameKindItem_MaxVersion]  DEFAULT ((65542)),
	[DataBaseName] [nvarchar](32) NOT NULL,
	[Nullity] [bit] NOT NULL CONSTRAINT [DF_GameKindItem_Nullity]  DEFAULT ((0)),
 CONSTRAINT [PK_GameKindItem] PRIMARY KEY CLUSTERED 
(
	[KindID] ASC
)
)
END
GO

/****** 对象:  Index [IX_GameKindItem_JoinID]    脚本日期: 01/23/2008 14:57:55 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[GameKindItem]') AND name = N'IX_GameKindItem_JoinID')
CREATE NONCLUSTERED INDEX [IX_GameKindItem_JoinID] ON [dbo].[GameKindItem] 
(
	[JoinID] ASC
)
GO

/****** 对象:  Index [IX_GameKindItem_SortID]    脚本日期: 01/23/2008 14:57:55 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[GameKindItem]') AND name = N'IX_GameKindItem_SortID')
CREATE NONCLUSTERED INDEX [IX_GameKindItem_SortID] ON [dbo].[GameKindItem] 
(
	[SortID] ASC
)
GO

/****** 对象:  Index [IX_GameKindItem_TypeID]    脚本日期: 01/23/2008 14:57:55 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[GameKindItem]') AND name = N'IX_GameKindItem_TypeID')
CREATE NONCLUSTERED INDEX [IX_GameKindItem_TypeID] ON [dbo].[GameKindItem] 
(
	[TypeID] ASC
)
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameKindItem', N'COLUMN',N'KindID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'类型标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'KindID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameKindItem', N'COLUMN',N'TypeID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'种类标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'TypeID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameKindItem', N'COLUMN',N'JoinID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'挂接标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'JoinID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameKindItem', N'COLUMN',N'SortID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'排序标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'SortID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameKindItem', N'COLUMN',N'KindName'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'类型名字' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'KindName'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameKindItem', N'COLUMN',N'ProcessName'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'进程名字' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'ProcessName'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameKindItem', N'COLUMN',N'MaxVersion'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'版本号码' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'MaxVersion'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameKindItem', N'COLUMN',N'DataBaseName'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'数据库名字' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'DataBaseName'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameKindItem', N'COLUMN',N'Nullity'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'无效标志' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameKindItem', @level2type=N'COLUMN',@level2name=N'Nullity'
GO
/****** 对象:  Table [dbo].[GameNodeItem]    脚本日期: 01/23/2008 14:57:55 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[dbo].[GameNodeItem]') AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
BEGIN
CREATE TABLE [dbo].[GameNodeItem](
	[NodeID] [int] NOT NULL,
	[KindID] [int] NOT NULL,
	[JoinID] [int] NOT NULL CONSTRAINT [DF_GameStationItem_JoinID]  DEFAULT ((0)),
	[SortID] [int] NOT NULL CONSTRAINT [DF_GameStationItem_SortID]  DEFAULT ((1000)),
	[NodeName] [nvarchar](32) NOT NULL,
	[Nullity] [bit] NOT NULL CONSTRAINT [DF_GameStationItem_Nullity]  DEFAULT ((0)),
 CONSTRAINT [PK_GameNodeItem] PRIMARY KEY CLUSTERED 
(
	[NodeID] ASC
)
)
END
GO

/****** 对象:  Index [IX_GameStationItem_JoinID]    脚本日期: 01/23/2008 14:57:55 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[GameNodeItem]') AND name = N'IX_GameStationItem_JoinID')
CREATE NONCLUSTERED INDEX [IX_GameStationItem_JoinID] ON [dbo].[GameNodeItem] 
(
	[JoinID] ASC
)
GO

/****** 对象:  Index [IX_GameStationItem_KindID]    脚本日期: 01/23/2008 14:57:55 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[GameNodeItem]') AND name = N'IX_GameStationItem_KindID')
CREATE NONCLUSTERED INDEX [IX_GameStationItem_KindID] ON [dbo].[GameNodeItem] 
(
	[KindID] ASC
)
GO

/****** 对象:  Index [IX_GameStationItem_SortID]    脚本日期: 01/23/2008 14:57:55 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[GameNodeItem]') AND name = N'IX_GameStationItem_SortID')
CREATE NONCLUSTERED INDEX [IX_GameStationItem_SortID] ON [dbo].[GameNodeItem] 
(
	[SortID] ASC
)
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameNodeItem', N'COLUMN',N'NodeID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'节点标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameNodeItem', @level2type=N'COLUMN',@level2name=N'NodeID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameNodeItem', N'COLUMN',N'KindID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'类型标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameNodeItem', @level2type=N'COLUMN',@level2name=N'KindID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameNodeItem', N'COLUMN',N'JoinID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'挂接标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameNodeItem', @level2type=N'COLUMN',@level2name=N'JoinID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameNodeItem', N'COLUMN',N'SortID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'排序标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameNodeItem', @level2type=N'COLUMN',@level2name=N'SortID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameNodeItem', N'COLUMN',N'NodeName'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'站点名字' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameNodeItem', @level2type=N'COLUMN',@level2name=N'NodeName'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameNodeItem', N'COLUMN',N'Nullity'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'无效标志' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameNodeItem', @level2type=N'COLUMN',@level2name=N'Nullity'
GO
/****** 对象:  Table [dbo].[GameTypeItem]    脚本日期: 01/23/2008 14:57:55 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[dbo].[GameTypeItem]') AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
BEGIN
CREATE TABLE [dbo].[GameTypeItem](
	[TypeID] [int] NOT NULL,
	[JoinID] [int] NOT NULL CONSTRAINT [DF_GameTypeItem_JoinID]  DEFAULT ((0)),
	[SortID] [int] NOT NULL CONSTRAINT [DF_GameTypeItem_SortID]  DEFAULT ((1000)),
	[TypeName] [nvarchar](32) NOT NULL,
	[Nullity] [bit] NOT NULL CONSTRAINT [DF_GameTypeItem_Nullity]  DEFAULT ((0)),
 CONSTRAINT [PK_GameTypeItem_TypeID] PRIMARY KEY CLUSTERED 
(
	[TypeID] ASC
)
)
END
GO

/****** 对象:  Index [IX_GameTypeItem_JoinID]    脚本日期: 01/23/2008 14:57:55 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[GameTypeItem]') AND name = N'IX_GameTypeItem_JoinID')
CREATE NONCLUSTERED INDEX [IX_GameTypeItem_JoinID] ON [dbo].[GameTypeItem] 
(
	[JoinID] ASC
)
GO

/****** 对象:  Index [IX_GameTypeItem_SortID]    脚本日期: 01/23/2008 14:57:55 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[GameTypeItem]') AND name = N'IX_GameTypeItem_SortID')
CREATE NONCLUSTERED INDEX [IX_GameTypeItem_SortID] ON [dbo].[GameTypeItem] 
(
	[SortID] ASC
)
GO

/****** 对象:  Index [IX_GameTypeItem_TypeName]    脚本日期: 01/23/2008 14:57:55 ******/
IF NOT EXISTS (SELECT * FROM dbo.sysindexes WHERE id = OBJECT_ID(N'[dbo].[GameTypeItem]') AND name = N'IX_GameTypeItem_TypeName')
CREATE NONCLUSTERED INDEX [IX_GameTypeItem_TypeName] ON [dbo].[GameTypeItem] 
(
	[TypeName] ASC
)
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameTypeItem', N'COLUMN',N'TypeID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'类型标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameTypeItem', @level2type=N'COLUMN',@level2name=N'TypeID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameTypeItem', N'COLUMN',N'JoinID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'挂接标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameTypeItem', @level2type=N'COLUMN',@level2name=N'JoinID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameTypeItem', N'COLUMN',N'SortID'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'排序标识' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameTypeItem', @level2type=N'COLUMN',@level2name=N'SortID'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameTypeItem', N'COLUMN',N'TypeName'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'类型名字' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameTypeItem', @level2type=N'COLUMN',@level2name=N'TypeName'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameTypeItem', N'COLUMN',N'Nullity'))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'无效标志' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameTypeItem', @level2type=N'COLUMN',@level2name=N'Nullity'
GO
IF NOT EXISTS (SELECT * FROM ::fn_listextendedproperty(N'MS_Description' , N'USER',N'dbo', N'TABLE',N'GameTypeItem', NULL,NULL))
EXEC dbo.sp_addextendedproperty @name=N'MS_Description', @value=N'类型信息' , @level0type=N'USER',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GameTypeItem'