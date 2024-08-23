#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>

#define SEM_WRITE 1
#define SEM_READ  0

sem_t *semr, *semw;
int shmid;
void* shmaddr;
int semid;

void delsemrhandler(int sig)
{
    printf("input sig %d\n", sig);
    semctl(semid, 0, IPC_RMID);
    shmctl(shmid, IPC_RMID, NULL);
    exit(0);
}

union semun{
    int val;
};

struct sembuf sopsP, sopsV;

void Psops(int semid, int sem_num){
    sopsP.sem_num = sem_num;
    sopsP.sem_op = -1;
    sopsP.sem_flg = 0;
    semop(semid, &sopsP, 1);
}

void Vsops(int semid, int sem_num){
    sopsV.sem_num = sem_num;
    sopsV.sem_op = 1;
    sopsV.sem_flg = 0;
    semop(semid, &sopsV, 1);
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
    
    semid = semget(key, 1, IPC_CREAT | 0666);
    if(semid == -1){
	perror("semget");
	return -1;
    }
    union semun mysem;
    mysem.val = 0;
    semctl(semid, SEM_READ, SETVAL, &mysem);
    mysem.val = 1;
    semctl(semid, SEM_WRITE, SETVAL, &mysem);
    
    pid_t pid = fork();
    if(pid < 0){
	perror("fork");
	shmctl(shmid, IPC_RMID, NULL);
	semctl(semid, 0, IPC_RMID);
	return -1;
    }else if(pid == 0){
	while(1){
	    Psops(semid, SEM_READ);
	    printf("%s\n",shmaddr);
	    Vsops(semid, SEM_WRITE);
	}
    }else{
	while(1){
	    Psops(semid,SEM_WRITE);
	    printf(">");
	    fgets(shmaddr, 1024, stdin);
	    Vsops(semid,SEM_READ);
	}
    }



    /*
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
    
*/
    return 0;
}
