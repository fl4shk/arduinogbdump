#ifndef cart_helper_class_h
#define cart_helper_class_h

#include "misc_types.h"		// Needed for stdint.h
#include "tpak_class.h"

#include "cart_helper_enums.h"




class cart_helper
{
//protected:		// variables
public:			// variables
	
	// Here are the --RELEVANT-- contents of the cartridge header
	uint8_t raw_cart_type;
	uint8_t raw_rom_size;
	uint8_t raw_ram_size;
	// End of --RELEVANT-- contents of the cartridge header
	
	
	// The type of MBC that the cartridge has (if any)
	mbc_type cart_mbc_type;
	
	// The number of 16 kB ROM banks
	uint16_t rom_size;
	
	// The amount of external cart RAM (if any)
	ram_size_type ram_size;
	
	// The Transfer Pak to talk to (couldn't think of a better identifier)
	tpak my_tpak;
	
	
public:		// functions
	cart_helper();
	~cart_helper();
	
	void set_cart_stuff();
	void print_cart_stuff();
	
	void set_raw_data( uint8_t s_raw_cart_type, uint8_t s_raw_rom_size,
		uint8_t s_raw_ram_size );
	void print_raw_data();
	
	void interpret_raw_data();
	
	void dump_rom();
	//void dump_ram();
	//void restore_ram();
	
	
//protected:		// functions
	
	
	// Misc. Helper Functions
	
	uint8_t calc_tpak_bank( uint16_t gb_addr );
	uint16_t calc_tpak_addr( uint16_t gb_addr );
	
	void calc_tpak_bank_and_tpak_addr( uint16_t gb_addr, 
		uint8_t& tpak_bank, uint16_t& tpak_addr );
	
	// Read from GB address(auto tpak bank stuffs)
	void read_with_gb_addr( uint16_t gb_addr );
	
	// Write to GB address(auto tpak bank stuffs)
	void write_byte_with_gb_addr( uint16_t gb_addr, uint8_t data );
	
	
	// End of Misc. Helper Functions
	
	
	
	// Dumping/Restoring Functions
	
	void rom_only_dump_rom();
	void mbc1_dump_rom();
	void mbc2_dump_rom();
	void mbc3_dump_rom();
	void mbc5_dump_rom();
	
	
	void mbc1_dump_ram();
	//void mbc2_dump_ram();
	//void mbc3_dump_ram();
	void mbc5_dump_ram();
	
	
	//void mbc1_restore_ram();
	//void mbc2_restore_ram();
	//void mbc3_restore_ram();
	//void mbc5_restore_ram();
	
	// End of Dumping/Restoring Functions
	
	
	
	// MBC1 Functions
	
	void mbc1_set_rom_bank_lo( uint8_t n_rom_bank_lo );
	void mbc1_set_rom_bank_hi( uint8_t n_rom_bank_hi );
	void mbc1_set_rom_bank( uint8_t n_rom_bank_full );
	
	void mbc1_enable_ram();
	void mbc1_disable_ram();
	
	
	// End of MBC1 Functions
	
	
	
	// MBC5 Functions
	
	void mbc5_set_rom_bank( uint8_t n_rom_bank, uint8_t hbit );
	void mbc5_set_ram_bank( uint8_t n_ram_bank );
	void mbc5_enable_ram();
	void mbc5_disable_ram();
	
	// End of MBC5 Functions
	
	int interpret_serial_message();
	int interpret_serial_message2( int num_recv );
	
};


#endif		// cart_helper_class_h
