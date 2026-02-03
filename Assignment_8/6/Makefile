CC = gcc

CFLAGS = -Wall -Wextra -O2
LIBFLAGS = -fPIC -shared

LIB_SRC = $(wildcard lib_src/*.c)
LIB_OBJ = $(LIB_SRC:.c=.o)

LIB = libmath.so
TARGET = main

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(LIB) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) -L. -lmath

$(LIB): $(LIB_OBJ)
	$(CC) $(CFLAGS) $(LIBFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	@LD_LIBRARY_PATH=. ./$(TARGET)
clean:
	rm -f $(OBJ) $(TARGET) $(LIB) $(LIB_OBJ)
help:
	@echo "Usage:"
	@echo "  make        -> build the program"
	@echo "  make run    -> run the program"
	@echo "  make clean  -> remove build files"
