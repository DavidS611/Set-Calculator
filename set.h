#ifndef SET_H
#define SET_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BITS 128 /* total bits of a set / total numbers between 0 and 127*/
#define BYTE_SIZE 8 /* size of one byte of a set in bits*/


typedef char SET[BITS/BYTE_SIZE];

/* Function that checks if the number is inside the given set.
    Returns 1 if the number is inside the set, otherwise returns 0.
    @param SET - the set from SETA to SETF
    @param num - the number we want to check to see if it's in the set*/
int bit_check(const SET SET, long int num);

/* Function that reads a particular number into a set.
    In other words, it sets the bit that represents the number - on.
    @param SET - the set from SETA to SETF
    @param number - the number to put inside the set */
void read_set(SET SET,  long int number);

/* Function that prints all the numbers in the set from 0 to 127.
    If the set is empty, it prints a message.
    @param SET - pointer to the set from SETA to SETF*/
void print_set(SET *SET);

/* Function that unions SET1 numbers with SET2 numbers into result_set
    @param SET1 - the first set
    @param SET2 - the second set
    @param result_set - the third set */
void union_set(SET SET1, SET SET2, SET result_set);

/* Function that intersects SET1 numbers with SET2 numbers into result_set
    @param SET1 - the first set
    @param SET2 - the second set
    @param result_set - the third set*/
void intersect_set(SET SET1, SET SET2, SET result_set);

/* Function that subtracts numbers from SET2 with numbers from SET1 into result_set
    @param SET1 - the first set
    @param SET2 - the second set
    @param result_set - the third set*/
void sub_set(SET SET1, SET SET2, SET result_set);

/* Function that symmetric difference numbers from SET1 and numbers from SET2 into result_set
    @param SET1 - the first set
    @param SET2 - the second set
    @param result_set - the third set*/
void symdiff_set(SET SET1, SET SET2, SET result_set);

/* Function that stops the calculator*/
void stop();


#endif
