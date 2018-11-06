#include <iostream>
#include <string.h>
using namespace std;

int* decodings_table;

int num_decodings_dyn(char* msg, int start_pos, int len){
  // cout << "start position: " << start_pos << '\n';

  int chars_left = len - start_pos;
  int first_branch_decodings = 0;
  int second_branch_decodings = 0;

  if (chars_left == 0){
    // cout << start_pos << ": No characters left.  Returning 1.\n";
    return 1;
  }
  else if (decodings_table[start_pos] != -1){
    // cout << "I've seen this before, it's" << decodings_table[start_pos] << ".\n";
    return decodings_table[start_pos];
  }
  else if (msg[start_pos] == '0'){
    decodings_table[start_pos] = 0;
    return 0;
  }
  else if (chars_left == 1){
    // cout << start_pos << ": One character left.  Returning 1.\n";
    decodings_table[start_pos] = 1;
    return 1;
  }
  else {
    int first_int = msg[start_pos] - '0';
    int second_int = msg[start_pos+1] - '0';
    if ((first_int <= 2) && (second_int <= 6)) {
      // cout << "Calculating second_branch_decoding\n";
      second_branch_decodings = num_decodings_dyn(msg, start_pos + 2, len);
    }
    first_branch_decodings = num_decodings_dyn(msg, start_pos + 1, len);
    // cout << start_pos << ": Two or more left. Branch 1: " << first_branch_decodings << ", Branch 2: " << second_branch_decodings << '\n';
    decodings_table[start_pos] = first_branch_decodings + second_branch_decodings;
    return first_branch_decodings + second_branch_decodings;
  }
}

int num_decodings(char* msg) {
  int len = strlen(msg);

  decodings_table = new int[len];
  for(int i = 0; i < len; i++)
    decodings_table[i] = -1;

  return num_decodings_dyn(msg, 0, len);
}

int main(int argc, char *argv[])
{
  char* msg = argv[1];
  cout << "the message is " << msg << '\n';
  int n = num_decodings(msg);
  cout << "The number of decodings of " << msg << " seems to be " << n;
}
