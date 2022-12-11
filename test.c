#ifdef EBUG
#include"calculator.h"
int main() {
    Stack* st = stack_init();
    Tree* tr = tree_build("1 + 2 * 3 - 4 + 6 ^ 2 / 2 ^ 2 - 1");
    printf("%f", get_value(tr));
    tree_del(tr);
    return 0;
}
#endif