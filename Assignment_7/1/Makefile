all: client

mkhelperlib:
	gcc -fPIC -shared -o libhelper.so helper.c

mkperfectlib: mkhelperlib
	gcc -fPIC -shared -o libperfect.so perfect.c

client: mkperfectlib
	gcc -o client client.c -L. -lperfect -lhelper

clean:
	rm -rf *.so *.o client

