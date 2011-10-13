
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

-- ��Ϸ��¼
CREATE PROC GSP_GR_RecordGameScore
	@wKindID INT,								-- ��Ϸ I D
	@wServerID INT,								-- ���� I D
	@wTableID INT,								-- ���Ӻ���
	@lWasteCount BIGINT,						-- �����Ŀ
	@lRevenueCount BIGINT,						-- ��Ϸ˰��
	@dwPlayTimeCount INT,						-- ��Ϸʱ��
	@dwUserID1 INT=0,							-- �û���ʶ
	@lGameScore1 BIGINT=0,						-- ��Ϸ����
	@dwUserID2 INT=0,							-- �û���ʶ
	@lGameScore2 BIGINT=0,						-- ��Ϸ����
	@dwUserID3 INT=0,							-- �û���ʶ
	@lGameScore3 BIGINT=0,						-- ��Ϸ����
	@dwUserID4 INT=0,							-- �û���ʶ
	@lGameScore4 BIGINT=0,						-- ��Ϸ����
	@dwUserID5 INT=0,							-- �û���ʶ
	@lGameScore5 BIGINT=0,						-- ��Ϸ����
	@dwUserID6 INT=0,							-- �û���ʶ
	@lGameScore6 BIGINT=0,						-- ��Ϸ����
	@dwUserID7 INT=0,							-- �û���ʶ
	@lGameScore7 BIGINT=0,						-- ��Ϸ����
	@dwUserID8 INT=0,							-- �û���ʶ
	@lGameScore8 BIGINT=0						-- ��Ϸ����
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ִ���߼�
BEGIN

	-- �����¼
	INSERT RecordGameScore (KindID, ServerID, TableID, PlayTimeCount, UserID1, GameScore1, UserID2, GameScore2, UserID3, GameScore3, 
		UserID4, GameScore4, UserID5, GameScore5, UserID6, GameScore6, UserID7, GameScore7, UserID8, GameScore8)
	VALUES (@wKindID, @wServerID, @wTableID, @dwPlayTimeCount, @dwUserID1, @lGameScore1, @dwUserID2, @lGameScore2, @dwUserID3, @lGameScore3, 
		@dwUserID4, @lGameScore4, @dwUserID5, @lGameScore5, @dwUserID6, @lGameScore6, @dwUserID7, @lGameScore7, @dwUserID8, @lGameScore8)

END

RETURN 0

GO

----------------------------------------------------------------------------------------------------