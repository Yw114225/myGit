#include "net.h"
#include <signal.h>

void sighandle(int signo){
    if(signo == SIGINT){
	puts("udp client quit");
    }
}

void usage(char* s){
    printf("\n%s srv_ip_addr srv_port", s);
    printf("\nsrv_ip_adr: server_ip_address");
    printf("\nsrv_ip_port: server_port\n\n");
}

int main(int argc, char* argv[])
{
    if(argc != 3){
	usage(argv[0]);
	exit(-1);
    }

    struct sigaction exitsig;
    exitsig.sa_handler = sighandle;
    sigemptyset(&exitsig.sa_mask);
    exitsig.sa_flags = 0;
    sigaction(SIGINT, &exitsig, NULL);

    /* 创建socket套接字 */
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0){
	perror("socket");
	exit(-1);
    }

    int port = atoi(argv[2]);
    /* 客户端sendto */
    char buf[1024] = {0};
    struct sockaddr_in srvaddr;
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = htons(port);
    if( inet_pton(AF_INET, argv[1], (void *)&srvaddr.sin_addr.s_addr) != 1){
	perror("inet_pton");
	exit(-1);
    }
    while(1){
	if( fgets(buf, sizeof(buf), stdin) == NULL){
	    perror("fgets");
	    continue;
	}
	if( sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&srvaddr, sizeof(srvaddr)) == -1){
	    perror("sendto");
	    continue;
	}
	if(strncasecmp(buf, "quit", 4) == 0){
	    printf("clien is exited\n");
	    break;
	}

	printf("send data to(%s:%s): %s\n", argv[1], argv[2], buf);
	memset(buf, 0, sizeof(buf));
    }

    /* 接收服务器反馈 */
    //recvfrom();

    close(sockfd);

}
