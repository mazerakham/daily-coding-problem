Given an string of numeric characters such as

"101327"

we wish to count how many different unique ASCII strings
could be represented by this string, if we are allowed
to insert spaces, and if we assume that

'a' is encoded by '1'
'b' is encoded by '2'
...
'j' is encoded by '10'
...
'z' is encoded by '26'

In our example with the string "1013152", this could be 
read, for example, as

10-1-3-15-2 -> jacob
10-13-1-5-2 -> jmaeb

Again, the question is to compute the NUMBER of possible
unique strings that could be represented by this string
"1013152" (or any such given string).  
