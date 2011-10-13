
USE master
GO

IF EXISTS (SELECT name FROM master.dbo.sysdatabases WHERE name = N'UserDB')
DROP DATABASE [UserDB]
GO

IF EXISTS (SELECT name FROM master.dbo.sysdatabases WHERE name = N'GameTreasureDB')
DROP DATABASE [GameTreasureDB]
GO

IF EXISTS (SELECT name FROM master.dbo.sysdatabases WHERE name = N'GameServerInfoDB')
DROP DATABASE [GameServerInfoDB]
GO

IF EXISTS (SELECT name FROM master.dbo.sysdatabases WHERE name = N'GameScoreDB')
DROP DATABASE [GameScoreDB]

IF EXISTS (SELECT name FROM master.dbo.sysdatabases WHERE name = N'GameEducateDB')
DROP DATABASE [GameEducateDB]
GO

