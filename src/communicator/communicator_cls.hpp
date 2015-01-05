#ifndef communicator_cls_hpp
#define communicator_cls_hpp


class communicator
{
public:		// variables
	int fd;
	
	// Buffers for Sending/Receiving data
	// They really don't need to be as large as they are.
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
	communicator ( int s_fd, const string& s_of_name, 
		const string& s_if_name );
	~communicator ();
	
	void get_cart_stuff ();
	
	
	
	// High Level Helper Functions
	void hl_read_32_bytes ( u16 gb_addr );
	void hl_read_bytes_and_write_to_ofile ( u16 gb_start_addr, 
		u16 num_bytes );
	
	void hl_write_32_bytes ( u16 gb_addr );
	void hl_write_rept_byte ( u16 gb_addr, u8 the_byte );
	
	inline int loop_for_reading_32_bytes ();
	
	
	void dump_rom_test ();
	
	
	void rom_only_dump_rom ( u16 start_bank=0x0000, u16 num_banks=0x0000 );
	void mbc1_dump_rom ( u16 start_bank=0x0000, u16 num_banks=0x0000 );
	void mbc2_dump_rom ( u16 start_bank=0x0000, u16 num_banks=0x0000 );
	void mbc3_dump_rom ( u16 start_bank=0x0000, u16 num_banks=0x0000 );
	void mbc5_dump_rom ( u16 start_bank=0x0000, u16 num_banks=0x0000 );
	
};




#endif		// communicator_cls_hpp
