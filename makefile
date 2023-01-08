#Define which compiler to use
CC = gcc
#Define which compiler flags to use.
CFLAGS = -g -Wall -ansi -pedantic


a.out: myset.o
	$(CC) $(CFLAGS) myset.o set.o -o a.out

myset.o: myset.c set.c
	$(CC) $(CFLAGS) -c myset.c set.c

output:
	./a.out < test > output
	./a.out < readTest > readOutput
	./a.out < printTest > printOutput
	./a.out < groupTest > groupOutput
clean:
	rm readOutput a.out -f *.o
