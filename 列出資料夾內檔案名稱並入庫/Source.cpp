/*
-------------------------------------------------------------
|	               											|
|	���Ƨ��ɮצ۰ʤJ�w									|
|															|
|	by.ChingYue												|
-------------------------------------------------------------
*/
#include <windows.h>
#include <stdio.h>
#include <mysql.h>
#include <string>
#include <Tchar.h>
#include <iostream>
void main()
{
	char InputPath[] = "D:\\�ڬO��Ƨ�\\";
	//��nŪ���ɮת���Ƨ����|��InputPath�r���
	char FileType[] = "*.mxf"; // ���w�ؼ��ɮ׮榡 
	char szDir[MAX_PATH];
	char dir[MAX_PATH];
	char sos[MAX_PATH];
	WIN32_FIND_DATA FileData;
	HANDLE          hList;
//------------------------------------------------------
	//��Ʈw�ܼ�
	char user[] = "root";
	char pswd[] = "";
	char host[] = "localhost";
	char table[] = "user";
	unsigned int port = 3306;
	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	int res;
//----------------------------------------------------------


	mysql_init(&myCont);
	sprintf_s(szDir, "%s%s*", InputPath, FileType);
	if ((hList = FindFirstFile(szDir, &FileData)) == INVALID_HANDLE_VALUE)
		printf("No files be found.\n\n");
	else {
		while (1) {
			if (!FindNextFile(hList, &FileData)) {
				if (GetLastError() == ERROR_NO_MORE_FILES)
					break;
			}
			sprintf_s(dir, "%s",  FileData.cFileName);
			if (strlen(dir) > 3){
				if (mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0)) //�s����Ʈw
				{
					mysql_query(&myCont, "SET NAMES BIG5");
					sprintf_s(sos, "INSERT INTO ddd SELECT NULL, '%s','�饻','�ڶٳ�' FROM dual WHERE not exists(select * from ddd where dirName = '%s');", dir, dir);  //MYSQL�y�k 
					MessageBoxA(0, sos, "Title", MB_OK);
					mysql_query(&myCont, sos);
				}
				printf("%s\n", dir);
				printf("%s\n", sos);
			}					
		}
	}
	FindClose(hList);
	mysql_close(&myCont);
	system("pause");
}