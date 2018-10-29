#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>
#include <math.h>
#include "string.h"
#include "linkList.h"


/** 
 * Funcition name: getInitializedNode
 * Purpose: initialize the nodes 
 * Developer: Osama Elsamny
 * Input: head, the tree head
 *        level, the level of the node to be used for array size
 * Output: Node*, return a pointer of type Node to
 *         the created object
*/
Node* getInitializedNode(Node *head, int level){
    Node *init = (Node *) malloc(sizeof(Node));
    init->left = NULL;
    init->right = NULL;
    init->parent = NULL;
    init->treeHead = head;
    init->level = level;
    init->guessUntillNode = (bool *) malloc((level) * sizeof(bool));
    return init;
}

/** 
 * Funcition name: addLeft
 * Purpose: adding a Node to the left of the parent Node
 * Developer: Osama Elsamny
 * Input: parent, a Node pointer to the parent in 
 *        which we insert to the left of it
 * Output: N/A
*/
void addLeft(Node *parent, Node *add){
    parent->left = add;
    add->parent = parent;
    add->data = false;
    for(int i = 0; i < parent->level; i++){
        add->guessUntillNode[i] = parent->guessUntillNode[i];
    }
    add->guessUntillNode[add->level - 1] = false;
}

/** 
 * Funcition name: addRight
 * Purpose: adding a Node to the right of the parent Node
 * Developer: Osama Elsamny
 * Input: parent, a Node pointer to the parent in 
 *        which we insert to the right of it
 * Output: N/A
*/
void addRight(Node *parent, Node *add){
    parent->right = add;
    add->parent = parent;
    add->data = true;
    for(int i = 0; i < parent->level; i++){
        add->guessUntillNode[i] = parent->guessUntillNode[i];
    }
    add->guessUntillNode[add->level - 1] = true;
}