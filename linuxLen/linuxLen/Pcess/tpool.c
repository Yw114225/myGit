#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define POOL_NUM 10

typedef struct Task
{
    struct Task *next;
    void* (*func)(void *arg);
    void *arg;
}Task;

typedef struct ThreadPool
{
    pthread_mutex_t tasklock;
    pthread_cond_t  newWork;
    pthread_t tid[POOL_NUM];
    Task *queue_head;
    int busywork;
}ThreadPool;

ThreadPool *pool;

void* WorkThread(void* arg)
{
    int flag = 0;
    while(1){
	pthread_mutex_lock(&pool->tasklock);
	pthread_cond_wait(&pool->newWork, &pool->tasklock);
	printf("%d\n",flag++ );
	Task* temp = pool->queue_head;
	pool->queue_head = pool->queue_head->next;
	
	pthread_mutex_unlock(&pool->tasklock);

	temp->func(temp->arg);
	--pool->busywork;
    }

}
void* realwork(void* arg){
    printf("%d work finished\n", (int)arg);
    return NULL;
}


void pool_init(void)
{
    pool = (ThreadPool*)malloc(sizeof(ThreadPool));
    pthread_mutex_init(&pool->tasklock, NULL);
    pthread_cond_init(&pool->newWork, NULL);

    for(int i = 0; i < POOL_NUM; ++i)
    {
	pthread_create(&pool->tid[i], NULL, WorkThread, NULL);
	//pthread_detach(pool->tid[i]);
    }
    pool->queue_head = NULL;
    pool->busywork = 0;
}

void pool_destroy(void){
    Task* temp = NULL;
    while(pool->queue_head != NULL){
	temp = pool->queue_head;
	pool->queue_head = pool->queue_head->next;
	free(temp);
    }
    pthread_mutex_destroy(&pool->tasklock);
    pthread_cond_destroy(&pool->newWork);
    free(pool);
}

void pool_add_task(int arg)
{
    pthread_mutex_lock(&pool->tasklock);
    while(pool->busywork >= POOL_NUM)
    {
	pthread_mutex_unlock(&pool->tasklock);
	usleep(10000);
	pthread_mutex_lock(&pool->tasklock);
    }
    pthread_mutex_unlock(&pool->tasklock);

    Task* newTask = (Task*)malloc(sizeof(Task));
    newTask->func = realwork;
    newTask->arg = arg;

    pthread_mutex_lock(&pool->tasklock);

    Task* temp = pool->queue_head;
    if(temp == NULL)
	pool->queue_head = newTask;
    else{
	while(temp->next != NULL)
	    temp = temp->next;
	temp->next = newTask;
    }

    ++pool->busywork;
    pthread_cond_signal(&pool->newWork);
    pthread_mutex_unlock(&pool->tasklock);

}


int main(int argc, char *argv[])
{
    pool_init();
    sleep(2);
    for(int i = 1; i < 21; ++i){
	pool_add_task(i);
    }
    sleep(3);
    pool_destroy();

}
