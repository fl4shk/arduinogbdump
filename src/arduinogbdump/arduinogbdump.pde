#include "misc_types.h"

#include "some_globals.h"
#include "aux_code.h"
#include "tpak_class.h"
#include "cart_helper_class.h"



void setup()
{
	memset( N64_raw_dump, 0, 33 );
	
	Serial.begin(115200);
	
	// 1 ms timeout
	Serial.setTimeout(1);
	
	pinMode( 13, OUTPUT );
	
	// Communication with gamecube controller on this pin
	// Don't remove these lines, we don't want to push +5V to the controller
	digitalWrite( N64_PIN, LOW );  
	pinMode( N64_PIN, INPUT );
	
	
	// Initialize the gamecube controller by sending it a null byte.  This
	// is unnecessary for a standard controller, but is required for the
	// Wavebird.
	unsigned char initialize = 0x00;
	noInterrupts();
	N64_send( &initialize, 1 );
	N64_read_addr();
	
	
	// Stupid routine to wait for the gamecube controller to stop
	// sending its response. We don't care what it is, but we
	// can't start asking for status if it's still responding
	int x;
	for ( x=0; x<64; x++ )
	{
		// make sure the line is idle for 64 iterations, should
		// be plenty.x
		
		if (!N64_QUERY)
		{
			x = 0;
			
			digitalWrite( 13, HIGH );
			delay(200);
			digitalWrite( 13, LOW );
		}
	}
	
	// Query for the gamecube controller's status. We do this
	// to get the 0 point for the control stick.
	//unsigned char command[] = { 0x01 };
	//N64_send( command, 1 );
	// read in data and dump it to N64_raw_dump
	//N64_get();
	interrupts();
	
	
	//tpak_stuff_2();
}


void loop()
{
	tpak_stuff_2();
}

