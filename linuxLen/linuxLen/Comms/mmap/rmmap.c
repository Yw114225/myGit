#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    void* addr = NULL;
    int fd;
    fd = open("./test", O_RDONLY);
    if(fd < 0){
	perror("open");
	return -1;
    }

    addr = mmap(NULL, 2048, PROT_READ, MAP_SHARED, fd, 0);
    if(addr == MAP_FAILED){
	perror("mmap");
	return -1;
    }

    while(1){
	printf("read = %s\n", (char*)addr);
	sleep(1);
    }
    return 0;
}
