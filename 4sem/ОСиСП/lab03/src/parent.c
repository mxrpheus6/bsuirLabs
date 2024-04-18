#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include "stack.h"

#define BUFFER_SIZE 64

void signal1_handler(int signum) {}
void signal2_handler(int signum) {}

int main(int argc, char** argv, char** envp) {
    if (argc < 2)
        return EXIT_FAILURE;
    
    signal(SIGUSR1, signal1_handler);
    signal(SIGUSR2, signal2_handler);

    int child_count = 0;
    pid_t child_pid;
    Node* child_pid_stack = NULL;

    char buffer[BUFFER_SIZE] = "\0";

    while (scanf(" %s", buffer)) {
        char* child_argv[2] = {(char*)0};

        switch (buffer[0])
        {
        case '+':
        {
            switch (child_pid = fork())
            {
            case -1:
            {
                child_count--;
                perror("Fork error");
                break;
            }
            case 0:
            {
                child_argv[0] = (char*)malloc(sizeof(char) * 6);
                sprintf(child_argv[0], "C_%d", child_count);

                if (execve(argv[1], child_argv, envp) == -1) 
                {
                    perror("Execve");
                    free(child_argv[0]);
                    exit(1);
                }
                break;
            }
            default:
                push_stack(&child_pid_stack, child_pid);
                child_count++;
                break;
            }

            break;
        }
        case '-':
        {
            if (child_count > 0) 
            {
                kill(pop_stack(&child_pid_stack), SIGKILL);
                child_count--;
                printf("C_%d was killed. %d left\n", child_count, child_count);
            }
            else
                puts("Nothing to kill");

            break;
        }
        case 'l':
        {
            printf("PPID: %d\n", getpid());
            print_stack(child_pid_stack);
            break;
        }
        case 'k':
        {
            while(child_count > 0) {
                kill(pop_stack(&child_pid_stack), SIGKILL);
                child_count--;
            }
            printf("All child process were succesfully killed\n");
            break;
        }
        case 's':
        {
            if (strlen(buffer) > 1)
            {
                if(child_count < atoi(buffer + 1))
                    puts("Child with this number are not exitst");
                else
                    kill(get_pid_at_index(child_pid_stack, atoi(buffer + 1)), SIGUSR1);
            }
            else
                kill(0, SIGUSR1);

            break;
        }
        case 'g':
        {
            if (strlen(buffer) > 1)
            {
                if(child_count < atoi(buffer + 1))
                    puts("Child with this number are not exitst");
                else
                    kill(get_pid_at_index(child_pid_stack, atoi(buffer + 1)), SIGUSR2);
            }
            else
                kill(0, SIGUSR2);

            break;
        }
        case 'p':
        {
            if (strlen(buffer) <= 1) {
                break;
            }

            kill(0, SIGUSR1);
            kill(get_pid_at_index(child_pid_stack, atoi(buffer + 1)), SIGUSR2);

            sleep(1);

            kill(get_pid_at_index(child_pid_stack, atoi(buffer + 1)), SIGUSR1);

            sleep(5);
            
            kill(0, SIGUSR2);

            break;
        }
        case 'q':
        {
            kill(0, SIGKILL);
            return 0;
        }
        default:
            break;
        }
    }
}