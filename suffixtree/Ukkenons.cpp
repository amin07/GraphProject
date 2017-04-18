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


int getNextElement(int );
void vPrint(_vint v){
	for(auto i:v) cout<<" "<<i;

}

void testGetNextElement(){
	// unit test function to test getNextElement method

	// set up
	int input_seq[] = {1,2,3,1,2,4,1};
	input_vect.assign(input_seq, input_seq+sizeof(input_seq)/sizeof(int));
	//vPrint(input_vect);

	_tnode *head = new _tnode();
	head->addChild(1,new _tnode({0,2}));
	head->addChild(2,new _tnode({1,2}));
	head->addChild(3,new _tnode({2,2}));
	anode = head;
	alen = 2;
	aedge = 0;
	cout<<"next element should be 3, we get "<<getNextElement(5)<<endl;

}
int getNextElement(int curr_pos){
	int curr_element = input_vect[curr_pos];
	//cout<<curr_element<<endl;
	//return 0;
	_tnode *nodeDir = anode->childs[input_vect[aedge]];
	int edgeLen =  (nodeDir->edge_label.second-nodeDir->edge_label.first);
	//cout<<"edge len"<<edgeLen<<endl;
	//cout<<"alen"<<alen<<endl;
	if(edgeLen>=alen){
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
	_tnode *lastIntNode = 0;
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
			// getting the next element in case active len not 0
			int nextElm = getNextElement(start_pos);

			if(nextElm==input_vect[start_pos]){

				if(lastIntNode){
					lastIntNode->suffix_link = anode[input_vect[aedge]];
				}
			}
			else{

			}

		}
	}
}

_tnode * buildTree(_vint input_vect){
	 root = new _tnode();
	_ap.active_node = root;
	_ap.active_edge = -1;
	_ap.active_len = 0;


	for(int i=0;i<input_vect.size();i++)
	{
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


	//testGetNextElement();
	_tnode *tree = buildTree(input_vect);

	//calculateLeftDiverse(tree, input_vect);

	//printSuffixes(tree, {});
	return 0;
}
