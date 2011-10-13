
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
INSERT GameTypeItem (TypeID, TypeName, SortID, Nullity) VALUES ( 1, '�Ƹ���Ϸ',100, 0)
INSERT GameTypeItem (TypeID, TypeName, SortID, Nullity) VALUES ( 2, '��Ƶ��Ϸ',200, 0)
INSERT GameTypeItem (TypeID, TypeName, SortID, Nullity) VALUES ( 3, '������Ϸ',300, 0)
INSERT GameTypeItem (TypeID, TypeName, SortID, Nullity) VALUES ( 4, '������Ϸ',400, 0)
INSERT GameTypeItem (TypeID, TypeName, SortID, Nullity) VALUES ( 5, '�齫��Ϸ',500, 0)
INSERT GameTypeItem (TypeID, TypeName, SortID, Nullity) VALUES ( 6, '������Ϸ',600, 0)


----------------------------------------------------------------------------------------------------

-- �Ƹ���Ϸ
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 1, 1, '���', 'ShowHand.exe', 67078, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 3, 1, 'ը��', 'ZaJinHua.exe', 67078, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 5, 1, 'ţţ', 'Ox.exe', 67078, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 2, 1, '��ʽ����', 'HKFiveCard.exe', 67078, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 7, 1, '�����˿�', 'DZShowHand.EXE', 67078, 100, 0, 'QPTreasureDB')
-- ������Ϸ

INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 102, 3, '��񶷵���', 'LandCrazy.exe', 67078, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 145, 3, '���ɵ���', 'Gandengyan.exe', 67078, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 121, 3, '���', 'QingDun.exe', 67078, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 502, 3, '������', 'Land.exe', 67078, 100, 0, 'QPTreasureDB')
-- ������Ϸ
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 506, 2, '�й�����', 'ChinaChessVD.exe', 67078, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 203, 4, '������', 'GoBang.exe', 67078, 100, 0, 'QPTreasureDB')

-- �齫��Ϸ
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 301, 5, '�㶫�齫', 'SparrowGD.exe', 67078, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 528, 2, '�����齫', 'SparrowDZVD.exe', 67078, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 324, 5, '�ɶ��齫', 'SparrowCD.exe', 67078, 100, 0, 'QPTreasureDB')

-- ��Ƶ��
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 500, 2, '��Ƶ����', 'UpGradeVD.exe', 1, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 100, 2, '��Ƶ������', 'LandVD.exe', 67078, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 135, 2, '�Ĵ�������', 'LandSCVD.exe', 67078, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 522, 2, '��񶷵���', 'LandCrazyVD.exe', 67078, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 529, 2, 'ţţ', 'OxVD.exe', 67078, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 537, 2, '��Ƶͬ��', 'BurrowVD.exe', 67078, 100, 0, 'QPTreasureDB')

----------------------------------------------------------------------------------------------------

GO