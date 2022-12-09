#include"config.h"
#include<iostream>
#include<string>
#include<cmath>
using namespace std;
int main() {
    string s = "1 + 2 * 3 - 4 + 6 ^ 2 / 2 ^ 2 - 1";
    Tree* tr = new Tree(s);
    cout << tr->get_value() << endl;
    delete tr;
    return 0;
}
