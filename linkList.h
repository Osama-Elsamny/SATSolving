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
  struct Node *treeHead;
  struct Node *parent;
  struct Node *left;
  struct Node *right;
  int level;
  bool *guessUntillNode;
}Node; 

Node* getInitializedNode(int level);
void addLeft(Node *parent, Node *add);
void addRight(Node *parent, Node *add);