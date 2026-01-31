CC = gcc
CFLAGS = -fPIC -Wall
LDFLAGS = -L.

all: client

mkhelperlib:
	$(CC) $(CFLAGS) -shared -o libhelper.so helper.c

mkperfectlib: mkhelperlib
	$(CC) $(CFLAGS) -shared -o libperfect.so perfect.c -L. -lhelper

client: mkperfectlib
	$(CC) -o client client.c -L. -lperfect -lhelper

clean:
	rm -rf *.so *.o client

