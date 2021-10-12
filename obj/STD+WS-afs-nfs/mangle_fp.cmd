del /F %1.o
cpp -nostdinc -DCMU -DINET -DMACH -DAT386 -DCMUCS -DKERNEL -DASSEMBLER -DLOCORE -I. -I..\..  ../../i386/fp/fp_%1.s | sed -e 's/_\ /_/g'| sed -e 's/\ ;/;/g' | sed -e 's/\ :/:/g' |grep -v # >%1.i
a386 %1.i -o %1.o
del /F %1.i