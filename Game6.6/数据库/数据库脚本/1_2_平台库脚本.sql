USE [master]
GO
/****** 对象:  Database [GameServerInfoDB]    脚本日期: 12/08/2008 11:49:33 ******/
CREATE DATABASE [GameServerInfoDB] ON  PRIMARY 
( NAME = N'GameServerInfoDB', FILENAME = N'D:\数据库\GameServerInfoDB.mdf' , SIZE = 2304KB , MAXSIZE = UNLIMITED, FILEGROWTH = 1024KB )
 LOG ON 
( NAME = N'GameServerInfoDB_log', FILENAME = N'D:\数据库\GameServerInfoDB_log.LDF' , SIZE = 504KB , MAXSIZE = 2048GB , FILEGROWTH = 10%)
 COLLATE Chinese_PRC_CI_AS
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [GameServerInfoDB].[dbo].[sp_fulltext_database] @action = 'enable'
end
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