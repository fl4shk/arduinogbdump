gbdumpderp
=============

This is a very much unpolished/unfinished GB/GBC ROM dumper that uses an Arduino, an N64 controller, and an N64 Transfer Pak.

It should be rather easy for someone to take this and make a GB save data dumper/restorer as well, since the N64 Transfer pak can do that as well.

Much of the code used for this project was taken from this project:
	https://github.com/brownan/Gamecube-N64-Controller

There are some instructions included with that project for actually connecting the Arduino to the N64 controller.



Here's a tiny amount of the history behind this project, in case anyone cares:  

For figuring out some of the Transfer Pak shenanigans, I used some information from Project64 as well as some "debugging" of Pokemon Stadium 2.  Most of my own code is within the tpak_cls.h source file, but I believe I had to modify some of the borrowed stuff as well.  (It's been a year and a half, as of this writing, since I did anything with the source code for this project).
