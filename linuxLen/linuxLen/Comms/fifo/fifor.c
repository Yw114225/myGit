#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char rbuf[32];
    int fd = open("./fifotest", O_RDONLY);
    if(fd < 0){
	perror("open");
	return -1;
    }
    while(1){
	memset(rbuf, 0, strlen(rbuf));
	int re = read(fd, rbuf, 32);
	if(re > 0)
	    printf("read fifo = %s", rbuf);
	else if(re == 0)
	    return 0;
    }
    return 0;
}
