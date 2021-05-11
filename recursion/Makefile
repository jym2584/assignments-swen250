test: tests.o recurse.o
	gcc -g -o test tests.o recurse.o

tests.o: tests.c recurse.h
	gcc -g -c tests.c

recurse.o: recurse.c recurse.h
	gcc -g -c recurse.c
	 
clean:
	rm -f tests tests.exe
	rm -f *.o *.bak *~*
