USE [master]
GO
/****** 对象:  Database [GameTreasureDB]    脚本日期: 12/08/2008 11:49:53 ******/
CREATE DATABASE [GameTreasureDB] ON  PRIMARY 
( NAME = N'GameTreasureDB', FILENAME = N'D:\数据库\GameTreasureDB.mdf' , SIZE = 4352KB , MAXSIZE = UNLIMITED, FILEGROWTH = 1024KB )
 LOG ON 
( NAME = N'GameTreasureDB_log', FILENAME = N'D:\数据库\GameTreasureDB_log.LDF' , SIZE = 12352KB , MAXSIZE = 2048GB , FILEGROWTH = 10%)
 COLLATE Chinese_PRC_CI_AS
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [GameTreasureDB].[dbo].[sp_fulltext_database] @action = 'enable'
end
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