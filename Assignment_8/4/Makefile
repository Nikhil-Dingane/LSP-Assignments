CC = gcc
CFLAGS = -Wall -Wextra -O2
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
run: $(TARGET)
	@./$(TARGET)
clean:
	rm -f $(OBJ) $(TARGET)
help:
	@echo "Usage:"
	@echo "  make        -> build the program"
	@echo "  make run    -> run the program"
	@echo "  make clean  -> remove build files"
