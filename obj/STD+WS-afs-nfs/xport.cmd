del /F mod.tar mod.tar.gz
tar -cf mod.tar *.o vmunix.swap
gzip mod.tar
tar -cf mod.tar *.o vmunix.swap
tar -cf \qemu-0.10.5\a.tar mod.tar.gz mod.tar