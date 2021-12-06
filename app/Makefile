CC=gcc
CFLAGS=-Wall -Werror -g -O  -I../lib
LDFLAGS=-lfile -L=../lib
BIN=app

.PHONY: all clean

all: $(BIN)

app: app.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

app.o: app.c

run: app
	LD_LIBRARY_PATH=../lib ./app $(FILE)

ivrun: app
	LD_LIBRARY_PATH=../lib ~/IV ~/glibc ./app $(FILE)

gdb: app
	LD_LIBRARY_PATH=../lib gdb --args ~/IV ~/glibc ./app $(FILE)

clean: 
	rm -f *.o $(BIN) 