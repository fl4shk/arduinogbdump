#ifndef cart_helper_enums_h
#define cart_helper_enums_h


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
	// non-MBC2, non-MBC5 RAM sizes
	rs_none,		// 0 kiB of external cart RAM
	rs_2,			// 2 kiB of external cart RAM, not even a full bank
	rs_8,			// 8 kiB of external cart RAM, 1 bank of 8 kiB
	rs_32,			// 32 kiB of external cart RAM, 4 banks of 8 kiB each
	
	// Only MBC5 allows 128 kiB of external cart RAM
	rs_128,			// 128 kiB of external cart RAM, 16 banks of 8 kiB each
	
	
	// MBC2 includes some NON-EXTERNAL cart RAM, i.e. it's in the MBC2 chip
	// itself.  It is weird though, since it's 512x4 bits, where each
	// "byte" is 4 bits.  It shouldn't be surprising that MBC2 wasn't used
	// in that many games though.
	rs_mbc2,
	
};




// Serial Messages between Arduino and Computer
// Types of Serial Message
enum serial_msg_type
{
	sm_print_cart_stuff,
	sm_get_cart_stuff,
	
	sm_reset_tpak,
	
	sm_gb_read_32_bytes,
	sm_gb_write_32_bytes,
	
	
	// Read a variable number of bytes from the cartridge
	sm_gb_read_var_num_bytes,
	
	// Write a variable number of bytes to the cartridge
	sm_gb_write_var_num_bytes,
	
	
};


#endif		// cart_helper_enums_h
