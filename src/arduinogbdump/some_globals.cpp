#include "misc_types.h"

#include "some_globals.h"

N64_status_t N64_status;
char N64_raw_dump[33]; // 1 received bit per byte

char N64_mem_dump[N64_mem_size+1];

unsigned char N64_mem_managed[N64_byte_size];

char buf[bufsize];
