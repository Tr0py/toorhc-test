CC=gcc
CFLAGS= -Wall -Werror -g -O -fPIC
LDFLAGS=-ldl -shared
RM=rm -f

.PHONY: all clean

all: libfile.so


libfile.so: libfile.o iv.o
	$(CC) -o $@ $^ $(LDFLAGS)

libfile.o: libfile.c libfile.h

clean:
	$(RM) *.o *.so