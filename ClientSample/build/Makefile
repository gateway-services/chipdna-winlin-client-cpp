# Set these values as appropriate; example values below.
# 
# OPENSSL_INSTALL_DIR = /opt/openssl-3
#
# CPP_ROOT_DIR = /opt/rh/gcc-toolset-12/root
# CPP_ROOT_DIR_ARMHF = /opt/ci/x-tools/armv6-rpi-linux-gnueabihf
# CPP_PREFIX_ARMHF = armv6-rpi-linux-gnueabihf

CFLAGS = -std=c++11

all:
	@echo "Rules: sample-x86 sample-armhf sample-x64"

sample-x64 :
	$(MAKE) -e \
	CFLAGS="$(CFLAGS)" \
	CPP_COMPILE="$(CPP_ROOT_DIR)/bin/g++ -m64" \
	LDFLAGS="-L$(OPENSSL_INSTALL_DIR)/lib64" \
	-f Makefile.x64 all

sample-x86 :
	$(MAKE) -e \
	CFLAGS="$(CFLAGS)" \
	CPP_COMPILE="$(CPP_ROOT_DIR)/bin/g++" \
	LDFLAGS="-m32 -L$(OPENSSL_INSTALL_DIR)/lib" \	
	-f Makefile.x86 all

sample-armhf : 
	$(MAKE) -e \
	CFLAGS="$(CFLAGS)" \
	CPP_COMPILE="$(CPP_ROOT_DIR_ARMHF)/bin/$(CPP_PREFIX_ARMHF)-g++" \
	LDFLAGS="-L$(OPENSSL_INSTALL_DIR).arm/lib" \
	-f Makefile.armhf all


clean :
	$(MAKE) -f Makefile.x64 clean
	$(MAKE) -f Makefile.x86 clean
	$(MAKE) -f Makefile.armhf clean
