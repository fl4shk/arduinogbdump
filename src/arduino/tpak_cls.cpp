#include "aux_code.h"
#include "tpak_cls.h"
#include "cart_helper_cls.h"

tpak::tpak ()
{
}


tpak::~tpak ()
{
}


void tpak::init ( cart_helper& the_cart_helper )
{
	delay (255+150);
	
	enable_tpak ();
	delay (100);
	
	read ();
	delay (100);
	
	enable_tpak ();
	delay (100);
	
	read ();
	delay (100);
	
	get_access_mode ();
	delay (100);
	
	set_access_mode (0xFF);
	delay (100);
	
	get_access_mode ();
	delay (100);
	
	the_cart_helper.set_cart_stuff ();
	
}




void tpak::enable_tpak ()
{
	memset ( &command [3], 0x84, 32 );
	write (0x8000);
}  


void tpak::get_access_mode ()
{
	read (0xB000);
}


void tpak::set_access_mode ( bool n_mode )
{
	memset ( &command [3], (char)n_mode, 32 );
	write (0xB000);
}


void tpak::set_bank ( char n_tpak_bank )
{
	current_bank = n_tpak_bank;
	
	memset ( &command [3], n_tpak_bank, 32 );
	write (0xA000);
}


// There is no way to ask the real life Transfer Pak for its current bank,
// so this class will keep track of it.
char tpak::get_bank () const
{
	return current_bank;
}


void tpak::write ()
{
	command [0] = 0x03;
	command [1] = addr_pkt.hi;
	command [2] = addr_pkt.lo;
	
	N64_stuff ( command, wcmd_size );
}



void tpak::write ( u16 write_addr )
{
	addr_pkt.w = calc_addr_crc (write_addr);
	command [0] = 0x03;
	command [1] = addr_pkt.hi;
	command [2] = addr_pkt.lo;
	
	N64_stuff ( command, wcmd_size );
}



void tpak::write ( u16 write_addr, u8* msg )
{
	addr_pkt.w = calc_addr_crc (write_addr);
	memcpy ( &command [3], msg, 32 );
	command [0] = 0x03;
	command [1] = addr_pkt.hi;
	command [2] = addr_pkt.lo;
	
	N64_stuff ( command, wcmd_size );
}


// Write a single, repeated byte
void tpak::write_byte ( u16 write_addr, u8 data )
{
	addr_pkt.w = calc_addr_crc (write_addr);
	//memcpy ( &command [3], msg, 32 );
	
	memset ( &command [3], data, 32 );
	command [0] = 0x03;
	command [1] = addr_pkt.hi;
	command [2] = addr_pkt.lo;
	
	N64_stuff ( command, wcmd_size );
}


//void tpak::write_nocrc ( u16 write_addr )
//{
//	addr_pkt.w = write_addr;
//	command [0] = 0x03;
//	command [1] = addr_pkt.hi;
//	command [2] = addr_pkt.lo;
//	
//	N64_stuff ( command, wcmd_size );
//}



//void tpak::write_nocrc ( u16 write_addr, u8 *msg )
//{
//	addr_pkt.w = write_addr;
//	memcpy ( &command [3], msg, 32 );
//	command [0] = 0x03;
//	command [1] = addr_pkt.hi;
//	command [2] = addr_pkt.lo;
//	
//	N64_stuff ( command, wcmd_size );
//}



void tpak::read ()
{
	command [0] = 0x02;
	command [1] = addr_pkt.hi;
	command [2] = addr_pkt.lo;
	
	N64_stuff ( command, rcmd_size );
}



void tpak::read ( u16 read_addr )
{
	addr_pkt.w = calc_addr_crc (read_addr);
	command [0] = 0x02;
	command [1] = addr_pkt.hi;
	command [2] = addr_pkt.lo;
	
	N64_stuff ( command, rcmd_size );
}



//void tpak::read_nocrc ( u16 read_addr )
//{
//	addr_pkt.w = read_addr;
//	command [0] = 0x02;
//	command [1] = addr_pkt.hi;
//	command [2] = addr_pkt.lo;
//	
//	N64_stuff ( command, rcmd_size );
//}


