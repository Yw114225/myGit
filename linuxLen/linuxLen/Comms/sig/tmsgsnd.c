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
    msgp.msg_type = 1;
    strcpy(msgp.buf, "abcdefg");

    int msgid = msgget(key, IPC_CREAT|0666);
    if(msgid < 0){
	perror("msgget");
	return -1;
    }
    int msglen = sizeof(msgT) - sizeof(long);
    int ret = msgsnd(msgid, &msgp, msglen, 0);
    if(ret < 0){
	perror("msgsnd");
	return -1;
    }
    return 0;

}
