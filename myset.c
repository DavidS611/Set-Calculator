#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "set.h"

#define FOREVER for(;;) /* infinite loop*/
/* A macro that returns false every time the substring's first letters are equal to one of the set names.*/
#define SET_MACRO(substring) \
            strncmp(substring, "SETA", strlen("SETA"))!=0 && \
            strncmp(substring, "SETB", strlen("SETB"))!=0 && \
            strncmp(substring, "SETC", strlen("SETC"))!=0 && \
            strncmp(substring, "SETD", strlen("SETD"))!=0 && \
            strncmp(substring, "SETE", strlen("SETE"))!=0 && \
            strncmp(substring, "SETF", strlen("SETF"))!=0
/* A macro that returns false every time the substring's first letters are equal to one of the command names: 'union_set', 'sub_set', 'intersect_set' or 'symdiff_set'.*/
#define COMMAND_MACRO(substring) \
            strncmp(substring, "union_set", strlen("union_set"))!=0 && \
            strncmp(substring, "sub_set", strlen("sub_set"))!=0 &&     \
            strncmp(substring, "symdiff_set", strlen("symdiff_set"))!=0 && \
            strncmp(substring, "intersect_set", strlen("intersect_set"))!=0

#define WELCOME_MESSAGE \
    printf("\t\t---------------------------------------------------\n"); \
    printf("\t\t\tWelcome to the SET CALCULATOR:\n"); \
    printf("\t\t---------------------------------------------------\n"); \
    printf("There are seven possible groups from 'SETA' to 'SETF' that can be filled with numbers between zero and 127.\n"); \
    printf("\t1. The calculator can be stopped immediately by using the 'stop' action or EOF.\n"); \
    printf("\t2. There is a 'read_set' action to read numbers into a particular set group.\n"); \
    printf("\t   Numbers must be positive and at the end of the read action should be the number -1,\n"); \
    printf("\t   and each number should be separated by a comma. (e.g. \"read_set SETA, 3, 1, 22, -1\").\n"); \
    printf("\t3. A print action is provided, 'print_set' followed by the set name.\n"); \
    printf("\t   This prints all numbers inserted into the group, up to sixteen numbers per line.\n"); \
    printf("\t4. You can also perform group manipulation using union with 'union_set', subtraction with 'sub_set',\n"); \
    printf("\t   intersection with 'intersect_set', and symmetrical difference with 'symdiff_set'.\n"); \
    printf("\t   Each must be followed by three set-groups, separated by a comma.\n"); \
    printf("\nBy pressing the enter key, you can enter orders one after another in the calculator.\n"); \
    printf("You can use whitespace as you wish. However, additional text or commas are not allowed.\n"); \
    printf("GOOD LUCK & HAVE FUN.\n\n")

enum error{ERROR = -1, NO_ERROR};

/* Prototype declarations*/
SET *setIdentifier(char *setString);
void commandLine();
int errorHandling(char commandLine[], char commandName[]);
int validNumber(char *pointerNumbers);

/**************************__________MAIN__________**************************/
int main(){
    WELCOME_MESSAGE;
    commandLine();
    return 0;
}
/*_____________________________________________________________________________*/

/************************__________COMMAND_LINE__________************************/
int errorHandling(char commandLine[], char commandName[]){
    int i=0, commaFlag=1, whitespaceFlag=1, numFlag=1;
    char *substring = commandLine;
    /* error check for 'stop' command*/
    if(strcmp(commandName, "stop")==0){
        /*checks if there is nothing before the stop command*/
        for(i=0; strncmp(substring+i, "stop", strlen("stop"))!=0; i++){
            if(isspace(substring[i])==0){
                printf("Unknown chars before command\n");
                return ERROR;
            }
        }
        substring = strstr(commandLine, "stop") + strlen("stop"); /* substring after "stop" letters*/
        /* checks for any characters other than whitespaces after the stop command*/
        for(i=0; substring[i] != '\0'; i++){
            if(isspace(substring[i])==0){
                printf("Extraneous text after end of command\n");
                return ERROR;
            }
        }
    }
    /* error check for 'read_set' command*/
    else if(strcmp(commandName, "read_set")==0){
        /*checks if there are no characters before the command other than whitespace*/
        for(i=0; strncmp(substring+i, "read_set", strlen("read_set"))!=0; i++){
            if(isspace(substring[i])==0){
                printf("Unknown chars before command\n");
                return ERROR;
            }
        }
        substring = strstr(commandLine, "read_set") + strlen("read_set"); /* substring points after read_set*/
        /* check if there is at least one space between the command name and the set name without additional letters.*/
        for(i=0; SET_MACRO(substring+i) && substring[i]!='\0'; i++){
            if(isspace(substring[i])!=0){
                whitespaceFlag = 0;
            }
            if (substring[i] == ',') {
                printf("Illegal comma\n");
                return ERROR;
            }
            if (isspace(substring[i]) == 0) {
                printf("Undefiled set name\n");
                return ERROR;
            }
        }
        if(whitespaceFlag){ /* if there is no whitespace between command name and set name*/
            printf("Missing whitespace\n");
            return ERROR;
        }
        substring = strstr(substring, "SET"); /* substring points to set name*/
        /*checks set name*/
        if(substring == NULL){
            printf("Missing parameter\n");
            return ERROR;
        }
        substring = substring + strlen("SET?"); /* substring points after set name*/
        /* checking if there is nothing between set name and first comma except whitespaces*/
        for(i=0; substring+i!= strchr(substring, ','); i++){
            if(isspace(substring[i])==0){
                printf("Missing comma\n");
                return ERROR;
            }
        }
        /*checks -1 at the end and no more chars after it except for whitespaces*/
        substring = strstr(commandLine, "-1"); /* substring points to first appearance of "-1"*/
        if(substring==NULL){
            printf("List of set members is not terminated correctly\n");
            return ERROR;
        }
        substring = strstr(commandLine, ","); /* substring points to the first comma*/

        /* checks if there is a number out of range*/
        if(validNumber(substring+1)==ERROR) { /* substring+1 points after the first comma*/
            printf("Invalid set member – value out of range\n");
            return ERROR;
        }

        /* checks if there is an invalid char inside the number, and if there is an empty number, and if there is a number that is separated by whitespace*/
        for(i=0, commaFlag=1; substring[i]!='\0' && strncmp(substring+i, "-1", strlen("-1"))!=0; i++){
            /* if char is punctuation or alphabetic except for comma*/
            if((ispunct(substring[i]) || isalpha(substring[i])) && substring[i]!=','){
                printf("Invalid set member – not an integer\n");
                return ERROR;
            }
            /* turn off numFlag turn on comma flag ,check if there are commas separated by whitespaces*/
            if(commaFlag && substring[i]==','){
                numFlag=1;
                commaFlag = 0;
                continue;
            }
            /* turn off commaFlag turn on numFlag, check if there are numbers that are separated by whitespaces*/
            if(numFlag && isdigit(substring[i])){
                commaFlag=1;
                numFlag=0;
                continue;
            }
            /* commas that seperated only by whitespaces*/
            if(commaFlag==0 && substring[i]==','){
                printf("Missing number\n");
                return ERROR;
            }
            /* numbers separated only by whitespaces*/
            if(numFlag==0 && isdigit(substring[i]) && isspace(substring[i-1])){
                printf("Missing comma\n");
                return ERROR;
            }
        }
        /* checks if there are no other characters after the end of the command other than whitespaces*/
        substring = strstr(commandLine, "-1") + strlen("-1"); /* substring points after "-1" chars*/
        for(i=0; substring[i]!='\0'; i++){
            if(isspace(substring[i])==0){
                printf("Extraneous text after end of command\n");
                return ERROR;
            }
        }
    }
    /* error check for 'print_set' command*/
    else if(strcmp(commandName, "print_set")==0){
        /*checks if there is nothing before the print_set command other than whitespaces*/
        for (i = 0; strncmp(substring + i, "print_set", strlen("print_set")) != 0 && substring[i] != '\0'; i++) {
            if (isspace(substring[i]) == 0) {
                printf("Unknown chars before command name\n");
                return ERROR;
            }
        } /* checks if there is nothing before the command name except whitespaces*/
        substring = strstr(commandLine, "print_set") + strlen("print_set"); /* substring points after print_set on the command line*/
        /* check if there is at least one space between the command name and the set name without additional letters.*/
        for(i=0; SET_MACRO(substring+i) && substring[i]!='\0'; i++){
            if(isspace(substring[i])!=0){
                whitespaceFlag = 0;
            }
            if (substring[i] == ',') {
                printf("Illegal comma\n");
                return ERROR;
            }
            if (isspace(substring[i]) == 0) {
                printf("Undefiled set name\n");
                return ERROR;
            }
        }
        if(whitespaceFlag){ /* if there is no whitespace between command name and set name*/
            printf("Missing whitespace\n");
            return ERROR;
        }
        substring = strstr(substring, "SET"); /* substring points to SET on the command line*/
        /*checks set name*/
        if(substring == NULL){
            printf("Missing parameter\n");
            return ERROR;
        }
        substring = substring + strlen("SET?"); /* substring points after set name*/
        /* checks if there is nothing after set name*/
        for(i=0; substring[i]!='\0'; i++){
            if(isspace(substring[i])==0){
                printf("Extraneous text after end of command\n");
                return ERROR;
            }
        }
    }
    /* error check for 'union_set'/'sub_set'/'intersect_set'/'symdiff_set' commands*/
    else if(strcmp(commandName, "union_set")==0 || strcmp(commandName, "sub_set")==0 || strcmp(commandName, "intersect_set")==0 || strcmp(commandName, "symdiff_set")==0){
        /*checks if there are no other characters before the command name except whitespaces*/
        for(i=0; COMMAND_MACRO(substring+i) && substring[i]!='\0'; i++){
            if (isspace(substring[i]) == 0) {
                printf("Unknown chars before command name\n");
                return ERROR;
            }
        }

        /* substring points after command name*/
        if(strstr(commandLine, "union_set")!=NULL)
            substring = strstr(commandLine, "union_set") + strlen("union_set");
        else if(strstr(commandLine, "sub_set")!=NULL)
            substring = strstr(commandLine, "sub_set") + strlen("sub_set");
        else if(strstr(commandLine, "intersect_set")!=NULL)
            substring = strstr(commandLine, "intersect_set") + strlen("intersect_set");
        else
            substring = strstr(commandLine, "symdiff_set") + strlen("symdiff_set");

        /* checks if there are no other characters between command name and first set name other than whitespaces*/
        for(i=0; SET_MACRO(substring+i) && substring[i]!='\0'; i++){
            /* checks if there is at least one whitespace after command name and before set1 name*/
            if(whitespaceFlag && isspace(substring[i])!=0){
                whitespaceFlag = 0;
            }
            if(substring[i]==','){
                printf("Illegal comma\n");
                return ERROR;
            }
            if(isspace(substring[i])==0){
                printf("Undefined set name\n");
                return ERROR;
            }
        }
        /* if there is no white space between command name and set name*/
        if(whitespaceFlag){
            printf("Missing whitespace\n");
            return ERROR;
        }

        /* +if there is no set name, error will pop at end of string*/
        if(substring[i]=='\0'){
            printf("Missing parameter\n");
            return ERROR;
        }

        substring = strstr(commandLine, "SET") + strlen("SET?"); /* substring points after first set name*/
        /* checks if there is no other chars between set1 name and set2 name other than whitespaces and one comma*/
        for(i=0; SET_MACRO(substring+i) && substring[i]!='\0'; i++){
            /* checks if there is one comma between set1 name and set2 name*/
            if(commaFlag && substring[i]==','){
                commaFlag = 0;
                continue;
            }
            /* checks there is no chars between set1 and set2*/
            if(isspace(substring[i])==0){
                printf("Undefined set name\n");
                return ERROR;
            }
        }
        /* if there was no comma between set1 and set2*/
        if(commaFlag){
            printf("Missing comma\n");
            return ERROR;
        }
        /* checks if there is a missing parameter*/
        substring = strstr(substring, "SET"); /* substring points to set2*/
        if(substring==NULL){
            printf("Missing parameter\n");
            return ERROR;
        }

        substring = strstr(substring, "SET") + strlen("SET?"); /* substring points after second set name*/
        /* checks if there is no other chars between set2 name and set3 name other than whitespaces and one comma*/
        for(i=0, commaFlag=1; SET_MACRO(substring+i) && substring[i]!='\0'; i++){
            /* checks if there is one comma between set2 name and set3 name*/
            if(commaFlag && substring[i]==','){ /* commaFlag is needed here if there is multiple commas*/
                commaFlag = 0;
                continue;
            }
            /* checks there is no chars between set2 and set3*/
            if(isspace(substring[i])==0){
                printf("Undefined set name\n");
                return ERROR;
            }
        }
        /* if there was no comma between set2 and set3*/
        if(commaFlag){
            printf("Missing comma\n");
            return ERROR;
        }
        substring = strstr(substring, "SET"); /* substring points to set3 name*/
        if(substring==NULL){
            printf("Missing parameter\n");
            return ERROR;
        }
        substring = substring + strlen("SET?"); /* substring points after set3*/

        /* checks if there is no other chars except whitespaces*/
        for(i=0; substring[i]!='\0'; i++){
            if(isspace(substring[i])==0){
                printf("Extraneous text after end of command\n");
                return ERROR;
            }
        }
    }
    return NO_ERROR;
}
/*_____________________________________________________________________________*/

/************************__________COMMAND_LINE__________************************/
void commandLine() {
    int i , commandLineSize=1;
    char c, *substring, s1, s2, *commandLine, *num;
    SET *set1=NULL, *set2=NULL, *set3=NULL;

    printf("prompt~ ");
    FOREVER {
        /* allocating memory for command line*/
        commandLine = (char*) calloc(commandLineSize, sizeof(char));
        if(!commandLine){ /* checks if the allocation failed*/
            printf("Error: out of memory\n");
            continue;
        }
        /* read command line string every new line, EOF - end the program immediately*/
        for (i=0; (c = getchar())!='\n'; i++) {
            commandLine[i] = c;
            if(c==EOF){ /* exit with EOF*/
                free(commandLine);
                commandLine = NULL;
                stop();
            }
            /* enlarge dynamic memory if needed*/
            if (i == commandLineSize) {
                commandLine = realloc(commandLine, commandLineSize * 2 * sizeof(char));
                commandLineSize *= 2;
            }
        }
        commandLine[i]='\0';
        printf("Your input is: %s\n", commandLine);

        /**********************_COMMAND_IDENTIFIER_************************/
        substring = commandLine, i=0;
        /* multi consecutive comma check*/
        if(strstr(commandLine, ",,")){
            printf("Multiple consecutive commas\n");
        }
        /* execution of stop command*/
        else if(strstr(commandLine, "stop")!=NULL){ /* is it stop command*/
            if(errorHandling(commandLine, "stop")==0)
                stop();
        }
        /* execution of read_set command*/
        else if(strstr(commandLine, "read_set")!=NULL){ /* is it read_set command*/
            if(errorHandling(commandLine, "read_set")==NO_ERROR){
                substring = strstr(commandLine, "SET"); /* substring points to set name on command line*/
                set1 = setIdentifier(substring);
                c = substring[3]; /* saving set name*/
                num = substring = strstr(commandLine, ","); /* substring points to the second comma (before first number)*/
                substring = strtok(substring, ","); /* first number*/
                memset(set1, 0, sizeof(SET)); /* initializing set1*/
                for(i=0; substring!=NULL; i++){
                    read_set(*set1, strtol(num+1, &num, 10));
                    substring = strtok(NULL, ",");
                }
                printf("SET%c has been read.\n", c);
            }
        }
        /* execution of print_set command*/
        else if(strstr(commandLine, "print_set")!=NULL) { /* is it print_set command*/
            if(errorHandling(commandLine, "print_set")==NO_ERROR) {
                substring = strstr(commandLine, "SET"); /* substring points to set name*/
                set1 = setIdentifier(substring);
                print_set(set1);
                printf("SET%c has been printed.\n", substring[3]);
            }
        }
        /* execution of union_set command*/
        else if(strstr(commandLine, "union_set")!=NULL){ /* is it union_set command*/
            if(errorHandling(commandLine, "union_set")==NO_ERROR) {
                substring = strstr(commandLine, "SET"); /* points to first set name*/
                s1 = substring[3]; /* saving set1 name*/
                set1 = setIdentifier(substring);
                substring = substring + strlen("SET?"); /* points after set1*/
                substring = strstr(substring, "SET"); /* points to set2 name*/
                s2 = substring[3]; /* saving set2 name*/
                set2 = setIdentifier(substring);
                substring = substring + strlen("SET?"); /* points after set2*/
                substring = strstr(substring, "SET"); /* points to set3 name*/
                set3 = setIdentifier(substring);
                union_set(*set1, *set2, *set3);
                printf("Union SET%c and SET%c inserted into SET%c.\n", s1, s2,substring[3]);
            }
        }
        /* execution of sub_set command*/
        else if(strstr(commandLine, "sub_set")!=NULL){ /* is it sub_set command*/
            if(errorHandling(commandLine, "sub_set")==NO_ERROR) {
                substring = strstr(commandLine, "SET"); /* points to first set name*/
                s1 = substring[3]; /* saving set1 name*/
                set1 = setIdentifier(substring);
                substring = substring + strlen("SET?"); /* points after set1*/
                substring = strstr(substring, "SET"); /* points to set2 name*/
                s2 = substring[3]; /* saving set2 name*/
                set2 = setIdentifier(substring);
                substring = substring + strlen("SET?"); /* points after set2*/
                substring = strstr(substring, "SET"); /* points to set3 name*/
                set3 = setIdentifier(substring);
                sub_set(*set1, *set2, *set3);
                printf("Subtraction of SET%c from SET%c inserted into SET%c.\n", s2, s1,substring[3]);
            }
        }
        /* execution of intersect_set command*/
        else if(strstr(commandLine, "intersect_set")!=NULL){ /* is it intersect_set command */
            if(errorHandling(commandLine, "intersect_set")==NO_ERROR) {
                substring = strstr(commandLine, "SET"); /* points to first set name*/
                s1 = substring[3]; /* saving set1 name*/
                set1 = setIdentifier(substring);
                substring = substring + strlen("SET?"); /* points after set1*/
                substring = strstr(substring, "SET"); /* points to set2 name*/
                s2 = substring[3]; /* saving set2 name*/
                set2 = setIdentifier(substring);
                substring = substring + strlen("SET?"); /* points after set2*/
                substring = strstr(substring, "SET"); /* points to set3 name*/
                set3 = setIdentifier(substring);
                intersect_set(*set1, *set2, *set3);
                printf("Intersection of SET%c and SET%c inserted into SET%c.\n", s1, s2,substring[3]);
            }
        }
        /* execution of symdiff_set command*/
        else if(strstr(commandLine, "symdiff_set")!=NULL){ /* is it symdiff_set command*/
            if(errorHandling(commandLine, "symdiff_set")==NO_ERROR) {
                substring = strstr(commandLine, "SET"); /* points to first set name*/
                s1 = substring[3]; /* saving set1 name*/
                set1 = setIdentifier(substring);
                substring = substring + strlen("SET?"); /* points after set1*/
                substring = strstr(substring, "SET"); /* points to set2 name*/
                s2 = substring[3]; /* saving set2 name*/
                set2 = setIdentifier(substring);
                substring = substring + strlen("SET?"); /* points after set2*/
                substring = strstr(substring, "SET"); /* points to set3 name*/
                set3 = setIdentifier(substring);
                symdiff_set(*set1, *set2, *set3);
                printf("Symmetric difference of SET%c and SET%c inserted into SET%c.\n", s1, s2,substring[3]);
            }
        }
        else /* Command wasn't detected*/{
            printf("Undefined command\n");
        }
        free(commandLine);
        commandLine = NULL;
        printf("\nprompt~ ");
    }
}
/*_____________________________________________________________________________*/

/**************__________SET_IDENTIFIER__________**************/
SET *setIdentifier(char *setName){
    /* static SET variables that preserve their value between function calls*/
    static SET SETA, SETB, SETC, SETD, SETE, SETF;
    unsigned int setLength = 4, len = strlen(setName); /* len = set name length*/

    /* checks if set name length isn't shorter*/
    if(len< strlen("SET?")){
        printf("Undefined set name\n");
        return NULL;
    }
    else if(strncmp(setName, "SETA", setLength)==0) {
        return &SETA;
    }
    else if(strncmp(setName, "SETB", setLength)==0) {
        return &SETB;
    }
    else if(strncmp(setName, "SETC", setLength)==0) {
        return &SETC;
    }
    else if(strncmp(setName, "SETD", setLength)==0) {
        return &SETD;
    }
    else if(strncmp(setName, "SETE", setLength)==0) {
        return &SETE;
    }
    else if(strncmp(setName, "SETF", setLength)==0) {
        return &SETF;
    }
    else
        return NULL;
}
/*_____________________________________________________________________________*/

/* checking if there is a number out of range*/
int validNumber(char *pointerNumbers){ /* pointerNumbers point after the first comma in read_set command*/
    long int num, len = strlen(pointerNumbers);
    char *copyPointerNumbers = malloc(sizeof(char)*len);
    char *crusor;
    strcpy(copyPointerNumbers, pointerNumbers); /* creating a copy of the string numbers*/
    crusor = strtok(copyPointerNumbers, ","); /* first number inside crusor*/
    num = strtol(crusor, NULL, 10); /* first number inside num as a long int*/
    while (crusor!=NULL) {
        num = strtol(crusor, NULL, 10);
        /* if the number inside the string is negative or greater than 127 return and error*/
        if(num<-1 || num>127) {
            free(copyPointerNumbers); /* freeing the memory if there is an invalid number*/
            return ERROR;
        }
        crusor = strtok(NULL, ","); /* next number inside crusor*/
    }
    free(copyPointerNumbers); /* freeing the memory if the numbers are valid*/
    return NO_ERROR;
}