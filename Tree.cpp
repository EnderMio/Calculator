// #include"config.h"
#include<vector>
#include<cmath>
#include<sstream>
#include<string>
#include<iostream>
using namespace std;
namespace nval {
    bool isSign = 0;
    int num = 1, fa = 2, lson = 4, rson = 8;
    double power = 0.5, value = 0.25;
    char sign = 64;
}
double fabs(double x) {
    return x >= 0 ? x : -x;
}
class Tree {
    class Node {
        bool isSign;
        double value, power;
        char sign;
        int fa, lson, rson, num;
        public:
            Node() {}
            Node(char sign, int num, int root, int preFa) {
                this->sign = sign;
                isSign = true;
                this->num = num;
                if(sign == '+' || sign == '-') {
                    fa = 0;
                    lson = root;
                }
                else {
                    fa = preFa;
                    lson = num - 1;
                }
            }
            Node(double value, int num) {
                power = 1;
                this->num = num;
                this->value = value;
                fa = num - 1;
                isSign = false;
            }
            void change_val(const int& val, const int& opt) {
                if(opt == 2) fa = val;
                if(opt == 4) lson = val;
                if(opt == 8) rson = val;
            }
            void change_val(const double& val, const double& opt) {
                if(opt == 0.5) power = val;
            }
            int get_val(const int& opt) {
                if(opt == 1) return num;
                if(opt == 2) return fa;
                if(opt == 4) return lson;
                if(opt == 8) return rson;
                return 0;
            }
            double get_val(const double& opt) {
                if(opt == 0.5) return power;
                if(opt == 0.25) return value;
                return 0;
            }
            char get_val(const char& opt) {
                if(opt == 64) return sign;
                return 0;
            }
            bool get_val(const bool& opt) {
                if(opt == 0) return isSign;
                return 0;
            }
    };
    int cnt, root;
    bool err;
    vector<Node*> ptrNode;
    void add_node(char sign) {
        int pre = cnt - 1, preFa = ptrNode[pre]->get_val(nval::fa);
        ptrNode.push_back(new Node(sign, cnt, root, preFa));
        if(sign == '+' || sign == '-') {
            ptrNode[root]->change_val(cnt, nval::fa);
            root = cnt;
        }
        else {
            ptrNode[preFa]->change_val(cnt, nval::rson);
            ptrNode[pre]->change_val(cnt, nval::fa);
        }
        cnt++;
    }
    void add_node(double value) {
        if(cnt) {
            int pre = cnt - 1;
            ptrNode[pre]->change_val(cnt, nval::rson);
        }
        ptrNode.push_back(new Node(value, cnt));
        cnt++;
    }
    double dfs(int num) {
        Node& now = *(ptrNode[num]);
        if(!now.get_val(nval::isSign)) return now.get_val(nval::value);
        double lval = dfs(now.get_val(nval::lson));
        double rval = dfs(now.get_val(nval::rson));
        if(err) return 0;
        char sign = now.get_val(nval::sign);
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
    public:
        Tree() {}
        Tree(string str) {
            cnt = 0;
            root = 0;
            err = 0;
            stringstream form(str);
            string s;
            while(form >> s) {
                if(s == "^") {
                    form >> s;
                    ptrNode.back()->change_val(stod(s), nval::power);
                }
                else if(s == "+" || s == "-" || s == "*" || s == "/") {
                    add_node(s[0]);
                }
                else{
                    add_node(stod(s));
                }
            }
        }
        double get_value() {
            return dfs(root);
        }
        ~Tree() {
            for(int i = 0; i < cnt; i++) {
                delete ptrNode[i];
                ptrNode.pop_back();
            }
        }
};
int main() {
    string s = "1 + 2 * 3 - 4 + 6 * 6 / 4 - 1";
    Tree* tr = new Tree(s);
    cout << tr->get_value() << endl;
    delete tr;
    return 0;
}
