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
    int literalNum = 0;
    Node *solutionNode = NULL;
    Node *head = getInitializedNode(0);
    header_read(argv[1], &variablesNum, &clauseNum, &literalNum);
    int clauses[literalNum];
    int literalPerClause[clauseNum];
    data_read(argv[1], clauseNum, literalNum, clauses, literalPerClause);
    solutionNode = getSolution(head, variablesNum, clauseNum, literalPerClause, clauses);
    printSolution(solutionNode, head, variablesNum);
    return 0;
}
/** 
 * Funcition name:
 * Purpose: 
 * Developer:
 * Input: 
 * Output: 
*/