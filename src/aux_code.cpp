
#include "aux_code.h"
#include "tpak_cls.h"
#include "cart_helper_cls.h"

void print_mem_managed ()
{
	for ( int i=0; i<N64_byte_size-1; ++i )
	{
		Serial.print ( N64_mem_managed [i], HEX );
		Serial.print (" ");
	}
	Serial.println ();
}
void write_mem_managed ()
{
	for ( int i=0; i<N64_byte_size-1; ++i )
	{
		Serial.write (N64_mem_managed [i]);
	}
}

void print_crc_managed ()
{
	Serial.println ( N64_mem_managed [N64_byte_size-1], HEX );
}
void clear_mem_dump ()
{
	memset ( &N64_mem_dump, 0x00, N64_mem_size );
}
void manage_mem_dump ()		// arrange data into bytes 
{
	memset ( N64_mem_managed, 0, 33 );
	for ( int i=0; i<N64_byte_size; ++i )
	{
		for ( int j=0; j<8; ++j )
		{
			// not sure if this is considered "hackish" or not...
			N64_mem_managed [i] += ( ( N64_mem_dump [i*8+j]!=0 )<<( 7-j ) );
		}
	}
}


void N64_stuff ( unsigned char *buff, char length )
{
	noInterrupts ();
	N64_send ( buff, length );
	N64_read_addr ();
	interrupts ();
}

void N64_stuff2 ( unsigned char *buff, char length )
{
	N64_send ( buff, length );
	N64_read_addr ();
}

void tpak_stuff2 ()
{
	//tpak pak0; 
	//
	//clear_mem_dump ();
	//pak0.init ();
	
	for ( int i=0; i<5; ++i )
	{
		Serial.print ("Delay #");
		Serial.print ( i, DEC );
		Serial.println (" before reading from the Transfer Pak.");
		//delay (1000);
		delay (100);
	}
	
	clear_mem_dump ();
	cart_helper hamburger;
	
	//hamburger.print_cart_stuff ();
	//hamburger.rom_only_dump_rom ();
	hamburger.mbc1_dump_rom ();
}

void tpak_stuff ()
{
	//delay (255+150);
	//
	//addr_packet addr_pkt; 
	//
	//const word cmd_size = 36;
	//unsigned char command [cmd_size] = { 0x03, 0x80, 0x01 };
	//
	//
	//// begin tpak init
	//clear_mem_dump ();
	//memset ( &command [3], 0x84, 32 );
	//
	//N64_stuff ( command, cmd_size-1 );
	//
	//manage_mem_dump ();
	//print_mem_managed ();
	//delay (100);
	//
	//
	//clear_mem_dump ();
	//command [0] = 0x02; 
	////command [1] = 0x80; command [2] = 0x01;
	//
	//N64_stuff ( command, 3 );
	//
	//manage_mem_dump ();
	//print_mem_managed ();
	//delay (100);
	//
	//
	//// need to send this again for some reason
	//clear_mem_dump ();
	//command [0] = 0x03;
	//memset ( &command [3], 0x84, 32 );
	//
	//N64_stuff ( command, cmd_size-1 );
	//
	//manage_mem_dump ();
	//print_mem_managed (); 
	//delay (100);
	//// end tpak init
	//
	//
	//// read back init state (should be 0x84)
	//clear_mem_dump ();
	//command [0] = 0x02; 
	////command [1] = 0x80; command [2] = 0x01;
	//
	//N64_stuff ( command, 3 );
	//
	//manage_mem_dump ();
	//print_mem_managed (); 
	//delay (100);
	//
	//
	//// get tpak access mode (0x80 if mode 0, 0x89 if mode 1)
	//clear_mem_dump ();
	//command [0] = 0x02; 
	//
	//addr_pkt.w = calc_addr_crc (0xB000);
	////command [1] = 0x80; command [2] = 0x01;
	//command [1] = addr_pkt.hi; command [2] = addr_pkt.lo;
	//
	//N64_stuff ( command, 3 );
	//
	//manage_mem_dump ();
	//print_mem_managed ();
	//delay (100);
	//
	//
	//// set tpak access mode
	//clear_mem_dump ();
	//command [0] = 0x03;
	//memset ( &command [3], 0xFF, 32 );		// 0xFF for good measure
	//command [1] = addr_pkt.hi; command [2] = addr_pkt.lo;
	//
	//N64_stuff ( command, cmd_size-1 );
	//
	//manage_mem_dump ();
	//print_mem_managed (); 
	//delay (100);
	//
	//
	//// get tpak access mode (0x80 if mode 0, 0x89 if mode 1)
	//clear_mem_dump ();
	//command [0] = 0x02; 
	//
	//addr_pkt.w = calc_addr_crc (0xB000);
	////command [1] = 0x80; command [2] = 0x01;
	//command [1] = addr_pkt.hi; command [2] = addr_pkt.lo;
	//
	//N64_stuff ( command, 3 );
	//
	//manage_mem_dump ();
	//print_mem_managed (); 
	//delay (100);
	//
	//
	//// set current TPak bank
	//clear_mem_dump ();
	//command [0] = 0x03;  // write command
	//memset ( &command [3], 0x00, 32 );
	//
	//addr_pkt.w = calc_addr_crc (0xA000);
	//command [1] = addr_pkt.hi; command [2] = addr_pkt.lo;
	//
	//N64_stuff ( command, cmd_size-1 );
	//
	//manage_mem_dump ();
	//print_mem_managed (); 
	//delay (100);
	//
	//
	//// read address 0xC100 (GB address 0x0100)
	//clear_mem_dump ();
	//command [0] = 0x02;		 // read command
	//
	//addr_pkt.w = calc_addr_crc (0xC040);
	//command [1] = addr_pkt.hi; command [2] = addr_pkt.lo;
	//
	//N64_stuff ( command, 3 );
	//
	//manage_mem_dump ();
	//print_mem_managed (); 
	////Serial.println ( calc_data_crc ((unsigned char *)N64_mem_managed), HEX );
	//delay (100);
	//
	//
	//Serial.println ("Done.");
	
}

void translate_raw_data()
{
	// The get_N64_status function sloppily dumps its data 1 bit per byte
	// into the get_status_extended char array. It's our job to go through
	// that and put each piece neatly into the struct N64_status
	int i;
	memset(&N64_status, 0, sizeof(N64_status));
	// line 1
	// bits: A, B, Z, Start, Dup, Ddown, Dleft, Dright
	for (i=0; i<8; i++) {
		N64_status.data1 |= N64_raw_dump[i] ? (0x80 >> i) : 0;
	}
	// line 2
	// bits: 0, 0, L, R, Cup, Cdown, Cleft, Cright
	for (i=0; i<8; i++) {
		N64_status.data2 |= N64_raw_dump[8+i] ? (0x80 >> i) : 0;
	}
	// line 3
	// bits: joystick x value
	// These are 8 bit values centered at 0x80 (128)
	for (i=0; i<8; i++) {
		N64_status.stick_x |= N64_raw_dump[16+i] ? (0x80 >> i) : 0;
	}
	for (i=0; i<8; i++) {
		N64_status.stick_y |= N64_raw_dump[24+i] ? (0x80 >> i) : 0;
	}
}


/**
 * This sends the given byte sequence to the controller
 * length must be at least 1
 * Oh, it destroys the buffer passed in as it writes it
 */
void N64_send(unsigned char *buffer, char length)
{
	// Send these bytes
	char bits;
	
	bool bit;
	
	// This routine is very carefully timed by examining the assembly
	// output.  Do not change any statements, it could throw the timings
	// off.
	//
	// We get 16 cycles per microsecond, which should be plenty, but we
	// need to be conservative. Most assembly ops take 1 cycle, but a few
	// take 2.
	//
	// I use manually constructed for-loops out of gotos so I have more
	// control over the outputted assembly. I can insert nops where it was
	// impossible with a for loop.
	
	asm volatile (";Starting outer for loop");
outer_loop:
	{
		asm volatile (";Starting inner for loop");
		bits=8;
inner_loop:
		{
			// Starting a bit, set the line low
			asm volatile (";Setting line to low");
			N64_LOW; // 1 op, 2 cycles
			
			asm volatile (";branching");
			if (*buffer >> 7) {
				asm volatile (";Bit is a 1");
				// 1 bit
				// remain low for 1us, then go high for 3us
				// nop block 1
				asm volatile ("nop\nnop\nnop\nnop\nnop\n");
				
				asm volatile (";Setting line to high");
				N64_HIGH;
				
				// nop block 2
				// we'll wait only 2us to sync up with both conditions
				// at the bottom of the if statement
				asm volatile ("nop\nnop\nnop\nnop\nnop\n"  
							  "nop\nnop\nnop\nnop\nnop\n"  
							  "nop\nnop\nnop\nnop\nnop\n"  
							  "nop\nnop\nnop\nnop\nnop\n"  
							  "nop\nnop\nnop\nnop\nnop\n"  
							  "nop\nnop\nnop\nnop\nnop\n"  
							  );
				
			} else {
				asm volatile (";Bit is a 0");
				// 0 bit
				// remain low for 3us, then go high for 1us
				// nop block 3
				asm volatile ("nop\nnop\nnop\nnop\nnop\n"  
							  "nop\nnop\nnop\nnop\nnop\n"  
							  "nop\nnop\nnop\nnop\nnop\n"  
							  "nop\nnop\nnop\nnop\nnop\n"  
							  "nop\nnop\nnop\nnop\nnop\n"  
							  "nop\nnop\nnop\nnop\nnop\n"  
							  "nop\nnop\nnop\nnop\nnop\n"  
							  "nop\n");
				
				asm volatile (";Setting line to high");
				N64_HIGH;
				
				// wait for 1us
				asm volatile ("; end of conditional branch, need to wait 1us more before next bit");
				
			}
			// end of the if, the line is high and needs to remain
			// high for exactly 16 more cycles, regardless of the previous
			// branch path
			
			asm volatile (";finishing inner loop body");
			--bits;
			if (bits != 0) {
				// nop block 4
				// this block is why a for loop was impossible
				asm volatile ("nop\nnop\nnop\nnop\nnop\n"  
							  "nop\nnop\nnop\nnop\n");
				// rotate bits
				asm volatile (";rotating out bits");
				*buffer <<= 1;
				
				goto inner_loop;
			} // fall out of inner loop
		}
		asm volatile (";continuing outer loop");
		// In this case: the inner loop exits and the outer loop iterates,
		// there are /exactly/ 16 cycles taken up by the necessary operations.
		// So no nops are needed here (that was lucky!)
		--length;
		if (length != 0) {
			++buffer;
			goto outer_loop;
		} // fall out of outer loop
	}
	
	// send a single stop (1) bit
	// nop block 5
	asm volatile ("nop\nnop\nnop\nnop\n");
	N64_LOW;
	// wait 1 us, 16 cycles, then raise the line 
	// 16-2=14
	// nop block 6
	asm volatile ("nop\nnop\nnop\nnop\nnop\n"
				  "nop\nnop\nnop\nnop\nnop\n"  
				  "nop\nnop\nnop\nnop\n");
	N64_HIGH;
	
}

void N64_get()
{
	// listen for the expected 8 bytes of data back from the controller and
	// blast it out to the N64_raw_dump array, one bit per byte for extra speed.
	// Afterwards, call translate_raw_data() to interpret the raw data and pack
	// it into the N64_status struct.
	asm volatile (";Starting to listen");
	unsigned char timeout;
	char bitcount = 32;
	char *bitbin = N64_raw_dump;
	
	// Again, using gotos here to make the assembly more predictable and
	// optimization easier (please don't kill me)
read_loop:
	timeout = 0x3f;
	// wait for line to go low
	while (N64_QUERY) {
		if (!--timeout)
			return;
	}
	// wait approx 2us and poll the line
	asm volatile (
				  "nop\nnop\nnop\nnop\nnop\n"  
				  "nop\nnop\nnop\nnop\nnop\n"  
				  "nop\nnop\nnop\nnop\nnop\n"  
				  "nop\nnop\nnop\nnop\nnop\n"  
				  "nop\nnop\nnop\nnop\nnop\n"  
				  "nop\nnop\nnop\nnop\nnop\n"  
			);
	*bitbin = N64_QUERY;
	++bitbin;
	--bitcount;
	if (bitcount == 0)
		return;
	
	// wait for line to go high again
	// it may already be high, so this should just drop through
	timeout = 0x3f;
	while (!N64_QUERY) {
		if (!--timeout)
			return;
	}
	goto read_loop;
	
}

void loop2()
{
	// Command to send to the gamecube
	// The last bit is rumble, flip it to rumble
	// yes this does need to be inside the loop, the
	// array gets mutilated when it goes through N64_send
	unsigned char command[] = {0x01};
	
	// don't want interrupts getting in the way
	noInterrupts();
	// send those 3 bytes
	//N64_send(command, 1);
	// read in data and dump it to N64_raw_dump
	//N64_get();
	// end of time sensitive code
	interrupts();
	
	delay(25);
	
}


word calc_addr_crc ( word address )
{
	/* CRC table */
	uint16_t xor_table[16] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x15, 0x1F, 0x0B, 0x16, 0x19, 0x07, 0x0E, 0x1C, 0x0D, 0x1A, 0x01 };
	uint16_t crc = 0;
	
	/* Make sure we have a valid address */
	address &= ~0x1F;
	
	/* Go through each bit in the address, and if set, xor the right value into the output */
	for( int i = 15; i >= 5; i-- )
	{
		/* Is this bit set? */
		if( ((address >> i) & 0x1) )
		{
		   crc ^= xor_table[i];
		}
	}
	
	/* Just in case */
	crc &= 0x1F;
	
	/* Create a new address with the CRC appended */
	return address | crc;
}

unsigned char calc_data_crc( unsigned char *data )
{
	unsigned char ret = 0;
	
	for( int i = 0; i <= 32; i++ )
	{
		for( int j = 7; j >= 0; j-- )
		{
			int tmp = 0;
			
			if( ret & 0x80 )
			{
				tmp = 0x85;
			}
			
			ret <<= 1;
			
			if( i < 32 )
			{
				if( data[i] & (0x01 << j) )
				{
					ret |= 0x1;
				}
			}
			
			ret ^= tmp;
		}
	}
	
	return ret;
}

void N64_read_addr ()
{
	// listen for the expected 8 bytes of data back from the controller and
	// blast it out to the N64_raw_dump array, one bit per byte for extra speed.
	// Afterwards, call translate_raw_data() to interpret the raw data and pack
	// it into the N64_status struct.
	asm volatile (";Starting to listen");
	unsigned char timeout;
	word bitcount = N64_mem_size;
	char *bitbin = N64_mem_dump;
	
	// Again, using gotos here to make the assembly more predictable and
	// optimization easier (please don't kill me)
read_loop:
	timeout = 0x3f;
	// wait for line to go low
	while (N64_QUERY) {
		if (!--timeout)
			return;
	}
	// wait approx 2us and poll the line
	asm volatile (
				  "nop\nnop\nnop\nnop\nnop\n"  
				  "nop\nnop\nnop\nnop\nnop\n"  
				  "nop\nnop\nnop\nnop\nnop\n"  
				  "nop\nnop\nnop\nnop\nnop\n"  
				  "nop\nnop\nnop\nnop\nnop\n"  
				  "nop\nnop\nnop\nnop\nnop\n"  
			);
	*bitbin = N64_QUERY;
	++bitbin;
	--bitcount;
	if (bitcount == 0)
		return;
	
	// wait for line to go high again
	// it may already be high, so this should just drop through
	timeout = 0x3f;
	while (!N64_QUERY) {
		if (!--timeout)
			return;
	}
	goto read_loop;
	
}

