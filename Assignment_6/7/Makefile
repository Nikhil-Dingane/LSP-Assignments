all: clean mklib client

mklib:
	gcc -fPIC -shared -o libserver.so server.c

client:
	gcc -o client client.c

clean:
	rm -f *.o client *.so
