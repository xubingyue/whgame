@echo off

TITLE �������ݿ⡾Ver6.6_Spreader�� �����ű�������... [�ڼ�����ر�]

md D:\���ݿ�

Rem �������ݿ�����
set rootPath=���ݿ�ű�\
osql -E -S "(local)\sqlexpress" -i "%rootPath%���ݿ�ɾ��.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%1_1_�û���ű�.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%1_2_ƽ̨��ű�.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%1_3_�Ƹ���ű�.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%1_4_���ֿ�ű�.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%2_1_�û���ű�.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%2_2_ƽ̨��ű�.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%2_3_�Ƹ���ű�.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%2_4_���ֱ�ű�.sql"


Rem �����ӷ�����������
set rootPath=���ݽű�express\
osql -E -S "(local)\sqlexpress" -i "%rootPath%������Ϣ.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%��Ϸ�б�.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%�Ƹ�����.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%ƽ̨����.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%�û�����.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%�ʻ�����.sql"


Rem �洢����
set rootPath=�洢����\�û���\
osql -E -S "(local)\sqlexpress" -i "%rootPath%��ʶ��¼.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%�ʺŵ�¼.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%ע���ʺ�.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%�û�Ȩ��.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%�����ʺ�.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%�Զ���ͷ��.sql"

set rootPath=�洢����\ƽ̨��\
osql -E -S "(local)\sqlexpress" -i "%rootPath%��������.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%��������.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%������Ϣ.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%���ؽڵ�.sql"

set rootPath=�洢����\�Ƹ���\
osql -E -S "(local)\sqlexpress" -i "%rootPath%��ʶ��¼.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%���ػ�����.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%�뿪����.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%��Ϸд��.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%�û�Ȩ��.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%�������.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%�����һ�.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%�ʻ�����.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%���м�¼.sql"

set rootPath=�洢����\���ֿ�\
osql -E -S "(local)\sqlexpress" -i "%rootPath%��ʶ��¼.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%���ػ�����.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%�뿪����.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%��Ϸд��.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%�û�Ȩ��.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%�������.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%�����һ�.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%�ʻ�����.sql"
osql -E -S "(local)\sqlexpress" -i "%rootPath%���м�¼.sql"

pause

CLS
@echo off
@echo ����������ϷID ����
set rootPath=���ݽű�\
osql -E -S "(local)\sqlexpress" -i "%rootPath%��ʶ����.sql"

COLOR 0A
CLS
@echo off
cls
echo ------------------------------
echo.
echo	��Ҫ���ݿ⽨����ɣ�������Լ�ƽ̨�Ļ�����Ϸִ�� 
echo.
echo.
echo	��Ȩ���У� �й��������Ƽ����޹�˾
echo ------------------------------

pause


