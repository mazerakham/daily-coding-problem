#include<iostream>
#include<string>
#include<vector>
#include<sstream> // stringstream

using namespace std;

/**
 * Convenience methods for printing various vectors.
 */
string toString(vector<int>* intvec){
  stringstream s;
  for(int i = 0; i < intvec->size(); i++){
    s << intvec->at(i) << " ";
  }
  return s.str();
}

/**
 *  Represents a node in a search tree which can see its parent as well as its children.
 */
class SearchTree {
public:
  SearchTree* parent; // If parent is NULL, this is the base tree.
  int n;
  int col;
  int row;
  bool dead;
  bool leaf;
  vector<SearchTree*>* children; // Only living children shall be placed in a node.
public:
  /*
   * Constructs the base.  col will always be the generation of the node.
   */
  SearchTree(SearchTree* parent, int n){
    this->parent = parent;
    this->n = n;
    this->col = -1;
    this->children = new vector<SearchTree*>();
    this->dead = false;
  }

  /*
   * Constructs a "typical node" in the search which knows its parent but
   * doesn't yet know its children.
   */
  SearchTree(SearchTree* parent, int n, int col, int row){
    this->parent = parent;
    this->n = n;
    this->col = col;
    this->row = row;
    this->dead = false;
    this->leaf = (col == n-1) ? true : false;
    this->children = (this->leaf) ? NULL : new vector<SearchTree*>();
  }

  /*
   * Returns the list of ancestral nodes INCLUDING THIS NODE.
   */
  vector<SearchTree*>* getAncestors(){
    // Base node is special--it gives empty ancestor list.
    if (this->parent == NULL) {
      return new vector<SearchTree*>();
    }

    // General case.  Don't forget, a node adds itself to its ancestor list
    // (unless it is the base node).
    vector<SearchTree*>* ancestors = this->parent->getAncestors();
    ancestors->push_back(this);
    return ancestors;
  }

  /**
   * Returns the list of rows in which a queen can be legally placed in the
   * next column.
   */
  vector<int>* getImmediatelyValidRows(){
    vector<int>* validRows = new vector<int>();
    vector<SearchTree*>* ancestors = getAncestors();
    for(int i = 0; i < this->n; i++){
      bool legal = true;
      for(int j = 0; j < ancestors->size(); j++){
        SearchTree* ancestor = ancestors->at(j);
        int a_x = ancestor->col;
        int a_y = ancestor->row;
        int c_x = this->col + 1;
        int c_y = i;
        if (c_y == a_y || a_y - c_y == a_x - c_x || a_y - c_y == c_x - a_x) {
          legal = false;
          break;
        }
      } //end of inner loop
      if (legal) validRows->push_back(i);
    } // end of loop through rows.
    return validRows;
  }

  /*
   * 1.  Constructs a list of "immediately valid" rows.
   * 2.  Constructs children for each of them, recursively calling
   *      growValidBranches() on each
   * 3.  Only adds children which are ALIVE.
   * 4.  Declares itself dead if all its children are dead.
   */
  void growValidBranches(){
    vector<int>* immediatelyValidRows = this->getImmediatelyValidRows();
    for(int i = 0; i < immediatelyValidRows->size(); i++){
      SearchTree* child = new SearchTree(this, this->n, this->col + 1, immediatelyValidRows->at(i));
      if(!child->leaf) {
        child->growValidBranches();
      }
      if(!child->dead) {
        this->children->push_back(child); // Only living children are added.
      }
    }

    if (this->children->size() == 0) {
      this->dead = true;
    }
  }

  /*
   * Counts how many leaves are below this node.
   */
  int countLeaves(){
    // Leaf case
    if (this->leaf) {
      return 1;
    }

    // General recursive step
    int count = 0;
    for(int i = 0; i < this->children->size(); i++){
      count += this->children->at(i)->countLeaves();
    }
    return count;
  }
};

SearchTree* buildSearchTree(int n){
  SearchTree* base = new SearchTree(NULL, n);
  base->growValidBranches();
  return base;
}

int calculate_arrangements(int n){
  SearchTree* tree = buildSearchTree(n);
  return tree->countLeaves();
}

int main(int argc, char** argv){
  int n = stoi(argv[1]);  // Size of the board is passed as an argument.
  cout << "Counting all queen arrangements on baord of size " << n << '\n';
  int num_queen_arrangements = calculate_arrangements(n);
  stringstream s;
  s << "The number of arrangements on a board of size " << n << " is " << num_queen_arrangements << '\n';
  cout << s.str();
}
