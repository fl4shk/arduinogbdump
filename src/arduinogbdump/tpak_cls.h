#ifndef tpak_cls_h
#define tpak_cls_h


#include "some_globals.h"

#include "misc_types.h"

class cart_helper;

// A class for talking to an N64 Transfer Pak
class tpak
{
protected:	// variables
	static const word wcmd_size = 35, rcmd_size = 3;
	u8 command [wcmd_size];
	addr_packet addr_pkt;
	
	
	//char mbc, rom_size, ram_size; int num_rom_banks, num_ram_kb;
	
	// The Transfer Pak's current bank
	char current_bank;
	
public:  // functions
	tpak ();
	~tpak ();
	
	void init ( cart_helper& the_cart_helper );
	
	void enable_tpak ();
	
	void get_access_mode ();
	void set_access_mode ( bool n_mode );
	
	void set_bank ( char n_tpak_bank );
	
	// There is no way to ask the real life Transfer Pak for its current
	// bank, so this class will keep track of it.
	char get_bank () const;
	
	void write ();
	
	// appends address CRC to write_addr
	void write ( u16 write_addr );
	void write ( u16 write_addr, u8* msg );
	
	// Write a single, repeated byte
	void write_byte ( u16 write_addr, u8 data );
	
	
	//// doesn't touch write_addr's CRC stuff
	//void write_nocrc ( u16 write_addr );
	//void write_nocrc ( u16 write_addr, u8 *msg );
	
	
	void read ();
	void read ( u16 read_addr );
	
	//void read_nocrc ( u16 read_addr );
	
};

#endif		// tpak_cls_h
