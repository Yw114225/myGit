#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SRV_IP_ADDR "127.0.0.1"
#define SRV_PORT     6001

#define REGE  11 //用户注册
#define LGIN  12 //用户登录
#define QUIT  13 //请求退出
#define EROR  14 //错误信息
#define VFOK  15 //正确信息
#define INQY  16 //请求查询
#define HSTY  17 //历史查询

#define BUFSIZE 256
//约定通信双方数据类型
typedef struct message{
    int type;
    char name[32];
    char data[BUFSIZE];
}MSG;

//
struct sockaddr_in srvaddr, clnaddr;


