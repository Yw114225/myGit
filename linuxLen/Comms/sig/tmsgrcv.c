#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

typedef struct{
    long msg_type;
    char buf[128];
}msgT;

int main(int argc, char*argv[])
{
    key_t key = ftok("./test", 10);
    if(key < 0){
	perror("ftok");
	return -1;
    }
    msgT msgp;

    int msgid = msgget(key, IPC_CREAT|0666);
    if(msgid < 0){
	perror("msgget");
	return -1;
    }
    int msglen = sizeof(msgT) - sizeof(long);
    int ret;
    while(1){
	ret = msgrcv(msgid, &msgp, msglen, 1, 0);
	if(ret < 0){
	    perror("msgrcv");
	    return -1;
	}
	printf("msgtypr %ld, msg %s\n", msgp.msg_type, msgp.buf);
    }
    return 0;

}
