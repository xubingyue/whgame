@echo off

TITLE �������ݿ⡾Ver6.5_Spreader�� �����ű�������... [�ڼ�����ر�]

md D:\���ݿ�

@echo �������ݿ�����
set rootPath=���ݿ�ű�\
@echo ���ݿ�ɾ��
osql -E -i "%rootPath%���ݿ�ɾ��.sql"
@echo ƽ̨���ݿ�
osql -E -i "%rootPath%ƽ̨���ݿ�.sql"
@echo ������ݿ�
osql -E -i "%rootPath%������ݿ�.sql"
@echo �û����ݿ�
osql -E -i "%rootPath%�û����ݿ�.sql"
@echo �������ݿ�
osql -E -i "%rootPath%�������ݿ�.sql"
@echo ѵ�����ݿ�
osql -E -i "%rootPath%ѵ�����ݿ�.sql"


@echo �����ӷ�����������
set rootPath=���ݽű�\
osql -E -i "%rootPath%������Ϣ.sql"
osql -E -i "%rootPath%��Ϸ�б�.sql"


@echo �������ӽű�
set rootPath=���ӽű�\
osql -E -i "%rootPath%�Ƹ�����.sql"
osql -E -i "%rootPath%ƽ̨����.sql"
osql -E -i "%rootPath%�û�����.sql"

@echo �洢����
set rootPath=�洢����\�û����ݿ�\
osql -E  -i "%rootPath%ID��¼.sql"
osql -E  -i "%rootPath%�ʺŵ�¼.sql"
osql -E  -i "%rootPath%ע���ʺ�.sql"

set rootPath=�洢����\ƽ̨���ݿ�\
osql -E  -i "%rootPath%��������.sql"
osql -E  -i "%rootPath%��������.sql"
osql -E  -i "%rootPath%������Ϣ.sql"
osql -E  -i "%rootPath%���ؽڵ�.sql"

set rootPath=�洢����\������ݿ�\
osql -E  -i "%rootPath%ID��¼.sql"
osql -E  -i "%rootPath%���ػ�����.sql"
osql -E  -i "%rootPath%�뿪����.sql"
osql -E  -i "%rootPath%��Ϸд��.sql"
osql -E  -i "%rootPath%��Ϸ��¼.sql"

set rootPath=�洢����\�������ݿ�\
osql -E  -i "%rootPath%ID��¼.sql"
osql -E  -i "%rootPath%���ػ�����.sql"
osql -E  -i "%rootPath%�뿪����.sql"
osql -E  -i "%rootPath%��Ϸд��.sql"
osql -E  -i "%rootPath%��Ϸ��¼.sql"

set rootPath=�洢����\ѵ�����ݿ�\
osql -E  -i "%rootPath%ID��¼.sql"
osql -E  -i "%rootPath%���ػ�����.sql"
osql -E  -i "%rootPath%�뿪����.sql"
osql -E  -i "%rootPath%��Ϸ��¼.sql"
osql -E  -i "%rootPath%��Ϸд��.sql"

pause

CLS
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
echo	��Ҫ���ݿ⽨����ɣ�������Լ�ƽ̨�Ļ�����Ϸִ�� 
echo.
echo.
echo	��Ȩ���У� �����������Ƽ����޹�˾
echo ------------------------------

pause


