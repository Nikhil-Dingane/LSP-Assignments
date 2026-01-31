all: clean client

mkmystrlenlib:
	gcc -fPIC -shared mystrlen.c -o libmystrlen.so

client: mkmystrlenlib
	gcc -o client client.c

clean:
	rm -rf *.so *.o client
