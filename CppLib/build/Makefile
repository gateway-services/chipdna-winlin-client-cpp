# Set these values as appropriate; example values below.
# 
# OPENSSL_INSTALL_DIR = /opt/openssl-3
#
# CPP_ROOT_DIR = /opt/rh/gcc-toolset-12/root
# CPP_ROOT_DIR_ARMHF = /opt/ci/x-tools/armv6-rpi-linux-gnueabihf
# CPP_PREFIX_ARMHF = armv6-rpi-linux-gnueabihf
#
# CPP_LIB_SUBDIR_X64 = usr/lib/gcc/x86_64-redhat-linux/12
# CPP_LIB_SUBDIR_X86 = usr/lib/gcc/x86_64-redhat-linux/12/32
# CPP_LIB_SUBDIR_ARMHF = lib

OPENSSL_INSTALL_DIR = 

CPP_ROOT_DIR =
CPP_ROOT_DIR_ARMHF =
CPP_PREFIX_ARMHF =

CPP_LIB_SUBDIR_X64 =
CPP_LIB_SUBDIR_X86 =
CPP_LIB_SUBDIR_ARMHF =

CFLAGS = -std=c++11
CPP_LIB_NAME=libstdc++

all:
	@echo "Use make (libchipdnaclient-x64 | libchipdnaclient-x86 | libchipdnaclient-armhf | clean)"

libchipdnaclient-x64 :
	$(MAKE) -e \
	CFLAGS="$(CFLAGS)" \
	LIBOPENSSL_INC=$(OPENSSL_INSTALL_DIR)/include/ \
	CPP_LIB_PATH=$(CPP_ROOT_DIR)/$(CPP_LIB_SUBDIR_X64) \
	CPP_LIB_NAME=$(CPP_LIB_NAME) \
	CPP_COMPILE="$(CPP_ROOT_DIR)/bin/g++ -m64" \
	AR=$(CPP_ROOT_DIR)/bin/gcc-ar \
	LDFLAGS="-L$(CPP_ROOT_DIR)/$(CPP_LIB_SUBDIR_X64)" \
	-f Makefile.x64 all

libchipdnaclient-x86 :
	$(MAKE) -e \
	CFLAGS="$(CFLAGS)" \
	LIBOPENSSL_INC=$(OPENSSL_INSTALL_DIR)/include/ \
	CPP_LIB_PATH=$(CPP_ROOT_DIR)/$(CPP_LIB_SUBDIR_X86) \
	CPP_LIB_NAME=$(CPP_LIB_NAME) \
	CPP_COMPILE="$(CPP_ROOT_DIR)/bin/g++" \
	AR=$(CPP_ROOT_DIR)/bin/gcc-ar \
	LDFLAGS="-m32 -L$(CPP_ROOT_DIR)/$(CPP_LIB_SUBDIR_X86)" \
	-f Makefile.x86 all

libchipdnaclient-armhf :
	$(MAKE) -e \
	CFLAGS="$(CFLAGS)" \
	LIBOPENSSL_INC=$(OPENSSL_INSTALL_DIR).arm/include/ \
	CPP_LIB_PATH=$(CPP_ROOT_DIR_ARMHF)/$(CPP_PREFIX_ARMHF)/$(CPP_LIB_SUBDIR_ARMHF) \
	CPP_LIB_NAME=$(CPP_LIB_NAME) \
	CPP_COMPILE="$(CPP_ROOT_DIR_ARMHF)/bin/$(CPP_PREFIX_ARMHF)-g++" \
	AR=$(CPP_ROOT_DIR_ARMHF)/bin/$(CPP_PREFIX_ARMHF)-ar \
	LDFLAGS="-L$(CPP_ROOT_DIR_ARMHF)/$(CPP_PREFIX_ARMHF)/$(CPP_LIB_SUBDIR_ARMHF)" \
	-f Makefile.armhf all


clean :
	$(MAKE) -f Makefile.x64 clean
	$(MAKE) -f Makefile.x86 clean
	$(MAKE) -f Makefile.armhf clean
