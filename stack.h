#ifndef _Stack_H_
#define _Stack_H_

#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
typedef struct STACK {
    char* vol;
    size_t top;
    size_t capacity;
}Stack;
Stack* stack_build();
void stack_del(Stack* st);
void stack_push(Stack* st, char c);
void stack_pop(Stack* st);
char stack_top(Stack* st);
bool stack_empty(Stack* st);
size_t stack_size(Stack* st);

#ifdef __cplusplus
}
#endif

#endif