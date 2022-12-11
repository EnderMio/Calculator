#include "stack.h"
Stack* stack_build() {
    Stack* st = (Stack *)malloc(sizeof(Stack));
    st->vol = NULL;
    st->top = st->capacity = 0;
    return st;
}
void stack_del(Stack* st) {
    free(st->vol);
    free(st);
    st = NULL;
}
void stack_push(Stack* st, char c) {
    if(st->top == st->capacity) {
        size_t newcap = st->capacity == 0 ? sizeof(char) : (st->capacity + 1);
        st->vol = (char *)realloc(st->vol, newcap * sizeof(char));
        st->capacity = newcap;
    }
    st->vol[st->top++] = c;
}
void stack_pop(Stack* st) {
    assert(st->top > 0);
    st->top--;
}
char stack_top(Stack* st) {
    assert(st->top);
    return st->vol[st->top - 1];
}
bool stack_empty(Stack* st) {
    return st->top == 0 ? 1 : 0;
}
size_t stack_size(Stack* st) {
    return st->top;
}