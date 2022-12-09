#include"config.h"
#include<iostream>
#include<string>
using namespace std;
int main() {
    string s = "1 + 2 * 3 - 4 + 6 * 6 / 4 - 1";
    Tree* tr = new Tree(s);
    cout << tr->get_value() << endl;
    delete tr;
    return 0;
}
