#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void process_file(FILE* file) {
    char env_var_name[128];
    char *env_var_value;
    while (fscanf(file, "%s", env_var_name) != EOF) {
        env_var_value = getenv(env_var_name);
        if (env_var_value) {
            printf("%s: %s\n", env_var_name, env_var_value);
        }
        else {
            printf("%s: Value was'nt found\n", env_var_name);
            continue;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Argument amount error. Try: %s environment.txt\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening env file");
        return EXIT_FAILURE;
    }


    printf("PROGRAM NAME: %s\n", argv[0]);
    printf("PROGRAM PID: %d\n", getpid());
    printf("PROGRAM PPID: %d\n", getppid());

    process_file(file);
    fclose(file);

    return EXIT_SUCCESS;
}