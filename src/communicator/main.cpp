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



int main ( int argc, char** argv )
{
	if ( argc < 3 )
	{
		cout << "Error:  Not enough parameters." << endl;
		return 1;
	}
	
	int fd = open ( argv [1], O_RDWR | O_NOCTTY | O_NONBLOCK );
	
	if ( fd < 0 )
	{
		cout << "Error opening device." << endl;
		return 1;
	}
	
	communicator the_communicator ( fd, argv [2], "" );
	
	//the_communicator.dump_rom_test ();
	
	//cout << the_communicator.cart_mbc_type << endl;
	//cout << the_communicator.rom_size << endl;
	//cout << the_communicator.ram_size << endl;
	
	//the_communicator.mbc5_dump_rom ();
	
	if ( argc == 3 )
	{
		the_communicator.mbc3_dump_rom ();
	}
	else if ( argc == 4 )
	{
		stringstream the_sstm;
		the_sstm << argv [3];
		
		u16 sb_u16;
		the_sstm >> sb_u16;
		
		the_communicator.mbc3_dump_rom (sb_u16);
	}
	else if ( argc == 5 )
	{
		stringstream the_sstm;
		the_sstm << argv [3];
		
		u16 sb_u16;
		the_sstm >> sb_u16;
		
		//the_communicator.mbc3_dump_rom (sb_u16);
	}
	
	
	return 0;
}
