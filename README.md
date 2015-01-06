arduinogbdump
=============

This is an unpolished/unfinished GB/GBC ROM dumper that uses an Arduino, an
N64 controller, an N64 Transfer Pak, and a pull-up resistor.


arduinogbdump is heavily based on brownan's [Gamecube-N64-Controller](https://github.com/brownan/Gamecube-N64-Controller)

*Please note that this readme is not always up to date with the latest
code, especially regarding Features/Compatibility*


#Features/Compatibility
There is currently support for dumping ROMs from cartridges of the
following types:
  1.  ROM Only (32 kiB)
  2.  MBC2
  3.  MBC3
  4.  MBC5 (incomplete support, only works for ROMs up to 4 MiB)

There is currently support for dumping RAM from cartridges of the following
types:
  1.  MBC2
  2.  MBC3 (No RTC support yet)
  3.  MBC5


There is currently support for restoring RAM to cartridges of the following
types:
  2.  MBC3 (No RTC support yet)
  3.  MBC5


All testing of the communicator program has been done on Linux.  It is not
known whether it would even compile on other systems, but there's a good
chance of it working on other Unices (such as FreeBSD).


#How to Connect the Arduino Board to the N64 Controller
  1.  Follow the instructions included with brownan's
  Gamecube-N64-Controller project,
  2.  And then **also** connect the the N64 controller's power wire to the
  Arduino's 3.3V source.


#Arduino Board Compatibility
As is the case with the Gamecube-N64-Controller project, the timing code is
specific to Arduino boards with 8-bit AVRs clocked at 16 MHz.

The following Arduino boards have been tested and are working with this
project for sure:
  1.  Arduino Uno
  2.  Arduino Micro

However, it is likely that the other Arduino boards that use the following
AVR microcontrollers would work as well:
  1.  ATmega328P or ATmega168
  2.  ATmega32U4


Support for the Arduino Mega and the Arduino Mega 2560 is planned as well.


#Credits/Thanks
As previously mentioned, arduinogbdump is heavily based on [This](https://github.com/brownan/Gamecube-N64-Controller)

The 1964 emulator and the NRage plugin (compiled with debugging functions)
were really helpful in figuring out how real games (Pokemon Stadium 2 in
particular) used the Transfer Pak.  The NRage docs were also instrumental
for getting this to work.  Some of them have been included with this
project for reference.

The two CRC-related functions were taken from libdragon.

There were also various websites whose URLs escape me.

Additionally, the folks of #n64dev on EFnet have been very helpful,
especially when I was first working on this project in Spring 2013.


