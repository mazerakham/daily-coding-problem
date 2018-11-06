#include <iostream>
#include <string.h>

using namespace std;

/*
  Really this is a special binary tree with helper functions for efficiently
  counting how many unival subtrees it contains.
*/
class BinaryTree {
public:
  int val;
  int univalFlag = -1;
  int univalCount = -1;
  BinaryTree* left = NULL;
  BinaryTree* right = NULL;

public:
  BinaryTree(int val) {
    this->val = val;
  }
  BinaryTree(int val, BinaryTree* left, BinaryTree* right){
    this->val = val;
    this->left = left;
    this->right = right;
  }
  void show() {
    cout << '(' << this->val;
    if (this->left != NULL) this->left->show();
    if (this->right != NULL) this->right->show();
    cout << ')';
  }
  bool isUnival() {
    if (univalFlag == -1) {
      univalFlag =
      (this->left == NULL || (this->left->isUnival() && this->left->val == this->val))
      &&
      (this->right == NULL || (this->right->isUnival() && this->right->val == this->val));
      return univalFlag;
    } else return univalFlag;
  }
  int univalSubtreesCount(){
    if (univalCount != -1) return univalCount;

    int leftCount = 0;
    int rightCount = 0;
    int me = 0;
    if (this->left != NULL) leftCount = this->left->univalSubtreesCount();
    if (this->right != NULL) rightCount = this->right->univalSubtreesCount();
    if (
      ((this->left == NULL)||(this->left->isUnival() && (this->left->val == this->val)))
      &&
      ((this->right == NULL)||(this->right->isUnival() && (this->right->val == this->val)))
    ) me = 1;
    return leftCount + rightCount + me;
  }
};

int main(){
  BinaryTree* testTree =
  new BinaryTree(1,
    new BinaryTree(0),
    new BinaryTree(1,
      new BinaryTree(1,
        new BinaryTree(0),
        NULL
      ),
      new BinaryTree(1,
        NULL,
        new BinaryTree(1)
      )
    )
  );
  testTree->show();
  cout << '\n' << "Number of unival subtrees: " << testTree->univalSubtreesCount();
}
