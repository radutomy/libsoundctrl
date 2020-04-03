# Make sure to compile with the -lasound flag:

libsoundctrl.o: src/soundctrl.c
	gcc -shared -lasound -o bin/libsoundctrl.so src/soundctrl.c
	cp -f bin/libsoundctrl.so /usr/lib/
