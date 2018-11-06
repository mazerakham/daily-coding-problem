#include<string>
#include<iostream>
#include<vector>

using namespace std;

class StrSearchTree {
public:
  char val;
  vector<StrSearchTree*>* children; // List of pointers to children.
public:
  StrSearchTree(char c){
    this->val = c;
    this->children = new vector<StrSearchTree*>();
  }
  StrSearchTree(){
    this->val = '\0';
    this->children = new vector<StrSearchTree*>();
  }
  StrSearchTree* getChildByIndex(int i){
    return (*(this->children))[i];
  }
  StrSearchTree* findChild(char c){
    /*
    Return a pointer to the child which contains the character as its val,
    or else return NULL.
    */
    for(int i = 0; i < this->children->size(); i++){
      StrSearchTree* child = this->getChildByIndex(i);
      if( child->val == c ){
        return child;
      }
    }
    return NULL;
  }

  bool hasPrefix(string pref){
    if(pref.length() == 0) return true;
    char first = pref[0];
    string rest = pref.substr(1);
    StrSearchTree* child = findChild(first);
    return (child!=NULL) && child->hasPrefix(rest);
  }

  string print(){
    string ret = "(";
    if(this->val != '\0'){
      ret.append(string(&(this->val),1));
    }
    for(int i = 0; i < this->children->size(); i++){
      ret.append( this->getChildByIndex(i)->print() );
    }
    char close = ')';
    string closeString = string(&close);
    ret.append(closeString);
    return ret;
  }
};

void processWord(StrSearchTree* searchTree, string word){
  if (word.length() == 0) {
    // do nothing.
    return;
  }
  char first = word[0];
  string rest = word.substr(1);
  StrSearchTree* theChild = searchTree->findChild(first);
  if(theChild == NULL){
    theChild = new StrSearchTree(first);
    searchTree->children->push_back(theChild);
  }
  processWord(theChild, rest);
}

StrSearchTree* constructTree(vector<string>* words) {
  StrSearchTree* searchTree = new StrSearchTree();
  for(int i = 0; i < words->size(); i++){
    processWord(searchTree, (*words)[i]);
  }
  return searchTree;
}

int main(int argc, char** argv) {
  int num_words = 8;
  vector<string> words = {"apple", "hello", "world", "hear", "here", "aardvark", "always", "apricot"};
  char search_pref1 [] = "hev"; // won't be there.
  char search_pref2 [] = "he"; //will be there

  StrSearchTree* tree = constructTree(&words);
  cout << tree->print() << '\n';
  cout << "Has " << search_pref1 << "? " << tree->hasPrefix(search_pref1) << '\n';
  cout << "Has " << search_pref2 << "? " << tree->hasPrefix(search_pref2) << '\n';
}
