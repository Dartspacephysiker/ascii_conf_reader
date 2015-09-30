# ---------------------------------------------------------------------------
# Makefile - Please don't hurt 'em, Hammer
# ---------------------------------------------------------------------------

SRC_DIR=./
CFLAGS=-D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -ggdb -fpack-struct=1
LDFLAGS = -pipe -Wall

CC = gcc

EXEC= ascii_conf_reader_example
SRC = ascii_conf_reader_example.c
OBJ = $(SRC:.c=.o)
HEADERS = ascii_conf_reader.h ascii_conf_reader_example.h ascii_conf_reader_example_structs.h

all: $(SRC) $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $(LDFLAGS) $?

.c.o: $(HEADERS)
	$(CC) -o $@ $(CFLAGS) -c $?

.PHONY: clean

clean:
	rm ascii_conf_reader_example *.o 
