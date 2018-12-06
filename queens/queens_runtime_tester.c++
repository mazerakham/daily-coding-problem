#include<iostream>
#include<string>
#include<ctime>
#include<fstream>

using namespace std;

#define FIRST_EXPERIMENT 3
#define LAST_EXPERIMENT 13
#define TOTAL_EXPERIMENTS (LAST_EXPERIMENT - FIRST_EXPERIMENT + 1)

int main(int argc, char** argv){
  fstream fs;
  clock_t start;
  fs.open("runtimes.txt", fstream::out);
  char argLists [TOTAL_EXPERIMENTS][20];
  for(int i = 0; i < TOTAL_EXPERIMENTS; i++) {
    string command = string("queens ") + to_string(i + FIRST_EXPERIMENT);
    command.copy(argLists[i], command.size() + 1);
    argLists[i][command.size()] = '\0';

    double duration;
    start = clock();
    system(argLists[i]);
    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;

    fs << duration << '\n';
  }
  fs.close();
  return 0;
}
