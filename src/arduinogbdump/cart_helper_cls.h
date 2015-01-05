#ifndef cart_helper_cls_h
#define cart_helper_cls_h

#include "misc_types.h"		// Needed for u8, s8, u16, and s16
#include "tpak_cls.h"

#include "cart_helper_enums.h"




class cart_helper
{
//protected:		// variables
public:			// variables
	
	// Here are the --RELEVANT-- contents of the cartridge header
	u8 raw_cart_type;
	u8 raw_rom_size;
	u8 raw_ram_size;
	// End of --RELEVANT-- contents of the cartridge header
	
	
	// The type of MBC that the cartridge has (if any)
	mbc_type cart_mbc_type;
	
	// The number of 16 kB ROM banks
	u16 rom_size;
	
	// The amount of external cart RAM (if any)
	ram_size_type ram_size;
	
	// The Transfer Pak to talk to (couldn't think of a better identifier)
	tpak my_tpak;
	
	
public:		// functions
	cart_helper ();
	~cart_helper ();
	
	void set_cart_stuff ();
	void print_cart_stuff ();
	
	void set_raw_data ( u8 s_raw_cart_type, u8 s_raw_rom_size,
		u8 s_raw_ram_size );
	void print_raw_data ();
	
	void interpret_raw_data ();
	
	void dump_rom ();
	//void dump_ram ();
	//void restore_ram ();
	
	
//protected:		// functions
	
	
	// Misc. Helper Functions
	
	u8 calc_tpak_bank ( u16 gb_addr );
	u16 calc_tpak_addr ( u16 gb_addr );
	
	void calc_tpak_bank_and_tpak_addr ( u16 gb_addr, u8& tpak_bank, 
		u16& tpak_addr );
	
	// Read from GB address (auto tpak bank stuffs)
	void read_with_gb_addr ( u16 gb_addr );
	
	// Write to GB address (auto tpak bank stuffs)
	void write_byte_with_gb_addr ( u16 gb_addr, u8 data );
	
	
	// End of Misc. Helper Functions
	
	
	
	// Dumping/Restoring Functions
	
	void rom_only_dump_rom ();
	void mbc1_dump_rom ();
	void mbc2_dump_rom ();
	void mbc3_dump_rom ();
	void mbc5_dump_rom ();
	
	
	void mbc1_dump_ram ();
	//void mbc2_dump_ram ();
	//void mbc3_dump_ram ();
	void mbc5_dump_ram ();
	
	
	//void mbc1_restore_ram ();
	//void mbc2_restore_ram ();
	//void mbc3_restore_ram ();
	//void mbc5_restore_ram ();
	
	// End of Dumping/Restoring Functions
	
	
	
	// MBC1 Functions
	
	void mbc1_set_rom_bank_lo ( u8 n_rom_bank_lo );
	void mbc1_set_rom_bank_hi ( u8 n_rom_bank_hi );
	void mbc1_set_rom_bank ( u8 n_rom_bank_full );
	
	void mbc1_enable_ram ();
	void mbc1_disable_ram ();
	
	
	// End of MBC1 Functions
	
	
	
	// MBC5 Functions
	
	void mbc5_set_rom_bank ( u8 n_rom_bank, u8 hbit );
	void mbc5_set_ram_bank ( u8 n_ram_bank );
	void mbc5_enable_ram ();
	void mbc5_disable_ram ();
	
	// End of MBC5 Functions
	
	int interpret_serial_message ();
	int interpret_serial_message2 ( int num_recv );
	
};


#endif		// cart_helper_cls_h