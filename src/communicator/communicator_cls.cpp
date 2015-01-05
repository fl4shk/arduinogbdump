#include <stdint.h>

typedef uint8_t u8; typedef int8_t s8;
typedef uint16_t u16; typedef int16_t s16;
typedef uint32_t u32; typedef int32_t s32;
typedef uint64_t u64; typedef int64_t s64;
typedef unsigned int uint;


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <array>
using namespace std;


#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "misc_types.hpp"
#include "stuffs.hpp"


#include "communicator_cls.hpp"


communicator::communicator ( int argc, char** argv )
{
	//if ( of_name != "" )
	//{
	//	ofile.open ( of_name, ios_base::out | ios_base::binary );
	//}
	//
	//if ( if_name != "" )
	//{
	//	ifile.open ( if_name, ios_base::in | ios_base::binary );
	//}
	
	fd = open ( argv [1], O_RDWR | O_NOCTTY | O_NONBLOCK );
	
	if ( fd < 0 )
	{
		cout << "Error opening Arduino." << endl;
		return;
	}
	
	string argv2 = argv [2], argv3 = argv [3];
	
	communicator_action action;
	
	if ( argv2 == "dump_rom" )
	{
		action = do_rom_dump;
	}
	else if ( argv2 == "dump_ram" )
	{
		action = do_ram_dump;
	}
	else if ( argv2 == "restore_ram" )
	{
		action = do_ram_restore;
	}
	else
	{
		cout << "Error:  Invalid command.\n";
		return;
	}
	
	
	
	u16 start_bank = 0x0000, num_banks = 0x0000;
	
	switch (action)
	{
		case do_rom_dump:
			of_name = argv3;
			ofile.open ( of_name, ios_base::out | ios_base::binary );
			
			if ( argc > 4 )
			{
				stringstream the_sstm;
				the_sstm << argv [4];
				
				the_sstm >> start_bank;
			}
			if ( argc > 5 )
			{
				stringstream the_sstm;
				the_sstm << argv [5];
				
				the_sstm >> num_banks;
			}
			// Arguments past argv [5] are ignored
			
			dump_rom ( start_bank, num_banks );
			
			break;
		
		case do_ram_dump:
			//of_name = argv3;
			//ofile.open ( of_name, ios_base::out | ios_base::binary );
			
			
			break;
		
		case do_ram_restore:
			//if_name = argv3;
			//ifile.open ( if_name, ios_base::in | ios_base::binary );
			
			
			break;
		
		default:
			cout << "There's some weird bug....\n";
			return;
			break;
	}
	
	
	
	get_cart_stuff ();
	
}

communicator::~communicator ()
{
}


void communicator::get_cart_stuff ()
{
	send_buf [0] = sm_get_cart_stuff;
	
	while ( do_select_for_write (fd) )
	{
		cout << "Unable to write!\n";
	}
	
	write ( fd, send_buf.data (), 1 );
	
	loop_for_reading_32_bytes ();
	
	
	cart_mbc_type = (mbc_type)(recv_buf [0]);
	
	addr_packet rom_size_pkt;
	rom_size_pkt.hi = recv_buf [1];
	rom_size_pkt.lo = recv_buf [2];
	
	rom_size = rom_size_pkt.w;
	
	ram_size = (ram_size_type)(recv_buf [3]);
	
}


void communicator::hl_read_32_bytes ( u16 gb_addr )
{
	send_buf [0] = sm_gb_read_32_bytes;
	
	addr_packet temp_pkt;
	temp_pkt.w = gb_addr;
	
	send_buf [1] = temp_pkt.hi;
	send_buf [2] = temp_pkt.lo;
	
	
	while ( do_select_for_write (fd) )
	{
		cout << "Unable to write!\n";
	}
	
	write ( fd, send_buf.data (), 3 );
	
	
	loop_for_reading_32_bytes ();
	
	// received data is now in recv_buf
}


// Note:  I need to make something like this for writing data
void communicator::hl_read_bytes_and_write_to_ofile ( u16 gb_start_addr, 
	u16 num_bytes )
{
	send_buf [0] = sm_gb_read_var_num_bytes;
	
	addr_packet gb_start_addr_pkt, num_bytes_pkt;
	
	gb_start_addr_pkt.w = gb_start_addr;
	num_bytes_pkt.w = num_bytes;
	
	send_buf [1] = gb_start_addr_pkt.hi;
	send_buf [2] = gb_start_addr_pkt.lo;
	
	send_buf [3] = num_bytes_pkt.hi;
	send_buf [4] = num_bytes_pkt.lo;
	
	
	while ( do_select_for_write (fd) )
	{
		cout << "Unable to write!\n";
	}
	
	write ( fd, send_buf.data (), 5 );
	
	
	for ( uint i2=0; i2<( num_bytes_pkt.w / 0x20 ); ++i2 )
	{
		loop_for_reading_32_bytes ();
		
		ofile.write ( recv_buf.data (), 0x20 );
		ofile.flush ();
	}
	
	
}

void communicator::hl_write_32_bytes ( u16 gb_addr )
{
	send_buf [0] = sm_gb_write_32_bytes;
	
	addr_packet temp_pkt;
	temp_pkt.w = gb_addr;
	
	send_buf [1] = temp_pkt.hi;
	send_buf [2] = temp_pkt.lo;
	
	//memset ( &send_buf [3], the_byte, 32 );
	
	while ( do_select_for_write (fd) )
	{
		cout << "Unable to write!\n";
	}
	
	write ( fd, send_buf.data (), 3 );
	
	loop_for_reading_32_bytes ();
	
	// received data is now in recv_buf
}

// This function writes a single, repeated byte (for stability) to an
// address in GB format, NOT tpak format.
void communicator::hl_write_rept_byte ( u16 gb_addr, u8 the_byte )
{
	//do_buf_memsets ();
	
	send_buf [0] = sm_gb_write_32_bytes;
	
	addr_packet temp_pkt;
	temp_pkt.w = gb_addr;
	
	send_buf [1] = temp_pkt.hi;
	send_buf [2] = temp_pkt.lo;
	
	memset ( &send_buf [3], the_byte, 32 );
	
	while ( do_select_for_write (fd) )
	{
		cout << "Unable to write!\n";
	}
	
	write ( fd, send_buf.data (), 35 );
	
	loop_for_reading_32_bytes ();
	
	// received data is now in recv_buf
}


inline int communicator::loop_for_reading_32_bytes ()
{
	int left_to_read = 32;
	
	while ( left_to_read > 0 )
	{
		int num_read = read ( fd, 
			&( recv_buf [32 - left_to_read] ), 
			recv_buf.size () );
		
		if ( num_read < 0 )
		{
			cout << "There was an error reading from the Arduino.\n";
			return 1;
		}
		
		left_to_read -= num_read;
		
		//cout << left_to_read << endl;
		//cout << "Still in left_to_read while loop!\n";
	}
	
	return 0;
}

void communicator::dump_rom_test ()
{
	send_buf [0] = sm_gb_read_var_num_bytes;
	
	addr_packet gb_start_addr_pkt, num_bytes_pkt;
	
	gb_start_addr_pkt.w = 0x0000;
	num_bytes_pkt.w = 0x4000;
	
	send_buf [1] = gb_start_addr_pkt.hi;
	send_buf [2] = gb_start_addr_pkt.lo;
	
	send_buf [3] = num_bytes_pkt.hi;
	send_buf [4] = num_bytes_pkt.lo;
	
	while ( do_select_for_write (fd) )
	{
		cout << "Unable to write!\n";
	}
	
	write ( fd, send_buf.data (), 5 );
	
	
	for ( uint i2=0; i2<( num_bytes_pkt.w / 0x20 ); ++i2 )
	{
		loop_for_reading_32_bytes ();
		
		ofile.write ( recv_buf.data (), 0x20 );
		ofile.flush ();
	}
	
	
}



void communicator::rom_only_dump_single_rom_bank ( u16 bank )
{
	cout << "Dumping ROM bank " << bank << endl;
	
	if ( bank == 0x0000 )
	{
		hl_read_bytes_and_write_to_ofile ( 0x0000, 0x4000 );
	}
	else
	{
		hl_read_bytes_and_write_to_ofile ( 0x4000, 0x4000 );
	}
}

void communicator::mbc1_dump_single_rom_bank ( u16 bank )
{
	cout << "Dumping ROM bank " << bank << endl;
	
	
}

void communicator::mbc2_dump_single_rom_bank ( u16 bank )
{
	cout << "Dumping ROM bank " << bank << endl;
	
	
}

void communicator::mbc3_dump_single_rom_bank ( u16 bank )
{
	cout << "Dumping ROM bank " << bank << endl;
	
	if ( bank == 0x0000 )
	{
		hl_read_bytes_and_write_to_ofile ( 0x0000, 0x4000 );
	}
	else
	{
		hl_write_rept_byte ( 0x2000, (u8)( bank & 0x7f ) );
		hl_read_bytes_and_write_to_ofile ( 0x4000, 0x4000 );
	}
}

void communicator::mbc5_dump_single_rom_bank ( u16 bank )
{
	cout << "Dumping ROM bank " << bank << endl;
	
	// MBC5 is nice because it lets me do everything with just the
	// SWITCHABLE ROM bank
	hl_write_rept_byte ( 0x2000, (u8)( bank & 0xff ) );
	hl_read_bytes_and_write_to_ofile ( 0x4000, 0x4000 );
}




void communicator::rom_only_dump_rom ()
{
	
}

void communicator::mbc1_dump_rom ( u16 start_bank, u16 num_banks )
{
	
}

void communicator::mbc2_dump_rom ( u16 start_bank, u16 num_banks )
{
	
}

void communicator::mbc3_dump_rom ( u16 start_bank, u16 num_banks )
{
	get_cart_stuff ();
	
	if ( ( cart_mbc_type != mbc3 ) && ( cart_mbc_type != mbc3_timer ) 
		&& ( cart_mbc_type != mbc3_timer_ram ) 
		&& ( cart_mbc_type != mbc3_ram ) )
	{
		cout << "Error:  The cartridge doesn't seem to have an MBC3!\n";
		return;
	}
	cout << "The cartridge DOES have an MBC3!\n";
	
	if ( ( num_banks == 0x0000 ) || ( num_banks - start_bank ) > rom_size )
	{
		for ( uint i=start_bank; i<rom_size; ++i )
		{
			mbc3_dump_single_rom_bank (i);
		}
	}
	else
	{
		for ( uint i=start_bank; i<start_bank+num_banks; ++i )
		{
			mbc3_dump_single_rom_bank (i);
		}
	}
}


void communicator::mbc5_dump_rom ( u16 start_bank, u16 num_banks )
{
	get_cart_stuff ();
	
	if ( ( cart_mbc_type != mbc5 ) && ( cart_mbc_type != mbc5_ram ) )
	{
		cout << "Error:  The cartridge doesn't seem to have an MBC5!\n";
		return;
	}
	
	if ( rom_size > 256 )
	{
		cout << "Error:  Even though the cartridge has an MBC5, it is not"
			<< " yet supported.\n";
		cout << "Details:  Too many ROM banks.\n";
		return;
	}
	
	
	if ( ( num_banks == 0x0000 ) || ( num_banks - start_bank ) > rom_size )
	{
		//cout << "1234\n\n";
		for ( uint i=start_bank; i<rom_size; ++i )
		{
			mbc5_dump_single_rom_bank (i);
		}
	}
	else
	{
		//cout << "5678\n\n";
		for ( uint i=start_bank; i<start_bank+num_banks; ++i )
		{
			mbc5_dump_single_rom_bank (i);
		}
	}
	
	
}

void communicator::dump_rom ( u16 start_bank, u16 num_banks )
{
	get_cart_stuff ();
	
	if ( cart_mbc_type == rom_only )
	{
		cout << "No MBC at all, just a 32 kiB ROM\n";
		rom_only_dump_rom ();
	}
	else if ( ( cart_mbc_type >= mbc1 ) && ( cart_mbc_type <= mbc1_ram ) )
	{
		cout << "MBC1\n";
		mbc1_dump_rom ( start_bank, num_banks );
	}
	else if ( cart_mbc_type == mbc2 )
	{
		cout << "MBC2\n";
		mbc2_dump_rom ( start_bank, num_banks );
	}
	else if ( ( cart_mbc_type >= mbc3 ) && ( cart_mbc_type <= mbc3_ram ) )
	{
		cout << "MBC3\n";
		mbc3_dump_rom ( start_bank, num_banks );
	}
	else if ( ( cart_mbc_type >= mbc5 ) && ( cart_mbc_type <= mbc5_ram ) )
	{
		cout << "MBC5\n";
		mbc5_dump_rom ( start_bank, num_banks );
	}
	
	else
	{
		cout << "Error:  Unknown ROM type\n";
	}
}
