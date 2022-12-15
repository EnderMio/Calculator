#ifdef EBUG
#include"calculator.h"
#include<stdio.h>
int main() {
    // Stack* st = stack_build();
    // for(int i = 0; i < 10; i++) stack_push(st, i + '0');
    // for(int i = 0; i < 10; i++) {
    //     printf("%c %d\n", stack_top(st), stack_size(st));
    //     stack_pop(st);
    // }

    printf("%f", tree_calc("( -1 + 2 * 3 - 4 + 6 ^ 2 / 2 ^ 2 - s -1 + 3.1415926 / 2 + 2 * 1 / 2 )"));

    // string *str = string_build();
    // string_add(str, "Hello World");
    // string_add(str, " Ender\n");
    // printf("%s", string_cstr(str));
    // printf("%s", "Hello\b\b  ");
    // string_del(str);
    return 0;
}
#endif