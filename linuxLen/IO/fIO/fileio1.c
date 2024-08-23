#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int fd = open("fileio.txt", O_RDWR | O_APPEND | O_CREAT);
    if(fd != -1)
	puts("open success");
    else{
	puts("open failed");
	return -1;
    }
    int bufw[] = {1, 2, 3, 4, 5};
    int bufr[5] = {0};
    ssize_t w = write(fd, &bufw, 4*sizeof(int));
    //close(fd);
    //fd = open("fileio.txt", O_RDWR | O_APPEND | O_CREAT);
    lseek(fd, 0, SEEK_SET);
    ssize_t r = read(fd, &bufr, 4*sizeof(int));
    printf("w = %d, r = %d\n", (int)w, (int)r);
    for(int i = 0; i < sizeof(bufr)/sizeof(bufr[0]); ++i)
	printf("%d ", bufr[i]);
    if( !close(fd) )
	puts("\nclose success");
    else puts("\nclose failed");
    return 0;
}
