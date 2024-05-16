#include "ring.h"

#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <pthread.h>
#include <stdio.h>

#define DEFAULT_RING_SIZE 10
#define MAX_THREADS_COUNT 50

Ring* ring;

pthread_cond_t  consumer_cond;
pthread_cond_t  producer_cond;
pthread_mutex_t mutex;

_Thread_local int continue_fl = 1;

void stop_handler(int signo) 
{
    if (signo != SIGUSR1)
        return;

    continue_fl = 0;
}

#define SLEEP_TIME 2

void* my_consumer()
{
    signal(SIGUSR1, stop_handler);

    while (continue_fl) 
    {
        pthread_mutex_lock(&mutex);
        while (ring->curr == 0) 
        {
            pthread_cond_wait(&consumer_cond, &mutex);
        } 

        Message* temp = ring->head->message;

        pop(&ring->head, &ring->tail);

        ring->consumed++;
        ring->curr--;

        printf("Consumed %ld message:\n", ring->consumed);
        print_mes(temp);

        free(temp);

        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&producer_cond);

        sleep(SLEEP_TIME);
    }

    return NULL;
}

void* my_producer()
{
    signal(SIGUSR1, stop_handler);

    while (continue_fl) 
    {
        pthread_mutex_lock(&mutex);
        while (ring->curr == ring->size) 
        {
            pthread_cond_wait(&producer_cond, &mutex);
        }

        push(&ring->head, &ring->tail);

        ring->produced++;
        ring->curr++;

        printf("Produced %ld message:\n", ring->produced);
        print_mes(ring->tail->message);

        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&consumer_cond);

        sleep(SLEEP_TIME);
    }

    return NULL;
}

int main()
{
    pthread_cond_init(&consumer_cond, NULL);
    pthread_cond_init(&producer_cond, NULL);
    pthread_mutex_init(&mutex, NULL);

    pthread_t threads[MAX_THREADS_COUNT];
    size_t producer_count = 0;
    size_t consumer_count = 0;
    size_t threads_count  = 0;
    char input[2];

    ring = (Ring*)calloc(1, sizeof(Ring));
    ring->size = DEFAULT_RING_SIZE;

    while (continue_fl)
    {
        scanf("%s", input);


        switch (input[0])
        {
        case 'p':
        {
            pthread_t producer_thread_id;
            pthread_create(&producer_thread_id, NULL, my_producer, NULL);
            threads[threads_count++] = producer_thread_id;
            producer_count++;
            break;
        }        
        case 'c':
        {
            pthread_t consumer_thread_id;
            pthread_create(&consumer_thread_id, NULL, my_consumer, NULL);
            threads[threads_count++] = consumer_thread_id;
            consumer_count++;
            break;
        }
        case 's':
        {
            printf("\nINFO\nProduced: %ld\nConsumed: %ld\nProducers count: %ld\nConsumers count: %ld\nCurrent ring size: %ld\n\n", ring->produced, ring->consumed, producer_count, consumer_count, ring->curr);                                                         
            break;
        }
        case '+':
        {
            pthread_mutex_lock(&mutex);
            ring->size++;
            pthread_cond_signal(&producer_cond);
            pthread_mutex_unlock(&mutex);
            break;
        }
        case '-':
        {
            pthread_mutex_lock(&mutex);
            if (ring->size > 0) 
            {
                ring->size--;
                if (ring->curr > ring->size)
                {
                    pop(&ring->head, &ring->tail);
                    ring->curr--;
                } 
            }
            else printf("\nRING IS EMPTY\n");
            pthread_mutex_unlock(&mutex);
            break;
        }
        case 'q':
        {
            while (threads_count != 0)
            {
                pthread_cancel(threads[threads_count - 1]);
                pthread_join(threads[threads_count - 1], NULL);
                threads_count--;
            }

            pthread_cond_destroy(&consumer_cond);
            pthread_cond_destroy(&producer_cond);
            pthread_mutex_destroy(&mutex);

            continue_fl = 0;

            break;
        }
        default:
            break;
        }
    }
    return 0;
}