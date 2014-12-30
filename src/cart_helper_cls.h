#ifndef cart_helper_cls_h
#define cart_helper_cls_h

#include "misc_types.h"		// Needed for u8, s8, u16, and s16
#include "tpak_cls.h"

// Only supported MBC types are listed here.
// There's no need to specify whether the cart has a battery or not, so
// that information is left out of this enum.
enum mbc_type
{
	// No MBC at all
	rom_only,				// 32 kiB of ROM, no MBC
	
	// MBC1
	mbc1,					// MBC1 only, no RAM
	mbc1_ram,				// MBC1 and RAM
	
	// MBC2
	mbc2,					// MBC2 (includes built-in RAM)
	
	// MBC3
	mbc3,					// MBC3 only, no RTC, no RAM
	mbc3_timer,				// MBC3 and RTC, but no RAM
	mbc3_timer_ram,			// MBC3, RTC, and RAM
	mbc3_ram,				// MBC3 and RAM, but no RTC
	
	// MBC5
	mbc5,					// MBC5 only, no RAM
	mbc5_ram,				// MBC5 and RAM
	
	// Something else
	unknown_mbc_type		// Debug, etc.
};

enum ram_size_type
{
	rs_none,		// 0 kiB of external cart RAM
	rs_2,			// 2 kiB of external cart RAM, not even a full bank
	rs_8,			// 8 kiB of external cart RAM, one bank of 8 kiB
	rs_32,			// 32 kiB of external cart RAM (4 banks of 8 kiB each)
	
	// MBC2 includes some non-external cart RAM, i.e. it's in the MBC2 chip
	// itself.  It is weird though, since it's 512x4 bits.
	rs_mbc2
};


class cart_helper
{
protected:		// variables
	
	// Here are the --RELEVANT-- contents of the cartridge header
	u8 raw_cart_type;
	u8 raw_rom_size;
	u8 raw_ram_size;
	// End of --RELEVANT-- contents of the cartridge header
	
	
	// The type of MBC that the cartridge has (if any)
	mbc_type cart_mbc_type;
	
	// The number of 16 kB ROM banks
	u8 rom_size;
	
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
	
	void interpret_raw_data ();
	
	void dump_rom ();
	//void dump_ram ();
	//void restore_ram ();
	
	
//protected:		// functions
	
	
	// Misc. Helper Functions
	
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
	
	
	//void mbc1_dump_ram ();
	//void mbc2_dump_ram ();
	//void mbc3_dump_ram ();
	//void mbc5_dump_ram ();
	//
	//
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
	
	
	// End of MBC1 functions
	
	
	
};


#endif		// cart_helper_cls_h
