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

void cart_helper::print_cart_stuff ()
{
	print_raw_data ();
	
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
			//Serial.println ("MBC type:  MBC5, with external RAM");
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
		
		case rs_128:
			Serial.println ("This cartridge has 128 kiB of external RAM.");
			break;
		
		case rs_mbc2:
			Serial.println ("This cartridge has no external RAM, but it"
				"does have an MBC2.  MBC2's have built-in RAM.");
			break;
		
		
	}
} 

void cart_helper::set_raw_data ( u8 s_raw_cart_type, u8 s_raw_rom_size,
	u8 s_raw_ram_size )
{
	raw_cart_type = s_raw_cart_type;
	raw_rom_size = s_raw_rom_size;
	raw_ram_size = s_raw_ram_size;
}

void cart_helper::print_raw_data ()
{
	Serial.println ( raw_cart_type, HEX );
	Serial.println ( raw_rom_size, HEX );
	Serial.println ( raw_ram_size, HEX );
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
	rom_size = 2 << raw_rom_size;
	
	
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
				ram_size = rs_32;
				break;
			
			// 128 kiB (16 banks of 8 kiB each) of external cart RAM
			case 0x04:
				ram_size = rs_128;
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




// Misc. Helper Functions

u8 cart_helper::calc_tpak_bank ( u16 gb_addr )
{
	// Unfortunately, the AVR instruction set can only shift by one bit at
	// a time, but this is still probably fast enough given that it won't
	// be called all that often.
	
	return (u8)( gb_addr >> 14 );
}


u16 cart_helper::calc_tpak_addr ( u16 gb_addr )
{
	return (u16)( gb_addr | 0xc000 );
}



void cart_helper::read_with_gb_addr ( u16 gb_addr )
{
	my_tpak.set_bank ( calc_tpak_bank (gb_addr) );
	my_tpak.read ( calc_tpak_addr (gb_addr) );
	
	//if ( ( gb_addr >= 0x0000 ) && ( gb_addr < 0x4000 ) )
	//{
	//	my_tpak.set_bank (0x00);
	//	my_tpak.read ( gb_addr + 0xc000 );
	//}
	//else if ( ( gb_addr >= 0x4000 ) && ( gb_addr < 0x8000 ) )
	//{
	//	my_tpak.set_bank (0x01);
	//	my_tpak.read ( gb_addr + 0x8000 );
	//}
	//else if ( ( gb_addr >= 0x8000 ) && ( gb_addr < 0xc000 ) )
	//{
	//	my_tpak.set_bank (0x02);
	//	my_tpak.read ( gb_addr + 0x4000 );
	//}
	//else
	//{
	//	my_tpak.set_bank (0x03);
	//	my_tpak.read (gb_addr);
	//}
}

void cart_helper::write_byte_with_gb_addr ( u16 gb_addr, u8 data )
{
	my_tpak.set_bank ( calc_tpak_bank (gb_addr) );
	my_tpak.write_byte ( calc_tpak_addr (gb_addr), data );
	
}

// End of Misc. Helper Functions



// This function ALSO waits for serial data
int cart_helper::interpret_serial_message ()
{
	memset ( buf, bufsize, 0 );
	
	int num_recv = Serial.readBytes ( buf, bufsize );
	//delay (10);
	
	
	//if ( num_recv > 0 )
	//{
	//	Serial.print ("I received this many bytes:  ");
	//	Serial.println ( num_recv, DEC );
	//}
	//delay (10);
	//
	//// temporary
	//return 0;
	
	
	// If we didn't receive anything
	if ( num_recv <= 0 )
	{
		//delay (10);
		return 0;
	}
	
	
	if ( buf [0] == sm_print_cart_stuff )
	{
		print_cart_stuff ();
	}
	else if ( buf [0] == sm_get_cart_stuff )
	{
		const uint num_to_write = 32;
		byte to_write [num_to_write];
		memset ( to_write, 0x00, num_to_write );
		
		addr_packet rom_size_pkt;
		rom_size_pkt.w = rom_size;
		
		
		to_write [0] = cart_mbc_type;
		
		// I like Big Endian more than Little Endian.
		to_write [1] = (byte)(rom_size_pkt.hi);
		to_write [2] = (byte)(rom_size_pkt.lo);
		
		to_write [3] = ram_size;
		
		
		Serial.write ( to_write, num_to_write );
	}
	
	// I'm not sure that this will work properly...
	else if ( buf [0] == sm_reset_tpak )
	{
		//// Disable the tpak
		//my_tpak.write_byte ( 0x8000, 0x80 );
		//delay (100);
		//
		//my_tpak.read ();
		//delay (100);
		//
		//my_tpak.write_byte ( 0x8000, 0x80 );
		//delay (100);
		//
		//my_tpak.read ();
		//delay (100);
		//
		//
		//// Enable the tpak
		//my_tpak.write_byte ( 0x8000, 0x84 );
		//delay (100);
		//
		//my_tpak.read ();
		//delay (100);
		//
		//my_tpak.write_byte ( 0x8000, 0x84 );
		//delay (100);
		//
		//my_tpak.read ();
		//delay (100);
		//
		
		for ( u8 i=0; i<32; ++i )
		{
			Serial.write (i);
		}
		return 1;
		
	}
	
	else if ( buf [0] == sm_gb_read_32_bytes )
	{
		// Treat the address as Big Endian
		addr_packet gb_addr_pkt;
		gb_addr_pkt.hi = (byte)(buf [1]);
		gb_addr_pkt.lo = (byte)(buf [2]);
		
		u16 gb_addr = gb_addr_pkt.w;
		
		//Serial.println ( gb_addr, HEX );
		
		u8 tpak_bank = calc_tpak_bank (gb_addr);
		u16 tpak_addr = calc_tpak_addr (gb_addr);
		
		//u8 tpak_bank = 0x00;
		//u16 tpak_addr = 0xc000 + gb_addr;
		
		my_tpak.set_bank (tpak_bank);
		
		clear_mem_dump ();
		my_tpak.read (tpak_addr);
		manage_mem_dump ();
		//print_mem_managed ();
		write_mem_managed ();
	}
	else if ( buf [0] == sm_gb_write_32_bytes )
	{
		// Treat the address as Big Endian
		addr_packet gb_addr_pkt;
		gb_addr_pkt.hi = (byte)(buf [1]);
		gb_addr_pkt.lo = (byte)(buf [2]);
		
		u16 gb_addr = gb_addr_pkt.w;
		
		
		u8 to_write [32];
		memcpy ( to_write, &buf [3], 32 );
		
		u8 tpak_bank = calc_tpak_bank (gb_addr);
		u16 tpak_addr = calc_tpak_addr (gb_addr);
		
		
		//clear_mem_dump ();
		
		//Serial.write ( to_write, 32 );
		
		
		my_tpak.set_bank (tpak_bank);
		my_tpak.write ( tpak_addr, to_write );
		
		
		
		
		// I don't necessarily NEED this loop, so I might be getting rid of
		// it in a later revision, if I can make stuff work properly
		// without it.
		
		//for ( uint i=0; i<32; ++i )
		for ( uint i=0; i<16; ++i )
		{
			//Serial.write (to_write [i]);
			//Serial.write ((u8)i);
			//Serial.write (my_tpak.get_bank ());
			
			Serial.write (gb_addr_pkt.hi);
			Serial.write (gb_addr_pkt.lo);
			
		}
	}
	
	else if ( buf [0] == sm_gb_read_var_num_bytes )
	{
		addr_packet gb_start_addr_pkt, num_bytes_pkt;
		
		// The GB address to read from is in buf [1] and buf [2] (u16)
		gb_start_addr_pkt.hi = (byte)(buf [1]);
		gb_start_addr_pkt.lo = (byte)(buf [2]);
		
		
		// The number of bytes to read is in buf [3] and buf [4] (u16)
		num_bytes_pkt.hi = (byte)(buf [3]);
		num_bytes_pkt.lo = (byte)(buf [4]);
		
		u16 gb_start_addr = gb_start_addr_pkt.w,
			num_bytes = num_bytes_pkt.w;
		
		u8 tpak_bank = calc_tpak_bank (gb_start_addr);
		long tpak_addr = calc_tpak_addr (gb_start_addr);
		long tpak_addr_end = tpak_addr + num_bytes;
		
		my_tpak.set_bank (tpak_bank);
		
		for ( ; tpak_addr<tpak_addr_end; tpak_addr+=0x20 )
		{
			clear_mem_dump ();
			my_tpak.read (tpak_addr);
			manage_mem_dump ();
			write_mem_managed ();
		}
	}
	
	// The (arbitrary) maximum number of bytes that can be sent to the
	// Arduino is 1024
	else if ( buf [0] == sm_gb_write_var_num_bytes )
	{
		addr_packet gb_start_addr_pkt, num_bytes_pkt;
		
		// The GB address to read from is in buf [1] and buf [2] (u16)
		gb_start_addr_pkt.hi = (byte)(buf [1]);
		gb_start_addr_pkt.lo = (byte)(buf [2]);
		
		// The number of bytes to write is in buf [3] and buf [4] (u16)
		num_bytes_pkt.hi = (byte)(buf [3]);
		num_bytes_pkt.lo = (byte)(buf [4]);
		
		
		u16 gb_start_addr = gb_start_addr_pkt.w,
			num_bytes = num_bytes_pkt.w;
		
		
		// 8*4 == 32.  Yay, math!
		for ( uint i=0; i<8; ++i )
		{
			Serial.write (gb_start_addr_pkt.hi);
			Serial.write (gb_start_addr_pkt.lo);
			
			Serial.write (num_bytes_pkt.hi);
			Serial.write (num_bytes_pkt.lo);
		}
		
		
		long left_to_read = num_bytes;
		
		while ( left_to_read > 0 )
		{
			int num_recv2 = Serial.readBytes 
				( &(buf [num_bytes - left_to_read]), 1024 );
			
			left_to_read -= num_recv2;
			
		}
		
		
		u8 tpak_bank = calc_tpak_bank (gb_start_addr);
		long tpak_addr = calc_tpak_addr (gb_start_addr);
		long tpak_addr_end = tpak_addr + num_bytes;
		my_tpak.set_bank (tpak_bank);
		
		const uint num_to_write = 32;
		u8 to_write [num_to_write];
		
		//memcpy ( to_write, &( buf [gb_start_addr-0xa000] ), num_to_write );
		
		//for ( uint i=0; i<num_to_write; ++i )
		//{
		//	Serial.print ( ( (u16)( buf [i]) ) & 0xff, HEX );
		//	Serial.print (" ");
		//}
		//Serial.println ();
		
		//Serial.println ( ( tpak_addr - 0xe000 ) / 0x400, HEX );
		//Serial.println ( tpak_addr, HEX );
		
		
		long buf_slot = 0x0000;
		for ( ; tpak_addr<tpak_addr_end; tpak_addr+=0x20, buf_slot += 0x20 )
		{
			memcpy ( to_write, &( buf [buf_slot] ), num_to_write );
			my_tpak.write ( tpak_addr, to_write );
			
			
			//Serial.print ( tpak_addr - 0xe000, HEX );
			//Serial.print (" ");
		}
		Serial.println ();
		
		
		//for ( uint i=0; i<32; ++i )
		//{
		//	Serial.print ( ( (u16)(buf [i]) ) & 0xff, HEX );
		//	Serial.print (" ");
		//}
		//Serial.println ();
		
	}
	
	else
	{
		Serial.println ("Invalid Command!!!!");
	}
	
	//delay (10);
	
	return 0;
}



#include "cart_helper_mbc_funcs.h"
