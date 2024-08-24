#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <pthread.h>

//#define SERV_IP_ADDR  "172.20.80.100"
#define SERV_IP_ADDR  "127.0.0.1"
#define SERV_PORT     5001

void *handler(void *arg){
    int newfd = *(int *)arg, ret;
    char buf[1024];
    while(1){
	do{
	    memset(buf, 0, sizeof(buf));
	    ret = read(newfd, buf, sizeof(buf));
	    printf("%d", ret);
	    if(ret < 0){
		perror("read");
		exit(-1);
	    }
	    if(strncmp(buf, "quit", 4) == 0){
		printf("sig = quit\n");
		close(newfd);
		exit(0);
	    }
	    printf("read %s\n", buf);
	}while(ret == 0);
    }
}

void usage(char *s){
    printf("\n%s serv_ip serv_port", s);;
    printf("\nserv_ip: server_ip address");
    printf("\nserv_port: server_ip port(>5000)\n");
}

int main(int argc, char* argv[])
{
    if(argc != 3){
	usage(argv[0]);
	exit(-1);
    }
    short port;
    struct sockaddr_in saddr;
    /*创建socket*/
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0){
	perror("socket");
	return -1;
    }
    port = atoi(argv[2]);
    if(port < 5000){
	usage(argv[0]);
	exit(-1);
    }

    bzero(&saddr, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
#if 0
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
#else
    if(inet_pton(AF_INET, argv[1], (void *)&saddr.sin_addr.s_addr) != 1){
	perror("iner_pton");
	return -1;
    }
#endif

    /* 绑定  */
    int b_reuse = -1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &b_reuse, sizeof(int));
    if(bind(fd, (struct sockaddr *)&saddr, sizeof(saddr))< 0 ){
	perror("bind");
	return -1;
    }
    
    if(listen(fd, 5) != 0){
	perror("listen");
	return -1;
    }
    /* 多并发accept */
    struct sockaddr_in cin;
    socklen_t cinlen;
    while(1){
	int newfd = accept(fd, (struct sockaddr *)&cin.sin_addr, &cinlen);
	if(newfd < 0){
	    perror("accept");
	    return -1;
	}
	char ipv4_addr[16];
	if(!inet_ntop(AF_INET, (void *)&cin.sin_addr, ipv4_addr, sizeof(cin))){
	    perror("inet_ntop");
	    return -1;
	}
	printf("Client(%s:%d) is connected\n", ipv4_addr, ntohs(cin.sin_port));
	pthread_t tid;
	pthread_create(&tid, NULL, handler, (void *)&newfd);
    }

    close(fd);

}
