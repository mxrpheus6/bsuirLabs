#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "structures.h"

int main(int argc, char* argv[]) {
    if (argc > 1) {
        srand(time(NULL));
        index_hdr_s header;
        // Получение размера файлы
        header.records = atoi(argv[1]);                                                    
        if (header.records % 256 != 0) {
            printf("Wrong size, it should be cratniy 256.\n");
            exit(0);
        }
        // Выделение места
        header.idx = (index_record *)malloc(header.records * sizeof(index_record));  
        // Генерация структур
        for (uint64_t i = 0; i < header.records; i++) {
            header.idx[i].recno = i + 1;                                              
            header.idx[i].time_mark = 15020 + rand() % (60378 - 15020 + 1);
            header.idx[i].time_mark +=
                    0.5 * ((rand() % 24) * 60 * 60 + (rand() % 60) * 60 + rand() % 60) / (12 * 60 * 60);
        }

        FILE *f = fopen(argv[2], "wb");
        if (f == NULL)
            printf("Error while creating file.\n");
        else {
            // Запись в файл
            fwrite(&header.records, sizeof(header.records), 1, f);
            fwrite(header.idx, sizeof(index_record), header.records, f);              
        }
        fclose(f);
        free(header.idx);
    } else
        printf("Put parameters.\n");
    return 0;
}