#include<string>
#include<iostream>
#include<vector>

using namespace std;

/**
 * Represents a square on the board.
 *
 * Fields:
 * isWall (bool) represents whether is is a wall.
 * visited (bool) whether the square has been visited
 * pathDist (int) if it's been visited, this will store how far.
 */
class Square{
public:
  bool isWall;
  bool visited = false;
  int pathDist;
  int x;
  int y;
public:
  Square(int x, int y, int wall){
    this->isWall = (bool) wall;
    visited = false;
    this->pathDist = -1;
    this->x = x;
    this->y = y;
  }
  string toString(){
    string retval = (this->isWall) ? "X" : "O";
    retval += ( (this->visited) ? to_string(this->pathDist) : "?" );
    return retval;
  }
};


/**
 * Represents a node in a search queue.
 */
 class SearchQueueNode{
 public:
   Square* val;
   SearchQueueNode* next;
 public:
   SearchQueueNode(Square* val){
     this->val = val;
     this->next = NULL;
   }
   bool hasNext(){
     return (this->next != NULL);
   }
 };

/**
 * Represents a queue of Squares.
 */
class SearchQueue{
public:
  SearchQueueNode* head;
  SearchQueueNode* tail;
public:
  SearchQueue(){
    this->head = NULL;
    this->tail = NULL;
  }
  bool isEmpty(){
    return (this->head == NULL);
  }
  void enqueue(Square* square){
    SearchQueueNode* nextNode = new SearchQueueNode(square);
    if(this->isEmpty()){
      this->head = nextNode;
      this->tail = nextNode;
    }
    else {
      this->tail->next = nextNode;
      this->tail = nextNode;
    }
  }
  Square* dequeue(){
    SearchQueueNode* oldHead = this->head;
    this->head = this->head->next;
    return oldHead->val;
  }

};

/**
 *  Represents a board.
 *
 * Fields:
 * board (vector<vector<square*>*>*) -- represents the board
 * m (int) the height
 * n (int) the width
 */
class Board{
public:
  vector<vector<Square*>*>* board;
  int m; // height
  int n; // width
public:
  Board(int** board_arr, int m, int n){
    this->m = m;
    this->n = n;
    board = new vector<vector<Square*>*>();
    vector<Square*>* row;
    for(int i = 0; i < m; i++){
      row = new vector<Square*>();
      board->push_back(row);
      for(int j = 0; j < n; j++){
        row->push_back(new Square(i,j,board_arr[i][j]));
      }
    }
  }

  string toString(){
    string retval = " ";
    for(int i = 0; i < this->m; i++){
      retval += " ";
      for(int j = 0; j < this->n; j++){
        retval += this->board->at(i)->at(j)->toString();
        retval += " ";
      }
      retval += "\n ";
    }
    return retval;
  }

  Square* at(int i, int j){
    return this->board->at(i)->at(j);
  }

  Square* at(int coords[]){
    return this->board->at(coords[0])->at(coords[1]);
  }

  bool isValidNeighbor(int i, int j){
    return (
      0 <= i &&
      i < this->m &&
      0 <= j &&
      j < this->n &&
      this->at(i,j)->visited==false &&
      this->at(i,j)->isWall==false
    );
  }

  vector<Square*>* getValidNeighbors(Square* square){
    vector<Square*>* validNeighbors = new vector<Square*>();
    int x = square->x;
    int y = square->y;
    if (isValidNeighbor(x-1,y)) validNeighbors->push_back(this->at(x-1,y));
    if (isValidNeighbor(x+1,y)) validNeighbors->push_back(this->at(x+1,y));
    if (isValidNeighbor(x,y-1)) validNeighbors->push_back(this->at(x,y-1));
    if (isValidNeighbor(x,y+1)) validNeighbors->push_back(this->at(x,y+1));
    return validNeighbors;
  }

  void visit(SearchQueue* queue, Square* square){
    if(square->visited) return; // We already visited this square.
    square->visited = true;
    vector<Square*>* neighbors = getValidNeighbors(square);
    Square* neighbor;
    for(int i = 0; i < neighbors->size(); i++){
      neighbor = neighbors->at(i);
      neighbor->pathDist = square->pathDist + 1;
      queue->enqueue(neighbor);
    }

  }

  int shortestPathlength(int start[], int end[]){
    int i = 0;
    SearchQueue* queue = new SearchQueue();
    Square* startSquare = this->at(start);
    startSquare->pathDist = 0;
    queue->enqueue(startSquare);
    while(!(this->at(end)->visited) && !queue->isEmpty()){
      cout << "step " << (i++) << ":\n" << this->toString() << '\n';
      this->visit(queue, queue->dequeue());
    }
    if(!(this->at(end)->visited)) return -1;
    else return this->at(end)->pathDist;
  }
};



int main(int argc, char** argv){
  const int m = 4;
  const int n = 4;
  int** board_arr;
  board_arr = new int* [m];
  board_arr[0] = new int [4] {0,0,0,0};
  board_arr[1] = new int [4] {1,1,0,0};
  board_arr[2] = new int [4] {0,0,0,1};
  board_arr[3] = new int [4] {0,0,0,1};
  Board* board = new Board(board_arr,m,n);
  cout << "The board:\n";
  cout << '\n' << board->toString() << '\n';

  int start [2] = {3,0};
  int end [2] = {0,0};

  cout << "Computing shortest path from (" << start[0] << "," << start[1]
       << ") to (" << end[0] << "," << end[1] << ").\n...\n";
  int answer = board->shortestPathlength(start, end);
  cout << "Shortest path: " << answer << '\n';
  return 0;
}
