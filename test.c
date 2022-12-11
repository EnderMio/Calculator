#ifdef EBUG
#include"calculator.h"
int main() {
    // Stack* st = stack_build();
    // for(int i = 0; i < 10; i++) stack_push(st, i + '0');
    // for(int i = 0; i < 10; i++) {
    //     printf("%c %d\n", stack_top(st), stack_size(st));
    //     stack_pop(st);
    // }
    // Tree* tr = tree_build("( -1 + 2 * 3 - 4 + 6 ^ 2 / 2 ^ 2 - 1");
    Tree* tr = tree_build("( 1 - s ( -1 - 2.1415926 ) / 2 )");
    printf("%f", get_value(tr));
    tree_del(tr);
    return 0;
}
#endif