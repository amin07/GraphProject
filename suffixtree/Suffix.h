#include<string>
#include<iostream>
#include<vector>
using namespace std;
struct TreeNode
{
    vector <TreeNode* > childs;
    int nodeMark;
    string edge_label;
    bool leftDiverse;
    char leftChar;
    TreeNode(){nodeMark=-1;edge_label="";leftDiverse=false;leftChar='*';}
    TreeNode(int n, string label):nodeMark(n),edge_label(label){leftDiverse=false;leftChar='*';}
    void addChild(TreeNode *node){this->childs.push_back(node);}
    void updateLabel(string n){edge_label=n;}
};
typedef TreeNode TN;
