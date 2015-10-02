#ifndef misc_types_h
#define misc_types_h

#include "Arduino.h"

#include <stdint.h>
//typedef unsigned char u8; typedef signed char s8;
//typedef unsigned int u16; typedef signed int s16;
//typedef unsigned int uint;

//typedef uint8_t u8; typedef int8_t s8;
//typedef uint16_t u16; typedef int16_t s16;
typedef unsigned int uint;


// 8 bytes of data that we get from the controller
struct N64_status_t {
	// bits: 0, 0, 0, start, y, x, b, a
	unsigned char data1;
	// bits: 1, L, R, Z, Dup, Ddown, Dright, Dleft
	unsigned char data2;
	char stick_x;
	char stick_y;
};

union addr_packet
{
	word w;
	struct
	{
		byte lo, hi;
	};
};


#endif		// misc_types_h
