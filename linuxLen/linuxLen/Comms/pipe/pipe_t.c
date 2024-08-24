#include <stdio.h>
#include <unistd.h>

int main()
{
    int pfd[2];

    int pipeflag = pipe(pfd);
    if(!pipeflag)
	perror("pipe");
    int pid = fork();

    char wbuf[] = {"abcdefg"};
    char rbuf[10];

    if(pid < 0)
	perror("fork");
    else if(pid == 0){
	puts("this is child process");
	write(pfd[1], wbuf, 7);
    }else{
	puts("this if father process");
	read(pfd[0], rbuf, 7);
    }
    printf("%s\n", rbuf);
    return 0;
}
