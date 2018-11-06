#include <iostream>
#include <string>

using namespace std;

int* scores;

int max(int a, int b){
  return (a > b) ? a : b;
}

int largest_nonadj_sum(int* nums, int start, int len){
  int nums_remaining = len - start;
  int branch_one = 0;
  int branch_two = 0;
  int this_score = 0;
  if (nums_remaining <= 0) return 0;
  else if (nums_remaining >= 1 && scores[start] != -1) return scores[start];
  else if (nums_remaining == 1 && nums[start] <= 0) {
    scores[start] = max(nums[start], 0);
    return max(nums[start], 0);
  }
  else if (nums_remaining > 1){
    // compute score if we accept this number...
    branch_one = max(nums[start],0) + largest_nonadj_sum(nums, start+2, len);
    // ... and if we reject this number...
    branch_two = max(nums[start+1],0) + largest_nonadj_sum(nums, start+3, len);
    this_score = max(branch_one, branch_two);
    scores[start] = this_score;
    return this_score;
  }
}

int main(int argc, char** argv){
  cout << "Arg Count: " << argc << '\n';
  int nums [argc-1];
  int largest_sum;
  scores = new int [argc-1];
  for(int i = 1; i < argc; i++){
    nums[i-1] = std::stoi(argv[i]);
    scores[i-1] = -1;
  }
  largest_sum = largest_nonadj_sum(nums, 0, argc-1);
  cout << "The largest sum seems to be " << largest_sum;
}
