#include<string>
#include<iostream>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<utility>
#include<unordered_map>
using namespace std;
typedef vector<int> _vint;
typedef pair<int, int> _pair;

struct TreeNode
{
    //vector <TreeNode* > childs;
    unordered_map<int, TreeNode *> childs;
    TreeNode *suffix_link;
    _vint start_pos;
    _pair edge_label;
    int nodeMark;
    bool leftDiverse;
    int leftChar;
    TreeNode(){nodeMark=-1;edge_label={};leftDiverse=false;leftChar=-1;}
    TreeNode(_pair label):edge_label(label){leftDiverse=false;leftChar=-2;}
    void addChild(int key, TreeNode *node){this->childs.insert({key,node});}
    void updateLabel(_pair n){edge_label=n;}
};
typedef TreeNode _tnode;

struct ActivePoint
{
	_tnode *active_node;
	int active_edge;
	int active_len;
};
