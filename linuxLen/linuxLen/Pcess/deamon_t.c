#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    puts("before fork");
    pid_t pid = fork();
    if(pid == 0){
	while(1){
	    puts("this is child process");
	    sleep(1);
	}
    }
    else if(pid > 0){
	while(1){
	    puts("this if father process");
	    sleep(1);
	}
    }
    else if(pid < 0){
	perror("fork");
	return -1;
    }


    return 0;
}
