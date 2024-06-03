#define _POSIX_C_SOURCE
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

#define BUFFER_SIZE 2048

int Socket(int domain, int type, int protocol) {
    int res = socket(domain, type, protocol);
    if (res == -1) {
        perror("Error opening socket");
        exit(EXIT_FAILURE);
    }
    return res;
}

int Bind(int fd, const struct sockaddr* addr, socklen_t len) {
    int res = bind(fd, addr, len);
    if (res == -1) {
        perror("Error binding");
        exit(EXIT_FAILURE);
    }
    return res;
}

int Listen(int fd, int n) {
    int res = listen(fd, n);
    if (res == -1) {
        perror("listen error");
        exit(EXIT_FAILURE);
    }
    return res;
}

int Accept(int fd, struct sockaddr* addr, socklen_t* addr_len) {
    int res = accept(fd, addr, addr_len);
    if (res == -1) {
        perror("accept error");
        exit(EXIT_FAILURE);
    }
    return res;
}

void get_current_time(char *buffer, size_t len) {
    struct timespec ts;
    struct tm *tm_info;
    clock_gettime(CLOCK_REALTIME, &ts);
    tm_info = localtime(&ts.tv_sec);
    strftime(buffer, len, "%Y.%m.%d-%H:%M:%S", tm_info);
    snprintf(buffer + strlen(buffer), len - strlen(buffer), ".%03ld", ts.tv_nsec / 1000000);
}

void handle_echo_command(int client_socket, const char* buffer) {
    char response[BUFFER_SIZE];
    char timestamp[100];
    get_current_time(timestamp, sizeof(timestamp));
    snprintf(response, sizeof(response), "%s %s", timestamp, buffer + 5);
    write(client_socket, response, strlen(response));
}

void handle_quit_command(int client_socket) {
    char response[BUFFER_SIZE];
    char timestamp[100];
    get_current_time(timestamp, sizeof(timestamp));
    snprintf(response, sizeof(response), "%s BYE", timestamp);
    write(client_socket, response, strlen(response));
    close(client_socket);
}

void handle_info_command(int client_socket) {
    char response[BUFFER_SIZE];
    char timestamp[100];
    get_current_time(timestamp, sizeof(timestamp));
    snprintf(response, sizeof(response), "%s Вас приветствует учебный сервер 'Kazachenko'", timestamp);
    write(client_socket, response, strlen(response));
}

void handle_cd_command(int client_socket, char *current_dir, const char* buffer, const char* root_dir) {
    char response[BUFFER_SIZE];
    char timestamp[100];
    get_current_time(timestamp, sizeof(timestamp));
    char new_dir[BUFFER_SIZE];

    snprintf(new_dir, sizeof(new_dir), "%s/%s", current_dir, buffer + 3);
    if (new_dir[strlen(new_dir) - 1] == '\n') {
        new_dir[strlen(new_dir) - 1] = '\0';
    }

    if (strncmp(buffer + 3, "..", 2) == 0) {
        if (strcmp(current_dir, root_dir) == 0) {
            snprintf(response, sizeof(response), "%s Error: access denied", timestamp);
        } else {
            if (chdir("..") == 0) {
                getcwd(current_dir, BUFFER_SIZE);
                if (strncmp(current_dir, root_dir, strlen(root_dir)) != 0) {
                    chdir(root_dir);
                    getcwd(current_dir, BUFFER_SIZE);
                    snprintf(response, BUFFER_SIZE, "%s Error: access denied", timestamp);
                } else {
                    snprintf(response, sizeof(response), "%s %s>", timestamp, current_dir);
                }
            } else {
                snprintf(response, sizeof(response), "%s Error: cannot change directory", timestamp);
            }
        }
    } else {
        if (chdir(new_dir) == 0) {
            getcwd(current_dir, BUFFER_SIZE);
            if (strncmp(current_dir, root_dir, strlen(root_dir)) != 0) {
                chdir(root_dir);
                getcwd(current_dir, sizeof(current_dir));
                snprintf(response, sizeof(response), "%s Error: access denied", timestamp);
            } else {
                snprintf(response, sizeof(response), "%s <%s>", timestamp, new_dir);
            }
        } else {
            snprintf(response, sizeof(response), "%s", new_dir);
        }
    }
    write(client_socket, response, strlen(response));
}

void handle_list_command(int client_socket, char *current_dir) {
    char response[BUFFER_SIZE];
    char timestamp[100];
    get_current_time(timestamp, sizeof(timestamp));
    DIR *dir;
    struct dirent *entry;
    dir = opendir(current_dir);
    if (dir == NULL) {
        snprintf(response, sizeof(response), "%s Error: cannot list directory", timestamp);
    } else {
        snprintf(response, sizeof(response), "%s\n", timestamp);
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_DIR) {
                strncat(response, entry->d_name, sizeof(response) - strlen(response) - 1);
                strncat(response, "/", sizeof(response) - strlen(response) - 1);
            } else if (entry->d_type == DT_REG) {
                strncat(response, entry->d_name, sizeof(response) - strlen(response) - 1);
            }
            strncat(response, "\n", sizeof(response) - strlen(response) - 1);
        }
        closedir(dir);
    }
    write(client_socket, response, strlen(response) - 1);
}

void handle_unknown_command(int client_socket) {
    char response[BUFFER_SIZE];
    char timestamp[100];
    get_current_time(timestamp, sizeof(timestamp));
    snprintf(response, sizeof(response), "%s Unknown command", timestamp);
    write(client_socket, response, strlen(response));
}

void *handle_client(void *arg) {
    char *root_dir = ((char **)arg)[0];
    int client_socket = *(int *)((char **)arg)[1];
    free(arg);
    
    char buffer[BUFFER_SIZE];
    char current_dir[BUFFER_SIZE];
    strcpy(current_dir, root_dir);

    while (1) {
        bzero(buffer, BUFFER_SIZE);
        ssize_t nread = read(client_socket, buffer, BUFFER_SIZE - 1);
        if (nread <= 0) {
            if (nread == 0) {
                printf("Client disconnected.\n");
            } else {
                perror("read failed");
            }
            close(client_socket);
            return NULL;
        }

        if (strncmp(buffer, "ECHO ", 5) == 0) {
            handle_echo_command(client_socket, buffer);
        } else if (strncmp(buffer, "QUIT", 4) == 0) {
            handle_quit_command(client_socket);
            return NULL;
        } else if (strncmp(buffer, "INFO", 4) == 0) {
            handle_info_command(client_socket);
        } else if (strncmp(buffer, "CD ", 3) == 0) {
            handle_cd_command(client_socket, current_dir, buffer, root_dir);
        } else if (strncmp(buffer, "LIST", 4) == 0) {
            handle_list_command(client_socket, current_dir);
        } else {
            handle_unknown_command(client_socket);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <port> <root_directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);
    char *root_dir = realpath(argv[2], NULL);
    if (root_dir == NULL) {
        perror("Invalid root directory");
        exit(EXIT_FAILURE);
    }

    int serverfd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    Bind(serverfd, (struct sockaddr*)&addr, sizeof(addr));
    Listen(serverfd, 5);

    printf("Server is ready. Root directory: %s\n", root_dir);

    while (1) {
        socklen_t addrlen = sizeof(addr);
        int clientfd = Accept(serverfd, (struct sockaddr*)&addr, &addrlen);

        pthread_t thread_id;
        int *new_sock = malloc(sizeof(int));
        *new_sock = clientfd;

        char **args = malloc(2 * sizeof(char *));
        args[0] = root_dir;
        args[1] = (char *)new_sock;

        if (pthread_create(&thread_id, NULL, handle_client, (void *)args) < 0) {
            perror("pthread_create");
            free(new_sock);
            free(args);
            continue;
        }

        pthread_detach(thread_id);
    }

    close(serverfd);
    free(root_dir);
    return 0;
}
