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
void vPrint(int start_pos){
	for(int i=start_pos;i<input_vect.size();i++) cout<<" "<<input_vect[i];
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
	debug_stmt(cout<<"\ninside getnextel "<<nodeDir->_start<<" "<<edgeLen<<" "<<alen<<" "<<curr_element<<" "<<aedge<<endl;)

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
		debug_stmt(cout<<"foitta before return "<<anode->_start<<" "<<alen<<"  "<<aedge<<endl;)
		return getNextElement(curr_pos);
	}
}
void buildPhases(int start_pos){
	_end->end_val++;
	_tnode *lastIntNode = 0;
	_suffixToBeAdded++;
	debug_stmt(cout<<"end val "<<_end->end_val<<" ";)
	while(_suffixToBeAdded > 0){
		if(_ap.active_len==0){
			if(anode->childs.find(input_vect[start_pos])!=anode->childs.end()){
				debug_stmt(cout<<"if if"<<endl;)
				// show stopper
				_ap.active_edge = anode->childs[input_vect[start_pos]]->_start;
				_ap.active_len++;
				debug_stmt(cout<<" active edge "<<aedge<<"alen "<<alen<<endl;)
				break;
			}
			else{
				debug_stmt(cout<<"if else"<<endl;)
				_tnode *newChild = new _tnode(start_pos,_end);
				root->addChild(input_vect[start_pos],newChild);
				_suffixToBeAdded--;
			}
		}
		else{
			// getting the next element in case active len not 0
			int nextElm = getNextElement(start_pos);



			if(nextElm==-1){	// a leaf node need to be added here
				debug_stmt(cout<<"else if -1"<<endl;)
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
				debug_stmt(cout<<" active edge "<<aedge<<"alen "<<alen<<endl;)
				continue;
			}

			if(nextElm==input_vect[start_pos]){
				debug_stmt(cout<<"else if"<<endl;)
				if(lastIntNode){
					lastIntNode->suffix_link = anode->childs[input_vect[aedge]];
				}

				// updating active len and other things
				_tnode *currNode = anode->childs[input_vect[aedge]];
				debug_stmt(cout<<"comparison"<<currNode->_end->end_val<<"-"<<currNode->_start<<" "<<alen<<endl;)

				if(currNode->_end->end_val-currNode->_start < alen){
					anode = currNode;
					alen = alen - (currNode->_end->end_val-currNode->_start);
					aedge = currNode->childs[input_vect[start_pos]]->_start;
				}
				else {
					alen++;
				}
				debug_stmt(cout<<" active edge "<<aedge<<"alen "<<alen<<endl;)
				break;
			}
			else{
				debug_stmt(cout<<"else else"<<endl;)
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
		debug_stmt(cout<<" active edge "<<aedge<<"alen "<<alen<<endl;)
	}
}

void printTreeNodes(_tnode *tree){

	if(tree!=root){

		cout<<"nodeMark "<<tree->nodeMark<<" [s-e] "<<tree->_start<<"-"<<tree->_end->end_val<<endl;
		/*if(tree->nodeMark==-1){}
		else{
			cout<<"suffix started at "<<tree->nodeMark<<endl;
			vPrint(tree->nodeMark);
			cout<<endl;

		}*/
	}
	MM::iterator it=tree->childs.begin();
	if(it==tree->childs.end()) return;
	for(;it!=tree->childs.end();++it){
		printTreeNodes(it->second);
	}
}

void printMaxRepeats(_tnode *tree){
	if(tree!=root){
		if(tree->leftDiverse){
			cout<<"maximal repeat, starts from"<<endl;
			vPrint(tree->start_pos);
			cout<<endl;cout<<"ends at "<<tree->_end->end_val<<endl;
		}
	}
	MM::iterator it=tree->childs.begin();
	if(it==tree->childs.end()) return;
	for(;it!=tree->childs.end();++it){
		printMaxRepeats(it->second);
	}
}

// recursive procedure mark every leaf node with start pos of suffix it reps
void assignNodeMarker(_tnode *node, int cumLen){
	if(node->childs.empty()){
		cout<<"cumLen "<<cumLen<<" nodeMark "<<node->nodeMark<<" [s-e] "<<node->_start<<"-"<<node->_end->end_val<<endl;
		node->nodeMark = node->_start-cumLen;
		return ;
	}
	for(MM::iterator it=node->childs.begin();it!=node->childs.end();++it){
		assignNodeMarker(it->second, (cumLen+(node->_end->end_val - node->_start+1)));
	}
}

// recursive function for calculating left diverseness hence maximal repeats
bool calcLeftDiverse(_tnode *node){
	cout<<"here "<<node->nodeMark<<" "<<node->_start<<endl;
	if(node->nodeMark>=0){
		if(node->nodeMark>0)
			node->leftChar = input_vect[node->nodeMark-1];
		node->start_pos.push_back(node->nodeMark);
		return false;
	}

	for(MM::iterator it=node->childs.begin();it!=node->childs.end();++it){
		node->leftDiverse = calcLeftDiverse(it->second) || node->leftDiverse;
		node->start_pos.insert(node->start_pos.end(),it->second->start_pos.begin(),it->second->start_pos.end());
	}

	if(node->leftDiverse) return true;
	unordered_set<int> dup_set;

	for(MM::iterator it=node->childs.begin();it!=node->childs.end();++it){
		if(it==node->childs.begin()) {dup_set.insert(it->second->leftChar);continue;}

		if(dup_set.find(it->second->leftChar)==dup_set.end()){
			node->leftDiverse = true; return true;
		}
	}
	node->leftChar = node->childs.begin()->second->leftChar;
	return false;

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

	cout<<"Ukkenon's program..."<<endl;

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
	cout<<endl;
	_tnode *tree = buildTree(input_vect);

	assignNodeMarker(tree, -1);		// has to call with -1 because of root label is 0,0
	//calcLeftDiverse(tree);
	//printMaxRepeats(tree);

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
