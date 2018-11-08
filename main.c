#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>
#include <math.h>
#include "string.h"
#include "inputOutput.h"

#define THREAD_NUM 4

typedef struct{
    int id;
    int variablesNum;
    int clauseNum;
    int* literalPerClause;
    int* clauses;
    Node* head;
    Node* solutionNode;
}Args;

/** 
 * Funcition name:
 * Purpose: 
 * Developer:
 * Input: 
 * Output: 
*/
void* threadFunc(void* arg){
    Args *input = (Args *) arg;
    input->solutionNode = getSolution(input->head, input->variablesNum, input->clauseNum, input->literalPerClause, input->clauses);
    return NULL;
}

/** 
 * Funcition name:
 * Purpose: 
 * Developer:
 * Input: 
 * Output: 
*/
void initializeThreadArg(Args **input, Node *node, int lastLevel, int clauseNum,  int literalPerClause[], int clauses[]){
    for(int i = 0; i < THREAD_NUM; i++){
        input[i] = (Args*) malloc(sizeof(Args));
        input[i]->head = node;
        input[i]->id = i;
        input[i]->variablesNum = lastLevel;
        input[i]->clauseNum = clauseNum;
        input[i]->literalPerClause = literalPerClause;
        input[i]->clauses = clauses;
        input[i]->solutionNode = NULL;
    }
}

/** 
 * Funcition name:
 * Purpose: 
 * Developer:
 * Input: 
 * Output: 
*/
void setup4threads(Node* node, Args **input){
    Node* right = getInitializedNode(node->level + 1);
    Node* left = getInitializedNode(node->level + 1);
    addLeft(node, left);
    addRight(node, right);
    Node* right1 = getInitializedNode(node->level + 2);
    Node* left1 = getInitializedNode(node->level + 2);
    addLeft(node->right, left1);
    addRight(node->right, right1);
    input[3]->head = node->right->right;
    input[2]->head = node->right->left;
    Node* right2 = getInitializedNode(node->level + 2);
    Node* left2 = getInitializedNode(node->level + 2);
    addLeft(node->left, left2);
    addRight(node->left, right2);
    input[1]->head = node->left->right;
    input[0]->head = node->left->left;
}

int main(int argc, char* argv[]){
    int variablesNum = 0;
    int clauseNum = 0;
    int literalNum = 0;
    pthread_t threads[THREAD_NUM];
    Args *threadsArgs[THREAD_NUM];
    Node *solutionNode = NULL;

    Node *head = getInitializedNode(0);
    header_read(argv[1], &variablesNum, &clauseNum, &literalNum);
    int clauses[literalNum];
    int literalPerClause[clauseNum];
    data_read(argv[1], clauseNum, literalNum, clauses, literalPerClause);
    
    initializeThreadArg(threadsArgs, head, variablesNum, clauseNum, literalPerClause, clauses);
    if(variablesNum > 2){
        setup4threads(head, threadsArgs);
    }else{
        solutionNode = getSolution(head, variablesNum, clauseNum, literalPerClause, clauses);
        printSolution(solutionNode, head, variablesNum);
        return 1;
    }
    for(int i = 0; i < THREAD_NUM; i++){
        pthread_create(&threads[i], NULL, threadFunc, (void *) threadsArgs[i]);
    }
    for(int i = 0; i < THREAD_NUM; i++){
        pthread_join(threads[i], NULL);
        printf("With Thread_id %d ", threadsArgs[i]->id);
        printSolution(threadsArgs[i]->solutionNode, threadsArgs[i]->head, variablesNum);
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