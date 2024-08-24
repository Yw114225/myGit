#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char wbuf[32] = {0};
    int fifore = mkfifo("./fifotest", 0666);
    if(!fifore){
	perror("mkfifo");
	return -1;
    }
    int fd = open("./fifotest", O_WRONLY);
    if(fd < 0){
	perror("open");
	return -1;
    }
    while(1){
	    fgets(wbuf, 32, stdin);
	    write(fd, wbuf, strlen(wbuf));
    }
    return 0;
}
