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
  struct Node *treeHead;
  struct Node *parent;
  struct Node *left;
  struct Node *right;
  int level;
  bool *guessUntillNode;
}Node; 

Node* getInitializedNode(Node *head, int level);
void addLeft(Node *parent, Node *add);
void addRight(Node *parent, Node *add);