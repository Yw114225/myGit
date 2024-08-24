#include "net.h"


int main(int argc, char *argv[]){

    /* 信号处理  */

    /* 创建socket套接字 */
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0){
	perror("socket");
	exit(-1);
    }
    /* 允许绑定地址快速重用 */
    int b_reuse = -1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &b_reuse, sizeof(int));
#if 0
    int port = atoi(port);
#else
    int port = SRV_PORT;
#endif
    /* 服务器绑定本机ip */
    struct sockaddr_in srvaddr;
    memset(&srvaddr, 0, sizeof(srvaddr));
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = htons(port);
#if 1
    srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
#else
    if( inet_pton(AF_INET, SRV_IP_ADDR, (void *)&srvaddr.sin_addr.s_addr) != 1){
	perror("inet_pton");
	return -1;
    }
#endif
    if( bind(sockfd, (struct sockaddr *)&srvaddr, sizeof(srvaddr)) != 0){
	perror("bind");
	exit(-1);
    }
    /* 接收udp数据报 */
    struct sockaddr_in clnaddr;
    //memset(&clnaddr, 0 , sizeof(clnaddr));
    socklen_t clnaddrlen = sizeof(clnaddr);
    char buf[1024];
    int ret;
    puts("ready to recv");
    while(1){
	memset(buf, 0, sizeof(buf));
	ret = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&clnaddr, &clnaddrlen);
	if(ret == -1){
	    perror("recvfrom");
	    continue;
	}
	/* 数据处理  */
	do{
	    ret = 0;
	    char ipv4_addr[16];
	    if( inet_ntop(AF_INET, (void *)&clnaddr.sin_addr, ipv4_addr, sizeof(clnaddr)) == NULL){
		perror("inet_ntop");
		exit(-1);
	    }

	    if(strncasecmp(buf, "quit", 4) == 0){
		printf("clien(%s:%d) quit\n", ipv4_addr, ntohs(clnaddr.sin_port));
	    }
	    printf("rec from(%s:%d): %s\n", ipv4_addr, ntohs(clnaddr.sin_port), buf);
	}while(ret != 0);
    }
    /*  */
    //sendto(sockfd, buf, sizeof(buf), 0, );



    close(sockfd);
    return 0;
}
