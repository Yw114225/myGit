#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>

sem_t *semr, *semw;
int shmid;
void* shmaddr;

void delsemrhandler(int sig)
{
    printf("input sig %d\n", sig);
    sem_close(semw);
    sem_unlink("mysem_w");
    shmdt(&shmaddr);
    shmctl(shmid, IPC_RMID, NULL);

}


int main(int argc, char* argv[])
{
    key_t key = ftok("./semtest", 10);
    shmid = shmget(key, 1024, IPC_CREAT | 0666);
    if(shmid < 0){
	perror("shmget");
	return -1;
    }
    
    struct sigaction act;
    act.sa_handler = delsemrhandler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);
    
    shmaddr = shmat(shmid, NULL, 0);
    
    semw = sem_open("mysem_w", O_CREAT | O_RDWR, 0666, 1);
    semr = sem_open("mysem_r", O_CREAT | O_RDWR, 0666, 0);
    if(semw == SEM_FAILED){
	perror("sem_open");
	return -1;
    }
    while(1){
	sem_wait(semw);//p
	printf(">");
	fgets(shmaddr, 1024, stdin);
	sem_post(semr);//v
    }
    

    return 0;
}
