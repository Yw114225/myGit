#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int fd = open("fileio.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
    if(fd == -1){
	printf("create failed\n");
	return -1;
    }
    else puts("success");
    printf("%d ", fd);
    if( !close(fd) )
	puts("close success");
    else puts("close failed");
    return 0;
}
