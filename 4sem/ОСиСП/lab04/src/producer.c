#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE
#include <sys/random.h>
#include <time.h>
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

//djb2
uint16_t hash(u_int8_t* data, size_t len) {
    uint16_t hash = 5381;
    int num;

    for (size_t i = 0; i < len; i++) {
        num = data[i];
        hash = ((hash << 5) + hash) + num; //hash * 33 + num
    }

    return hash;
}

Message generate_message() {
    srand(time(NULL));
    const char symbols[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%%^&*().";

    Message message;
    uint16_t message_size = 0;

    while(message_size == 0) {
        message_size = rand();
        message_size = message_size % 256;
        message.size = message_size;
    }

    for (int i = 0; i < message_size; i++) {
        message.data[i] = symbols[rand() % 74];
    }

    message.type = rand() % 256;
    message.hash = hash(message.data, message_size);

    return message;
}

int main(int argc, char* argv[]) {
    signal(SIGUSR1, sigusr1_handler);

    //открытие семафоров
    sem_t* producer = sem_open("/producer", 0);
    sem_t* mutex = sem_open("/mutex", 0);

    //открытие и отображение объекта разделяемой памяти
    int desc = shm_open("/mem", O_RDWR, S_IRUSR | S_IWUSR);
    Ring* ring = (Ring*)mmap(NULL, sizeof(Ring), PROT_READ | PROT_WRITE, MAP_SHARED, desc, 0);

    while (flag) {
        //блокировка процесса пока семафоры не доступны
        sem_wait(producer);
        sem_wait(mutex);

        Message message = generate_message();
        if (!is_full(ring)) {
            push_ring(ring, message);
            ring->produced++;
            printf("%s | Message: %s\n", argv[0], message.data);
        }

        //разблокировка семафоров
        sem_post(mutex);
        sem_post(producer);

        sleep(5);
    }
    
    munmap(ring, sizeof(Ring));
    sem_close(producer);
    sem_close(mutex);

    return 0;
}