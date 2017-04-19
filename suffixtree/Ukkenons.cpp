#include "Ukkenons.h"
#define DATA_SIZE 10000
ActivePoint _ap;
#define anode _ap.active_node
#define aedge _ap.active_edge
#define alen _ap.active_len

_End *_end = new _End(-1);		// this value will be the second item of each edge's label pair
int _suffixToBeAdded = 0;
_tnode *root;
_vint input_vect;



int getNextElement(int );
void vPrint(_vint v){
	for(auto i:v) cout<<" "<<i;
}
void vPrint(_vint v, _pair p){
	for(int i=p.first;i<=p.second;i++) cout<<" "<<v[i];
}

void testGetNextElement(){
	// unit test function to test getNextElement method
	/*
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
*/
}

int getNextElement(int curr_pos){
	int curr_element = input_vect[curr_pos];


	_tnode *nodeDir = anode->childs[input_vect[aedge]];

	int edgeLen =  (nodeDir->_end->end_val-nodeDir->_start);
	cout<<"\ninside getnextel "<<nodeDir->_start<<" "<<edgeLen<<" "<<alen<<" "<<curr_element<<" "<<aedge<<endl;

	if(edgeLen>=alen){
		return input_vect[nodeDir->_start+alen];
	}
	if((edgeLen+1) == alen){
		if(nodeDir->childs.find(curr_element)!=nodeDir->childs.end()){
			return curr_element;
		}
		else return -1; // this means we will have to create a new leaf
	}
	else{
		// updating active points
		//cout<<"yeah um here"<<endl;
		int tempanodestart = anode->_start;
		anode = nodeDir;
		//int tempalen = alen;
		alen = alen - edgeLen-1;
		aedge = aedge + edgeLen + 1;
		//aedge =  edgeLen + tempalen + 1;
		//aedge = aedge + tempalen + 1;
		//aedge = aedge + tempalen;
		//nodeDir = anode->childs[input_vect[aedge]];
		//if(nodeDir==NULL) cout<<"this"<<endl;
		//cout<<"foitta before return "<<anode->_start<<" "<<alen<<"  "<<aedge<<endl;
		return getNextElement(curr_pos);
	}
}
void buildPhases(int start_pos){
	_end->end_val++;
	_tnode *lastIntNode = 0;
	_suffixToBeAdded++;
	cout<<"end val "<<_end->end_val<<" ";
	while(_suffixToBeAdded > 0){
		if(_ap.active_len==0){
			if(anode->childs.find(input_vect[start_pos])!=anode->childs.end()){
				cout<<"if if"<<endl;
				// show stopper
				_ap.active_edge = anode->childs[input_vect[start_pos]]->_start;
				_ap.active_len++;
				cout<<" active edge "<<aedge<<"alen "<<alen<<endl;
				break;
			}
			else{
				cout<<"if else"<<endl;
				_tnode *newChild = new _tnode(start_pos,_end);
				root->addChild(input_vect[start_pos],newChild);
				_suffixToBeAdded--;
			}
		}
		else{
			// getting the next element in case active len not 0
			int nextElm = getNextElement(start_pos);



			if(nextElm==-1){	// a leaf node need to be added here
				cout<<"else if -1"<<endl;
				_tnode *newLeaf = new _tnode(start_pos,_end);
				anode->childs[input_vect[aedge]]->addChild(input_vect[start_pos],newLeaf);

				if(lastIntNode){
					lastIntNode->suffix_link = anode;
				}

				// just made anode an internal one
				lastIntNode = anode;

				if(anode==root){
					aedge++;
					alen--;
				}
				else{
					anode = anode->suffix_link;
				}

				_suffixToBeAdded--;
				cout<<" active edge "<<aedge<<"alen "<<alen<<endl;
				continue;
			}

			if(nextElm==input_vect[start_pos]){
				cout<<"else if"<<endl;
				if(lastIntNode){
					lastIntNode->suffix_link = anode->childs[input_vect[aedge]];
				}

				// updating active len and other things
				_tnode *currNode = anode->childs[input_vect[aedge]];
				cout<<"comparison"<<currNode->_end->end_val<<"-"<<currNode->_start<<" "<<alen<<endl;

				if(currNode->_end->end_val-currNode->_start < alen){
					anode = currNode;
					alen = alen - (currNode->_end->end_val-currNode->_start);
					aedge = currNode->childs[input_vect[start_pos]]->_start;
				}
				else {
					alen++;
				}
				cout<<" active edge "<<aedge<<"alen "<<alen<<endl;
				break;
			}
			else{
				cout<<"else else"<<endl;
				_tnode *currNode = anode->childs[input_vect[aedge]];

				int currentStart = currNode->_start;
				currNode->_start = currNode->_start+alen;

				_tnode *newLeafNode = new _tnode(start_pos, _end);
				_tnode *newInternalNode = new _tnode(currentStart, new _End(currentStart+alen-1));
				newInternalNode->nodeMark = -1;

				newInternalNode->addChild(input_vect[alen+newInternalNode->_start], currNode);
				newInternalNode->addChild(input_vect[start_pos], newLeafNode);
				// replacing newInternal node with previous node
				anode->childs[input_vect[newInternalNode->_start]] = newInternalNode;
				if(lastIntNode){
					lastIntNode->suffix_link = newInternalNode;
				}
				newInternalNode->suffix_link = root;
				lastIntNode = newInternalNode;


				if(anode == root){
					//cout<<"root"<<endl;
					alen--;
					aedge++;
				}
				else{
					//cout<<"not root"<<endl;
					anode = anode->suffix_link;
				}

				_suffixToBeAdded--;
			}

		}
		cout<<" active edge "<<aedge<<"alen "<<alen<<endl;
	}
}

void printTreeNodes(_tnode *tree){

	if(tree!=root){
		cout<<tree->_start<<" "<<tree->_end->end_val;
		if(tree->nodeMark==-1) cout<<" internal"<<endl;
		else cout<<" leaf"<<endl;
	}
	MM::iterator it=tree->childs.begin();
	if(it==tree->childs.end()) return;
	for(;it!=tree->childs.end();++it){
		printTreeNodes(it->second);
	}
}

_tnode * buildTree(_vint input_vect){
	 root = new _tnode();
	_ap.active_node = root;
	_ap.active_edge = -1;
	_ap.active_len = 0;


	for(int i=0;i<input_vect.size();i++)
	{
		//cout<<"calling builds"<<endl;
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


	input_vect.push_back(100);		// adding unique last char
	//testGetNextElement();
	vPrint(input_vect);
	_tnode *tree = buildTree(input_vect);

	//_tnode *obj = tree->childs[1];

	printTreeNodes(tree);
	/*
	MM::iterator it;
	for(it=tree->childs.begin();it!=tree->childs.end();++it){
		cout<<it->second->_start<<" "<<it->second->_end->end_val<<"internal marker"<<it->second->nodeMark<<endl;
	}
	*/

	//calculateLeftDiverse(tree, input_vect);

	//printSuffixes(tree, {});

	return 0;
}
