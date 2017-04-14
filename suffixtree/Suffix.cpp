#include "Suffix.h"

#define DATA_SIZE 10000

//int numOfMatchedChar(string str, int start_pos, string str2)
void vPrint(VINT v){
	for(auto i:v) cout<<" "<<i; cout<<endl;
}
int numOfMatchedChar(VINT str, int start_pos, VINT str2)
{
	int ret=0;
	for(int i=0;i<str2.size();i++){
		if(str2[i]!=str[i+start_pos]) break;
		ret++;
	}
	return ret;
}

void addSuffix(VINT str, int start_pos, int suffix_label, TN *currNode){

	// checking matching child node

	bool matchedFlag = false;
	for(int i=0 ;i<currNode->childs.size(); i++){
		TN *n = currNode->childs[i];

		if(str.at(start_pos)==n->edge_label.at(0)){
			int matchedLen = numOfMatchedChar(str, start_pos, n->edge_label);
			if(matchedLen==n->edge_label.size()){
				addSuffix(str, start_pos+matchedLen, suffix_label, n);
			}
			else
			{
				// breaking the edge
				//TN *newRoot = new TN(-1, str.substr(start_pos, matchedLen));
				TN *newRoot = new TN(-1, VINT(str.begin()+start_pos , str.begin()+start_pos+matchedLen));
				//TN *newRoot = new TN(-1, "dummy");
				//n->updateLabel(n->edge_label.substr(matchedLen));		// from matchedLen pos up to end
				n->updateLabel(VINT(n->edge_label.begin()+matchedLen , n->edge_label.end()));
				TN *modifiedChild = n;
				//TN *newChild = new TN(suffix_label, str.substr(start_pos+matchedLen));
				TN *newChild = new TN(suffix_label, VINT(str.begin()+start_pos+matchedLen , str.end()));

				newRoot->addChild(modifiedChild);
				newRoot->addChild(newChild);

				// deleting previous link and adding new link
				swap(currNode->childs[i], currNode->childs.back());
				currNode->childs.pop_back();
				currNode->addChild(newRoot);
			}
			matchedFlag = true;
			break;
		}
	}

	if(matchedFlag==false){
		//currNode->addChild(new TN(suffix_label, str.substr(start_pos)));
		currNode->addChild(new TN(suffix_label, VINT(str.begin()+start_pos, str.end())));
	}

}


TN * buildTree(VINT str){
	TN *root = new TN();
	root->addChild(new TN(0,str));	// adding full suffix

	for(int i=1;i<str.size();i++){
		addSuffix(str, i,i,root);
	}

	return root;
}
/*
 * Recursive function to calculate left diverse nodes in a suffix tree
 * params:
 * nd : root node of the suffix tree
 * str : string for which nd is a suffix tree
 * */
//bool calculateLeftDiverse(TN *nd, string &str){
bool calculateLeftDiverse(TN *nd, VINT &str){

	if(nd->nodeMark>=0){
		if(nd->nodeMark>0)
			nd->leftChar = str[nd->nodeMark-1];
		return false;
	}
	else{
		for(auto n:nd->childs){
			nd->leftDiverse = calculateLeftDiverse(n, str) || nd->leftDiverse;
		}
	}

	if(nd->leftDiverse) return true;

	int firstLeftChar = nd->childs[0]->leftChar;
	for(int i=1;i<nd->childs.size();i++){
		if(firstLeftChar!=nd->childs[i]->leftChar) {nd->leftDiverse=true; return true;}
	}
	nd->leftChar = firstLeftChar;
	return false;
}

void printSuffixes(TN *nd, VINT runString){
	if(nd->nodeMark>=0){
		// nothing to do in case of leaves
	}
	for(auto n : nd->childs){

		//if(n->leftDiverse && n->nodeMark<0 && n->edge_label.compare("")){

		VINT temp = runString;
		temp.insert(temp.end(),n->edge_label.begin(), n->edge_label.end());

		if(n->leftDiverse && n->nodeMark<0 && n->edge_label.empty()==false)
		{
			vPrint(temp);
		}

		printSuffixes(n, temp);
	}

}


int main(){
	/*
	string str;
	cin>>str;
	str.append("#");*/

	//VINT str = {1,1,2,3,1,1,2,-2};
	//VINT str = {1,1,2,3,1,1,2,4,1,1,2,3,-2};
	//VINT str = {6,3,6,4,6,3,5,1,1,2,7};*/
	VINT input_vect;
	char input_str[DATA_SIZE];
	fgets(input_str,DATA_SIZE,stdin);
	char *token = strtok(input_str, " ");
	do{
		input_vect.push_back(atoi(token));
		token = strtok(NULL, " ");
	}while(token);
	//vPrint(input_vect);

	TN *tree = buildTree(input_vect);
	calculateLeftDiverse(tree, input_vect);

	printSuffixes(tree, {});


	return 0;
}
