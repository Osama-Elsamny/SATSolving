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


Node* getSolution(Node *node, int lastLevel, int level);
Node* backTrack(Node *node);
bool evaulateClauses();