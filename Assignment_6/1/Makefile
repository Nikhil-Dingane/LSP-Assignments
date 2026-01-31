all: clean mklib client

mklib:
	gcc -o server.o -c server.c
	gcc -fPIC -shared -o libserver.so server.o

client: 
	gcc -o client client.c
clean:
	rm -rf *.so *.o client
