#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE
#include <signal.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/shm.h>

#include "ring.h"

bool flag = true; 

void sigusr1_handler(int signo) {
    if (signo != SIGUSR1) {
        return;
    }

    flag = false;
}

int main(int argc, char* argv[]) {
    signal(SIGUSR1, sigusr1_handler);

    sem_t* consumer = sem_open("/consumer", 0);
    sem_t* mutex = sem_open("/mutex", 0);

    int desc = shm_open("/mem", O_RDWR, S_IRUSR | S_IWUSR);
    Ring* ring = (Ring*)mmap(NULL, sizeof(Ring), PROT_READ | PROT_WRITE, MAP_SHARED, desc, 0);

    while (flag) {
        sem_wait(consumer);
        sem_wait(mutex);

        if (!is_empty(ring)) {
            Message message = pop_ring(ring);
            ring->consumed++;
            printf("%s | Message: %s\n", argv[0], message.data);
        }

        sem_post(mutex);
        sem_post(consumer);

        sleep(5);
    }

    munmap(ring, sizeof(Ring));
    sem_close(consumer);
    sem_close(mutex);

    return 0;
}