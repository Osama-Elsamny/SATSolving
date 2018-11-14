#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

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
#define MAX_STRING_SIZE 1024

void header_read(char* file_name, int *v_num, int *c_num, int *l_num);
bool spaceCheck(char* word);
void data_read(char* file_name, int c_num, int l_num, int clauses[], int literalPerClause[]);
void printSolution(Node* solutionNode, Node* head, int variablesNum);

#endif