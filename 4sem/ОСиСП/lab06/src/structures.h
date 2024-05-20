#include <stdint.h>

typedef struct {
    double time_mark;
    uint64_t recno;
} index_record;

typedef struct {
    uint64_t records;
    index_record * idx;
} index_hdr_s;