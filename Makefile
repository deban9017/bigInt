UltraIntLib.so : ultra.c
	gcc -O3 -shared -fPIC -o UltraIntLib.so ultra.c
clean:
	rm -f UltraIntLib.so