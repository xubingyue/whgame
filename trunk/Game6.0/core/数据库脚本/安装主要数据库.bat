@echo off

TITLE 安装数据库中... [期间请勿关闭]


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

cls
echo ------------------------------
echo.
echo	主要数据库建立完成，请根据自己平台的积分游戏执行 
echo.
echo.
echo ------------------------------

pause


