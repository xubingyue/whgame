@echo off

TITLE �������ݿ⡾Ver6.6_Spreader�� �����ű�������... [�ڼ�����ر�]

md D:\���ݿ�
del *.log
Rem �������ݿ�����
set rootPath=���ݿ�ű�\
osql -E -i "%rootPath%���ݿ�ɾ��.sql" >>���ݿ�ű�.log
osql -E -i "%rootPath%1_1_�û���ű�.sql" >>���ݿ�ű�.log
osql -E -i "%rootPath%1_2_ƽ̨��ű�.sql" >>���ݿ�ű�.log
osql -E -i "%rootPath%1_3_�Ƹ���ű�.sql" >>���ݿ�ű�.log
osql -E -i "%rootPath%1_4_���ֿ�ű�.sql" >>���ݿ�ű�.log
osql -E -i "%rootPath%2_1_�û���ű�for2000.sql" >>���ݿ�ű�.log
osql -E -i "%rootPath%2_2_ƽ̨��ű�.sql" >>���ݿ�ű�.log
osql -E -i "%rootPath%2_3_�Ƹ���ű�.sql" >>���ݿ�ű�.log
osql -E -i "%rootPath%2_4_���ֱ�ű�.sql" >>���ݿ�ű�.log


Rem �����ӷ�����������
set rootPath=���ݽű�\
osql -E -i "%rootPath%������Ϣ.sql" >>���ݽű�.log
osql -E -i "%rootPath%��Ϸ�б�.sql" >>���ݽű�.log
osql -E -i "%rootPath%�Ƹ�����.sql" >>���ݽű�.log
osql -E -i "%rootPath%ƽ̨����.sql" >>���ݽű�.log
osql -E -i "%rootPath%�û�����.sql" >>���ݽű�.log
osql -E -i "%rootPath%�ʻ�����.sql" >>���ݽű�.log


Rem �洢����
set rootPath=�洢����\�û���\
osql -E  -i "%rootPath%��ʶ��¼.sql" >>�洢����_�û���.log
osql -E  -i "%rootPath%�ʺŵ�¼.sql" >>�洢����_�û���.log
osql -E  -i "%rootPath%ע���ʺ�.sql" >>�洢����_�û���.log
osql -E  -i "%rootPath%�û�Ȩ��.sql" >>�洢����_�û���.log
osql -E  -i "%rootPath%�����ʺ�.sql" >>�洢����_�û���.log
osql -E  -i "%rootPath%�Զ���ͷ��for2000.sql" >>�洢����_�û���.log

set rootPath=�洢����\ƽ̨��\
osql -E  -i "%rootPath%��������.sql" >>�洢����_ƽ̨��.log
osql -E  -i "%rootPath%��������.sql" >>�洢����_ƽ̨��.log
osql -E  -i "%rootPath%������Ϣ.sql" >>�洢����_ƽ̨��.log
osql -E  -i "%rootPath%���ؽڵ�.sql" >>�洢����_ƽ̨��.log

set rootPath=�洢����\�Ƹ���\
osql -E  -i "%rootPath%��ʶ��¼.sql" >>�洢����_�Ƹ���.log
osql -E  -i "%rootPath%���ػ�����.sql" >>�洢����_�Ƹ���.log
osql -E  -i "%rootPath%�뿪����.sql" >>�洢����_�Ƹ���.log
osql -E  -i "%rootPath%��Ϸд��.sql" >>�洢����_�Ƹ���.log
osql -E  -i "%rootPath%�û�Ȩ��.sql" >>�洢����_�Ƹ���.log
osql -E  -i "%rootPath%�������.sql" >>�洢����_�Ƹ���.log
osql -E  -i "%rootPath%�����һ�.sql" >>�洢����_�Ƹ���.log
osql -E  -i "%rootPath%�ʻ�����.sql" >>�洢����_�Ƹ���.log
osql -E  -i "%rootPath%���м�¼.sql" >>�洢����_�Ƹ���.log

set rootPath=�洢����\���ֿ�\
osql -E  -i "%rootPath%��ʶ��¼.sql" >>�洢����_���ֿ�.log
osql -E  -i "%rootPath%���ػ�����.sql" >>�洢����_���ֿ�.log
osql -E  -i "%rootPath%�뿪����.sql" >>�洢����_���ֿ�.log
osql -E  -i "%rootPath%��Ϸд��.sql" >>�洢����_���ֿ�.log
osql -E  -i "%rootPath%�û�Ȩ��.sql" >>�洢����_���ֿ�.log
osql -E  -i "%rootPath%�������.sql" >>�洢����_���ֿ�.log
osql -E  -i "%rootPath%�����һ�.sql" >>�洢����_���ֿ�.log
osql -E  -i "%rootPath%�ʻ�����.sql" >>�洢����_���ֿ�.log
osql -E  -i "%rootPath%���м�¼.sql" >>�洢����_���ֿ�.log

pause

CLS
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
echo	��Ҫ���ݿ⽨����ɣ�������Լ�ƽ̨�Ļ�����Ϸִ�� 
echo.
echo.
echo	��Ȩ���У� �й��������Ƽ����޹�˾
echo ------------------------------

pause


