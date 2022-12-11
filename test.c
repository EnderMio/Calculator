#ifdef EBUG
#include"calculator.h"
int main() {
    // Tree* tr = tree_build("( -1 + 2 * 3 - 4 + 6 ^ 2 / 2 ^ 2 - 1");
    Tree* tr = tree_build("( 1 - c 1 + 2.1415926 ) * 2");
    printf("%f", get_value(tr));
    tree_del(tr);
    return 0;
}
#endif