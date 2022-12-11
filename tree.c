#include"tree.h"
void add_node_d(Tree* t, const double value) {
    Node* node = (Node *)malloc(sizeof(Node));
    node_init(node);
    node->fa = t->pre;
    node->value = value;
    node->isSign = 0;
    if(t->pre) t->pre->rson = node;
    else t->root = node;
    t->pre = node;
}
void add_node_c(Tree* t, const char sign) {
    Node* node = (Node *)malloc(sizeof(Node));
    Node* preFa = t->pre->fa;
    node_init(node);
    node->sign = sign;
    node->isSign = 1;
    if(sign == '+' || sign == '-') {
        node->lson = t->root;
        t->root->fa = node;
        t->root = node;
    }
    else {
        node->fa = t->pre->fa;
        node->lson = t->pre;
        preFa->rson = node;
        t->pre->fa = node;
    }
    t->pre = node;
}
void node_init(Node* n) {
    n->lson = n->rson = n->fa = NULL;
    n->power = 1;
}
void del_node(Node* now) {
    if(now->lson) del_node(now->lson);
    if(now->rson) del_node(now->rson);
    free(now);
}
void tree_del(Tree* t) {
    del_node(t->root);
    free(t);
    t = NULL;
}
Tree* tree_build(const char* str) {
    Tree* t = (Tree *)malloc(sizeof(Tree));
    t->root = NULL;
    t->pre = NULL;
    size_t len = strlen(str), lenc = 0;
    char * s = (char *)malloc(sizeof(char) * get_maxlen(str));
    while(len > lenc) {
        sscanf(str + lenc, "%s", s);
        size_t l = strlen(s);
        if(lenc) lenc++;
        lenc += l;
        if(s[0] == '^') {
            sscanf(str + lenc, "%s", s);
            lenc += strlen(s) + 1;
            t->pre->power = atof(s);
        }
        else if(l == 1 && (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/')) add_node_c(t, s[0]);
        else add_node_d(t, atof(s));
    }
    free(s);
    return t;
}
double get_value(Tree* t) {
    bool err = 0;
    double res = get_val(t->root, &err);
    assert(!err);
    return res;
}
double get_val(Node* n, bool* err) {
    if(!n->isSign) return n->value;
    double lval = get_val(n->lson, err);
    double rval = get_val(n->rson, err);
    lval = pow(lval, n->lson->power);
    rval = pow(rval, n->rson->power);
    if(*err) return 0;
    if(n->sign == '/' && (rval > 0 ? rval : -rval) < 1e-5) {
        *err = 1;
        return 0;
    }
    if(n->sign == '+') return lval + rval;
    if(n->sign == '-') return lval - rval;
    if(n->sign == '*') return lval * rval;
    if(n->sign == '/') return lval / rval;
    return 0;
}
int get_maxlen(const char* str) {
    size_t len = strlen(str);
    int p = -1, maxlen = 0;
    for(int i = 0; i < len; i++) {
        if(str[i] == ' ') {
            if(i - p > maxlen) {
                maxlen = i - p;
            }
            p = i;
        }
    }
    return maxlen > (len - p) ? maxlen : (len - p);
}