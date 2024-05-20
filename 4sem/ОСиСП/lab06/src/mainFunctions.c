#include "mainFunctions.h"

// Сравнение двух объектов для qsort.
int compare(const void* a, const void* b) {        
    if (((index_record*)a)->time_mark < ((index_record*)b)->time_mark)
        return -1;
    else if(((index_record*)a)->time_mark > ((index_record*)b)->time_mark)
        return 1;
    else
        return 0;
}

void* sorting(void* threadA) {
    // Получение параметров файла.
    thread_args* args = (thread_args*)threadA;
    pthread_barrier_wait(&barrier);

    // Сортировка блоков qsort.
    printf("Qsort in %d thread.\n", args->threadNum);
    while(cur < args->buf + size) {
        pthread_mutex_lock(&mutex);
        if(cur < args->buf + size) {
            index_record *temp = cur;
            cur += args->blockSize;
            pthread_mutex_unlock(&mutex);
            qsort(temp, args->blockSize, sizeof(index_record), compare);
        } else {
            pthread_mutex_unlock(&mutex);
            pthread_barrier_wait(&barrier);
            break;
        }
    }
    printf("Merging in %d thread.\n", args->threadNum);
    int mergeStep = 2;
    // merge
    while(mergeStep<=blocks) {
        // Слияние отсортированных блоков.
        pthread_barrier_wait(&barrier);
        cur = args->buf;
        while (cur < args->buf + size) {
            pthread_mutex_lock(&mutex);
            if(cur < args->buf + size) {
                index_record *temp = cur;
                cur += mergeStep*args->blockSize;
                pthread_mutex_unlock(&mutex);
                int bufSize = (mergeStep / 2) * args->blockSize;
                index_record *left = (index_record *) malloc(bufSize * sizeof(index_record));
                memcpy(left, temp, (mergeStep / 2) * args->blockSize*sizeof(index_record));
                index_record *right = (index_record *) malloc(bufSize * sizeof(index_record));
                memcpy(right, temp + (mergeStep / 2) * args->blockSize,(mergeStep / 2) * args->blockSize*sizeof(index_record));

                int i = 0, j = 0;
                while (i < bufSize && j < bufSize) {
                    if (left[i].time_mark < right[j].time_mark) {
                        temp[i+j].time_mark = left[i].time_mark;
                        temp[i+j].recno = left[i].recno;
                        i++;
                    } else {
                        temp[i+j].time_mark = right[j].time_mark;
                        temp[i+j].recno = right[j].recno;
                        j++;
                    }
                }
                if (i == bufSize) {
                    while (j > bufSize) {
                        temp[i+j].time_mark = right[j].time_mark;
                        temp[i+j].recno = right[j].recno;
                        j++;
                    }
                }
                if (j == bufSize) {
                    while (i < bufSize) {
                        temp[i+j].time_mark = left[i].time_mark;
                        temp[i+j].recno = left[i].recno;
                        i++;
                    }
                }
            } else {
                pthread_mutex_unlock(&mutex);
                break;
            }
        }
        mergeStep*=2;
    }
    pthread_mutex_unlock(&mutex);
    pthread_barrier_wait(&barrier);
    return NULL;
}

void* openMem(void* data) {
    printf("Opening data start.\n");
    create_data* c_data = (create_data*)data;      

    // Open file
    FILE* f = fopen(c_data->fname, "rb+");
    if (f == NULL) {
        printf("Error while opening file.\n");
        return 0;
    }

    fseek(f, 0, SEEK_END);
    size_t fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    int fd = fileno(f);
    void* buf;
    // Memory map the file
    if ((buf = mmap(NULL, fsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
        printf("Error while creating mapping, %d\n", errno);
        exit(errno);
    }

    // Advance to the structure
    buf = (char*)buf + sizeof(uint64_t);                    
    cur = (index_record*)buf;

    printf("Creating threads.\n");

    // Launch threads
    pthread_t threadsId[c_data->threads - 1];     
    for (int i = 1; i < c_data->threads; i++) {
        thread_args* args = (thread_args*)malloc(sizeof(thread_args));
        args->blockSize = c_data->blockSize;
        args->threadNum = i;
        args->buf = (index_record*)buf;

        if (pthread_create(&threadsId[i - 1], NULL, sorting, args) != 0) {
            printf("Error while creating %d thread.\n", i);
            exit(0);
        }
    }
    thread_args* args = (thread_args*)malloc(sizeof(thread_args));
    args->blockSize = c_data->blockSize;
    args->threadNum = 0;
    args->buf = (index_record*)buf;
    sorting(args);

    for (int i = 1; i < c_data->threads; i++) {
        // Wait for threads to finish
        pthread_join(threadsId[i - 1], NULL); 
    }   
    printf("End of threads.\n");

    munmap(buf, fsize);
    fclose(f);
    printf("Memory closing.\n");
    return NULL;
}