// #include<Arduino.h>
#ifndef _Config_H_
#define _Config_H_
#include<string>
#include<vector>
using std::string;
class Tree {
    class Node {
        bool isSign;
        double value, power;
        char sign;
        Node *fa, *lson, *rson;
        public:
            Node();
            Node(const char& sign, Node* root, Node* pre);
            Node(const double& value, Node* pre);
            void change_val(Node* val, const int& opt);
            void change_val(const double& val, const double& opt);
            Node* get_val(const int& opt);
            double get_val(const double& opt);
            char get_val(const char& opt);
            bool get_val(const bool& opt);
            double get_value(int& err);
    };
    Node *root, *pre;
    void add_node(const char& sign);
    void add_node(const double& value);
    void del_node(Node* now);
    public:
        Tree();
        Tree(string str);
        double get_value();
        ~Tree();
};
#endif