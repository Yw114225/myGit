#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>


#define SQL_NAME "stu.db"



void sqlite3_insert(sqlite3 *db, char *cmd)
{
    char sql0[100] = "insert into stu vallues ";
    strcat(sql0, cmd);
    printf("%s \n", sql0);
}

void sqlite3_delete(sqlite3 *db);

int main(int argc, char* argv[])
{
    sqlite3 *db;
    if(sqlite3_open(SQL_NAME, &db) != SQLITE_OK){
	printf("%s\n", sqlite3_errmsg(db));
	exit(-1);
    }
    puts("OPEN SUCCESS");
    char sql[] = "create table stu (id integer, name char, score float)";
    char errmsg[100];
    sqlite3_exec(db, sql, NULL, NULL, &errmsg);

    int cmd;
    while(1){
	printf("数据库操作指南：\n");
	printf("指令1：数据插入；\n");
	printf("指令2：数据删除；\n");
	printf("指令3：数据修改；\n");
	printf("指令4：数据查询；\n");
	
	scanf("%d", &cmd);
	switch(cmd){
	    case 1:
		puts("input the values: (id integer, name char, score float)");
		scanf("%s", &cmd);
		sqlite3_insert(db, cmd);
		break;
	    case 2:
		puts("input the values: (id integer, name char, score float)");
		//sqlite3_delete();
		break;
	    case 3:
		//sqlite3_set();
		break;
	    case 4:
		//sqlite3_index();
		break;
	}
    }

    if(sqlite3_close(db) != SQLITE_OK){
	perror("sqlite3_close");
	exit(-1);
    }





    return 0;
}
