#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


void handler(int sig)
{
    puts("input ctrl + c");
}


/*void sighandler(int sig)
{
    printf("input crtl + c\n");
    signal(SIGINT, o_handler);
}
*/

int main(int argc, char* argv[])
{
    struct sigaction act;

    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    
    //sigaction(SIGINT, &act, NULL);
    alarm(2);
    sigaction(SIGALRM, &act, NULL);
    while(1){
	sleep(1);
    }
    return 0;
}
