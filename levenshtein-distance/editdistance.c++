#include<iostream>
#include<string>
#include<vector>

using namespace std;

int min(int a, int b, int c){
  return min(min(a,b),c);
}

int saveAndReturn(int val, vector<vector<int>*>* savedDistances, int m, int n){
  savedDistances->at(m)->at(n) = val;
  return val;
}

int editDistance(string* first, string* second, vector<vector<int>*>* savedDistances, int m, int n){
  // Memoized case
  int memoizedVal = savedDistances->at(m)->at(n);
  if (memoizedVal != -1)
    return memoizedVal;

  // Trivial case: m == 0, n == 0
  else if (m == 0 && n == 0){
    return saveAndReturn(0, savedDistances, m, n);
  }

  // Edge case: m == 0, n > 0
  else if (m == 0 && n > 0){
    return saveAndReturn(n, savedDistances, m, n);
  }

  // Edge case: m > 0, n == 0
  else if (m > 0 && n == 0){
    return saveAndReturn(m, savedDistances, m, n);
  }

  // General case.  m > 0 && n > 0
  else {
    char a = (*first)[m-1];
    char b = (*second)[n-1];
    int indicator = (a == b) ? 0 : 1;
    return min(
      editDistance(first, second, savedDistances, m-1, n) + 1,
      editDistance(first, second, savedDistances, m, n-1) + 1,
      editDistance(first, second, savedDistances, m-1, n-1) + indicator
    );
  }
}

int editDistance(string* first, string* second){
    int m = first->length();
    int n = second->length();
    vector<vector<int>*>* savedDistances = new vector<vector<int>*>();
    for(int i = 0; i <= m; i++){
      vector<int>* row = new vector<int>();
      for(int j = 0; j <= n; j++){
        row->push_back(-1);
      }
      savedDistances->push_back(row);
    }
    return(editDistance(first, second, savedDistances, m, n));
}

int main(int argc, char** argv){
  string* first = new string(argv[1]);
  string* second = new string(argv[2]);

  cout << "Computing edit distance between " << *first << " and " << *second << ":\n";
  int dist = editDistance(first, second);
  cout << "Edit distance between " << *first << " and " << *second << ": " << dist << '\n';
}
