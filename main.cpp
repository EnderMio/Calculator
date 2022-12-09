#include"config.h"
#include<iostream>
#include<string>
#include<cmath>
using namespace std;
int main() {
    string s = "1 + 2 * 3 - 4 + 6 ^ 2 / 2 ^ 2 - 1";
    Tree* tr = new Tree(s);
    if(tr) {
        try{
            cout << tr->get_value() << endl;
        }catch(const char* msg) {
            cerr << msg << endl;
        }
        delete tr;
    }
    else {
        cerr << "Out Of Memory!" << endl;
    }
    return 0;
}
