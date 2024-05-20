#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE

#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <threads.h>
#include <pthread.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>

typedef struct {
    index_record * buf;
    int blockSize;
    int threadNum;
} thread_args;

typedef struct {
    int blockSize;
    int threads;
    char* fname;
} create_data;

extern int size;
extern int blocks;
extern int threads;

extern pthread_barrier_t barrier;
extern pthread_mutex_t mutex;
extern index_record* cur;

int compare(const void* a, const void* b);
void* sorting(void* threadA);
void *openMem(void* data);