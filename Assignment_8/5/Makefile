CC = gcc
AR = ar

CFLAGS = -Wall -Wextra -O2

LIB_SRC = $(wildcard lib_src/*.c)
LIB_OBJ = $(LIB_SRC:.c=.o)

LIB = libmath.a
TARGET = main

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(LIB) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) -L. -lmath

$(LIB): $(LIB_OBJ)
	$(AR) rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	@./$(TARGET)
clean:
	rm -f $(OBJ) $(TARGET) $(LIB) $(LIB_OBJ)
help:
	@echo "Usage:"
	@echo "  make        -> build the program"
	@echo "  make run    -> run the program"
	@echo "  make clean  -> remove build files"
