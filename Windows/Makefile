# Auhtor: Dusten Knull

# Base commands, do not edit!
CC=gcc
RM=rm -rf
CP=cp

# Add all C files with full relative paths here
SRC=../src/*.c

# Output EXE file, please only edit the name and no the extension
BINDIR=../bin
BIN=$(BINDIR)/Game.exe

# Individual OS architecture directories for 32- and 64-bit archs
ARCH=i386
ARCH_64=x86_64

# Include dirs for both libs and headers
LIBINCLUDES=-L$(ARCH)/SDL2/lib
LIBINCLUDE_64=-L$(ARCH_64)/SDL2/lib
INCLUDES=-I../include

# Library linker flags for SDL2
LIBS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

# Extra flags to specify how the CC command should compile our code (add -fPIC later)
FLAGS=-Wall -O2 -g3

.PHONY: all
all: clean build

# Make using arguments 'make arch64' if compiling on a 64-bit OS
.PHONY: all_64
all_64: clean build_64

.PHONY: build
build:
	$(CC) $(SRC) -o $(BIN) $(FLAGS) $(INCLUDES) $(LIBINCLUDES) $(LIBS)
	$(CP) $(ARCH)/SDL2/bin/*.dll $(BINDIR)
	
.PHONY: build_64
build_64:
	$(CC) $(SRC) -o $(BIN) $(FLAGS) $(INCLUDES) $(LIBINCLUDES_64) $(LIBS)
	$(CP) $(ARCH_64)/SDL2/bin/*.dll $(BINDIR)

.PHONY: clean
clean:
	$(RM) $(BIN)
	$(RM) $(BINDIR)/*.dll
	
