#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CHILD_COUNT 100
#define MAX_FILENAME_LEN 255
#define MAX_PATH_LEN 4096

extern char **environ;

int string_comparator(const void *a, const void *b) {
    const char **str1 = (const char**)a;
    const char **str2 = (const char**)b;

    return strcoll(*str1, *str2);
}

char** sort_envp(char **envp) {
    int env_count = 0;

    while (envp[env_count] != NULL) {
        env_count++;
    }

    char **sorted_envp = malloc(sizeof(char*) * (env_count + 1));

    for (int i = 0; i < env_count; i++) {
        sorted_envp[i] = envp[i]; 
    }

    qsort(sorted_envp, env_count, sizeof(char*), string_comparator);

    return sorted_envp;
}

char* get_child_path(char *envVar, char **envp)
{
    for (int i = 0; envp[i] != NULL; i++)
    {
        if (strncmp(envp[i], envVar, strlen(envVar)) == 0)
        {
            char *value = envp[i];
            int j = 0;
            while (envp[i][j] != '=') {
                j++;
            }
            value += j + 1;

            if (value != NULL)
            {
                return value;
            }
            else
            {
                return NULL;
            }

            break;
        }
    }
    return NULL;
}

int main(int argc, char* argv[], char* envp[]) {
    if (argc < 2) {
        printf("PArgument amount error. Try: %s child_path\n", argv[0]);
        return EXIT_FAILURE;
    }

    setlocale(LC_COLLATE, "C");

    char **sorted_envp = sort_envp(envp);

    int i = 0;
    while (sorted_envp[i] != NULL) {
        printf("%s\n", sorted_envp[i]);
        i++;
    }

    char key;
    char *child_path;
    int child_counter = 0;

    while(1) {
        printf("\nThis is parent process. Enter command (q to quit): ");
        scanf(" %c", &key);

        switch(key) {
            case '+':
            {
                if (child_counter >= MAX_CHILD_COUNT) {
                    printf("Reached max amount of child processes\n");
                    break;
                }

                pid_t pid = fork();

                if (pid == 0) {
                    child_path = getenv("CHILD_PATH");
                    if (child_path == NULL) {
                        printf("CHILD_PATH environment variable not set\n");
                        exit(EXIT_FAILURE);
                    }

                    char child_name[MAX_FILENAME_LEN];
                    snprintf(child_name, sizeof(child_name), "child_%02d", child_counter);

                    char *args[] = {child_name, argv[1], NULL};
                    
                    //char full_child_path[MAX_PATH_LEN];
                    //snprintf(full_child_path, sizeof(full_child_path), "%s/child", child_path);

                    execve(NULL, args, envp);

                    perror("execve() failed");
                }
                else if (pid < 0) {
                    perror("fork() failed");
                }
                else {
                    child_counter++;
                    wait(NULL);
                }
                break;
            }
            case '*': 
            {
                if (child_counter >= MAX_CHILD_COUNT) {
                    printf("Reached max amount of child processes\n");
                    break;
                }

                pid_t pid = fork();

                if (pid == 0) {
                    child_path = get_child_path("CHILD_PATH", envp);

                    if (child_path == NULL)
                    {
                        printf("CHILD_PATH environment variable not set\n");
                        exit(EXIT_FAILURE);
                    }

                    char child_name[MAX_FILENAME_LEN];
                    snprintf(child_name, sizeof(child_name), "child_%02d", child_counter);

                    char *args[] = {child_name, argv[1], NULL};

                    execve(child_path, args, envp);

                    perror("execve() failed");
                }
                else if (pid < 0) {
                    perror("fork() failed");
                }
                else {
                    child_counter++;
                    wait(NULL);
                }
                break;
            }
            case '&':
            {
                if (child_counter >= MAX_CHILD_COUNT) {
                    printf("Reached max amount of child processes\n");
                    break;
                }

                pid_t pid = fork();

                if (pid == 0) {
                    child_path = get_child_path("CHILD_PATH", environ);

                    if (child_path == NULL)
                    {
                        printf("CHILD_PATH environment variable not set\n");
                        exit(EXIT_FAILURE);
                    }

                    char child_name[MAX_FILENAME_LEN];
                    snprintf(child_name, sizeof(child_name), "child_%02d", child_counter);

                    char *args[] = {child_name, argv[1], NULL};

                    execve(child_path, args, environ);

                    perror("execve() failed");
                }
                else if (pid < 0) {
                    perror("fork() failed");
                }
                else {
                    child_counter++;
                    wait(NULL);
                }
                break;
            }
            case 'q': 
            {
                printf("Goodbye!\n");
                return EXIT_SUCCESS;
                break;
            }
            default: 
            {
                printf("\nThere is no such command, try again\n");
                break;
            }
        }
    }
    return EXIT_SUCCESS;
}