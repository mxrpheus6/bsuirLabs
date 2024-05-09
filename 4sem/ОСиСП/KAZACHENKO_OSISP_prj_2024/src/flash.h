#ifndef FLASH_H
#define FLASH_H

typedef struct {
    char* part;
    char* mount;
    char* model;
    char* vendor;
    int size_mb;
    int available_size_mb;
} Flash;

Flash* create_flash();
Flash** init_flash_array(int size);
void free_flash(Flash *flash);
void free_flash_array(Flash**flash_array, int size);

int count_flash(const char* path);
void parse_proc_partitions(Flash** flash_array, int size);
void parse_sys_block(Flash** flash_array, int size);
void parse_proc_mounts(Flash** flash_array, int size);

char* readpart_by_id(const char* serial_number);

#endif // FLASH_H