#include<string>
#include<iostream>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<utility>
#include<unordered_map>
#include<unordered_set>
using namespace std;

#ifdef DEBUG
#define debug_stmt(x) x
#else
#define debug_stmt(x)
#endif

typedef vector<int> _vint;
typedef pair<int, int> _pair;
struct _End{
	int end_val;
	_End(int a):end_val(a){}
};
struct TreeNode
{
    //vector <TreeNode* > childs;
    unordered_map<int, TreeNode *> childs;
    TreeNode *suffix_link;
    _vint start_pos;
    //_pair edge_label;
    int _start;
    _End *_end;
    int nodeMark;
    bool leftDiverse;
    int leftChar;
    TreeNode(){nodeMark=-1;leftDiverse=false;leftChar=-1;_start=0;_end=new _End(0);}
    //TreeNode(_pair label):edge_label(label){leftDiverse=false;leftChar=-2;}
    TreeNode(int st, _End *e):_start(st),_end(e){leftDiverse=false;leftChar=-2;}
    void addChild(int key, TreeNode *node){this->childs.insert({key,node});}
    //void updateLabel(_pair n){edge_label=n;}
};
typedef TreeNode _tnode;
typedef unordered_map<int, TreeNode *> MM;
struct ActivePoint
{
	_tnode *active_node;
	int active_edge;
	int active_len;
};


