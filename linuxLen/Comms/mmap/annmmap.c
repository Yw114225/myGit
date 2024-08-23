#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    void* addr = NULL;
    char rbuf[2048] = {0};
    addr = mmap(NULL, 2048, PROT_WRITE | PROT_READ, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if(addr == MAP_FAILED){
	perror("mmap");
	return -1;
    }
    pid_t pid = fork();
    if(pid < 0)
	perror("fork");
    else if(pid == 0){
	sleep(1);
	printf("pchild read = %s\n", (char *)addr);
    }else{
	memcpy(addr, "1234567890", 10);
	wait(NULL);
    }	    
    munmap(addr, 2048);
    
    return 0;
}
