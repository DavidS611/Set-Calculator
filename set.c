
#include "set.h"

void read_set(SET set, long int num){
    set[num/BYTE_SIZE] |= 1<<(num%BYTE_SIZE);
}

int bit_check(const SET s, long int num){
    return (s[num/BYTE_SIZE] & (1<<(num%BYTE_SIZE)))? 1: 0;
}

void print_set(SET *set){
    int num=0, numsInLineCounter=0, lineNumber=0;
    /* print all numbers between 0 and 127 that are inside the set*/
    while(num<BITS){
        if(bit_check(*set, num))
        {
            printf("%d\t", num);
            numsInLineCounter++;
        }
        if(numsInLineCounter == 16){ /* max number per line check*/
            printf("\n");
            numsInLineCounter = 0;
            lineNumber++;
        }
        num++;
    }
    /* if it's first line and no numbers have been counted the set is empty*/
    if(lineNumber == 0 && numsInLineCounter == 0)
        printf("this set is empty");
    putchar('\n');
}

void union_set(SET SET1, SET SET2, SET SET1_union_SET2){
    int num;
    SET tmp1;
    memmove(tmp1, SET1, sizeof(SET));
    memmove(SET1_union_SET2, SET2, sizeof(SET)); /* initializing SET1_union_SET with SET2 numbers*/
    for(num=0; num<BITS ; num++) {
        /* adding SET1 numbers to SET1_union_SET2*/
        if(bit_check(tmp1,num))
            read_set(SET1_union_SET2,num);
    }
}

void intersect_set(SET SET1, SET SET2, SET SET1_intersect_SET2){
    int i;
    SET tmp1, tmp2;
    memmove(tmp1, SET1, sizeof(SET));
    memmove(tmp2, SET2, sizeof(SET));
    memset(SET1_intersect_SET2, 0, sizeof(SET)); /* initialize set*/
    /* reads tmp1 (SET1) and tmp2 (SET2) common numbers to SET1_symdiff_SET2*/
    for(i=0; i<BITS; i++){
        if(bit_check(tmp1, i) && bit_check(tmp2, i))
            read_set(SET1_intersect_SET2, i);
    }
}

void sub_set(SET SET1, SET SET2, SET SET1_sub_SET2){
    int i;
    SET tmp1, tmp2;
    memmove(tmp1, SET1, sizeof(SET));
    memmove(tmp2, SET2, sizeof(SET));
    memset(SET1_sub_SET2, 0, sizeof(SET)); /* initialize set*/
    /* reads tmp1 (SET1) numbers to SET1_sub_SET2 set if tmp2 (SET2) set doesn't have those numbers*/
    for(i=0; i<BITS; i++){
        if(bit_check(tmp1, i) && !bit_check(tmp2, i))
            read_set(SET1_sub_SET2, i);
    }
}

void symdiff_set(SET SET1, SET SET2, SET SET1_symdiff_SET2){
    int num;
    SET tmp1, tmp2;
    memmove(tmp1, SET1, sizeof(SET));
    memmove(tmp2, SET2, sizeof(SET));
    memset(SET1_symdiff_SET2, 0, sizeof(SET)); /* initialize set*/
    /* reads tmp1 (SET1) and tmp2 (SET2) numbers to SET1_symdiff_SET2 without tmp1 and tmp2 common numbers*/
    for(num=0; num<BITS ; num++){
        if((bit_check(tmp1, num) && !bit_check(tmp2,num)) || (!bit_check(tmp1,num) && bit_check(tmp2, num)))
            read_set(SET1_symdiff_SET2, num);
    }
}

void stop(){
    printf("Calculator shutdown.\n");
    exit(EXIT_SUCCESS);
}
