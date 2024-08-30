#include "../inc/mystd.h"
#include <sqlite3.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>

#define DATABASE "../user_db/userinfo.db"

void childhandler(int signo){
    if(signo == SIGCHLD){
	int pid = waitpid(-1, NULL, WNOHANG);
	if( pid != -1){
	    printf("process %d is stop", pid);
	}
	puts("resource reclaim success");
    }
}

MSG regester(MSG* recvbuf, sqlite3* db){
    MSG retbuf;
    char *errmsg;
    char sqlcmd[512];
    sprintf(sqlcmd, "insert into user values ('%s', '%s');", recvbuf->name, recvbuf->data);
    printf("%s\n", sqlcmd);
    if(sqlite3_exec(db, sqlcmd, NULL, NULL, &errmsg) != SQLITE_OK){
	printf("%s\n", errmsg);
	retbuf.type = EROR;
    }else{
	printf("client regester success\n");
	retbuf.type = VFOK;
    }
    return retbuf;
}
MSG login(MSG* recvbuf, sqlite3* db){
    MSG retbuf;
    char *errmsg;
    char **presult;
    int nrow, ncolume;
    char sqlcmd[512];
    sprintf(sqlcmd, "select * from user where name = '%s' and password = '%s';", recvbuf->name, recvbuf->data);
    printf("%s\n", sqlcmd);
    if(sqlite3_get_table(db, sqlcmd, &presult, &nrow, &ncolume, &errmsg) != SQLITE_OK){
	printf("%s\n", errmsg);
	retbuf.type = EROR;
    }else{
	if(nrow == 1){ //查询成功: 有一行name和password和输入相等
	    puts("login, welcome");
	    retbuf.type = VFOK;
	}else retbuf.type = EROR;
    }
    return retbuf;


}

void get_date(char* date){
    time_t t;
    struct tm *tp;
    time(&t);
    tp = localtime(&t);
    sprintf(date, "%d-%d-%d %d:%d:%d", tp->tm_year+1900, tp->tm_mon+1, tp->tm_mday, tp->tm_hour, tp->tm_min, tp->tm_sec);
}

void inquire(MSG* recvbuf, sqlite3* db){
    recvbuf->type = VFOK;
    int result = -1;
    char *errmsg;
    char word[64], date[128], sql[128];
    strncpy(word, recvbuf->cmd, strlen(recvbuf->cmd) + 1);
    printf("waitting...\n");
    result = search_word(recvbuf, word);
    printf("result %d cmd %s name %s\n", result, recvbuf->cmd, recvbuf->name);
    if(result == 1){
	get_date(date);
	sprintf(sql, "insert into history values ('%s','%s','%s');", recvbuf->name, date, recvbuf->cmd);
	if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK){
	    printf("sql_exrc_err: %s\n", errmsg);
	    exit(0);
	}else printf("%s\n", sql);
    }else {
	recvbuf->type = EROR;
	printf("failed to search %s\n", recvbuf->cmd);

    }
}

int search_word(MSG *recvbuf, char *word){
    char temp[512];
    char *pret = NULL;
    FILE *fp = fopen("/root/myGit/OL_Dictonary/dict.txt", "r");
    if(fp == NULL){
	perror("fopen");
	exit(0);
    }
    int flag = 0;
    int len = strlen(word);
    while(fgets(temp, 512, fp) != NULL){
	flag = strncmp(temp, word, len);
	if(flag < 0)
	    continue;
	else if(flag > 0 || ((flag == 0) && (temp[len] != ' '))){
	    printf("flag %d, temp %s", flag, temp[len]);
	    break;
	}
	pret = temp + len;
	while(*pret == ' ')
	    ++pret;
	printf("found %s\n", recvbuf->cmd);
	strcpy(recvbuf->data, pret);
	fclose(fp);
	return 1;
    }
    fclose(fp);
    return 0;
}

int history_callback(void *para, int f_num, char** f_value, char** f_name){
    MSG htry;
    htry.type = VFOK;
    int acceptfd = *(int *)para;
    //history::    name    date    word
    sprintf(htry.data, "'%s': '%s'", f_value[1], f_value[2]);
    send(acceptfd, &htry, sizeof(MSG), 0);
}

void history(MSG* recvbuf, sqlite3* db, int acceptfd){
    printf("waitting...\n");
    MSG sendbuf;
    sendbuf.type = EROR;
    char sql[128] = {0};
    char *errmsg;
    sprintf(sql, "select * from history where name = '%s' ", recvbuf->name);
    
    if(sqlite3_exec(db, sql, history_callback, (void *)&acceptfd , &errmsg) != SQLITE_OK){
	perror("server history");
	send(acceptfd, &sendbuf, sizeof(MSG), 0);
	return ;
    }else {
	printf("%s\n", sql);
	printf("history record got!\n");
    }
    return ;
}

//客户端进程程序
void clnhandler(int fd, sqlite3* db){
    MSG recvbuf, sendbuf;
    while(1){
	memset(&recvbuf, 0, sizeof(MSG));
	memset(&sendbuf, 0, sizeof(MSG));
	if(recv(fd, &recvbuf, sizeof(recvbuf), 0) == -1){
	    perror("recv");
	    continue;
	}
	switch(recvbuf.type){
	    case REGE:
		sendbuf = regester(&recvbuf, db);
		if(send(fd, &sendbuf, sizeof(MSG), 0) == -1){
		    perror("send");
		    exit(0);
		}
		break;
	    case LGIN:
		sendbuf = login(&recvbuf, db);
		if(send(fd, &sendbuf, sizeof(MSG), 0) == -1){
		    perror("send");
		    exit(0);
		}
		break;
	    case QUIT:	
		printf("client request quit\n");
		exit(0);
		break;
	    case INQY:
		inquire(&recvbuf, db);
		if(send(fd, &recvbuf, sizeof(MSG), 0) == -1){
		    perror("send");
		    exit(0);
		}
		break;
	    case HSTY:
		history(&recvbuf, db, fd);
		break;
	    default :
		sendbuf.type = EROR;
	}
    }
}

int main(int argc, char* argv[])
{

    //创建用户信息数据库，存储用户信息表
    sqlite3* db = NULL;
    if(sqlite3_open(DATABASE, &db) != SQLITE_OK){
	perror("sqlite3_open");
	exit(-1);
    }else printf("open database: %s success\n", DATABASE);

    //创建服务器流式套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
	perror("socket");
	exit(-1);
    }

    memset(&srvaddr, 0, sizeof(srvaddr));
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = htons(SRV_PORT);
    srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    //快速复用
    int b_reuse = -1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &b_reuse, sizeof(int));

    /* 绑定本地服务器 */
    if( bind(sockfd, (struct sockaddr *)&srvaddr, sizeof(srvaddr)) != 0){
	perror("bind");
	exit(-1);
    }

    /* 设置为监听模式 最大连接数量 = 2n+1*/
    if( listen(sockfd, 5) != 0){
	perror("listen");
	exit(-1);
    } 
    //处理子进程状态改变信息
    struct sigaction childhandler;
    sigaction(SIGCHLD, &childhandler, NULL);

    int newfd;
    socklen_t clnlen;
    while(1){
	newfd =  accept(sockfd, (struct sockaddr *)&clnaddr.sin_addr, &clnlen);
	//printf("%d\n",clnaddr.sin_addr.s_addr);
	//printf("%d\n",clnaddr.sin_port);
	if(newfd < 0){
	    perror("accept");
	    continue;
	}else{
	    //把ip地址、端口转换为本地字节序
	    char ipv4_addr[16];
	    if( !inet_ntop(AF_INET, (void *)&clnaddr.sin_addr, ipv4_addr, sizeof(clnaddr)))
		perror("inet_ntop");
	    printf("client(%s:%d) is connected\n", ipv4_addr, ntohs(clnaddr.sin_port));
	}
	pid_t pid = fork();
	if(pid < 0){
	    perror("fork");
	    continue;
	}else if(pid > 0){ //父进程继续处于accept状态
	    close(newfd);
	}else{	//子进程处理数据
	    close(sockfd);
	    clnhandler(newfd, db);
	}

    }

    close(sockfd);
    return 0;

}
