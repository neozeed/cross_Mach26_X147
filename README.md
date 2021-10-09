# cross_Mach26_X147
Mach 2.6 X147 setup to compile under windows.  Need to do a native link. Tested on Qemu 0.10.5

You'll need the compiler & tools from here:

https://sourceforge.net/projects/linux011/

cd \aoutgcc\src\mach25-X113\obj\STD+WS-afs-nfs

you have 3 build scripts:

* build-gcc1.cmd
  gcc 1.40
  
* build-gcc22.cmd
  gcc 2.3.3
  
* build-gcc258.cmd
  gcc 2.5.8
 
Currently the following cant be built:

fd.o

hd.o

kd.o

kdasm.o

kd_event.o

The environment was prepped and MiG'd under a native machine.  The only drawback is that the Mach bootloader doesn't like the Linux a.out linker.  So you need to get the objects into Mach to do a native link.  Once that's done it'll boot.

Also init_main.c must be built with GCC 1.x
