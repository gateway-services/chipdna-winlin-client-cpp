CPP_VERSION = 5.4.0

all: 
	@echo "Use make (libchipdnaclient-arm | libchipdnaclient-armhf | libchipdnaclient-x64 | libchipdnaclient-x86 | clean)"

libchipdnaclient-arm :
	$(MAKE) -e CFLAGS=-std=c++11 AR=$(AR) CPP_VERSION=$(CPP_VERSION) -f Makefile.arm all

libchipdnaclient-armhf :
	$(MAKE) -e CFLAGS=-std=c++11 AR=$(AR) CPP_VERSION=$(CPP_VERSION) CPP_ROOTPATH=/usr/lib/gcc-cross/arm-linux-gnueabihf CPP_COMPILE=arm-linux-gnueabihf-g++ LFLAGS=-L/usr/arm-linux-gnueabihf/lib -f Makefile.arm all LIBCHIPDNACLIENT_LIBNAME=libchipdnaclient-armhf.a

libchipdnaclient-x64 :
	$(MAKE) -e CFLAGS=-std=c++11 AR=$(AR) CPP_VERSION=$(CPP_VERSION) -f Makefile.x64 all

libchipdnaclient-x86 :
	$(MAKE) -e CFLAGS=-std=c++11 AR=$(AR) CPP_VERSION=$(CPP_VERSION) -f Makefile.x86 all


clean :
	$(MAKE) -e -f Makefile.arm clean
	$(MAKE) -e -f Makefile.x64 clean
	$(MAKE) -e -f Makefile.x86 clean
	
