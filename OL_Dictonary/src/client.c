#include "../inc/mystd.h"

MSG regester(int sockfd, MSG* sendbuf);
MSG signin(int sockfd, MSG* sendbuf);
//MSG inquire(int sockfd, MSG* sendbuf, );
//MSG history(int sockfd, MSG* sendbuf, );
void quit(int sockfd, MSG* sendbuf);
void list(int order);

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
		    goto scdrylist;
		}else puts("information error, try again");
		break;
	    case 3:
		quit(sockfd, &sendbuf);
		sleep(1);
		goto end;
		break;
	    default :
		puts("Invalide cmd");
	}
    }

scdrylist:
    while(1){
	int cmd = -1;
	list(2);
	scanf("%d", &cmd);
	switch(cmd){
	    case 1:
		/*recvbuf = inquire(sockfd, &sendbuf);
		if(recvbuf.type == VDOF){
		    printf("%s: %s\n", recvbuf.name, recvbuf.data);
		}else printf("There is no word: %s\n", recvbuf.name);
		*/
		break;
	    case 2:
		//recvbuf = history(sockfd, &sendbuf);

		break;
	    case 3:
		quit(sockfd, &sendbuf);
		goto end;
		break;
	    case 4:
		goto list1;
	    default :
		puts("Invalide emd");
	}
list1:
	break;
    }

end:
    sleep(1);
    close(sockfd);
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
	puts("* 1.inquire  2.history  3.quit  4:last list *");
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
/*
MSG inquire(int sockfd, MSG* sendbuf, ){

}

MSG history(int sockfd, MSG* sendbuf, ){

}
*/
void quit(int sockfd, MSG* sendbuf){
    send(sockfd, sendbuf, sizeof(MSG), 0);
    printf("waitting to quit ...\n");
}
