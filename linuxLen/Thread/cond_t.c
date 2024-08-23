#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

struct taxi{
    struct taxi* next;
    int num;
};

void taxicreate(struct taxi* qtaxi){
    
    ta->next = (struct taxi*)malloc(sizeof(struct taxi));
    ta->num = i++;
    ta->next = qtaxi;
    qtaxi = ta;

}



int main(int argc, char* argv)
{
    struct taxi* qtaxi = NULL;
    int i = 0;

    pthread_mutex_t lock = PTHREAD_MUTEX_INITATION;
    pthread_cond_t  hasTaxi = PTHREAD_COND_INITATION;

    //生产者
    pthread_mutex_lock(&lock);

    struct taxi* ta = NULL;
    ta->next = (struct taxi*)malloc(sizeof(struct taxi));
    ta->num = i++;
    ta->next = qtaxi;
    qtaxi = ta;

    pthread_cond_signal(&lock);

    printf("taxi %d is ready\n", i);

    pthread_mutex_unlock(&lock);
    

    //消费者
    pthread_mutex_lock(&lock);
    while(){
	pthread_cond_wait(&hasTaxi, &lock);
    }
    pthread_mutex_unlock(&lock);

    return 0;
}
