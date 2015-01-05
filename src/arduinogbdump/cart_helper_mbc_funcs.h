#ifndef cart_helper_mbc_funcs_h
#define cart_helper_mbc_funcs_h

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
		
		
		
		case mbc5:
		case mbc5_ram:
			mbc5_dump_rom ();
			break;
		
		default:
			break;
	}
}

// Dump a ROM from a cartridge with no MBC (or a very small part of one
// that DOES have an MBC)
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
	}
	
	// Work with GB addresses 0x4000-0x7fff
	my_tpak.set_bank (0x01);
	
	for ( long j=0xc000; j<0x10000; j+=0x20 )
	{
		clear_mem_dump ();
		my_tpak.read (j);
		manage_mem_dump ();
		write_mem_managed ();
	}
	
}


// Dump a ROM from a cartridge with an MBC1
// Note:  This function is incomplete
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
		}
	}
	
}

// Dump a ROM from a cartridge that has an MBC5
void cart_helper::mbc5_dump_rom ()
{
	// MBC5 is nice because allows me to do everything with just GB
	// addresses 0x4000-0x7fff, ENTIRELY bypassing the need for the very
	// first for loop that is used in other dump_rom () functions 
	
	for ( int i=0; i<rom_size; ++i )
	{
		mbc5_set_rom_bank ( (u8)i, 0x00 );
		my_tpak.set_bank (0x01);
		
		for ( long j=0xc000; j<0x10000; j+=0x20 )
		{
			clear_mem_dump ();
			my_tpak.read (j);
			manage_mem_dump ();
			write_mem_managed ();
			//delay (1);
			//delay (10);
		}
		
		//delay (1);
	}
	
}

// Dump the RAM of a cartridge that has an MBC5
void cart_helper::mbc5_dump_ram ()
{
	long tpak_addr_start = 0xe000;
	long tpak_addr_end;
	
	
	switch (ram_size)
	{
		case rs_none:
			break;
		
		// 2 kiB of SRAM fills only GB addresses 0xa000-0xa800
		case rs_2:
			tpak_addr_end = 0xe800;
			
			//mbc5_set_ram_bank (i);
			
			mbc5_enable_ram ();
			
			my_tpak.set_bank (0x02);
			
			for ( long j=tpak_addr_start; j<tpak_addr_end; j+=0x20 )
			{
				clear_mem_dump ();
				my_tpak.read (j);
				manage_mem_dump ();
				write_mem_managed ();
			}
			
			mbc5_disable_ram ();
			
			break;
		
		// 8 kiB of SRAM fills all of GB addresses 0xa000-0xbffff
		case rs_8:
			
			tpak_addr_end = 0x10000;
			
			
			mbc5_enable_ram ();
			
			my_tpak.set_bank (0x02);
			
			for ( long j=tpak_addr_start; j<tpak_addr_end; j+=0x20 )
			{
				clear_mem_dump ();
				my_tpak.read (j);
				manage_mem_dump ();
				write_mem_managed ();
			}
			
			mbc5_disable_ram ();
			
			break;
		
		// 32 kiB of SRAM means that we need to do RAM banking shenanigans
		// There are 4 banks of SRAM in this case.
		case rs_32:
			
			tpak_addr_end = 0x10000;
			
			//for ( u8 i=0; i<16; ++i )
			for ( u8 i=0; i<4; ++i )
			{
				mbc5_disable_ram ();
				
				mbc5_set_ram_bank (i);
				
				mbc5_enable_ram ();
				
				my_tpak.set_bank (0x02);
				
				for ( long j=tpak_addr_start; j<tpak_addr_end; j+=0x20 )
				{
					clear_mem_dump ();
					my_tpak.read (j);
					manage_mem_dump ();
					write_mem_managed ();
				}
			}
			
			mbc5_disable_ram ();
			
			break;
		
		
		// 128 kiB of SRAM means that we need to do RAM banking shenanigans
		// There are 16 banks of SRAM in this case.
		case rs_128:
			
			//for ( u8 i=0; i<4; ++i )
			for ( u8 i=0; i<16; ++i )
			{
				mbc5_disable_ram ();
				
				mbc5_set_ram_bank (i);
				
				mbc5_enable_ram ();
				
				my_tpak.set_bank (0x02);
				
				for ( long j=tpak_addr_start; j<tpak_addr_end; j+=0x20 )
				{
					clear_mem_dump ();
					my_tpak.read (j);
					manage_mem_dump ();
					write_mem_managed ();
				}
				
			}
			
			mbc5_disable_ram ();
			
			break;
		
		default:
			break;
	}
}


// MBC Control Functions

// MBC1 Control Functions
void cart_helper::mbc1_set_rom_bank_lo ( u8 n_rom_bank_lo )
{
	write_byte_with_gb_addr ( 0x2000, n_rom_bank_lo );
}

void cart_helper::mbc1_enable_ram ()
{
	write_byte_with_gb_addr ( 0x0000, 0x0a );
}

void cart_helper::mbc1_disable_ram ()
{
	write_byte_with_gb_addr ( 0x0000, 0x00 );
}
// End of MBC1 Control Functions


// MBC5 Control Functions
void cart_helper::mbc5_set_rom_bank ( u8 n_rom_bank, u8 hbit )
{
	my_tpak.set_bank (0x00);
	my_tpak.write_byte ( 0xe000, n_rom_bank );
	my_tpak.write_byte ( 0xf000, ( hbit & 0x01 ) );
}


// This should only be called when cart RAM is --DISABLED--
void cart_helper::mbc5_set_ram_bank ( u8 n_ram_bank )
{
	write_byte_with_gb_addr ( 0x4000, ( n_ram_bank & 0x0f ) );
}

void cart_helper::mbc5_enable_ram ()
{
	write_byte_with_gb_addr ( 0x0000, 0x0a );
}

void cart_helper::mbc5_disable_ram ()
{
	write_byte_with_gb_addr ( 0x0000, 0x00 );
}

// End of MBC5 Control Functions

// End of MBC Control Functions

#endif		// cart_helper_mbc_funcs_h
