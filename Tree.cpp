#include"config.h"
#include<vector>
#include<cmath>
#include<sstream>
#include<string>
#include<iostream>
using namespace std;
namespace nval {
    bool isSign = 1;
    int fa = 2, lson = 4, rson = 8;
    double power = 0.5, value = 0.25;
    char sign = 64;
}
Tree::Node::Node() {}
Tree::Node::Node(const char& sign, Node* root, Node* pre) {
    power = 1;
    this->sign = sign;
    isSign = true;
    if(sign == '+' || sign == '-') {
        fa = NULL;
        lson = root;
    }
    else {
        fa = pre->get_val(nval::fa);
        lson = pre;
    }
}
Tree::Node::Node(const double& value, Node* pre) {
    power = 1;
    this->value = value;
    fa = pre;
    isSign = false;
}
void Tree::Node::change_val(Node* val, const int& opt) {
    if(opt == 2) fa = val;
    if(opt == 4) lson = val;
    if(opt == 8) rson = val;
}
void Tree::Node::change_val(const double& val, const double& opt) {
    if(opt == 0.5) power = val;
}
Tree::Node* Tree::Node::get_val(const int& opt) {
    if(opt == 2) return fa;
    if(opt == 4) return lson;
    if(opt == 8) return rson;
    return NULL;
}
double Tree::Node::get_val(const double& opt) {
    if(opt == 0.5) return power;
    if(opt == 0.25) return value;
    return 0;
}
char Tree::Node::get_val(const char& opt) {
    if(opt == 64) return sign;
    return 0;
}
bool Tree::Node::get_val(const bool& opt) {
    if(opt == 1) return isSign;
    return 0;
}
double Tree::Node::get_value(int& err) {
    if(!isSign) return value;
    double lval = lson->get_value(err);
    double rval = rson->get_value(err);
    lval = pow(lval, lson->get_val(nval::power));
    rval = pow(rval, rson->get_val(nval::power));
    if(err) return 0;
    if(sign == '/' && abs(rval) < 1e-5) {
        err = 1;
        return 0;
    }
    if(sign == '+') return lval + rval;
    if(sign == '-') return lval - rval;
    if(sign == '*') return lval * rval;
    if(sign == '/') return lval / rval;
    return 0;
}
void Tree::add_node(const char& sign) {
    Node* node = new Node(sign, root, pre);
    Node* preFa = pre->get_val(nval::fa);
    if(sign == '+' || sign == '-') {
        root->change_val(node, nval::fa);
        root = node;
    }
    else {
        preFa->change_val(node, nval::rson);
        pre->change_val(node, nval::fa);
    }
    pre = node;
}
void Tree::add_node(const double& value) {
    Node* node = new Node(value, pre);
    if(pre) pre->change_val(node, nval::rson);
    else root = node;
    pre = node;
}
Tree::Tree() {}
Tree::Tree(string str) {
    root = NULL;
    pre = NULL;
    stringstream form(str);
    string s;
    while(form >> s) {
        if(s == "^") {
            form >> s;
            pre->change_val(stod(s), nval::power);
        }
        else if(s == "+" || s == "-" || s == "*" || s == "/") add_node(s[0]);
        else add_node(stod(s));
    }
}
double Tree::get_value() {
    int err = 0;
    double res = root->get_value(err);
    if(err) throw "Division by zero condition!";
    return res;
}
void Tree::del_node(Node* now) {
    if(now->get_val(nval::lson)) del_node(now->get_val(nval::lson));
    if(now->get_val(nval::rson)) del_node(now->get_val(nval::rson));
    delete now;
}
Tree::~Tree() {
    del_node(root);
}