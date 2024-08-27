#include "../inc/mystd.h"
#include <sqlite3.h>
#include <signal.h>
#include <sys/wait.h>

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

MSG regester(int fd, MSG* recvbuf, sqlite3* db){
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
MSG login(int fd, MSG* recvbuf, sqlite3* db){
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
MSG inquire(int fd, MSG* recvbuf, sqlite3* db){



}
MSG history(int fd, MSG* recvbuf, sqlite3* db){


    
}

//客户端进程程序
void clnhandler(int fd, sqlite3* db){
    MSG recvbuf, sendbuf;
    while(1){
	if(recv(fd, &recvbuf, sizeof(recvbuf), 0) == -1){
	    perror("recv");
	    continue;
	}
	switch(recvbuf.type){
	    case REGE:
		sendbuf = regester(fd, &recvbuf, db);
		if(send(fd, &sendbuf, sizeof(MSG), 0) == -1){
		    perror("send");
		    exit(0);
		}
		break;
	    case LGIN:
		sendbuf = login(fd, &recvbuf, db);
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
		//比对单词表
		break;
	    case HSTY:
		//历史记录输出
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
