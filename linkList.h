#ifndef LINKLIST_H
#define LINKLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>
#include <math.h>
#include "string.h"



typedef struct Node{ 
  bool data; 
  bool status;
  int level;
  bool* guessUntillNode;
  struct Node *parent;
  struct Node *left;
  struct Node *right;
}Node; 

Node* getInitializedNode(int level);
void addLeft(Node *parent, Node *add);
void addRight(Node *parent, Node *add);

#endif