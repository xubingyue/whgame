
----------------------------------------------------------------------------------------------------

USE GameEducateDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[GSP_GR_RecordGameScore]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].[GSP_GR_RecordGameScore]
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO

----------------------------------------------------------------------------------------------------

-- 游戏记录
CREATE PROC GSP_GR_RecordGameScore
	@wKindID INT,								-- 游戏 I D
	@wServerID INT,								-- 房间 I D
	@wTableID INT,								-- 桌子号码
	@lWasteCount BIGINT,						-- 损耗数目
	@lRevenueCount BIGINT,						-- 游戏税收
	@dwPlayTimeCount INT,						-- 游戏时间
	@dwUserID1 INT=0,							-- 用户标识
	@lGameScore1 BIGINT=0,						-- 游戏积分
	@dwUserID2 INT=0,							-- 用户标识
	@lGameScore2 BIGINT=0,						-- 游戏积分
	@dwUserID3 INT=0,							-- 用户标识
	@lGameScore3 BIGINT=0,						-- 游戏积分
	@dwUserID4 INT=0,							-- 用户标识
	@lGameScore4 BIGINT=0,						-- 游戏积分
	@dwUserID5 INT=0,							-- 用户标识
	@lGameScore5 BIGINT=0,						-- 游戏积分
	@dwUserID6 INT=0,							-- 用户标识
	@lGameScore6 BIGINT=0,						-- 游戏积分
	@dwUserID7 INT=0,							-- 用户标识
	@lGameScore7 BIGINT=0,						-- 游戏积分
	@dwUserID8 INT=0,							-- 用户标识
	@lGameScore8 BIGINT=0						-- 游戏积分
WITH ENCRYPTION AS

-- 属性设置
SET NOCOUNT ON

-- 执行逻辑
BEGIN

	-- 插入记录
	INSERT RecordGameScore (KindID, ServerID, TableID, PlayTimeCount, UserID1, GameScore1, UserID2, GameScore2, UserID3, GameScore3, 
		UserID4, GameScore4, UserID5, GameScore5, UserID6, GameScore6, UserID7, GameScore7, UserID8, GameScore8)
	VALUES (@wKindID, @wServerID, @wTableID, @dwPlayTimeCount, @dwUserID1, @lGameScore1, @dwUserID2, @lGameScore2, @dwUserID3, @lGameScore3, 
		@dwUserID4, @lGameScore4, @dwUserID5, @lGameScore5, @dwUserID6, @lGameScore6, @dwUserID7, @lGameScore7, @dwUserID8, @lGameScore8)

END

RETURN 0

GO

----------------------------------------------------------------------------------------------------