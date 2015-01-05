#ifndef stuffs_hpp
#define stuffs_hpp


int do_select_for_write ( int fd );
int do_select_for_read ( int fd );


// Send text to the Arduino
//void do_arduino_write ( int fd, string& to_arduino );

// Read text from the Arduino
void do_arduino_read ( int fd, string& from_arduino );



#endif		// stuffs_hpp
