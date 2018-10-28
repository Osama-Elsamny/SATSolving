#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>
#include <math.h>
#include "string.h"
#include "inputOutput.h"

int main(int argc, char* argv[]){
    int variablesNum = 0;
    int clauseNum = 0;
    header_read(argv[1], &variablesNum, &clauseNum);
    int clauses[3 * clauseNum];
    data_read(argv[1], clauseNum, clauses);
    return 0;
}
/** 
 * Funcition name:
 * Purpose: 
 * Developer:
 * Input: 
 * Output: 
*/