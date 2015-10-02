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
#include "communicator_class.hpp"



int main( int argc, char** argv )
{
	if ( argc < 4 )
	{
		cout << "Usage 1:  " << argv[0] << " arduino_serial_file dump_rom "
			<< "rom.gb\n";
		cout << "Usage 2:  " << argv[0] << " arduino_serial_file "
			<< "dump_rom_banks base_name\n";
		cout << "Usage 3:  " << argv[0] << " arduino_serial_file "
			<< "dump_rom_banks base_name start_bank\n";
		cout << "Usage 4:  " << argv[0] << " arduino_serial_file "
			<< "dump_rom_banks base_name start_bank num_banks\n";
		cout << "Usage 5:  " << argv[0] << " arduino_serial_file dump_ram "
			<< "save_data.sav\n";
		cout << "Usage 6:  " << argv[0] << " arduino_serial_file "
			<< "restore_ram save_data.sav\n";
		return 0;
	}
	
	communicator the_communicator( argc, argv );
	
	//communicator the_communicator( fd, argv[2], "" );
	
	
	
	
	
	//if ( argc == 3 )
	//{
	//	the_communicator.dump_rom();
	//}
	//else if ( argc == 4 )
	//{
	//	stringstream the_sstm;
	//	the_sstm << argv[3];
	//	
	//	u16 start_bank;
	//	the_sstm >> start_bank;
	//	
	//	the_communicator.dump_rom(start_bank);
	//}
	//else if ( argc == 5 )
	//{
	//	stringstream the_sstm;
	//	u16 start_bank, num_banks;
	//	
	//	the_sstm << argv[3];
	//	the_sstm >> start_bank;
	//	the_sstm.clear();
	//	
	//	the_sstm << argv[4];
	//	the_sstm >> num_banks;
	//	
	//	cout << start_bank << " " << num_banks << endl;
	//	
	//	the_communicator.dump_rom( start_bank, num_banks );
	//}
	
	
	return 0;
}
