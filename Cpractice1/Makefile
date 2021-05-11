HEADERS = cpractice1.h unit_tests.h

default: test

test:	cpractice1.o unit_tests.o
	gcc -o test -g cpractice1.o unit_tests.o
	
cpractice1.o: cpractice1.c $(HEADERS)
	gcc -c -g -Wall cpractice1.c

unit_tests.o: unit_tests.c $(HEADERS)
	gcc -c -g -Wall unit_tests.c

clean:
	-rm -f cpractice1.o
	-rm -f unit_tests.o
	-rm -f test
	
