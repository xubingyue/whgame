
----------------------------------------------------------------------------------------------------

USE GameServerInfoDB
GO

----------------------------------------------------------------------------------------------------

-- ɾ������
DELETE GameTypeItem
DELETE GameKindItem
DELETE GameNodeItem
GO

----------------------------------------------------------------------------------------------------

-- ��������
INSERT GameTypeItem (TypeID, TypeName, SortID, Nullity) VALUES ( 1, '������Ϸ',100, 0)
INSERT GameTypeItem (TypeID, TypeName, SortID, Nullity) VALUES ( 2, '�����Ϸ',200, 0)
INSERT GameTypeItem (TypeID, TypeName, SortID, Nullity) VALUES ( 3, '������Ϸ',300, 0)


----------------------------------------------------------------------------------------------------

-- ������Ϸ

INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 101, 1, '������', 'Land.exe', 66822, 100, 0, 'GameScoreDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 102, 1, '��񶷵���', 'LandCrazy.exe', 66822, 100, 0, 'GameScoreDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 103, 1, '����������', 'LandEX.exe', 66822, 100, 0, 'GameScoreDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 104, 1, '�����齫', 'SparrowDZ.exe', 66822, 100, 0, 'GameScoreDB')


-- �����Ϸ

INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 201, 2, '������', 'Land.exe', 66822, 100, 0, 'GameTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 202, 2, '��񶷵���', 'LandCrazy.exe', 66822, 100, 0, 'GameTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 203, 2, '����������', 'LandEX.exe', 66822, 100, 0, 'GameTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 204, 2, '�����齫', 'SparrowDZ.exe', 66822, 100, 0, 'GameTreasureDB')

--������Ϸ
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 301, 3, '������', 'Land.exe', 66822, 100, 0, 'GameMatchDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 302, 3, '��񶷵���', 'LandCrazy.exe', 66822, 100, 0, 'GameMatchDB')


----------------------------------------------------------------------------------------------------

GO