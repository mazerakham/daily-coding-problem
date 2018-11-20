Given a string without spaces like "bedbathandbeyond"
and a dictionary like {"bed", "bath", "bedbath", "and", "beyond"},

we want to return a valid splitting of the sentence, as in

{"bed", "bath", "and", "beyond"}

or

{"bedbath", "and", "beyond"}.

Solution:
sentencesplit.c++ implements the function sentenceSplit(string sentence, vector<string>* words)
which performs this task.  We use memoization so that we don't repeat computations and a search
tree to efficiently store and search the dictionary.  (See the class StrSearchTree.) 
