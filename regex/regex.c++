#include<iostream>
#include<string>
#include<vector>

using namespace std;

class RegexNode{
public:
  bool isComputed;
  bool isValid;
public:
  RegexNode(){
    this->isComputed = false;
  }
  bool setValid(bool valid){
    this->isComputed = true;
    this->isValid = valid;
    return valid;
  }
};

bool isValid(string* regex, string* str, vector<vector<RegexNode*>*>* states, int i, int j){

  //Trivial case: empty regex and empty string.
  if(i == regex->length() && j == str->length())
    return true;

  RegexNode* thisState = states->at(i)->at(j);

  //Memoized case: we already computed this.
  if(thisState->isComputed){
    return thisState->isValid;
  }

  //Edge case 1: reached end of regex but not the end of the string.
  if(i == regex->length() && j < str->length()){
    thisState->setValid(false);
  }

  //Edge case 2: we reached the end of the string but not the end of the regex.
  char nextRegexChar = (*regex)[i];
  if(i < regex->length() && j == str->length()){
    if (nextRegexChar == '*'){
      return thisState->setValid(isValid(regex, str, states, i+1, j));
    }
    else{
      return thisState->setValid(false);
    }
  }

  //General case: not at end of string or end of regex.
  char nextStrChar = (*str)[j];
  if(nextRegexChar == '*'){
    //General case A: *
    //Take greedy approach--match it to as much as possible.
    for(int jNew = str->length(); jNew >= j; jNew--){
      if(isValid(regex, str, states, i+1, jNew)){
        return thisState->setValid(true);
      }
    }
    // If we reached end of for loop, it means that we failed.
    return thisState->setValid(false);
  }
  else if (nextRegexChar == '.'){
    //General case B: .
    return thisState->setValid(isValid(regex, str, states, i+1, j+1));
  }
  else {
    //General case C: standard character
    if(nextStrChar == nextRegexChar) // verbatim match.
      return thisState->setValid(isValid(regex, str, states, i+1, j+1));
    else // non-match.
      return thisState->setValid(false);
  }
}

bool match(string* regex, string* str){
  int regexLen = regex->length();
  int strLen = str->length();
  vector<vector<RegexNode*>*>* states = new vector<vector<RegexNode*>*>();
  for(int i = 0; i < regex->length(); i++){
    vector<RegexNode*>* row = new vector<RegexNode*>();
    states->push_back(row);
    for(int j = 0; j <= str->length(); j++){ // Note that we must check the end-of-string.
      row->push_back(new RegexNode());
    }
  }

  return isValid(regex, str, states, 0, 0);
}

int main(int argc, char** argv){
  string* theRegex = new string(argv[1]);
  string* theWord = new string(argv[2]);
  if(match(theRegex, theWord))
    cout<<"It's a match!\n";
  else
    cout<<"It's not a match.\n";
  return 0;
}
