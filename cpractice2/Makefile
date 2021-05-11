HEADERS = cpractice2.h unit_tests.h

default: test

test:	main.o cpractice2.o unit_tests.o
	gcc -g -o test main.o cpractice2.o unit_tests.o
	
cpractice1.o: cpractice2.c $(HEADERS)
	gcc -Wall -g -c cpractice2.c

main.o: main.c $(HEADERS)
	gcc -Wall -g -c main.c
	
unit_tests.o: unit_tests.c $(HEADERS)
	gcc -Wall -g -c unit_tests.c

clean:
	-rm -f cpractice2.o
	-rm -f main.o
	-rm -f unit_tests.o
	-rm -f test
	
