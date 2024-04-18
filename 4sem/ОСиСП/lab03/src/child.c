#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define COUNT_OF_REPEATS 101
#define ARR_SIZE 4
#define SEC_TIMER 16116

typedef struct Pair {
    int first;
    int second;
} Pair;

Pair arr_of_statistic[COUNT_OF_REPEATS];
Pair statistic;
int size = 0;
int is_collect = 1; 
int is_output_allowed = 1;
int is_continue_collect = 1;

void signal1_handler(int signum) {
    if (signum != SIGUSR1)
        return;

    is_output_allowed = 0;

    return;
}

void signal2_handler(int signum) {
    if (signum != SIGUSR2)
        return;

    is_output_allowed = 1;

    return;
}

void show_statistic() {
    printf("Statistic of child process with PID = %d, PPID = %d All values: ", getpid(), getppid());

    for (size_t i = 0; i < ARR_SIZE; ++i) {
        printf("{%d, %d} ", arr_of_statistic[i].first, arr_of_statistic[i].second);
    }

    printf("\n");
}

void take_statistic() {
    arr_of_statistic[size].first = statistic.first;
    arr_of_statistic[size++].second = statistic.second;
    is_continue_collect = 0;
}

int main(int argc, char* argv[]) {
    signal(SIGALRM, take_statistic);
    signal(SIGUSR1, signal1_handler);
    signal(SIGUSR2, signal2_handler);

    while (1) {
        for (int i = 0; i < COUNT_OF_REPEATS; ++i) {
            if (size == ARR_SIZE)
                size = 0;

            ualarm(SEC_TIMER, 0);
            
            size_t j = 0;
            while (is_continue_collect) {
                statistic.first = j % 2;
                statistic.second = j % 2;
                j++;
            }

            is_continue_collect = 1;
        }
        if (is_collect) {
            if (is_output_allowed)
                show_statistic();
        }
    }

    return 0;
}