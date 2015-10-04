#ifndef communicator_cls_hpp
#define communicator_cls_hpp

#include <errno.h>

enum communicator_action
{
	do_rom_dump,
	
	// do_rom_banks_dump was added because sometimes the Transfer Pak stops
	// being possible to read from.  It is so finicky.
	do_rom_banks_dump,
	
	do_ram_dump,
	do_ram_restore,
	
};

class communicator
{
public:		// variables
	static constexpr u32 rom_bank_size = 0x4000;
	
	int fd;
	
	// Buffers for Sending/Receiving data
	//// They really don't need to be as large as they are, but...
	array< char, 2048 > send_buf;
	array< char, rom_bank_size > recv_buf;
	
	
	
	// fstreams for I/O
	fstream ofile, ifile;
	
	// filenames
	string of_name, if_name;
	
	mbc_type cart_mbc_type;
	u16 rom_size;
	ram_size_type ram_size;
	
	
public:		// functions
	//communicator( int s_fd, const string& s_of_name, 
	//	const string& s_if_name );
	communicator( int argc, char** argv );
	~communicator();
	
	void get_cart_stuff();
	
	
	
	// High Level Helper Functions
	void hl_read_32_bytes( u16 gb_addr );
	void hl_read_bytes_and_write_to_ofile( u16 gb_start_addr, 
		u16 num_bytes );
	
	void hl_write_32_bytes( u16 gb_addr );
	void hl_write_rept_byte( u16 gb_addr, u8 the_byte );
	void hl_read_from_ifile_and_write_bytes( u16 gb_start_addr,
		u16 num_bytes, u8 gb_ram_bank=0x00 );
	
	inline int loop_for_reading_32_bytes();
	inline int loop_for_reading_var_num_bytes( u16 num_bytes );
	
	
	void dump_rom_test();
	
	
	// Single ROM bank dumping functions
	void rom_only_dump_single_rom_bank( u16 bank );
	void mbc1_dump_single_rom_bank( u16 bank );
	void mbc2_dump_single_rom_bank( u16 bank );
	void mbc3_dump_single_rom_bank( u16 bank );
	void mbc5_dump_single_rom_bank( u16 bank );
	
	// Main ROM dumping functions
	void rom_only_dump_rom();
	void mbc1_dump_rom( u16 start_bank=0x0000, u16 num_banks=0x0000 );
	void mbc2_dump_rom( u16 start_bank=0x0000, u16 num_banks=0x0000 );
	void mbc3_dump_rom( u16 start_bank=0x0000, u16 num_banks=0x0000 );
	void mbc5_dump_rom( u16 start_bank=0x0000, u16 num_banks=0x0000 );
	
	
	void rom_only_dump_rom_banks_to_separate_files();
	void mbc1_dump_rom_banks_to_separate_files( u16 start_bank=0x0000, 
		u16 num_banks=0x0000 );
	void mbc2_dump_rom_banks_to_separate_files( u16 start_bank=0x0000, 
		u16 num_banks=0x0000 );
	void mbc3_dump_rom_banks_to_separate_files( u16 start_bank=0x0000, 
		u16 num_banks=0x0000 );
	void mbc5_dump_rom_banks_to_separate_files( u16 start_bank=0x0000, 
		u16 num_banks=0x0000 );
	
	
	// Main RAM dumping functions
	void mbc1_dump_ram();
	void mbc2_dump_ram();
	void mbc3_dump_ram();
	void mbc5_dump_ram();
	
	// Main RAM restoring functions
	void mbc1_restore_ram();
	void mbc2_restore_ram();
	void mbc3_restore_ram();
	void mbc5_restore_ram();
	
	
	
	void dump_rom( u16 start_bank=0x0000, u16 num_banks=0x0000 );
	void dump_rom_banks_to_separate_files( u16 start_bank=0x0000,
		u16 num_banks=0x0000 );
	void dump_ram();
	void restore_ram();
};


inline int communicator::loop_for_reading_32_bytes()
{
	
	int left_to_read = 32;
	
	while ( left_to_read > 0 )
	{
		int num_read = read( fd, &( recv_buf[32 - left_to_read] ), 
			recv_buf.size() );
		
		if ( num_read < 0 )
		{
			cout << "There was an error reading from the Arduino:  "
				<< num_read << "\n";
			cout << "This was the error:  " << strerror(errno) << "\n";
			return 1;
		}
		//else if ( num_read == 0 )
		//{
		//	cout << "Nothing was read....\n";
		//	
		//	//exit(1);
		//}
		
		left_to_read -= num_read;
		
		//cout << left_to_read << endl;
		//cout << "Still in left_to_read while loop!\n";
	}
	
	return 0;
}
inline int communicator::loop_for_reading_var_num_bytes( u16 num_bytes )
{
	
	int left_to_read = num_bytes;
	
	while ( left_to_read > 0 )
	{
		int num_read = read( fd, &( recv_buf[num_bytes - left_to_read] ), 
			recv_buf.size() );
		
		if ( num_read < 0 )
		{
			cout << "There was an error reading from the Arduino.\n";
			return 1;
		}
		//else if ( num_read == 0 )
		//{
		//	cout << "Nothing was read....\n";
		//	
		//	//exit(1);
		//}
		
		left_to_read -= num_read;
		
		//cout << left_to_read << endl;
		//cout << "Still in left_to_read while loop!\n";
	}
	
	return 0;
}


#endif		// communicator_cls_hpp
