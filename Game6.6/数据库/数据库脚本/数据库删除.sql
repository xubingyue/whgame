
USE master
GO

IF EXISTS (SELECT name FROM master.dbo.sysdatabases WHERE name = N'GameUserDB')
DROP DATABASE [GameUserDB]
GO

IF EXISTS (SELECT name FROM master.dbo.sysdatabases WHERE name = N'GameTreasureDB')
DROP DATABASE [GameTreasureDB]
GO

IF EXISTS (SELECT name FROM master.dbo.sysdatabases WHERE name = N'GameServerInfoDB')
DROP DATABASE [GameServerInfoDB]
GO

IF EXISTS (SELECT name FROM master.dbo.sysdatabases WHERE name = N'GameScoreDB')
DROP DATABASE [GameScoreDB]
GO
