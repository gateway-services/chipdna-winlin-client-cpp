
LIBCHIPDNACLIENT_PATH_LIB = ../deps
LIBCHIPDNACLIENT_LIBNAME = chipdnaclient
LIBCHIPDNACLIENT_PATH_INCLUDE = ../include/clientlib
CHIPDNACLIENTSAMPLE_PATH_SRC = ../src
CHIPDNACLIENTSAMPLE_PATH_INCLUDE = ../include
CHIPDNACLIENTSAMPLE_NAME = chipdnaclientsample
CHIPDNACLIENTSAMPLE_SRC_ = \
	client.cpp \
	clientapp.cpp \
	configparser.cpp \
	ExtraParameter.cpp \
	BaseConfigParser.cpp \
	pugixml.cpp

CHIPDNACLIENTSAMPLE_SRC = $(patsubst %, $(CHIPDNACLIENTSAMPLE_PATH_SRC)/%, $(CHIPDNACLIENTSAMPLE_SRC_))
CHIPDNACLIENTSAMPLE_OBJ = $(CHIPDNACLIENTSAMPLE_SRC:.cpp=.o)

DEPENDENCIES = -lrt -lssl -lcrypto
CFLAGS = -std=c++11
G++ = g++
ABI_STRING = 

all:
	@echo "Rules: sample-x86 sample-arm sample-armhf sample-x64"

$(CHIPDNACLIENTSAMPLE_PATH_SRC)/%.o: $(CHIPDNACLIENTSAMPLE_PATH_SRC)/%.cpp
	$(G++) -c -I$(LIBCHIPDNACLIENT_PATH_INCLUDE) -I$(CHIPDNACLIENTSAMPLE_PATH_INCLUDE) -o $@ $< $(CFLAGS)

sample-arm: $(CHIPDNACLIENTSAMPLE_OBJ)
	$(G++) -L$(LIBCHIPDNACLIENT_PATH_LIB) $^ -o $(CHIPDNACLIENTSAMPLE_NAME)-arm -pthread -l$(LIBCHIPDNACLIENT_LIBNAME)-arm$(ABI_STRING) $(DEPENDENCIES) $(CFLAGS)

sample-armhf: $(CHIPDNACLIENTSAMPLE_OBJ)
	$(G++) -L$(LIBCHIPDNACLIENT_PATH_LIB) $^ -o $(CHIPDNACLIENTSAMPLE_NAME)-armhf -pthread -l$(LIBCHIPDNACLIENT_LIBNAME)-armhf$(ABI_STRING) $(DEPENDENCIES) $(CFLAGS)
	
sample-x86: $(CHIPDNACLIENTSAMPLE_OBJ)
	$(G++) -L$(LIBCHIPDNACLIENT_PATH_LIB) $^ -o $(CHIPDNACLIENTSAMPLE_NAME)-x86 -pthread -l$(LIBCHIPDNACLIENT_LIBNAME)-x86$(ABI_STRING) $(DEPENDENCIES) $(CFLAGS)

sample-x64: $(CHIPDNACLIENTSAMPLE_OBJ)
	$(G++) -L$(LIBCHIPDNACLIENT_PATH_LIB) $^ -o $(CHIPDNACLIENTSAMPLE_NAME)-x64 -pthread -l$(LIBCHIPDNACLIENT_LIBNAME)-x64$(ABI_STRING) $(DEPENDENCIES) $(CFLAGS)
	
clean:
	rm -f $(CHIPDNACLIENTSAMPLE_OBJ) $(CHIPDNACLIENTSAMPLE_NAME)
