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
#if 1
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
#else
    if(inet_pton(AF_INET, SERV_IP_ADDR, (void *)&saddr.sin_addr.s_addr) != 1){
	perror("iner_pton");
	return -1;
    }
#endif
    /*绑定  */
    if(bind(fd, (struct sockaddr *)&saddr, sizeof(saddr))< 0 ){
	perror("bind");
	return -1;
    }
    
    if(listen(fd, 5) != 0){
	perror("listen");
	return -1;
    }
    
#if 0
    int newfd = accept(fd, NULL, NULL);
    if(newfd < 0){
	perror("accpet");
	return -1;
    }else printf("one client is connected\n");
#else
    struct sockaddr_in cin;
    socklen_t cinlen;
    int newfd = accept(fd, (struct sockaddr *)&cin.sin_addr, &cinlen);
    if(newfd < 0){
	perror("accept");
	return -1;
    }
    char ipv4_addr[16];
    if(inet_ntop(AF_INET, (void *)&cin.sin_addr, ipv4_addr, sizeof(cin)) == NULL){
	perror("inet_ntop");
	return -1;
    }
    printf("Client(%s:%d) is connected!\n", ipv4_addr, ntohs(cin.sin_port));
#endif
    char buf[128] = {0};
    int ret;
    while(1){
	ret = read(newfd, buf, sizeof(buf));
	if(ret < 0){
	    perror("read");
	    return -1;
	}
	if(ret != 0)
	    printf("rec = %s\n", buf);
    }
    close(newfd);
    close(fd);

}
