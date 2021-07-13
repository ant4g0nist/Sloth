CFLAGS = -pthread -g -Wall -fPIC -ldl

all : sloth

libqemu.o:
	cd qemu && CC=clang CXX=clang++ CXXFLAGS=-fPIC ./configure --enable-linux-user --disable-system --disable-docs --disable-bsd-user --disable-gtk --disable-sdl --disable-vnc --target-list=aarch64-linux-user && make && cd -

libfuzzer.a: 
	cd fuzzer && ./build.sh && cd -

sloth.o: sloth.c
	clang sloth.c -c -o $@

sloth: libqemu.o libfuzzer.a sloth.o
	clang++ $(CFLAGS) sloth.o ./qemu/aarch64-linux-user/qemu-aarch64 ./fuzzer/libFuzzer.a -o $@
	rm sloth.o

clean:
	cd libQemu && make clean && cd -
	rm sloth