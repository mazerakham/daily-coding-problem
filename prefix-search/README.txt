For this problem, we are given a (possibly quite large) dictionary of words,
such as

{"apple", "hello", "world", "hear", "here", "aardvark", "always", "apricot"}

We wish to implement a data structure which allows us to search for a prefix
in constant time with respect to the size of the dictionary and linear
time with respect to the length of the prefix.  

Thus, for example, given a prefix "he" we would return TRUE because there is
a word with prefix "he", whereas given the prefix "hev" we would return FALSE
because there is no word with prefix "hev".

The program prefixsearch.c++ implements a search tree data structure called
StrSearchTree which allows for this constant-linear time search.  The main
challenge was to construct the tree, which is implemented with the function

StrSearchTree* constructTree(vector<string>* words)

There is also included a convenience function

string print()

which prints a string representation of the tree.  For example, for the
dictionary above, after construction, calling print() returns the string

((a(p(p(l(e)))(r(i(c(o(t))))))(a(r(d(v(a(r(k)))))))(l(w(a(y(s))))))(h(e(l(l(o)))(a(r))(r(e))))(w(o(r(l(d))))))

which represents

            a               h         w
         p   a   l          e         o
       p  r  r   w       l  a  r      r
       l  i  d   a       l  r  e      l
       e  c  v   y       o            d
          t  k   s
 
Of course, the function bool hasPrefix(string pref) is easy to implement
once this data structure exists.  
