#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef void (*sighandler_t)(int);

sighandler_t o_handler;

void sighandler(int sig)
{
    printf("input crtl + c\n");
    signal(SIGINT, o_handler);
}

int main(int argc, char* argv[])
{
    o_handler = signal(SIGINT, sighandler);
    while(1){
	sleep(1);
    }
    return 0;
}
