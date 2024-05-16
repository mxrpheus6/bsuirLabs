#define _POSIX_C_SOURCE
#define _DEFAULT_SOURCE

#include "producer_consumer.h"
#include "ring.h"

#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <pthread.h>

extern Ring* ring;

_Thread_local int consumer_continue = 1;

int threads_counter = 0;

void stop_handler(int signo) 
{
    if (signo != SIGUSR1)
        return;

    consumer_continue = 0;
}

#define SLEEP_TIME 2

void* my_consumer()
{
    signal(SIGUSR1, stop_handler);

    sem_t* consumer = sem_open("/consumer", 0);
    sem_t* mutex    = sem_open("/mutex", 0);

    while (consumer_continue) 
    {
        sem_wait(consumer);                                   
        sem_wait(mutex);

        if (ring->curr > 0) 
        {  
            Message* temp = ring->head->message;

            pop(&ring->head, &ring->tail);

            ring->consumed++;
            ring->curr--;

            printf("Consumed %ld message:\n", ring->consumed);
            print_mes(temp);

            free(temp);
        } 

        sem_post(mutex);                                       
        sem_post(consumer);

        sleep(SLEEP_TIME);
    }

    sem_close(consumer);                                    
    sem_close(mutex);

    printf("\nConsumer %d has finished\n", (threads_counter++ + 1));

    return NULL;
}

void* my_producer()
{
    signal(SIGUSR1, stop_handler);

    sem_t* producer = sem_open("/producer", 0);
    sem_t* mutex    = sem_open("/mutex", 0);

    while (consumer_continue) 
    {
        sem_wait(producer);                                   
        sem_wait(mutex);

        if (ring->curr < ring->size) 
        {  
            push(&ring->head, &ring->tail);

            ring->produced++;
            ring->curr++;

            printf("Produced %ld message:\n", ring->produced);
            print_mes(ring->tail->message);
        }

        sem_post(mutex);                                       
        sem_post(producer);

        sleep(SLEEP_TIME);
    }

    sem_close(producer);                                    
    sem_close(mutex);

    printf("\nProducer %d has finished\n", (threads_counter++ + 1));

    return NULL;
}