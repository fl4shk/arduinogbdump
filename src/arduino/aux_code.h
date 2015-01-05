#ifndef aux_code_h
#define aux_code_h

#include "some_globals.h"
#include "pins_arduino.h"


#if ( defined (__AVR_ATmega328P__) || defined (__AVR_ATmega168__) )
	#define PORT_THING default_bitwise_thing
#elif defined (__AVR_ATmega32U4__)
	#define PORT_THING micro_bitwise_thing
#else
	#error This program doesn't work on your Arduino (yet)!
#endif


// This should be used for the Arduino Uno.
static const byte default_bitwise_thing = 0x04;

// This should be used for the Arduino Micro.
static const byte micro_bitwise_thing = 0x02;


// If I knew the correct value for the Arduino Mega, I would have said to
// use this for it.
//static const byte mega_bitwise_thing =



#define N64_PIN 2
#define N64_PIN_DIR DDRD

// these two macros set arduino pin 2 to input or output, which with an
// external 1K pull-up resistor to the 3.3V rail, is like pulling it high or
// low.  These operations translate to 1 op code, which takes 2 cycles
#define N64_HIGH DDRD &= ~PORT_THING
#define N64_LOW DDRD |= PORT_THING
#define N64_QUERY (PIND & PORT_THING)




void print_mem_managed ();
void print_mem_managed2 ();
void write_mem_managed ();

void print_crc_managed ();

void clear_mem_dump ();

void manage_mem_dump ();		// arrange data into bytes 



void N64_stuff ( unsigned char *buff, char length );


void N64_stuff2 ( unsigned char *buff, char length );


void tpak_stuff2 ();


void tpak_stuff ();


void translate_raw_data();



/**
 * This sends the given byte sequence to the controller
 * length must be at least 1
 * Oh, it destroys the buffer passed in as it writes it
 */
void N64_send(unsigned char *buffer, char length);


void N64_get();


void loop2();


word calc_addr_crc ( word address );


unsigned char calc_data_crc( unsigned char *data );


void N64_read_addr ();


bool cmp_buf ( const char* to_cmp, int num_recv );


#endif		// aux_code_h
