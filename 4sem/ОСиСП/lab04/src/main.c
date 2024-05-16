#define _POSIX_C_SOURCE
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <signal.h>
#include <fcntl.h>

#include "ring.h"

#define PRODUCER_PATH "/home/mxrph/osisp/lab04/producer"
#define CONSUMER_PATH "/home/mxrph/osisp/lab04/consumer"

int main(int argc, char* argv[]) {
    sem_t* producer = sem_open("/producer", O_CREAT, 0644, 1);
    sem_t* consumer = sem_open("/consumer", O_CREAT, 0644, 1);
    sem_t* mutex = sem_open("/mutex", O_CREAT, 0644, 1);

    int desc = shm_open("/mem", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    ftruncate(desc, sizeof(Ring));
    Ring* ring = (Ring*)mmap(NULL, sizeof(Ring), PROT_READ | PROT_WRITE, MAP_SHARED, desc, 0);

    init_ring(ring);

    pid_t consumer_procs[50];
    pid_t producer_procs[50];
    size_t producer_count = 0;
    size_t consumer_count = 0;
    char input[2];

    while (1)
    {
        scanf("%s", input);

        switch (input[0])
        {
        case 'p':
        {
            producer_procs[producer_count++] = fork();

            if (producer_procs[producer_count - 1] == 0) 
            {
                char* child_argv[2];
                child_argv[0] = (char*)malloc(sizeof(char) * 30);
                child_argv[1] = NULL;
                sprintf(child_argv[0], "Producer_%ld", producer_count); 
                execv(PRODUCER_PATH, child_argv);
            }
            break;
        }        
        case 'c':
        {
            consumer_procs[consumer_count++] = fork();
        
            if (consumer_procs[consumer_count - 1] == 0) 
            {
                char* child_argv[2];
                child_argv[0] = (char*)malloc(sizeof(char) * 30);
                child_argv[1] = NULL;
                sprintf(child_argv[0], "Consumer_%ld", consumer_count); 
                execv(CONSUMER_PATH, child_argv);
            }
            break;
        }
        case 's':
        {
            printf("\nINFO\nProduced: %ld\nConsumed: %ld\nProducers count: %ld\nConsumers count: %ld\n", ring->produced, ring->consumed, producer_count, consumer_count);
            break;
        }
        case 'q':
        {
            while (kill(producer_procs[producer_count-- - 1], SIGUSR1) == 0);
            while (kill(consumer_procs[consumer_count-- - 1], SIGUSR1) == 0);
               
            munmap(ring, sizeof(Ring)); 
            close(desc);
            shm_unlink("/mem");

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