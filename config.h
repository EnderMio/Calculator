// #include<Arduino.h>
#ifndef _Config_H_
#define _Config_H_
#include<string>
#include<vector>
using std::vector, std::string;
class Tree {
    class Node {
        bool isSign;
        double value, power;
        char sign;
        int fa, lson, rson, num;
        public:
            Node();
            Node(char sign, int num, int root, int preFa);
            Node(double value, int num);
            void change_val(const int& val, const int& opt);
            void change_val(const double& val, const double& opt);
            int get_val(const int& opt);
            double get_val(const double& opt);
            char get_val(const char& opt);
            bool get_val(const bool& opt);
    };
    int cnt, root;
    bool err;
    vector<Node*> ptrNode;
    void add_node(char sign);
    void add_node(double value);
    double dfs(int num);
    public:
        Tree();
        Tree(string str);
        double get_value();
        ~Tree();
};
#endif