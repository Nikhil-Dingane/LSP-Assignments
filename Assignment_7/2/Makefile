all: clean client

mkadditionlib:
	gcc -fPIC -shared addition.c -o libaddition.so

mksubstractionlib:
	gcc -fPIC -shared substraction.c -o libsubstraction.so

client: mkadditionlib mksubstractionlib
	gcc -o client client.c

clean:
	rm -rf *.so *.o client
