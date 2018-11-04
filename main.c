#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>
#include <math.h>
#include "string.h"
#include "inputOutput.h"
#include "backTrackSearch.h"


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
    if(head->status == false){
        printf("No solution\n");
    }else{
        printf("Solution is:\n");
        for(int i = 0; i < variablesNum; i++){
            printf("X%d is, ",i +1);
            if(solutionNode->guessUntillNode[i]){
                printf("1\t");
            }else{
                printf("0\t");
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}
/** 
 * Funcition name:
 * Purpose: 
 * Developer:
 * Input: 
 * Output: 
*/