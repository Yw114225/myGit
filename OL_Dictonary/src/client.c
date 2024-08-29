#include "../inc/mystd.h"

MSG regester(int sockfd, MSG* sendbuf);
MSG signin(int sockfd, MSG* sendbuf);
MSG inquire(int sockfd, MSG* sendbuf);
//MSG history(int sockfd, MSG* sendbuf, );
void quit(int sockfd, MSG* sendbuf);
void list(int order);
void sublist(int sockfd, MSG* sendbuf, MSG* recvbuf);
void progend(int sockfd);

int main(int argc, char* argv[])
{
    if(argc != 3){
	printf("%s server_ip_address server_porti\n", argv[0]);
	exit(0);
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
	perror("socket");
	exit(0);
    }
    
    srvaddr.sin_port = htons(atoi(argv[2]));
    srvaddr.sin_family = AF_INET;
    if(inet_pton(AF_INET, argv[1], (void *)&srvaddr.sin_addr) != 1){
	perror("inet_pton");
	exit(0);
    }

    if(connect(sockfd, (struct sockaddr *)&srvaddr, sizeof(srvaddr)) != 0){
	perror("connect");
	exit(0);
    }
    
    printf("connecting...\n");
    
    MSG sendbuf, recvbuf;
    while(1){
	memset(&recvbuf, 0, sizeof(MSG));
	memset(&sendbuf, 0, sizeof(MSG));
	list(1);
	int cmd = -1;
	scanf("%d", &cmd);
	switch(cmd){
	    case 1:
		recvbuf = regester(sockfd, &sendbuf);
		if(recvbuf.type == VFOK){
		    puts("regester success");
		}else puts("username already exist");
		break;
	    case 2:
		recvbuf = signin(sockfd, &sendbuf);
		if(recvbuf.type == VFOK){
		    puts("log in success, welcome");
		    goto secondary;
		}else puts("information error, try again");
		break;
	    case 3:
		quit(sockfd, &sendbuf);
		sleep(1);
		progend(sockfd);
		break;
	    default :
		puts("Invalide cmd");
	}
    }
secondary:
    while(1){
        memset(&recvbuf, 0, sizeof(MSG));
        memset(&sendbuf, 0, sizeof(MSG));
        int cmd2 = -1;
        list(2);
        scanf("%d", &cmd2);
	if(cmd2 == 4){  //返回上级菜单
	    
	}
        switch(cmd2){
            case 1:
                recvbuf = inquire(sockfd, &sendbuf);
                if(recvbuf.type == VFOK){
                    printf("%s: %s\n", recvbuf.cmd, recvbuf.data);
                }else if(recvbuf.type == EROR){
		    printf("faild to inquire: %s\n", recvbuf.cmd);
		}else printf("exist to inquire\n");
                break;
            case 2:
                //recvbuf = history(sockfd, &sendbuf);

                break;
            case 3:
                quit(sockfd, &sendbuf);
                progend(sockfd);
            default :
                puts("Invalide cmd");
        }
    }

    return 0;

}

void list(int order){
    if(order == 1){
	puts("         welcome to use OL_dictionary        ");
	puts("*********************************************");
	puts("* 1.regester        2.sign in        3.quit *");
	puts("*********************************************");
    }else if(order == 2){
	puts("               secondary list                ");
	puts("*********************************************");
	puts("* 1.inquire  2.history  3.quit  #:last list *");
	puts("*********************************************");
    }
}

MSG regester(int sockfd, MSG* sendbuf){
    MSG retbuf;
    retbuf.type = VFOK;
    sendbuf->type = REGE;
    printf("input username: ");
    scanf("%s", sendbuf->name);
    printf("input password: ");
    scanf("%s", sendbuf->data);
    if(send(sockfd, sendbuf, sizeof(MSG), 0) == -1){
	perror("send");
	retbuf.type = EROR;
	return retbuf;
    }
    if(recv(sockfd, &retbuf, sizeof(MSG), 0) == -1){
        perror("recv");
        retbuf.type = EROR;
        return retbuf;
    }
    return retbuf;
}

MSG signin(int sockfd, MSG* sendbuf){
    MSG retbuf;
    retbuf.type = VFOK;
    sendbuf->type = LGIN;
    printf("input username: ");
    scanf("%s", sendbuf->name);
    printf("input password: ");
    scanf("%s", sendbuf->data);
    if(send(sockfd, sendbuf, sizeof(MSG), 0) == -1){
        perror("send");
        retbuf.type = EROR;
        return retbuf;
    }
    if(recv(sockfd, &retbuf, sizeof(MSG), 0) == -1){
        perror("recv");
        retbuf.type = EROR;
        return retbuf;
    }
    return retbuf;
}

MSG inquire(int sockfd, MSG* sendbuf){
    MSG retbuf;
    retbuf.type = VFOK;
    sendbuf->type = INQY;
    while(1){
	printf("Inquire the word: ");
	scanf("%s",  sendbuf->cmd);
	if( strncmp(sendbuf->cmd, "#", 1) == 0){
	    retbuf.type = QUIT;
	    return retbuf;
	}
	if( send(sockfd, sendbuf, sizeof(MSG), 0) == -1){
	    perror("send");
	    retbuf.type = EROR;
	    return retbuf;
	}
	if(recv(sockfd, &retbuf, sizeof(MSG), 0) == -1){
	    perror("recv");
	    retbuf.type = EROR;
	    return retbuf;
	}
	return retbuf;
    }
    return retbuf;
}
/*
MSG history(int sockfd, MSG* sendbuf, ){

}
*/
void quit(int sockfd, MSG* sendbuf){
    send(sockfd, sendbuf, sizeof(MSG), 0);
    printf("waitting to quit ...\n");
}
void progend(int sockfd){
    sleep(1);
    close(sockfd);
    exit(0);
}
