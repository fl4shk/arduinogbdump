// Note:  This code is C++


struct cart_header
{
public:  // variables
  static const int logo_size = 0x30;
  
  char cart_type, rom_size, ram_size, dest_code, old_lc, version_num, header_checksum;
  
  char mbc;
  
public:  // functions
  cart_header () { init_logo (); }
  ~cart_header () {}
  
  const char *get_ninty_logo () const { return const_cast <const char *>(ninty_logo); }
  
protected:  // variables
  static char ninty_logo [logo_size];
  
protected:  // functions
  static void init_logo ()
  {
    char temp [] 
        = { 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 
        0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
        0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 
        0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 
        0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 
        0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E };
    
    for ( int i=0; i<logo_size; ++i )
      ninty_logo [i] = temp [i];
  }
};

class tpak
{
protected:  // variables
  static const word wcmd_size = 35, rcmd_size = 3;
  u8 command [wcmd_size];
  addr_packet addr_pkt;
  
  
public:  // functions
  tpak () {}
  ~tpak () {}
  
  void init ()
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
    
  }
  
  void get_rom ()
  {
    for ( int i=0x04; i<0x10; ++i )
    {
      set_mbc1_rom_bank (i);
      
      for ( unsigned long j=0xC000; j<0x10000; j+=0x20 )
      {
        clear_mem_dump ();
        read (j);
        manage_mem_dump (); write_mem_managed ();
        delay (100);
      }
    }
  }
  
  void enable_tpak ()
  {
    memset ( &command [3], 0x84, 32 );
    write (0x8000);
  }  
  
  void get_access_mode ()
  {
    read (0xB000);
  }
  
  void set_access_mode ( bool n_mode )
  {
    memset ( &command [3], (char)n_mode, 32 );
    write (0xB000);
  }
  
  void set_bank ( char n_tpak_bank )
  {
    memset ( &command [3], n_tpak_bank, 32 );
    write (0xA000);
  }
  
  void set_mbc1_rom_bank ( char n_rom_bank )
  {
    set_bank (0x00);
    delay (100);
    
    memset ( &command [3], n_rom_bank, 32 );
    write (0xE000);
    delay (100);
    
    set_bank (0x01);
    delay (100);
  }
  
  void set_mbc1_ram_bank ( char n_ram_bank )
  {
    
  }
  
  //void set_mbc2_rom_bank ( 
  
  bool cart_supported ( char cart_type ) const
  {
    switch (cart_type)
    {
      case 0x00:  
      case 0x01:  
        return true;
      default:  
        return false;
    }
  }
  
  void write ()
  {
    command [0] = 0x03; command [1] = addr_pkt.hi; 
    command [2] = addr_pkt.lo;
    
    N64_stuff ( command, wcmd_size );
  }
  void write ( u16 write_addr )
  {
    addr_pkt.w = calc_addr_crc (write_addr);
    command [0] = 0x03; command [1] = addr_pkt.hi; 
    command [2] = addr_pkt.lo;
    
    N64_stuff ( command, wcmd_size );
  }
  void write ( u16 write_addr, u8 *msg )    // appends address CRC to write_addr
  {
    addr_pkt.w = calc_addr_crc (write_addr);
    memcpy ( &command [3], msg, 32 );
    command [0] = 0x03; command [1] = addr_pkt.hi; 
    command [2] = addr_pkt.lo;
    
    N64_stuff ( command, wcmd_size );
  }
  void write_nocrc ( u16 write_addr )
  {
    addr_pkt.w = write_addr;
    command [0] = 0x03; command [1] = addr_pkt.hi; 
    command [2] = addr_pkt.lo;
    
    N64_stuff ( command, wcmd_size );
  }
  void write_nocrc ( u16 write_addr, u8 *msg )    // doesn't touch write_addr's CRC stuff
  {
    addr_pkt.w = write_addr;
    memcpy ( &command [3], msg, 32 );
    command [0] = 0x03; command [1] = addr_pkt.hi; 
    command [2] = addr_pkt.lo;
    
    N64_stuff ( command, wcmd_size );
  }
  
  
  void read ()
  {
    command [0] = 0x02; command [1] = addr_pkt.hi; 
    command [2] = addr_pkt.lo;
    
    N64_stuff ( command, rcmd_size );
  }
  void read ( u16 read_addr )
  {
    addr_pkt.w = calc_addr_crc (read_addr);
    command [0] = 0x02; command [1] = addr_pkt.hi; 
    command [2] = addr_pkt.lo;
    
    N64_stuff ( command, rcmd_size );
  }
  void read_nocrc ( u16 read_addr )
  {
    addr_pkt.w = read_addr;
    command [0] = 0x02; command [1] = addr_pkt.hi; 
    command [2] = addr_pkt.lo;
    
    N64_stuff ( command, rcmd_size );
  }
  
  
  
protected:  // functions
  
};


