#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include "string.h"
#include "linkList.h"


Node* getSolution(Node *node, int lastLevel){
    bool temp = evaulateClauses();
    if(node->level == lastLevel){
        if(temp == false){
            Node* nextNode = backTrack(node);
            if(nextNode){
                return getSolution(nextNode, lastLevel);
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
            return getSolution(nextNode, lastLevel);
        }else{
            return nextNode;
        }
    }else{
        Node* right = getInitializedNode(node->level + 1);
        Node* left = getInitializedNode(node->level + 1);
        addLeft(node, left);
        addRight(node, right);
        Node* resultRight = getSolution(right, lastLevel);
        Node* resultLeft = getSolution(left, lastLevel);
        if(resultRight){
            return resultRight;
        }else{
            return resultLeft;
        }
    }
}

Node* backTrack(Node *node){
    node->status = false
    while(!(node)){
        node = node->parent;
        if((!(node->right->status)) && (!(node->left->status))){
            node->status = false;
        }else{
            if(!(node->left->status)){
                return node->right;
            }else{
                return node->left;
            }
        }
    }
    return NULL;
}

bool evaulateClauses(Node *node, int variblesNum, int clauseNum){
    bool clauseVal = false;
    int solutionGuess[variblesNum];
    for(int i = 0; i < clauseNum; i++){
        for(int j = 0; j < liter; j++){

        }
    }
    return clauseVal;
}