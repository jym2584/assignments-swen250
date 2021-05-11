test_pointers: main.o read_data.o
	gcc -o test_pointers -g main.o read_data.o
main.o: main.c read_data.h
	gcc -c -g -Wall main.c
read_data.o: read_data.c read_data.h
	gcc -c -g -Wall read_data.c
clean:
	rm test_pointers
	rm main.o
	rm read_data.o

