all: clean client

mkmystringlib:
	gcc -fPIC -shared mystring.c -o libmystring.so

mkmymathlib:
	gcc -fPIC -shared mymath.c -o libmymath.so

client: mkmystringlib mkmymathlib
	gcc -o client client.c -L. -lmystring -lmymath

clean:
	rm -rf *.so *.o client
