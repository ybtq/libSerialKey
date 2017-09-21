CC  = g++
CXX = g++

ARCH = x86_64;
ifeq ($(shell getconf LONG_BIT), 32)
    ARCH = x86
else
    ARCH = x86_64
endif


OS_NAME         = $(shell uname -o)
LC_OS_NAME      = $(shell echo $(OS_NAME) | tr '[A-Z]' '[a-z]')

#$(shell find . -maxdepth 3 -type d)         recurse 3 level subdirectory
SRC_PATH   =    ./src

# If you want to build a x86 application on a x86_64 system, you should install gcc-multilib and g++-multilib, add -m32 to CFLAGS/CPPFLAGS LDFLAGS.
TARGET          = ./bin/unix-like/$(ARCH)/libSerialKey.so
INSTALL_PATH    = ../bin/linux
CFLAGS          = -shared -fPIC -fpermissive -I./include/ -DANTI_CRACK
CPPFLAGS        = $(CFLAGS)
LDFLAGS         = -shared -fPIC -lstdc++

.PHONY:all
all:$(TARGET)

# source object
ifneq ($(SRC_PATH),)
SRC_C           = 
SRC_CXX         = $(SRC_PATH)/TBaseConfiguration.cpp \
                  $(SRC_PATH)/TBigNumber.cpp \
                  $(SRC_PATH)/TGenerateKey.cpp \
                  $(SRC_PATH)/TMiscUtils.cpp \
                  $(SRC_PATH)/TValidateKey.cpp \
                  $(SRC_PATH)/TSerialKey.cpp
                  
SRC_C_OBJ       = $(SRC_C:.c=.o)
SRC_CXX_OBJ     = $(SRC_CXX:.cpp=.o)
SRC_C_DEPS      = $(SRC_C:.c=.d)
SRC_CXX_DEPS    = $(SRC_CXX:.cpp=.d)
endif

#include $(SRC_C_DEPS)
#include $(SRC_CXX_DEPS)

# compile rule
$(SRC_C_DEPS):%.d:%.c
	rm -rf $@
	$(CC) $(CFLAGS) -M $< -o $@

$(SRC_CXX_DEPS):%.d:%.cpp
	rm -rf $@
	$(CXX) $(CPPFLAGS) -M $< -o $@
	
$(SRC_C_OBJ):%.o:%.c
	$(CC) -c $< -o $@ $(CFLAGS)
	
$(SRC_CXX_OBJ):%.o:%.cpp
	$(CXX) -c $< -o $@ $(CPPFLAGS)

$(TARGET):$(SRC_C_DEPS) $(SRC_CXX_DEPS) $(SRC_C_OBJ) $(SRC_CXX_OBJ)
	$(CXX) -o $(TARGET) $(SRC_C_OBJ) $(SRC_CXX_OBJ) $(LDFLAGS)

install:$(TARGET)
	cp $(TARGET) $(INSTALL_PATH)/$(TARGET)
	
clean:
	rm -rf $(TARGET) $(SRC_C_DEPS) $(SRC_CXX_DEPS) $(SRC_C_OBJ) $(SRC_CXX_OBJ) $(INSTALL_PATH)/$(TARGET)

