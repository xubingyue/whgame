@echo off

TITLE ������ϷID ... [�ڼ�����ر�]


@echo ���濪ʼ������ϷID
pause

@echo off
@echo ����������ϷID ����
set rootPath=���ݽű�\
osql -E  -i "%rootPath%��ʶ����.sql"

COLOR 0A
CLS
@echo off
cls
echo ------------------------------
echo.
echo	������ϷID���
echo.
echo.
echo ------------------------------

pause


