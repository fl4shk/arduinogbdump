#ifndef tpak_class_h
#define tpak_class_h


#include "some_globals.h"

#include "misc_types.h"

class cart_helper;

// A class for talking to an N64 Transfer Pak
class tpak
{
protected:	// variables
	static const word wcmd_size = 35, rcmd_size = 3;
	uint8_t command[wcmd_size];
	addr_packet addr_pkt;
	
	
	//char mbc, rom_size, ram_size; int num_rom_banks, num_ram_kb;
	
	// The Transfer Pak's current bank
	char current_bank;
	
public:  // functions
	tpak();
	~tpak();
	
	void init( cart_helper& the_cart_helper );
	
	void enable_tpak();
	
	void get_access_mode();
	void set_access_mode( bool n_mode );
	
	void set_bank( char n_tpak_bank );
	
	// There is no way to ask the real life Transfer Pak for its current
	// bank, so this class will keep track of it.
	char get_bank() const;
	
	void write();
	
	// appends address CRC to write_addr
	void write( uint16_t write_addr );
	void write( uint16_t write_addr, uint8_t* msg );
	
	// Write a single, repeated byte
	void write_byte( uint16_t write_addr, uint8_t data );
	
	
	//// doesn't touch write_addr's CRC stuff
	//void write_nocrc( uint16_t write_addr );
	//void write_nocrc( uint16_t write_addr, uint8_t *msg );
	
	
	void read();
	void read( uint16_t read_addr );
	
	//void read_nocrc( uint16_t read_addr );
	
};

#endif		// tpak_class_h
