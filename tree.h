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
typedef struct NODE {
    bool isSign;
    double value, power;
    char sign;
    struct NODE *fa, *lson, *rson;
}Node;
void node_init(Node* n);
typedef struct TREE {
    Node *root, *pre;
    char func;
}Tree;
void add_node_d(Tree* t, const double value);
void add_node_c(Tree* t, const char sign);
Tree* tree_build(const char* str);
void del_node(Node* now);
void tree_del(Tree* t);
double get_value(Tree* t);
double get_val(Node* n, bool* err);
int get_maxlen(const char* str);
void read_str(const char* str, char* s, size_t *lenc);
bool is_func(char c);
bool is_calc(char c);

#ifdef __cplusplus
}
#endif

#endif