#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define POOL_NUM 10


typedef struct Task{
    void *(*func)(void *arg);
    void *arg;
    struct Task *next;
}Task;

typedef struct ThreadPool{
    pthread_mutex_t tasklock;
    pthread_cond_t newTask;

    pthread_t tid[POOL_NUM];
    Task *queue_head;
    int busywork;

}ThreadPool;


ThreadPool *pool;

void *workThread(void *arg)
{
    while(1){
	pthread_mutex_lock(&pool->tasklock);
	pthread_cond_wait(&pool->newTask, &pool->tasklock);

	Task *ptask = pool->queue_head;
	pool->queue_head = pool->queue_head->next;

	pthread_mutex_unlock(&pool->tasklock);

	ptask->func(ptask->arg);
	--pool->busywork;
    }
}

void *realwork(void *arg)
{
    printf("Finish work %d\n", (int)arg);
}

void pool_add_task(int arg)
{
    Task *newTask;
    pthread_mutex_lock(&pool->tasklock);
    while(pool->busywork >= POOL_NUM){
	pthread_mutex_unlock(&pool->tasklock);
	usleep(10000);//休眠时保证其他任务能解锁
	pthread_mutex_lock(&pool->tasklock);
    }
    pthread_mutex_unlock(&pool->tasklock);

    newTask = (Task*)malloc(sizeof(Task));
    newTask->func = realwork;
    newTask->arg  = arg;

    pthread_mutex_lock(&pool->tasklock);
    Task *member = pool->queue_head;
    if(member == NULL){
	pool->queue_head = newTask;
    }else{
	while(member->next != NULL){
	    member = member->next;
	}
	member->next = newTask;
    }

    ++pool->busywork;
    pthread_cond_signal(&pool->newTask);

    pthread_mutex_unlock(&pool->tasklock);
}


void pool_init(void)
{
    pool = malloc(sizeof(ThreadPool));
    pthread_mutex_init(&pool->tasklock, NULL);
    pthread_cond_init(&pool->newTask, NULL);
    pool->queue_head = NULL;
    pool->busywork = 0;

    for(int i = 0; i < POOL_NUM; ++i){
	pthread_create(&pool->tid[i], NULL, workThread, NULL);
    }
}

void pool_destroy(void)
{
    Task* temp = NULL;
    while(pool->queue_head != NULL){
	temp = pool->queue_head;
	pool->queue_head = pool->queue_head->next;
	free(temp);
    }
    pthread_mutex_destroy(&pool->tasklock);
    pthread_cond_destroy(&pool->newTask);
    free(pool);

}
int main(int argc, char* argv[])
{
    pool_init();
    sleep(1);
    for(int i = 1; i <= 20; ++i){
	pool_add_task(i);
    }
    sleep(2);
    pool_destroy();
    return 0;
}



