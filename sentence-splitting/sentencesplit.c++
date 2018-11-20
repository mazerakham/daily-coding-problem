#include<iostream>
#include<string>
#include<vector>

using namespace std;

/**
 *  Fields:
 *  val (char) -- the character in this node
 *  children (vector<StrSearchTree>*) -- children to this node
 *  isEnd (bool) -- whether this node represents the end of a word in the vocabulary
 */
class StrSearchTree {
public:
  char val;
  vector<StrSearchTree*>* children; // List of pointers to children.
  bool isEnd;

public:
  StrSearchTree(char c, bool isEnd){
    this->val = c;
    this->children = new vector<StrSearchTree*>();
    this->isEnd = isEnd;
  }

  StrSearchTree(){
    this->val = '\0';
    this->children = new vector<StrSearchTree*>();
    this->isEnd = false;
  }

  StrSearchTree* getChildByIndex(int i){
    return (*(this->children))[i];
  }

  StrSearchTree* findChild(char c){
    for(int i = 0; i < this->children->size(); i++){
      StrSearchTree* child = this->getChildByIndex(i);
      if( child->val == c ){
        return child;
      }
    }
    return NULL;
  }
};

void processWord(StrSearchTree* searchTree, string word){
  if (word.length() == 0) {
    searchTree->isEnd = true;
    return;
  }
  char first = word[0];
  string rest = word.substr(1);
  StrSearchTree* theChild = searchTree->findChild(first);
  if(theChild == NULL){
    theChild = new StrSearchTree(first, false);
    searchTree->children->push_back(theChild);
  }
  processWord(theChild, rest);
}

StrSearchTree* constructTree(vector<string>* words) {
  StrSearchTree* searchTree = new StrSearchTree();
  for(int i = 0; i < words->size(); i++){
    processWord(searchTree, words->at(i));
  }
  return searchTree;
}



/*
 *  List of flags.  memoizedFlags[i] is false if we haven't yet memoized that
 *  index, and true if we have.
 */
bool* memoizedFlags;

/*
 *  Memoization table.  partialSplits[i] gives a sentence split starting at
 *  position i or NULL if it is impossible.  partialSplits[i] is undefined
 *  if memoizedFlags[i] == false
 */
vector<string>** partialSplits;

/**
 * Arguments:
 * input (string) -- string we are analyzing
 * dictTree (StrSearchTree*) -- dictionary we are using
 * i (int) -- index at which we are performing the analysis
 *
 * Returns:
 * possibleWords (vector<string>*) -- list of all words starting at i in input
 * which are in the dictTree.
 */
vector<string>* getPossibleWords(string input, StrSearchTree* dictTree, int i){
  vector<string>* possibleWords = new vector<string>();
  StrSearchTree* child = dictTree;
  int j = i;
  do{
    child = child->findChild(input[j++]);
    if (child != NULL && child->isEnd)
      possibleWords->push_back(input.substr(i,j-i));
  }while(j < input.length() && child != NULL);
  return possibleWords;
}

/**
 * Arguments:
 * input (string) -- sentence to split
 * dictTree (StrSearchTree*) -- tree representation of dictionary
 * i (int) -- the index in the input from which to start (for recursion)
 *
 * Returns:
 * split (vector<string>) -- a split of the input starting at i or NULL if
 * it is IMPOSSIBLE to do so.  Note, an empty vector means SUCCESS.
 */
vector<string>* sentenceSplit(string input, StrSearchTree* dictTree, int i){

  // Trivial case: i is end of the input.
  if (i == input.length()){
    return new vector<string>();
  }

  // Repeat case: we've seen i before.
  if (memoizedFlags[i] == true){
    return partialSplits[i];
  }

  // Non-trivial case.
  vector<string>* possibleWords = getPossibleWords(input, dictTree, i);
  for(int j = 0; j < possibleWords->size(); j++){
    string possibleWord = possibleWords->at(j);
    vector<string>* nextSplit = sentenceSplit(input, dictTree, i + possibleWord.length());
    if (nextSplit == NULL) continue;
    else{
      nextSplit->insert(nextSplit->begin(), possibleWord);
      memoizedFlags[i] = true;
      partialSplits[i] = nextSplit;
      return nextSplit;
    }
  }
  // If we reach this point, none of the splits were valid.  Conclude it is impossible.
  memoizedFlags[i] = true;
  partialSplits[i] = NULL;
  return NULL;
}

/**
 * Arguments:
 * input (string) -- sentence to split
 * dict (vector<string>*) -- dictionary with which to perform split
 *
 * Returns:
 * split (vector<string>*) -- list of strings representing the sentence split
 */
vector<string>* sentenceSplit(string input, vector<string>* dict){
  StrSearchTree* dictTree = constructTree(dict);
  int len = input.length();
  memoizedFlags = new bool[len];
  partialSplits = new vector<string>* [len];
  for(int i = 0; i < len; i++){
    memoizedFlags[i] = false;
  }
  return sentenceSplit(input, dictTree, 0);
}

int main(int argc, char** argv){
  string dict_arr [] = {"awe","awesome","awesomely","lye","year","ark"};
  string input = "awesomelyeark"; // awesome lye ark
  vector<string>* dict_vec = new vector<string>();
  for(int i = 0; i < 6; i++){
    dict_vec->push_back(dict_arr[i]);
  }

  cout << "word: " << input << '\n';
  cout << "dictionary: ";
  for(int i = 0; i < dict_vec->size(); i++) cout << dict_vec->at(i) << " ";
  cout << '\n';

  vector<string>* split = sentenceSplit(input, dict_vec);

  cout << "the split: ";
  if (split != NULL)
    for(int i = 0; i < split->size(); i++) cout << split->at(i) << " ";
  else
    cout << "[no split possible]";
  cout << '\n';
}
