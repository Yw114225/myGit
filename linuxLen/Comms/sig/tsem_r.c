#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>
#include <semaphore.h>
#include <signal.h>
#include <stdlib.h>

sem_t *semr, *semw;
int shmid;
void* shmaddr;

void delsemrhandler(int sig)
{
    printf("input sig %d\n", sig);
    sem_close(semr);
    sem_unlink("mysem_r");
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
    shmaddr = shmat(shmid, NULL, 0);
    
    struct sigaction act;
    act.sa_handler = delsemrhandler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);
    
    semw = sem_open("mysem_w", O_CREAT | O_RDWR, 0666, 1);
    semr = sem_open("mysem_r", O_CREAT | O_RDWR, 0666, 0);
    if(semr ==SEM_FAILED){
	perror("sem_open");
	return -1;
    }
    while(1){
	sem_wait(semr);//p
	printf("%s\n", shmaddr);
	memset(shmaddr,0,1024);
	sem_post(semw);//v
    }



    /* 
       sem_close(&semid);
       sem_unlink("mysem");
       shmdt(shmaddr);
       shmctl(shmid, IPC_RMID, NULL);
       */

    return 0;
}
