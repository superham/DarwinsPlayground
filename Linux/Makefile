CC=gcc
RM=rm -rf

BINDIR=../bin
BIN=$(BINDIR)/DarwinsPlayground.elf

SRC=../src/*.c

LIBS=-lm -lSDL2 -lSDL2_image -lSDL2_ttf
INCS=-I../include
FLAGS=-Wall -fPIC -O2 -g3

.PHONY: all
all: clean build

.PHONY: build
build:
    $(CC) $(SRC) -o $(BIN) $(FLAGS) $(INCS) $(LIBS)
    
.PHONY: clean
clean:
    $(RM) $(BIN) $(BINDIR)/*.exe $(BINDIR)/*.dll
