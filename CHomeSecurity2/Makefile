hs: hs.o hs_util.o
	gcc  -g  -o hs hs.o hs_util.o

hs.o: hs.c
	gcc  -g  -c hs.c

hs_util.o: hs_util.c hs_util.h
	gcc -g  -c hs_util.c

	
clean:
	rm *.o
	
