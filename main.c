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
#include "linkList.h"

#define THREAD_NUM 4

typedef struct{
    int id;
    int variablesNum;
    int clauseNum;
    int* literalPerClause;
    int* clauses;
    volatile bool threadStatus;
    Node* head;
    Node* solutionNode;
}Args;

/** 
 * Funcition name: threadFunc
 * Purpose: Calls the get soltuion function in order to solve the back tracking 
 * Developer: Osama Elsamny
 * Input: "arg", the specific input that corresponds to a specific thread
 * Output: N/A
*/
void* threadFunc(void* arg){
    Args *input = (Args *) arg;
    input->solutionNode = getSolution(input->head, input->variablesNum, input->clauseNum, input->literalPerClause, input->clauses);
    input->threadStatus = true;
    return NULL;
}

/** 
 * Funcition name: initializeThreadArg
 * Purpose: initialize the thread arguments
 * Developer: Osama Elsamny
 * Input: "Node", the tree head
 *        "lastLevel", which is the hight of the tree and 
 *          is supposed to be equal to the variable numbers
 *        "clauseNum", the number of clauses in the file
 *        "literalPerClause", an array indicating the number 
 *          of literals per clause
 *        "caluses", an array with all the clauses given in
 *          the input file
 *         "**input", the argument array to create the number of inputs for different threads
 * Output: "input", the arguments of other threads
*/
void initializeThreadArg(Args **input, Node *node, int lastLevel, int clauseNum,  int literalPerClause[], int clauses[]){
    for(int i = 0; i < THREAD_NUM; i++){
        input[i] = (Args*) malloc(sizeof(Args));
        if(input[i]){
            input[i]->head = node;
            input[i]->id = i;
            input[i]->variablesNum = lastLevel;
            input[i]->clauseNum = clauseNum;
            input[i]->literalPerClause = literalPerClause;
            input[i]->clauses = clauses;
            input[i]->solutionNode = NULL;
            input[i]->threadStatus = false;
        }
    }
}

/** 
 * Funcition name: setup4threads
 * Purpose: Creates a tree with level 2 for multithreading
 * Developer: Osama Elsamny
 * Input: "node", the head of the tree
 *        "input", the argument of the threads
 * Output: N/A
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

/** 
 * Funcition name: printProgressReport
 * Purpose: 
 * Developer:
 * Input: 
 * Output: 
*/
void printProgressReport(Args **input){
    while((!(input[0]->threadStatus)) && (!(input[1]->threadStatus)) && (!(input[2]->threadStatus)) && (!(input[3]->threadStatus))){ 
        sleep(2);
        pthread_mutex_lock(&backTrackCounter_mutex);
        printf("Number of BackTrack until now: %d\n", backTrackCounter);
        pthread_mutex_unlock(&backTrackCounter_mutex);
    }
}

int main(int argc, char* argv[]){
    int variablesNum = 0;
    int clauseNum = 0;
    int literalNum = 0;
    pthread_t threads[THREAD_NUM];
    Args *threadsArgs[THREAD_NUM];
    Node *solutionNode = NULL;
    backTrackCounter = 0;
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
    printProgressReport(threadsArgs);
    for(int i = 0; i < THREAD_NUM; i++){
        pthread_cancel(threads[i]);
        pthread_join(threads[i], NULL);
        if(threadsArgs[i]->threadStatus){
            printf("With Thread_id %d: \n", threadsArgs[i]->id);
            printSolution(threadsArgs[i]->solutionNode, threadsArgs[i]->head, variablesNum);
        }
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