#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include "string.h"
#include "backTrackSearch.h"





/** 
 * Funcition name: getSolution
 * Purpose: Recursively finds the solution of the formula
 * Developer: Osama Elsamny 
 * Input: "Node", the tree head
 *        "lastLevel", which is the hight of the tree and 
 *          is supposed to be equal to the variable numbers
 *        "clauseNum", the number of clauses in the file
 *        "literalPerClause", an array indicating the number 
 *          of literals per clause
 *        "caluses", an array with all the clauses given in
 *          the input file
 * Output: "Node", in wich the right solution is saved
*/
Node* getSolution(Node *node, int lastLevel, int clauseNum,  int literalPerClause[], int clauses[]){
    while(node->level <= lastLevel){
        bool temp = evaulateClauses(node, clauseNum,  literalPerClause, clauses);
        if(temp == false){
            Node* nextNode = backTrack(node);
            if(nextNode){
                node = nextNode;
            }else{
                return nextNode;
            }
        }else{
            if(node->level == lastLevel){
                break;
            }
            Node* right = getInitializedNode(node->level + 1);
            Node* left = getInitializedNode(node->level + 1);
            addLeft(node, left);
            addRight(node, right);
            node = right;
        }
        pthread_testcancel();
    }
    return node;
}

/** 
 * Funcition name: backTrack
 * Purpose: Back tracks to the next guess (node) to be tested
 * Developer: Osama Elsamny
 * Input: "Node", the node the thread is currently at
 * Output: "Node", the next node inline 
*/
Node* backTrack(Node *node){
    node->status = false;
    node = node->parent;
    pthread_mutex_lock(&backTrackCounter_mutex);
    backTrackCounter = backTrackCounter + 1;
    //printf("%d: \n", backTrackCounter);
    pthread_mutex_unlock(&backTrackCounter_mutex);
    while((node) && (node->level > 2)){
        if((!(node->right->status)) && (!(node->left->status))){
            node->status = false;
        }else{
            if(!(node->left->status)){
                return node->right;
            }else{
                return node->left;
            }
        }
        node = node->parent;
    }
    return NULL;
}

/** 
 * Funcition name: evaulateClauses
 * Purpose: To evaluate the formula given in the input file
 * Developer: Osama Elsamny
 * Input: "Node", the node with guess
 *        "clauseNum", the number of clauses in the file
 *        "literalPerClause", an array indicating the number 
 *          of literals per clause
 *        "caluses", an array with all the clauses given in
 *          the input file
 * Output: "formulaVal", returns the evaluation status
*/
bool evaulateClauses(Node *node, int clauseNum, int literalPerClause[], int clauses[]){
    bool formulaVal = true;
    bool clauseVal = true;
    bool temp = true;
    int literalIndex = 0;
    int index = 0;
    getGuessUntilNow(node);
    for(int i = 0; i < clauseNum; i++){
        clauseVal = false;
        for(int j = 0; j < literalPerClause[i]; j++){
            temp = (0 < clauses[literalIndex]);
            index = abs(clauses[literalIndex]);
            literalIndex++;
            if(index > node->level){
                clauseVal = true;
                continue;
            }
            if(node->guessUntillNode[index - 1] == temp){
                clauseVal = true;
            }
        }
        if(!clauseVal){
            formulaVal = false;
            break; 
        }
    }
    return formulaVal;
}

/** 
 * Funcition name: getGuessUntilNow
 * Purpose: To get all the guess from the given node
 *          to the root of the tree
 * Developer: Osama Elsamny
 * Input: "Node", the node to find the guess until
 * Output: "Node->guessUntilNode", an array with all the values
*/
void getGuessUntilNow(Node *node){
    if(!node){
        printf("Node is null\n");
    }
    Node* itr = node;
    node->guessUntillNode = (bool *) malloc((node->level) * sizeof(bool));
    if(!node->guessUntillNode){
        printf("failed to allocate memory in the heap\n");
        exit(1);
    }
    while(itr){
        if(itr->level == 0){
            break;
        }
        node->guessUntillNode[itr->level - 1] = itr->data;
        itr = itr->parent;
    }
}