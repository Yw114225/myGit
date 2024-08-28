#include "../inc/mystd.h"

int main(int argc, char* argv[])
{
    if(argc != 3){

    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){

    }
    
    clnaddr.sin_port = htons(argv[2]);
    clnaddr.sin_family = AF_INET;
    if(inet_pton(AF_INET, argv[2], (void *)srvaddr.sin_addr) != 1){

    }

    if(connect(sockfd, (struct sockaddr *)srvaddr, sizeof(srvaddr)) != 0){
	
	
    }
    
    printf("connecting...\n");

    while(1){
	//yiijcaidan
	int cmd = -1;
	scanf("%d", &cmd);
	switch(cmd){
	    case REGE:
		regester();
		break;
	    case LGIN:
		signin();
		break;


	}
    }

}
