@echo off

TITLE 棋牌数据库【Ver6.5_Spreader】 建立脚本启动中... [期间请勿关闭]

md D:\数据库

@echo 建主数据库三个
set rootPath=数据库脚本\
@echo 数据库删除
osql -E -i "%rootPath%数据库删除.sql"
@echo 平台数据库
osql -E -i "%rootPath%平台数据库.sql"
@echo 金币数据库
osql -E -i "%rootPath%金币数据库.sql"
@echo 用户数据库
osql -E -i "%rootPath%用户数据库.sql"
@echo 积分数据库
osql -E -i "%rootPath%积分数据库.sql"
@echo 训练数据库
osql -E -i "%rootPath%训练数据库.sql"


@echo 建连接服务和填充数据
set rootPath=数据脚本\
osql -E -i "%rootPath%连接信息.sql"
osql -E -i "%rootPath%游戏列表.sql"


@echo 建连链接脚本
set rootPath=链接脚本\
osql -E -i "%rootPath%财富链接.sql"
osql -E -i "%rootPath%平台链接.sql"
osql -E -i "%rootPath%用户链接.sql"

@echo 存储过程
set rootPath=存储过程\用户数据库\
osql -E  -i "%rootPath%ID登录.sql"
osql -E  -i "%rootPath%帐号登录.sql"
osql -E  -i "%rootPath%注册帐号.sql"

set rootPath=存储过程\平台数据库\
osql -E  -i "%rootPath%加载类型.sql"
osql -E  -i "%rootPath%加载种类.sql"
osql -E  -i "%rootPath%连接信息.sql"
osql -E  -i "%rootPath%加载节点.sql"

set rootPath=存储过程\金币数据库\
osql -E  -i "%rootPath%ID登录.sql"
osql -E  -i "%rootPath%加载机器人.sql"
osql -E  -i "%rootPath%离开房间.sql"
osql -E  -i "%rootPath%游戏写分.sql"
osql -E  -i "%rootPath%游戏记录.sql"

set rootPath=存储过程\积分数据库\
osql -E  -i "%rootPath%ID登录.sql"
osql -E  -i "%rootPath%加载机器人.sql"
osql -E  -i "%rootPath%离开房间.sql"
osql -E  -i "%rootPath%游戏写分.sql"
osql -E  -i "%rootPath%游戏记录.sql"

set rootPath=存储过程\训练数据库\
osql -E  -i "%rootPath%ID登录.sql"
osql -E  -i "%rootPath%加载机器人.sql"
osql -E  -i "%rootPath%离开房间.sql"
osql -E  -i "%rootPath%游戏记录.sql"
osql -E  -i "%rootPath%游戏写分.sql"

pause

CLS
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
echo	主要数据库建立完成，请根据自己平台的积分游戏执行 
echo.
echo.
echo	版权所有： 深圳市网狐科技有限公司
echo ------------------------------

pause


