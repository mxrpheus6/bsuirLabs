#define _POSIX_C_SOURCE
#define _DEFAULT_SOURCE

#include "ring.h"
#include "producer_consumer.h"

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

int main()
{
    sem_t* producer = sem_open("/producer", O_CREAT, 0644, 1);
    sem_t* consumer = sem_open("/consumer", O_CREAT, 0644, 1);
    sem_t* mutex    = sem_open("/mutex", O_CREAT, 0644, 1);

    pthread_t threads[MAX_THREADS_COUNT];
    size_t producer_count = 0;
    size_t consumer_count = 0;
    size_t threads_count  = 0;
    char input[2];

    ring = (Ring*)calloc(1, sizeof(Ring));
    ring->size = DEFAULT_RING_SIZE;

    while (1)
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
            sem_wait(mutex);
            ring->size++;
            sem_post(mutex);
            break;
        }
        case '-':
        {
            sem_wait(mutex);
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
            sem_post(mutex);
            break;
        }
        case 'q':
        {
            while (threads_count != 0)
            {
                pthread_kill(threads[threads_count - 1], SIGUSR1);
                pthread_join(threads[threads_count - 1], NULL);
                threads_count--;
            }

            sem_close(producer);
            sem_close(consumer);
            sem_close(mutex);
            
            sem_unlink("/producer");
            sem_unlink("/consumer");
            sem_unlink("/mutex");
            
            return 0;
        }
        default:
            break;
        }
    }
    return 0;
}