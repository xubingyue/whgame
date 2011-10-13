
-- 游戏标识生成

USE [UserDB]
GO


DECLARE @startGameID INT
DECLARE @endGameID INT

SET @startGameID=100000
SET @endGameID=999999

WHILE (@startGameID<=@endGameID)
BEGIN
INSERT [GameIdentifier] (GameID) VALUES(@startGameID)
SET @startGameID=@startGameID+1
END



update AccountsInfo
set AccountsInfo.Gameid=GameIdentifier.Gameid
from GameIdentifier
where AccountsInfo.userid=GameIdentifier.userid

