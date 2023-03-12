#Define which compiler to use
CC = gcc
#Define which compiler flags to use.
CFLAGS = -g -Wall -ansi -pedantic


a.out: myset.o
	$(CC) $(CFLAGS) myset.o set.o -o a.out

myset.o: myset.c set.c
	$(CC) $(CFLAGS) -c myset.c set.c

output:
	./a.out < mamanTest > mamanOutput
	./a.out < readTest > readOutput
	./a.out < printTest > printOutput
	./a.out < groupFunctionsTest > groupFunctionsOutput
clean:
	rm  a.out -f *Output -f *.o
