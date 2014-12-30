#ifndef some_globals_h
#define some_globals_h

#include "misc_types.h"

// 8 bytes of data that we get from the controller
extern N64_status_t N64_status;
extern char N64_raw_dump [33]; // 1 received bit per byte

static const word N64_mem_size = 264;
extern char N64_mem_dump [N64_mem_size+1];

static const word N64_byte_size = 33;
extern unsigned char N64_mem_managed [N64_byte_size];

#endif		// some_globals_h
