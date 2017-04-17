#include "Ukkenons.h"
#define DATA_SIZE 10000
ActivePoint _ap;
#define anode _ap.active_node
#define aedge _ap.active_edge
#define alen _ap.active_len

int _end = -1;		// this value will be the second item of each edge's label pair
int _suffixToBeAdded = 0;
_tnode *root;
_vint input_vect;

void vPrint(_vint v){
	for(auto i:v) cout<<" "<<i;
}

int getNextElement(int curr_pos){
	int curr_element = input_vect[curr_pos];
	_tnode *nodeDir = anode->childs[curr_element];
	int edgeLen =  (nodeDir->edge_label.second-nodeDir->edge_label.first);
	if(edgeLen>= alen){
		return input_vect[nodeDir->edge_label.first+alen];
	}
	if((edgeLen+1) == alen){
		if(nodeDir->childs.find(curr_element)!=nodeDir->childs.end()){
			return curr_element;
		}
		else return -1; // this means we will have to create a new leaf
	}
	else{
		// updating active points
		anode = nodeDir;
		alen = alen - edgeLen-1;
		aedge = aedge + alen + 1;
		return getNextElement(curr_pos);
	}
}
void buildPhases(int start_pos){
	_end++;
	_tnode *lastNode = 0;
	_suffixToBeAdded++;

	while(_suffixToBeAdded > 0){
		if(_ap.active_len==0){
			if(_ap.active_node->childs.find(input_vect[start_pos])!=_ap.active_node->childs.end()){
				_ap.active_edge = _ap.active_node->childs[input_vect[start_pos]]->edge_label.first;
				_ap.active_len++;
				break;
			}
			else{
				_tnode *newChild = new _tnode({start_pos,_end});
				_suffixToBeAdded--;
			}
		}
		else{
			int nextElm = getNextElement(start_pos);
		}
	}
}

_tnode * buildTree(_vint input_vect){
	 root = new _tnode();
	_ap.active_node = root;
	_ap.active_edge = -1;
	_ap.active_len = 0;


	for(int i=0;i<input_vect.size();i++){
		buildPhases(i);
	}

	return root;
}


int main()
{
	cout<<"Ukkenon's program.."<<endl;


	char input_str[DATA_SIZE];
	fgets(input_str,DATA_SIZE,stdin);
	char *token = strtok(input_str, " ");
	do{
		input_vect.push_back(atoi(token));
		token = strtok(NULL, " ");
	}while(token);


	_tnode *tree = buildTree(input_vect);
	//calculateLeftDiverse(tree, input_vect);

	//printSuffixes(tree, {});
	return 0;
}
