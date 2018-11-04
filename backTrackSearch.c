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


Node* getSolution(Node *node, int lastLevel, int clauseNum,  int literalPerClause[], int clauses[]){
    bool temp = evaulateClauses(node, clauseNum,  literalPerClause, clauses);
    if(node->level == lastLevel){
        if(temp == false){
            Node* nextNode = backTrack(node);
            if(nextNode){
                return getSolution(nextNode, lastLevel, clauseNum,  literalPerClause, clauses);
            }else{
                return nextNode;
            }
        }else{
            return node;
        }
    }
    if(temp == false){
        Node* nextNode = backTrack(node);
        if(nextNode){
            return getSolution(nextNode, lastLevel, clauseNum,  literalPerClause, clauses);
        }else{
            return nextNode;
        }
    }else{
        Node* right = getInitializedNode(node->level + 1);
        Node* left = getInitializedNode(node->level + 1);
        addLeft(node, left);
        addRight(node, right);
        Node* resultRight = getSolution(right, lastLevel, clauseNum,  literalPerClause, clauses);
        if(left->status){
            Node* resultLeft = getSolution(left, lastLevel, clauseNum,  literalPerClause, clauses);
            if(resultRight){
                return resultRight;
            }else{
                return resultLeft;
            }
        }
        return resultRight;
    }
}

Node* backTrack(Node *node){
    node->status = false;
    node = node->parent;
    while(node){
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
                j = literalPerClause[i];
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

void getGuessUntilNow(Node *node){
    Node* itr = node;
    node->guessUntillNode = (bool *) malloc(node->level * sizeof(bool));
    while(itr){
        if(itr->level == 0){
            break;
        }
        node->guessUntillNode[itr->level - 1] = itr->data;
        itr = itr->parent;
    }
}