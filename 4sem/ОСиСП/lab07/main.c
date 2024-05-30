#include <ctype.h>
#include <fcntl.h>
#include <math.h>
#include <memory.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

struct record {
  char name[80];
  char address[80];
  uint8_t semester;
};

const char* record_to_str(struct record *record) {
  static char buffer[512];
  sprintf( buffer, "| %s | %s | Semester %d |", record->name, record->address, record->semester);
  return buffer;
}

int fd = -1;

int origin_index = -1;
struct record origin;
struct record target;

int record_count = 0;
struct record *records = NULL;

void map_records() {
  struct stat stat;
  if (fstat(fd, &stat) == -1) {
    perror("Could not get stat of file\n");
    return;
  }
  records = mmap(NULL, stat.st_size, PROT_READ, MAP_SHARED, fd, 0);
  record_count = stat.st_size / sizeof(*records);
}

void map_records_for_change() {
  struct stat stat;
  if (fstat(fd, &stat) == -1) {
    perror("Could not get stat of file\n");
    return;
  }
  records = mmap(NULL, stat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  record_count = stat.st_size / sizeof(*records);
}

void unmap_records() {
  if (records == NULL) return;
  struct stat stat;
  if (fstat(fd, &stat) == -1) {
    perror("Could not get stat of file\n");
  }
  munmap(records, stat.st_size);
  record_count = 0;
  records = NULL;
}

void command_list() {
  map_records();
  for (int i = 0; i < record_count; i++) {
    printf("%d. %s\n", i, record_to_str(&records[i]));
  }
  unmap_records();
}

void command_read(int index) {
  map_records();
  if (!(0 <= index && index < record_count)) {
    printf("Index %d out of range [%d;%d)\n", index, 0, record_count);
    unmap_records();
    return;
  }
  origin_index = index;
  target = origin = records[index];
  unmap_records();
}

void command_update() {
  if (origin_index == -1) {
    printf("Nothing was loaded\n");
    return;
  }

  char buffer[80] = {0};

  printf("[Current: %s] Enter new name: ", target.name);
  fgets(buffer, sizeof(buffer), stdin);
  buffer[strlen(buffer) - 1] = '\0';
  if (strlen(buffer) > 0) strcpy(target.name, buffer);

  printf("[Current: %s] Enter new address: ", target.address);
  fgets(buffer, sizeof(buffer), stdin);
  buffer[strlen(buffer) - 1] = '\0';
  if (strlen(buffer) > 0) strcpy(target.address, buffer);

  printf("[Current: %d] Enter new semester: ", target.semester);
  fgets(buffer, sizeof(buffer), stdin);
  sscanf(buffer, " %hhu", &target.semester);
}

void command_save() {
  if (origin_index == -1) {
    printf("You need use GET before this command\n");
    return;
  }
  struct flock lock;
  lock.l_pid = getpid();
  lock.l_start = origin_index * sizeof(struct record);
  lock.l_type = F_WRLCK;
  lock.l_whence = SEEK_SET;
  lock.l_len = sizeof(struct record);

  fcntl(fd, F_SETLK, &lock);
  lock.l_type = F_UNLCK;
  map_records_for_change();
  if (memcmp(&origin, &records[origin_index], sizeof(origin)) != 0) {
    unmap_records();
    fcntl(fd, F_SETLK, &lock);
    printf("Record was changed in file. Abort saving. Record will be reloaded\n");
    command_read(origin_index);
    return;
  }
  records[origin_index] = target;
  unmap_records();
  fcntl(fd, F_SETLK, &lock);
  origin_index = -1;
}

void handle_command(const char *line) {
  int index;
  if (strcmp(line, "QUIT\n") == 0) {
    exit(EXIT_SUCCESS);
  } else if (strcmp(line, "LST\n") == 0) {
    command_list();
  } else if (strcmp(line, "UPDATE\n") == 0) {
    command_update();
  } else if (strcmp(line, "PUT\n") == 0) {
    command_save();
  } else if (sscanf(line, "GET %d\n", &index) == 1) {
    command_read(index);
  } else {
    printf("Unknown command: %s", line);
  }
}

int main() {
  fd = open("data.bin", O_RDWR, S_IRUSR | S_IWUSR);
  while (!feof(stdin)) {
    char buffer[256] = {0};
    printf("Enter command: ");
    handle_command(fgets(buffer, sizeof(buffer), stdin));
  }
  close(fd);
}
