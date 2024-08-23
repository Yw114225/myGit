#include <stdio.h>
#include <unistd.h>

int main(int argc, char*argv[])
{
    puts("father process output");
    pid_t pid = fork();
    if(pid > 0){
	puts("father: child process has benn creating");
	while(1){
	    sleep(1);
	    puts("father pcess");
	}
    }
    else if(pid == 0){
	puts("child : created by f");
	while(1){
	    sleep(1);
	    puts("child pcess");
	}
    }
    else{
	perror("fork");
	return -1;
    } 
    return 0;
}
