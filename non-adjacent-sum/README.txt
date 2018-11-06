Given an array of ints, we set out to find the largest "non-adjacent sum"
that can be formed from the array.  By this we mean, for example,
if we have the array 

[1 2 5 3 4 0 6]

then a "non-adjacent sum" would be 1 + 3 + 6 or 2 + 3 + 0.
However it would be illegal to take 1 + 2 + 6 because 1 and 2
are adjacent.  

The c++ program largesum.c++ solves this problem with the function

int largest_nonadj_sum(int* nums, int start, int len)

Calling this function with start=0 and len=<length of array of ints>
yields the largest non-adjacent sum.  
