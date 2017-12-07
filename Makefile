# Auhtor: Dusten Knull

# Base commands, do not edit!
CC=gcc
RM=rm -rf
CP=cp

# Add all C files with full relative paths here
SRC=src/*.c

# Output EXE file, please only edit the name and no the extension
BINDIR=bin
BIN=$(BINDIR)/Game.exe

# Change to 'x86_64' if compiling on a 64-bit OS
ARCH=i386

# Include dirs for both libs and headers
LIBINCLUDES=-L$(ARCH)/SDL2/lib
INCLUDES=-I$(ARCH)/SDL2/include

# Library linker flags for SDL2
LIBS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

# Extra flags to specify how the CC command should compile our code (add -fPIC later)
FLAGS=-Wall -O2 -g3

.PHONY: all
all: clean build

.PHONY: build
build:
	$(CC) $(SRC) -o $(BIN) $(FLAGS) $(INCLUDES) $(LIBINCLUDES) $(LIBS)
	$(CP) $(ARCH)/SDL2/bin/*.dll $(BINDIR)

.PHONY: clean
clean:
	$(RM) $(BIN)
	$(RM) $(BINDIR)/*.dll
	