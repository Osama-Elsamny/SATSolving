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


Node* getSolution(Node *node, int lastLevel, int clauseNum,  int literalPerClause[], int clauses[]);
Node* backTrack(Node *node);
bool evaulateClauses(Node *node, int clauseNum,  int literalPerClause[], int clauses[]);
void getGuessUntilNow(Node *node);