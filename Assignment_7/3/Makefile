all: clean client

mkdisplaylib:
	gcc -fPIC -shared display.c -o libdisplay.so

client: mkdisplaylib
	gcc -o client client.c

clean:
	rm -rf *.so *.o client
