
#include "aux_code.h"
#include "cart_helper_cls.h"




cart_helper::cart_helper ()
{
	my_tpak.init (*this);
}

cart_helper::~cart_helper ()
{
}

void cart_helper::set_cart_stuff ()
{
	clear_mem_dump ();
	my_tpak.read (0xC140);
	manage_mem_dump (); //print_mem_managed ();
	delay (100);
	
	
	set_raw_data ( N64_mem_managed [7], N64_mem_managed [8], 
		N64_mem_managed [9] );
	interpret_raw_data ();
	
	//mbc = N64_mem_managed [7];
	//rom_size = N64_mem_managed [8];
	//ram_size = N64_mem_managed [9];
	//set_num_rom_banks ();
	//set_num_ram_kb ();
	
	////print_cart_stuff ();
}

void cart_helper::set_raw_data ( u8 s_raw_cart_type, u8 s_raw_rom_size,
	u8 s_raw_ram_size )
{
	raw_cart_type = s_raw_cart_type;
	//Serial.println ( s_raw_cart_type, HEX );
	
	raw_rom_size = s_raw_rom_size;
	//Serial.println ( s_raw_rom_size, HEX );
	
	raw_ram_size = s_raw_ram_size;
	//Serial.println ( s_raw_ram_size, HEX );
	
	
}

void cart_helper::interpret_raw_data ()
{
	// Set the value of the MBC 
	switch (raw_cart_type)
	{
		// No MBC
		case 0x00:
			cart_mbc_type = rom_only;
			break;
		
		// MBC1
		case 0x01:
			cart_mbc_type = mbc1;
			break;
		case 0x02:
		case 0x03:
			cart_mbc_type = mbc1_ram;
			break;
		
		// MBC2
		case 0x05:
		case 0x06:
			cart_mbc_type = mbc2;
			break;
		
		// MBC3
		case 0x0f:
			cart_mbc_type = mbc3_timer;
			break;
		case 0x10:
			cart_mbc_type = mbc3_timer_ram;
			break;
		case 0x11:
			cart_mbc_type = mbc3;
			break;
		case 0x12:
		case 0x13:
			cart_mbc_type = mbc3_ram;
			break;
		
		// MBC5
		case 0x19:
			cart_mbc_type = mbc5;
			break;
		case 0x1a:
		case 0x1b:
			cart_mbc_type = mbc5_ram;
			break;
		case 0x1c:		// Technically includes rumble
			cart_mbc_type = mbc5;
			break;
		case 0x1d:		// Technically includes rumble
		case 0x1e:		// Technically includes rumble
			cart_mbc_type = mbc5_ram;
			break;
		default:
			cart_mbc_type = unknown_mbc_type;
			break;
	}
	
	
	// Set the number of ROM banks
	// You know what, I could probably be doing this instead of the switch
	// statement:  rom_size = 2 << raw_rom_size
	switch ( raw_rom_size & 0x07 )
	{
		case 0x00:
			rom_size = 2;		// No ROM banking
			break;
		case 0x01:
			rom_size = 4;
			break;
		case 0x02:
			rom_size = 8;
			break;
		case 0x03:
			rom_size = 16;
			break;
		case 0x04:
			rom_size = 32;
			break;
		case 0x05:
			rom_size = 64;		// Only 63 banks used by MBC1
			break;
		case 0x06:
			rom_size = 128;		// Only 125 banks used by MBC1
			break;
		case 0x07:
			rom_size = 256;
			break;
	}
	
	// Set the size of RAM
	if ( cart_mbc_type != mbc2 )
	{
		switch ( raw_ram_size & 0x03 )
		{
			// No external cart RAM
			case 0x00:
				ram_size = rs_none;
				break;
			
			// 2 kiB of external cart RAM
			case 0x01:
				ram_size = rs_2;
				break;
			
			// 8 kiB of external cart RAM
			case 0x02:
				ram_size = rs_8;
				break;
			
			// 32 kiB (4 banks of 8 kiB each) of external cart RAM
			case 0x03:
				Serial.println ("Setting 32 kiB external RAM");
				ram_size = rs_32;
				break;
		}
	}
	else
	{
		// MBC2 has its own built-in RAM that is rather odd in that it
		// stores 512 "bytes" that are 4 bits each.
		// Addressing for the MBC2's built-in RAM is the same as it would
		// be if the "bytes" were 8 bits each instead of 4 bits each.
		ram_size = rs_mbc2;
	}
}

void cart_helper::print_cart_stuff ()
{
	switch (cart_mbc_type)
	{
		// No MBC at all
		case rom_only:
			Serial.println ("MBC type:  None");
			break;
		
		// MBC1
		case mbc1:
		case mbc1_ram:
			Serial.println ("MBC type:  MBC1");
			break;
		
		// MBC2
		case mbc2:
			Serial.println ("MBC type:  MBC2");
			break;
		
		// MBC3
		case mbc3:
		case mbc3_timer:
		case mbc3_timer_ram:
		case mbc3_ram:
			Serial.println ("MBC type:  MBC3");
			break;
		
		// MBC5
		case mbc5:
		case mbc5_ram:
			Serial.println ("MBC type:  MBC5");
			break;
		
		// Something else
		case unknown_mbc_type:
			Serial.println ("Unknown MBC type.");
			break;
	}
	
	Serial.print ("This cartridge has ");
	Serial.print ( rom_size, DEC );
	Serial.println (" ROM banks.");
	
	switch (ram_size)
	{
		case rs_none:
			Serial.println ("This cartridge has no external RAM.");
			break;
		
		case rs_2:
			Serial.println ("This cartridge has 2 kiB of external RAM.");
			break;
		
		case rs_8:
			Serial.println ("This cartridge has 8 kiB of external RAM.");
			break;
		
		case rs_32:
			Serial.println ("This cartridge has 32 kiB of external RAM.");
			break;
		
		case rs_mbc2:
			Serial.println ("This cartridge has no external RAM, but it"
				"does have an MBC2.  MBC2's have built-in RAM.");
			break;
		
	}
} 
void cart_helper::read_with_gb_addr ( u16 gb_addr )
{
	if ( ( gb_addr >= 0x0000 ) && ( gb_addr < 0x4000 ) )
	{
		my_tpak.set_bank (0x00);
		my_tpak.read ( gb_addr + 0xc000 );
	}
	else if ( ( gb_addr >= 0x4000 ) && ( gb_addr < 0x8000 ) )
	{
		my_tpak.set_bank (0x01);
		my_tpak.read ( gb_addr + 0x8000 );
	}
	else if ( ( gb_addr >= 0x8000 ) && ( gb_addr < 0xc000 ) )
	{
		my_tpak.set_bank (0x02);
		my_tpak.read ( gb_addr + 0x4000 );
	}
	else		// This SHOULDN'T be used
	{
		my_tpak.set_bank (0x03);
		my_tpak.read (gb_addr);
	}
}

void cart_helper::write_byte_with_gb_addr ( u16 gb_addr, u8 data )
{
	
	if ( ( gb_addr >= 0x0000 ) && ( gb_addr < 0x4000 ) )
	{
		my_tpak.set_bank (0x00);
		my_tpak.write_byte ( gb_addr + 0xc000, data );
	}
	else if ( ( gb_addr >= 0x4000 ) && ( gb_addr < 0x8000 ) )
	{
		my_tpak.set_bank (0x01);
		my_tpak.write_byte ( gb_addr + 0x8000, data );
	}
	else if ( ( gb_addr >= 0x8000 ) && ( gb_addr < 0xc000 ) )
	{
		my_tpak.set_bank (0x02);
		my_tpak.write_byte ( gb_addr + 0x4000, data );
	}
	else		// This SHOULDN'T be used
	{
		my_tpak.set_bank (0x03);
		my_tpak.write_byte ( gb_addr, data );
	}
	
}


void cart_helper::dump_rom ()
{
	switch (cart_mbc_type)
	{
		case rom_only:
			rom_only_dump_rom ();
			break;
		
		case mbc1:
		case mbc1_ram:
			mbc1_dump_rom ();
			break;
		
		default:
			break;
	}
}




// Dump a ROM from a cartridge with no MBC (or a very small part of the ones
// that DO have MBCs)
void cart_helper::rom_only_dump_rom ()
{
	// Work with GB addresses 0x0000-0x3fff
	my_tpak.set_bank (0x00);
	
	for ( long j=0xc000; j<0x10000; j+=0x20 )
	{
		clear_mem_dump ();
		my_tpak.read (j);
		manage_mem_dump ();
		write_mem_managed ();
		//delay (100);		// Not sure if this is needed
	}
	
	// Work with GB addresses 0x4000-0x7fff
	my_tpak.set_bank (0x01);
	
	for ( long j=0xc000; j<0x10000; j+=0x20 )
	{
		clear_mem_dump ();
		my_tpak.read (j);
		manage_mem_dump ();
		write_mem_managed ();
		//delay (100);		// Not sure if this is needed
	}
	
}


// Dump a ROM from a cartridge with an MBC1
void cart_helper::mbc1_dump_rom ()
{
	// Work with GB addresses 0x0000-0x3fff
	my_tpak.set_bank (0x00);
	
	// Dump the first 16 kiB of ROM
	for ( long j=0xc000; j<0x10000; j+=0x20 )
	{
		clear_mem_dump ();
		my_tpak.read (j);
		manage_mem_dump ();
		write_mem_managed ();
		//delay (100);		// Not sure if this is needed
	}
	
	
	// Dump the rest of the ROM
	for ( int i=1; i<rom_size; ++i )
	{
		mbc1_set_rom_bank_lo ( (u8)i );
		
		my_tpak.set_bank (0x01);
		
		for ( long j=0xc000; j<0x10000; j+=0x20 )
		{
			clear_mem_dump ();
			my_tpak.read (j);
			manage_mem_dump ();
			write_mem_managed ();
			//delay (100);		// Not sure if this is needed
		}
	}
	
}

void cart_helper::mbc1_set_rom_bank_lo ( u8 n_rom_bank_lo )
{
	write_byte_with_gb_addr ( 0x2000, n_rom_bank_lo );
	
	//my_tpak.set_bank (0x00);
	//delay (100);
	
	//memset ( &my_tpak.command [3], n_rom_bank_lo, 32 );
	//my_tpak.write (0xE000);
	//delay (100);
}

void cart_helper::mbc1_enable_ram ()
{
	write_byte_with_gb_addr ( 0x0000, 0x0a );
}

void cart_helper::mbc1_disable_ram ()
{
	write_byte_with_gb_addr ( 0x0000, 0x00 );
}
