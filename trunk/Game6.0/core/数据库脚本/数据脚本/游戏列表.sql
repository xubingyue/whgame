
----------------------------------------------------------------------------------------------------

USE GameServerInfoDB
GO

----------------------------------------------------------------------------------------------------

-- 删除数据
DELETE GameTypeItem
DELETE GameKindItem
DELETE GameNodeItem
GO

----------------------------------------------------------------------------------------------------

-- 类型数据
INSERT GameTypeItem (TypeID, TypeName, SortID, Nullity) VALUES ( 1, '积分游戏',100, 0)
INSERT GameTypeItem (TypeID, TypeName, SortID, Nullity) VALUES ( 2, '金币游戏',200, 0)
INSERT GameTypeItem (TypeID, TypeName, SortID, Nullity) VALUES ( 3, '比赛游戏',300, 0)


----------------------------------------------------------------------------------------------------

-- 积分游戏

INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 101, 1, '斗地主', 'Land.exe', 66822, 100, 0, 'GameScoreDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 102, 1, '疯狂斗地主', 'LandCrazy.exe', 66822, 100, 0, 'GameScoreDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 103, 1, '两副斗地主', 'LandEX.exe', 66822, 100, 0, 'GameScoreDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 104, 1, '大众麻将', 'SparrowDZ.exe', 66822, 100, 0, 'GameScoreDB')


-- 金币游戏

INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 201, 2, '斗地主', 'Land.exe', 66822, 100, 0, 'GameTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 202, 2, '疯狂斗地主', 'LandCrazy.exe', 66822, 100, 0, 'GameTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 203, 2, '两副斗地主', 'LandEX.exe', 66822, 100, 0, 'GameTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 204, 2, '大众麻将', 'SparrowDZ.exe', 66822, 100, 0, 'GameTreasureDB')

--比赛游戏
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 301, 3, '斗地主', 'Land.exe', 66822, 100, 0, 'GameMatchDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 302, 3, '疯狂斗地主', 'LandCrazy.exe', 66822, 100, 0, 'GameMatchDB')


----------------------------------------------------------------------------------------------------

GO