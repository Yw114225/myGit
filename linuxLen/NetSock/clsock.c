#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

//#define SERV_IP_ADDR  "172.20.80.100"
#define SERV_IP_ADDR  "127.0.0.1"
#define SERV_PORT     5001

int main(int argc, char* argv[])
{
    /*创建socket*/
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0){
	perror("socket");
	return -1;
    }
    struct sockaddr_in saddr;
    bzero(&saddr, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(SERV_PORT);
#if 0
    addr.sin_addr.s_addr = inet_addr(SERV_IP_ADDR);
#else
    if(inet_pton(AF_INET, SERV_IP_ADDR, (void *)&saddr.sin_addr.s_addr) != 1){
	perror("iner_pton");
	return -1;
    }
#endif
    /*绑定  */
    if(connect(fd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0 ){
	perror("bind");
	return -1;
    }else printf("connect success\n");
    
    char buf[128] = {0};
    while(1){
	if(fgets(buf, sizeof(buf), stdin) == NULL){
	    continue;
	}
	write(fd, buf, strlen(buf));
	sleep(1);
    }
    close(fd);
    return 0;
}
