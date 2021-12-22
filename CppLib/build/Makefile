CPP_VERSION = 5.4.0
CFLAGS=-std=c++11

all: 
	@echo "Use make (libchipdnaclient-arm | libchipdnaclient-armhf | libchipdnaclient-x64 | libchipdnaclient-x86 | clean)"

libchipdnaclient-arm :
	$(MAKE) -f Makefile.arm all

libchipdnaclient-armhf :
	CPP_ROOTPATH=/usr/lib/gcc-cross/arm-linux-gnueabihf
	CPP_COMPILE=arm-linux-gnueabihf-g++
	LFLAGS=-L/usr/arm-linux-gnueabihf/lib
	$(MAKE) -f Makefile.arm all LIBCHIPDNACLIENT_LIBNAME=libchipdnaclient-armhf.a

libchipdnaclient-x64 :
	$(MAKE) -f Makefile.x64 all

libchipdnaclient-x86 :
	$(MAKE) -f Makefile.x86 all

clean :
	$(MAKE) -f Makefile.arm clean
	$(MAKE) -f Makefile.x64 clean
	$(MAKE) -f Makefile.x86 clean
	
