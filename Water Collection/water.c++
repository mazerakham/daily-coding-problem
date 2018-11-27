#include<iostream>
#include<string>
#include<vector>

using namespace std;

int calculate_water(vector<int>* elevationMap){
  int n = elevationMap->size();

  int score = 0;
  int maxLeft = 0;
  int maxRight = 0;
  int currElevation;

  // Forward Pass - take into account leftward run-off.
  for(int i = 0; i < n; i++){
    currElevation = elevationMap->at(i);
    if (currElevation > maxLeft) {
      score -= (i*(currElevation - maxLeft)); // Take into account run-off to left
      maxLeft = currElevation; // Raise water.
    }
    else {
      score += maxLeft - currElevation; // Take into account water collecting against left wall.
    }
  }

  //Backward pass.  Same thing in reverse.
  for(int i = n-1; i >= 0; i--){
    currElevation = elevationMap->at(i);
    if(currElevation > maxRight) {
      score -= ((n-1-i)*(currElevation - maxRight)); // Take into account run-off to right
      maxRight = currElevation;
    }
    else {
      score += maxRight - currElevation; // Take into account water collecting against right wall.
    }
  }

  return score / 2; //Any actual water collected will have been double-counted.
                    //Any one-way run-off will have been canceled in the passes.
}

int main(int argc, char** argv){

  vector<int>* elevationMap = new vector<int> {0,1,2,3,2,1,0,4,1,2,0};

  cout<< "Elevation map:";
  for(int i = 0; i < elevationMap->size(); i++){
    cout << elevationMap->at(i) << " ";
  }
  cout << '\n';

  int water_amount = calculate_water(elevationMap);
  cout << "Water collected: " << water_amount;

}
