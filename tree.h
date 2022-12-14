#ifndef _Tree_H_
#define _Tree_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#ifndef EBUG
#include<Arduino.h>
#endif

typedef struct NODE {
    bool isSign;
    double value, power;
    char sign;
    struct NODE *fa, *lson, *rson;
}Node;
typedef struct TREE {
    Node *root, *pre;
    char func;
}Tree;
double tree_calc(const char* str);

#ifdef __cplusplus
}
#endif

#endif