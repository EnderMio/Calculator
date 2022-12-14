#include"tree.h"

void add_node_d(Tree* t, const double value);
void add_node_c(Tree* t, const char sign);
void del_node(Node* now);
double get_val(Node* n, bool* err);
int get_maxlen(const char* str);
void read_str(const char* str, char* s, size_t *lenc);
void node_init(Node* n);
Tree* tree_build(const char* str);
void tree_del(Tree* t);
double get_value(Tree* t);
bool is_func(char c);
bool is_calc(char c);

double tree_calc(const char* str) {
    Tree* tr = tree_build(str);
    double res = get_value(tr);
    tree_del(tr);
    return res;
}
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
    node_init(node);
    node->sign = sign;
    node->isSign = 1;
    if(sign == '+' || sign == '-') {
        node->lson = t->root;
        t->root->fa = node;
        t->root = node;
    }
    else {
        node->lson = t->pre;
        if(t->root != t->pre) {
            node->fa = t->pre->fa;
            t->pre->fa->rson = node;
        }
        else t->root = node;
        t->pre->fa= node;
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
    t->pre = t->root = NULL;
    t->func = str[0];
    size_t len = strlen(str), lenc = 1;
    char * s = (char *)malloc(sizeof(char) * get_maxlen(str + 2));
    while(len > lenc) {
        read_str(str, s, &lenc);
        if(is_func(s[0])) {
            int cnt = 1;
            size_t tmplen = lenc - 1;
            while(cnt) {
                lenc++;
                if(is_func(str[lenc])) cnt++;
                if(str[lenc] == ')') cnt--;
            }
            size_t size = lenc++ - tmplen - 1;
            char * sub = (char *)malloc(sizeof(char) * size);
            strncpy(sub, str + tmplen, size);
            Tree* subt = tree_build(sub);
            free(sub);
            double res = get_value(subt);
            tree_del(subt);
            add_node_d(t, res);
        }
        else if(s[0] == '^') {
            read_str(str, s, &lenc);
            t->pre->power = atof(s);
        }
        else if(s[1] == 0 && is_calc(s[0])) add_node_c(t, s[0]);
        else add_node_d(t, atof(s));
    }
    free(s);
    return t;
}
double get_value(Tree* t) {
    bool err = 0;
    double res = get_val(t->root, &err);
    assert(!err);
    if(t->func == 's') return sin(res);
    if(t->func == 'c') return cos(res);
    if(t->func == 'e') return exp(res);
    if(t->func == 'l') return log(res);
    return res;
}
double get_val(Node* n, bool* err) {
    if(!n->isSign) return pow(n->value, n->power);
    double lval = get_val(n->lson, err);
    double rval = get_val(n->rson, err);
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
void read_str(const char* str, char* s, size_t* lenc) {
    ++*lenc;
    sscanf(str + *lenc, "%s", s);
    *lenc += strlen(s);
}
bool is_func(char c) {
    return c == '(' || c == 's' || c == 'c' || c == 'e' || c == 'l';
}
bool is_calc(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}