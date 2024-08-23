#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <signal.h>

sem_t semr, semw, sem;
struct arg{
    sem_t sem;
    void* shmaddr;
};

void* threadhandler1(void* argc)
{
    struct arg *args = (struct arg*)argc;
    while(1){
	sem_wait(&args->sem);
	printf(">");
	fgets(args->shmaddr, 1024, stdin);
	sem_post(&args->sem);
	sleep(1);
    }
    return NULL;
}

void* threadhandler2(void* argc){
    struct arg *args = (struct arg*)argc;
    while(1){
	if(sem_wait(&args->sem) == 0){
	    printf("%s\n", args->shmaddr);
	    sem_post(&args->sem);
	    }
	sleep(1);
    }
    return NULL;

}

void sighandler(int sig)
{
    printf("receive sig %d\n", sig);
    sem_destroy(&sem);
}

int main(int argc, char* argv[])
{
    //system V 创建共享内存
    key_t key = ftok("./test", 10);
    int shmid = shmget(key, 1024, IPC_CREAT | 0666);
    if(shmid < 0){
	perror("shmget");
	return -1;
    }
    void *shmaddr = shmat(shmid, NULL, 0);

    struct sigaction act;
    act.sa_handler = sighandler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);
    
    //无名信号量
    int ret  = sem_init(&sem, 0, 1);
    if(ret < 0){
	perror("sem_init");
	return -1;
    }
    pthread_t tid1, tid2; 
    struct arg pthd1arg;
    pthd1arg.sem = sem;
    pthd1arg.shmaddr = shmaddr;
    if( pthread_create(&tid1, NULL, threadhandler1, (void*)&pthd1arg) != 0){
	perror("pthread");
	return -1;
    }
    if( pthread_create(&tid2, NULL, threadhandler2, (void*)&pthd1arg) != 0){
	perror("pthread");
	return -1;
    }
    while(1){
	sleep(1);
    }


    return 0;
}
