#ifndef BACKTRACKSEARCH_H
#define BACKTRACKSEARCH_H

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

volatile int backTrackCounter;
pthread_mutex_t backTrackCounter_mutex;
Node* getSolution(Node *node, int lastLevel, int clauseNum,  int literalPerClause[], int clauses[]);
Node* backTrack(Node *node);
bool evaulateClauses(Node *node, int clauseNum,  int literalPerClause[], int clauses[]);
void getGuessUntilNow(Node *node);

#endif