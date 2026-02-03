CC = gcc
CFLAGS = -Wall -Wextra -O2
SRC = main.c

all:
	$(CC) $(CFLAGS) $(SRC) -o main
run:
	./main
clean:
	rm -f *.o main
help:
	@echo "Usage:"
	@echo "  make        -> build the program"
	@echo "  make run    -> run the program"
	@echo "  make clean  -> remove build files"
