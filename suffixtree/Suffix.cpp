#include "Suffix.h"

int numOfMatchedChar(string str, int start_pos, string str2)
{
	int ret=0;
	for(int i=0;i<str2.length();i++){
		if(str2[i]!=str[i+start_pos]) break;
		ret++;
	}
	return ret;
}

void addSuffix(string str, int start_pos, int suffix_label, TN *currNode){

	// checking matching child node

	bool matchedFlag = false;
	for(int i=0 ;i<currNode->childs.size(); i++){
		TN *n = currNode->childs[i];

		if(str.at(start_pos)==n->edge_label.at(0)){
			int matchedLen = numOfMatchedChar(str, start_pos, n->edge_label);
			if(matchedLen==n->edge_label.length()){
				addSuffix(str, start_pos+matchedLen, suffix_label, n);
			}
			else
			{
				// breaking the edge
				TN *newRoot = new TN(-1, str.substr(start_pos, matchedLen));
				//TN *newRoot = new TN(-1, "dummy");
				//n->updateLabel(n->edge_label.substr(start_pos+matchedLen));
				n->updateLabel(n->edge_label.substr(matchedLen));
				TN *modifiedChild = n;
				TN *newChild = new TN(suffix_label, str.substr(start_pos+matchedLen));

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
		currNode->addChild(new TN(suffix_label, str.substr(start_pos)));
	}

}


TN * buildTree(string str){
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
bool calculateLeftDiverse(TN *nd, string &str){

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

	char firstLeftChar = nd->childs[0]->leftChar;
	for(int i=1;i<nd->childs.size();i++){
		if(firstLeftChar!=nd->childs[i]->leftChar) {nd->leftDiverse=true; return true;}
	}
	nd->leftChar = firstLeftChar;
	return false;
}

void printSuffixes(TN *nd, string runString){
	if(nd->nodeMark>=0){
		//cout<<runString<<" "<<nd->nodeMark<<endl;
	}
	for(auto n : nd->childs){
		if(n->leftDiverse && n->nodeMark<0 && n->edge_label.compare(""))
			cout<<"Maximal repeats: "<<runString+n->edge_label<<endl;
		printSuffixes(n, runString+n->edge_label);
	}

}


int main(){
	string str = "aabcaabdaabcabyabz";
	str.append("#");

	TN *tree = buildTree(str);
	calculateLeftDiverse(tree, str);
	printSuffixes(tree, "");


	return 0;
}
