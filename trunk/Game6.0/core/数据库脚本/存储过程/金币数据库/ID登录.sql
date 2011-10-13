
----------------------------------------------------------------------------------------------------

USE GameTreasureDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[GSP_GR_EfficacyUserID]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].[GSP_GR_EfficacyUserID]
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO

----------------------------------------------------------------------------------------------------

-- I D ��¼
CREATE PROC GSP_GR_EfficacyUserID
	@dwUserID INT,								-- �û� I D
	@strPassword NCHAR(32),						-- �û�����
	@strClientIP NVARCHAR(15),					-- ���ӵ�ַ
	@strMachineSerial NCHAR(32),				-- ������ʶ
	@wKindID SMALLINT,							-- ��Ϸ I D
	@wServerID SMALLINT							-- ���� I D
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ������Ϣ
DECLARE @UserID INT
DECLARE @FaceID SMALLINT
DECLARE @Accounts NVARCHAR(31)
DECLARE @UnderWrite NVARCHAR(63)

-- ��չ��Ϣ
DECLARE @GameID INT
DECLARE @GroupID INT
DECLARE @UserRight INT
DECLARE @Gender TINYINT
DECLARE @MasterRight INT
DECLARE @MasterOrder SMALLINT
DECLARE @MemberOrder SMALLINT
DECLARE @GroupName NVARCHAR(31)

-- ���ֱ���
DECLARE @Score BIGINT
DECLARE @WinCount INT
DECLARE @LostCount INT
DECLARE @DrawCount INT
DECLARE @FleeCount INT
DECLARE @Experience INT

-- ��������
DECLARE @EnjoinLogon BIGINT
DECLARE @ErrorDescribe AS NVARCHAR(128)

-- ִ���߼�
BEGIN
	-- Ч���ַ
	SELECT @EnjoinLogon=EnjoinLogon FROM ConfineAddress(NOLOCK) WHERE AddrString=@strClientIP AND GETDATE()<EnjoinOverDate
	IF @EnjoinLogon IS NOT NULL AND @EnjoinLogon<>0
	BEGIN
		SELECT [ErrorDescribe]=N'��Ǹ��֪ͨ����ϵͳ��ֹ�������ڵ� IP ��ַ����Ϸ��¼Ȩ�ޣ�����ϵ�ͻ����������˽���ϸ�����'
		RETURN 4
	END
	
	-- Ч�����
	SELECT @EnjoinLogon=EnjoinLogon FROM ConfineMachine(NOLOCK) WHERE MachineSerial=@strMachineSerial AND GETDATE()<EnjoinOverDate
	IF @EnjoinLogon IS NOT NULL AND @EnjoinLogon<>0
	BEGIN
		SELECT [ErrorDescribe]=N'��Ǹ��֪ͨ����ϵͳ��ֹ�����Ļ�������Ϸ��¼Ȩ�ޣ�����ϵ�ͻ����������˽���ϸ�����'
		RETURN 7
	END
 
	-- ��ѯ�û�
	DECLARE @Nullity BIT
	DECLARE @StunDown BIT
	DECLARE @LogonPass AS NCHAR(32)
	DECLARE	@MachineSerial NCHAR(32)
	DECLARE @MoorMachine AS TINYINT
	SELECT @UserID=UserID, @GameID=GameID, @Accounts=Accounts, @UnderWrite=UnderWrite, @LogonPass=LogonPass, @FaceID=FaceID, 
		@Gender=Gender, @Nullity=Nullity, @StunDown=StunDown, @Experience=Experience, @UserRight=UserRight, @MasterRight=MasterRight,
		@MasterOrder=MasterOrder, @MemberOrder=MemberOrder, @MoorMachine=MoorMachine, @MachineSerial=MachineSerial
	FROM UserDBLink.UserDB.dbo.AccountsInfo WHERE UserID=@dwUserID

	-- ��ѯ�û�
	IF @UserID IS NULL
	BEGIN
		SELECT [ErrorDescribe]=N'�����ʺŲ����ڻ������������������֤���ٴγ��Ե�¼��'
		RETURN 1
	END	

	-- �ʺŽ�ֹ
	IF @Nullity<>0
	BEGIN
		SELECT [ErrorDescribe]=N'�����ʺ���ʱ���ڶ���״̬������ϵ�ͻ����������˽���ϸ�����'
		RETURN 2
	END	

	-- �ʺŹر�
	IF @StunDown<>0
	BEGIN
		SELECT [ErrorDescribe]=N'�����ʺ�ʹ���˰�ȫ�رչ��ܣ����뵽���¿�ͨ����ܼ���ʹ�ã�'
		RETURN 2
	END	
	
	-- �̶�����
	IF @MoorMachine=1
	BEGIN
		IF @MachineSerial<>@strMachineSerial
		BEGIN
			SELECT [ErrorDescribe]=N'�����ʺ�ʹ�ù̶�������¼���ܣ�������ʹ�õĻ���������ָ���Ļ�����'
			RETURN 1
		END
	END

	-- �����ж�
	IF @LogonPass<>@strPassword AND @strClientIP<>N'0.0.0.0' AND @strPassword<>N''
	BEGIN
		SELECT [ErrorDescribe]=N'�����ʺŲ����ڻ������������������֤���ٴγ��ԣ�'
		RETURN 3
	END

	-- �̶�����
	IF @MoorMachine=2
	BEGIN
		SET @MoorMachine=1
		SELECT [ErrorDescribe]=N'�����ʺųɹ�ʹ���˹̶�������¼���ܣ�'
		UPDATE AccountsInfo SET MoorMachine=@MoorMachine, MachineSerial=@strMachineSerial WHERE UserID=@UserID
	END

	-- ��������
	IF EXISTS (SELECT UserID FROM GameScoreLocker WHERE UserID=@dwUserID)
	BEGIN
		SELECT [ErrorDescribe]=N'���Ѿ��ڳ�ֵ��Ϸ�����ˣ�����ͬʱ�ڽ������Ϸ�����ˣ�'
		RETURN 4
	END
	INSERT GameScoreLocker (UserID,KindID,ServerID) VALUES (@dwUserID,@wKindID,@wServerID)

	-- ��Ϸ��Ϣ
	DECLARE @GameUserRight INT
	DECLARE @GameMasterRight INT
	DECLARE @GameMasterOrder SMALLINT
	SELECT @Score=Score, @WinCount=WinCount, @LostCount=LostCount, @DrawCount=DrawCount,
		@DrawCount=DrawCount, @FleeCount=FleeCount, @GameUserRight=UserRight, @GameMasterRight=MasterRight, @GameMasterOrder=MasterOrder
	FROM GameScoreInfo WHERE UserID=@dwUserID

	-- ��Ϣ�ж�
	IF @Score IS NULL
	BEGIN
		-- ��������
		INSERT INTO GameScoreInfo (UserID, LastLogonIP, RegisterIP)	VALUES (@dwUserID,@strClientIP,@strClientIP)

		-- ��Ϸ��Ϣ
		SELECT @Score=Score, @Score=Score, @WinCount=WinCount, @LostCount=LostCount,@DrawCount=DrawCount, @DrawCount=DrawCount, 
			@FleeCount=FleeCount, @GameUserRight=UserRight, @GameMasterOrder=MasterOrder, @MasterRight=MasterRight
		FROM GameScoreInfo WHERE UserID=@dwUserID
	END

	-- ������Ϣ
	UPDATE GameScoreInfo SET AllLogonTimes=AllLogonTimes+1, LastLogonDate=GETDATE(), LastLogonIP=@strClientIP WHERE UserID=@dwUserID

	-- ������Ϣ
	SET @GroupID=0
	SET @GroupName=''

	-- Ȩ�ޱ�־
	SET @UserRight=@UserRight|@GameUserRight
	SET @MasterRight=@MasterRight|@GameMasterRight

	-- Ȩ�޵ȼ�
	IF @MasterOrder<>0 OR @GameMasterOrder<>0
	BEGIN
		IF @GameMasterOrder>@MasterOrder SET @MasterOrder=@GameMasterOrder
	END
	ELSE SET @MasterRight=0

	-- �����¼
	INSERT RecordUserEnter (UserID, Score, KindID, ServerID, ClientIP) VALUES (@UserID, @Score, @wKindID, @wServerID, @strClientIP)

	-- ��¼ͳ��
	DECLARE @DateID INT
	SET @DateID=CAST(CAST(GETDATE() AS FLOAT) AS INT)
	UPDATE SystemStreamInfo SET LogonCount=LogonCount+1 WHERE DateID=@DateID AND KindID=@wKindID AND ServerID=@wServerID
	IF @@ROWCOUNT=0 INSERT SystemStreamInfo (DateID, KindID, ServerID, LogonCount) VALUES (@DateID, @wKindID, @wServerID, 1)

	-- �������
	SELECT @UserID AS UserID, @GameID AS GameID, @GroupID AS GroupID, @Accounts AS Accounts, @UnderWrite AS UnderWrite, @FaceID AS FaceID, 
		@Gender AS Gender, @GroupName AS GroupName, @MasterOrder AS MemberOrder, @UserRight AS UserRight, @MasterRight AS MasterRight, 
		@MasterOrder AS MasterOrder, @MemberOrder AS MemberOrder, @Score AS Score, @WinCount AS WinCount, @LostCount AS LostCount, 
		@DrawCount AS DrawCount, @FleeCount AS FleeCount, @Experience AS Experience, @ErrorDescribe AS ErrorDescribe

END

RETURN 0

GO

----------------------------------------------------------------------------------------------------