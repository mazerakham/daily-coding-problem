We say that a tree is a *unival tree* if every node contains the
same value.  So
     1
   /   \
  1     1
is unival whereas
      1
    /   \
   0     1
is not.  This program sets out to solve the following problem:

HOW MANY UNIVAL SUBTREES are there in a given tree?  

For example, the following tree has 3 unival subtrees: 

   a
  / \
 b   a
    / \
   a   b
  / \
 a   a

they are

a             a                a
                             /   \
                            a     a
                            
The code in unival.c++ solves this problem with the function 
BinaryTree::univalSubtreesCount().  The implemented
class BinaryTree also has a show() function and constuctor
for convenience.  
