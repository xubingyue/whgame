@echo off

TITLE 生成游戏ID ... [期间请勿关闭]


@echo 下面开始生成游戏ID
pause

@echo off
@echo 正在生成游戏ID ……
set rootPath=数据脚本\
osql -E  -i "%rootPath%标识生成.sql"

COLOR 0A
CLS
@echo off
cls
echo ------------------------------
echo.
echo	生成游戏ID完成
echo.
echo.
echo ------------------------------

pause


