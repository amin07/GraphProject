#include<string>
#include<iostream>
#include<vector>
#include<string.h>
#include<cstdlib>
using namespace std;
typedef vector<int> VINT;
struct TreeNode
{
    vector <TreeNode* > childs;
    VINT start_pos;
    int nodeMark;
    //string edge_label;
    VINT edge_label;
    bool leftDiverse;
    //char leftChar;
    int leftChar;
    //TreeNode(){nodeMark=-1;edge_label="";leftDiverse=false;leftChar='*';}
    TreeNode(){nodeMark=-1;edge_label={};leftDiverse=false;leftChar=-1;}
    //TreeNode(int n, string label):nodeMark(n),edge_label(label){leftDiverse=false;leftChar='*';}
    TreeNode(int n, VINT label):nodeMark(n),edge_label(label){leftDiverse=false;leftChar=-4;}
    void addChild(TreeNode *node){this->childs.push_back(node);}
    void updateLabel(VINT n){edge_label=n;}
};
typedef TreeNode TN;
