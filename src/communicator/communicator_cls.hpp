#ifndef communicator_cls_hpp
#define communicator_cls_hpp

enum communicator_action
{
	do_rom_dump,
	do_ram_dump,
	do_ram_restore
};

class communicator
{
public:		// variables
	int fd;
	
	// Buffers for Sending/Receiving data
	// They really don't need to be as large as they are, but...
	array < char, 2048 > send_buf;
	array < char, 1024 > recv_buf;
	
	
	
	// fstreams for I/O
	fstream ofile, ifile;
	
	// filenames
	string of_name, if_name;
	
	
	
	mbc_type cart_mbc_type;
	u16 rom_size;
	ram_size_type ram_size;
	
	
public:		// functions
	//communicator ( int s_fd, const string& s_of_name, 
	//	const string& s_if_name );
	communicator ( int argc, char** argv );
	~communicator ();
	
	void get_cart_stuff ();
	
	
	
	// High Level Helper Functions
	void hl_read_32_bytes ( u16 gb_addr );
	void hl_read_bytes_and_write_to_ofile ( u16 gb_start_addr, 
		u16 num_bytes );
	
	void hl_write_32_bytes ( u16 gb_addr );
	void hl_write_rept_byte ( u16 gb_addr, u8 the_byte );
	//void hl_read_from_ifile_and_write_bytes ( u16 gb_start_addr,
	// u16 num_bytes );
	
	inline int loop_for_reading_32_bytes ();
	
	
	void dump_rom_test ();
	
	
	// Single ROM bank dumping functions
	void rom_only_dump_single_rom_bank ( u16 bank );
	void mbc1_dump_single_rom_bank ( u16 bank );
	void mbc2_dump_single_rom_bank ( u16 bank );
	void mbc3_dump_single_rom_bank ( u16 bank );
	void mbc5_dump_single_rom_bank ( u16 bank );
	
	// Main ROM dumping functions
	void rom_only_dump_rom ();
	void mbc1_dump_rom ( u16 start_bank=0x0000, u16 num_banks=0x0000 );
	void mbc2_dump_rom ( u16 start_bank=0x0000, u16 num_banks=0x0000 );
	void mbc3_dump_rom ( u16 start_bank=0x0000, u16 num_banks=0x0000 );
	void mbc5_dump_rom ( u16 start_bank=0x0000, u16 num_banks=0x0000 );
	
	
	void dump_rom ( u16 start_bank=0x0000, u16 num_banks=0x0000 );
	//void dump_ram ();
	//void restore_ram ();
};




#endif		// communicator_cls_hpp
