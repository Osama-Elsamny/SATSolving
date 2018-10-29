#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include "string.h"
#include "inputOutput.h"

/** 
 * Funcition name: header_read
 * Purpose: Reads the variable and clause count from the 
 *          input file
 * Developer: Osama Elsamny
 * Input: "file_name", the name of the input file
 * Output: "v_num", the number of variables.
 *         "c_num", the number of clauses.
 *         "l_num", the number of liters need to create an array
*/
void header_read(char* file_name, int *v_num, int *c_num, int *l_num){
    FILE *inputFile = NULL;
    char *word = NULL;
    inputFile = fopen(file_name,"r");
    if(inputFile == NULL){
        printf("HEADER_READ - Input file failed to open\n");
        exit(1);
    }
    word = (char*)malloc(MAX_STRING_SIZE * sizeof(char));
    fscanf(inputFile, "%s", word); //skip
    fscanf(inputFile, "%s", word); //skip
    fscanf(inputFile, "%s", word);
    *v_num = atoi(word);
    if((*v_num >= 1024) || (*v_num <= 0)){
        printf("HEADER_READ - Invalid numbers of variables\n");
        exit(1);
    }
    fscanf(inputFile, "%s", word);
    *c_num = atoi(word);
    if((*c_num >= 1024) || (*c_num <= 0)){
        printf("HEADER_READ - Invalid numbers of variables\n");
        exit(1);
    }
    while(!feof(inputFile)){
        fscanf(inputFile, "%s", word);
        if((spaceCheck(word)) || (atoi(word) == 0))
            continue;
        *l_num += 1;
    }
    free(word);
    fclose(inputFile);
}

/** 
 * Funcition name: data_read
 * Purpose: Reads the data from the input file
 * Developer: Osama Elsamny
 * Input: "file_name", the name of the input file.
 *        "c_num", the number of clauses. 
 *        "l_num", the number of literals.
 * Output: "clauses", an array with all the clauses.
 *         "literalPerClause", an array with the number of 
 *          literal per clause order based on the clauses. 
*/
void data_read(char* file_name, int c_num, int l_num, int clauses[], int literalPerClause[]){
    FILE *inputFile = NULL;
    char *word = NULL;
    int skip = 4;
    int savedLiterals = 0;
    int count = 0;
    int savedClauses = 0;

    inputFile = fopen(file_name,"r");
    if(inputFile == NULL){
        printf("DATA_READ - Input file failed to open\n");
        exit(1);
    }
    word = (char*)malloc(MAX_STRING_SIZE * sizeof(char));
    for(int i = 0; i < skip; i++){
        fscanf(inputFile, "%s", word);
    }
    while(!feof(inputFile)){
        fscanf(inputFile, "%s", word);
        if((spaceCheck(word)) || (atoi(word) == 0)){
            if(atoi(word) == 0){
                literalPerClause[savedClauses] = count;
                count = 0;
                savedClauses++;
            }
            continue;
        }
        clauses[savedLiterals] = atoi(word);
        savedLiterals++;
        count++;
    }
    if(l_num != savedLiterals){
        printf("DATA_READ - The number of clauses faild to be equal to the number given in the header\n");
        exit(1);
    }
    if(c_num != savedClauses){
        printf("DATA_READ - The number of literals per clauses faild to be equal to the number given in the header\n");
        exit(1);
    }
    free(word);
    fclose(inputFile);
}

/** 
 * Funcition name: spaceCheck
 * Purpose: To check if the given string is a white-space
 * Developer: Osama Elsamny
 * Input: word, the string to be tested
 * Output: boolean with a the result of the test
*/
bool spaceCheck(char* word){
    return (strcmp(word, " ") == 0) || (strcmp(word, "\t") == 0) || (strcmp(word, "\n") == 0) || (strcmp(word, "\v") == 0) || (strcmp(word, "\f") == 0) || (strcmp(word, "\r") == 0);
}