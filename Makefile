# cmd used: ./configure -t 31 -f 48 -p /home/speed/arduino -d 1 -r -45
# The name of your project (used to name the compiled .hex file)
TARGET = StairwayLeds

# Folder where the .ino and .c/.cpp/.h files are located
SKETCHSRC = stairs

# Path were the arduino install is located
ARDUINOPATH = $(HOME)/arduino-1.6.3

# The teensy version to use, 30 or 31
TEENSY = 31

# Set to 24000000, 48000000, or 96000000 to set CPU core speed
TEENSY_CORE_SPEED = 96000000

# Some libraries will require this to be defined
ARDUINO = 162
TEENSYDUINO = 122

# configurable options
OPTIONS = -DUSB_SERIAL -DLAYOUT_US_ENGLISH

# more speed at the cost of size
#OPTIONS += -O2

# less size at the cost of speed
OPTIONS += -Os

# ------- stuff below shouldn't need to be modified -----------

#************************************************************************
# Location of Teensyduino utilities, Toolchain, and Arduino Libraries.
# To use this makefile without Arduino, copy the resources from these
# locations and edit the pathnames.  The rest of Arduino is not needed.
#************************************************************************

# directory to build in
BUILDDIR = $(abspath $(CURDIR)/build)

# path location for Teensy Loader, teensy_post_compile and teensy_reboot
#TOOLSPATH = $(CURDIR)/tools
TOOLSPATH = $(ARDUINOPATH)/hardware/tools

ifeq ($(OS),Windows_NT)
    $(error What is Win Dose?)
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        TOOLSPATH = /Applications/Arduino.app/Contents/Resources/Java/hardware/tools/
    endif
endif

# path location for Teensy 3 core
have_avr_in_path = $(wildcard $(ARDUINOPATH)/hardware/teensy/avr/cores/teensy3) 
ifeq ($(strip $(have_avr_in_path)),)
  # .. for arduino 1.0.x
  COREPATH = $(ARDUINOPATH)/hardware/teensy/cores/teensy3
else
  # .. for arduino 1.6.x
  COREPATH = $(ARDUINOPATH)/hardware/teensy/avr/cores/teensy3
endif

# path location for Arduino libraries
LIBRARYPATH = $(COREPATH)/../../libraries/OctoWS2811

# path location for the arm-none-eabi compiler
#COMPILERPATH = $(TOOLSPATH)/arm-none-eabi/bin
COMPILERPATH = $(TOOLSPATH)/arm/bin
#arm/bin

#************************************************************************
# Settings below this point usually do not need to be edited
#************************************************************************

GITREVISION = $(shell git log -n 1 --pretty=format:%h 2>/dev/null | echo unknown)
GITDIRTYTMP = $(shell git diff 2>/dev/null | md5sum | cut -c1-8)
BUILDTIME = $(shell date | sed -re 's/ /_/g')
ifeq ($(GITDIRTYTMP), d41d8cd9)
    GITDIRTY = clean
else
    GITDIRTY = dirty-$(GITDIRTYTMP)
endif

# CPPFLAGS = compiler options for C and C++
CPPFLAGS = -Wall -Werror -g -mcpu=cortex-m4 -mthumb -nostdlib -fdata-sections -ffunction-sections -MMD $(OPTIONS) -DF_CPU=$(TEENSY_CORE_SPEED) -I$(SKETCHSRC) -I$(COREPATH)
CPPFLAGS += -DTIME_T=$(shell date +%s)
CPPFLAGS += -DGIT_REVISION="$(GITREVISION)"
CPPFLAGS += -DGIT_DIRTY="$(GITDIRTY)"
CPPFLAGS += -DBUILD_TIME="$(BUILDTIME)"

# compiler options for C++ only
CXXFLAGS = -std=gnu++0x -felide-constructors -fno-exceptions -fno-rtti

# compiler options for C only
CFLAGS =


FLASHSIZE30=131072
RAMSIZE30=16384
FLASHSIZE31=262144
RAMSIZE31=65536
# compiler options specific to teensy version
ifeq ($(TEENSY), 30)
    CPPFLAGS += -D__MK20DX128__
    LDSCRIPT = $(COREPATH)/mk20dx128.ld
    FLASHSIZE=$(FLASHSIZE30)
    RAMSIZE=$(RAMSIZE30)
else
    ifeq ($(TEENSY), 31)
        CPPFLAGS += -D__MK20DX256__
        LDSCRIPT = $(COREPATH)/mk20dx256.ld
        FLASHSIZE=$(FLASHSIZE31)
        RAMSIZE=$(RAMSIZE31)
    else
        $(error Invalid setting for TEENSY)
    endif
endif


# set arduino define if given
ifdef ARDUINO
	CPPFLAGS += -DARDUINO=$(ARDUINO)
endif
ifdef TEENSYDUINO
	CPPFLAGS += -DTEENSYDUINO=$(TEENSYDUINO)
endif

# linker options
LDFLAGS = -Os -Wl,--gc-sections -mcpu=cortex-m4 -mthumb --specs=nano.specs -T$(LDSCRIPT) -Wl,-Map,$(TARGET).map
#LDFLAGS = -Os -Wl,--gc-sections -mcpu=cortex-m4 -mthumb -T$(LDSCRIPT) -Wl,-Map,$(TARGET).map

# additional libraries to link
LIBS = -lm

# gcc filter
GCCFILTER = gccfilter -c

# names for the compiler programs
CC = $(GCCFILTER) $(abspath $(COMPILERPATH))/arm-none-eabi-gcc
AR = $(GCCFILTER) $(abspath $(COMPILERPATH))/arm-none-eabi-ar
CXX = $(GCCFILTER) $(abspath $(COMPILERPATH))/arm-none-eabi-g++
OBJCOPY = $(GCCFILTER) $(abspath $(COMPILERPATH))/arm-none-eabi-objcopy
SIZE = $(GCCFILTER) $(abspath $(COMPILERPATH))/arm-none-eabi-size

# automatically create lists of the sources and objects
LC_FILES := $(wildcard $(LIBRARYPATH)/*.c)
LCPP_FILES := $(wildcard $(LIBRARYPATH)/*.cpp)
TC_FILES := $(wildcard $(COREPATH)/*.c)
TCPP_FILES := $(wildcard $(COREPATH)/*.cpp)
C_FILES := $(wildcard $(SKETCHSRC)/*.c)
CPP_FILES := $(wildcard $(SKETCHSRC)/*.cpp)
INO_FILES := $(wildcard $(SKETCHSRC)/*.ino)

# include paths for libraries
L_INC := $(foreach lib,$(filter %/, $(wildcard $(LIBRARYPATH)/)), -I$(lib))

SOURCES_SKETCH := $(C_FILES:.c=.o) $(CPP_FILES:.cpp=.o) $(INO_FILES:.ino=.o)
SOURCES_CORE   := $(TC_FILES:.c=.o) $(TCPP_FILES:.cpp=.o) $(LC_FILES:.c=.o) $(LCPP_FILES:.cpp=.o)
OBJS_SKETCH := $(foreach $(SKETCHSRC),$(SOURCES_SKETCH), $(BUILDDIR)/$($(SKETCHSRC)))
OBJS_CORE   := $(foreach $(SKETCHSRC),$(SOURCES_CORE), $(BUILDDIR)/$($(SKETCHSRC)))

all: hex

build: $(TARGET).elf

hex: $(TARGET).hex

post_compile: $(TARGET).hex
	@$(abspath $(TOOLSPATH))/teensy_post_compile -file="$(basename $<)" -path=$(CURDIR) -tools="$(abspath $(TOOLSPATH))"

reboot:
	@-$(abspath $(TOOLSPATH))/teensy_reboot

upload: post_compile reboot

screen:
	@while ! test -r /dev/ttyACM0 ; do echo -n . ; sleep 1 ; done ; screen /dev/ttyACM0

$(BUILDDIR)/%.o: %.c
	@/bin/echo -e "[CC]\t$<"
	@mkdir -p "$(dir $@)"
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(L_INC) -o "$@" -c "$<"

$(BUILDDIR)/%.o: %.cpp
	@/bin/echo -e "[CXX]\t$<"
	@mkdir -p "$(dir $@)"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(L_INC) -o "$@" -c "$<"

$(BUILDDIR)/%.o: %.ino
	@/bin/echo -e "[CXX]\t$<"
	@mkdir -p "$(dir $@)"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(L_INC) -o "$@" -x c++ -include Arduino.h -c "$<"

$(TARGET).elf: $(OBJS_SKETCH) $(BUILDDIR)/core.a $(LDSCRIPT)
	@/bin/echo -e "[LD]\t$@"
	@$(CC) $(LDFLAGS) -o "$@" $(OBJS_SKETCH) $(BUILDDIR)/core.a $(LIBS)

$(BUILDDIR)/core.a: $(OBJS_CORE)
	@/bin/echo -e "[AR]\t$@"
	@$(AR) rcs $(BUILDDIR)/core.a $(OBJS_CORE)

%.hex: %.elf
	@/bin/echo -e "[HEX]\t$@"
	@/bin/echo -e "[REV]\tgit.$(GITREVISION).$(GITDIRTY)"
	@$(SIZE) "$<" | awk '{ if (NR==2) { FLASH=$$1+$$2; RAM=$$2+$$3 } } END { printf "[FLASH]\t%6d/%6d (teensy30: %4.1f%%, teensy31: %4.1f%%)\n[RAM]\t%6d/%6d (teensy30: %4.1f%%, teensy31: %4.1f%%)\n", FLASH, $(FLASHSIZE), FLASH/$(FLASHSIZE30)*100, FLASH/$(FLASHSIZE31)*100, RAM, $(RAMSIZE), RAM/$(RAMSIZE30)*100, RAM/$(RAMSIZE31)*100 }'
	@$(OBJCOPY) -O ihex -R .eeprom "$<" "$@"

# compiler generated dependency info
-include $(OBJS:.o=.d)

clean:
	@echo "Cleaning sketch build (use distclean to clean teensy lib objects too)..."
	@rm -rfv "$(BUILDDIR)/$(SKETCHSRC)"
	@rm -fv "$(TARGET).elf" "$(TARGET).hex" "$(TARGET).map"

distclean:
	@echo Cleaning...
	@rm -rfv "$(BUILDDIR)"
	@rm -fv "$(TARGET).elf" "$(TARGET).hex" "$(TARGET).map"

