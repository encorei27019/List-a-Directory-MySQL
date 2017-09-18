/*
-------------------------------------------------------------
|	               											|
|	抓資料夾檔案自動入庫									|
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
	char InputPath[] = "D:\\我是資料夾\\";
	//放要讀取檔案的資料夾路徑到InputPath字串裡
	char FileType[] = "*.mxf"; // 指定目標檔案格式 
	char szDir[MAX_PATH];
	char dir[MAX_PATH];
	char sos[MAX_PATH];
	WIN32_FIND_DATA FileData;
	HANDLE          hList;
//------------------------------------------------------
	//資料庫變數
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
				if (mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0)) //連接資料庫
				{
					mysql_query(&myCont, "SET NAMES BIG5");
					sprintf_s(sos, "INSERT INTO ddd SELECT NULL, '%s','日本','歐嗨喲' FROM dual WHERE not exists(select * from ddd where dirName = '%s');", dir, dir);  //MYSQL語法 
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