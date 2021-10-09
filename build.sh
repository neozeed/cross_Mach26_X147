#!/bin/sh
#the build is weird as the config fails
#so this hack will config it and go
#
# So this make will fail. don't worry.
if [ ! -d obj ]; then
mkdir obj
fi

make
#
# manually do the kernel config
if [ ! -f obj/STD+WS-afs-nfs/vmunix ]; then
   cd obj/STD+WS-afs-nfs
   ../src/config/config.x -c ../../conf STD+WS-afs-nfs
   cd ../..
# and now it'll build
   make
fi
