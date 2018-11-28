#include<string>
#include<vector>
#include<iostream>
#include<iomanip> // setprecision
#include<sstream> // stringstream
#include<math.h> // log, exp
#include<limits> // numeric_limits

using namespace std;


string toString(vector<float>* pathTable){
    stringstream s;
    s << fixed << setprecision(2);
    for(int i = 0; i < pathTable->size(); i++){
      s << " ";
      s << pathTable->at(i);
    }
    s << "\n";
    return s.str();
}

const float inf = std::numeric_limits<float>::infinity();
vector<float>* infTable(int n){
  vector<float>* table = new vector<float>();
  for(int i = 0; i < n; i++){
    table->push_back(inf);
  }
  return table;
}

/**
 *  Take the negative logarithm of each entry in a 2D vector of floats.
 */
vector<vector<float>*>* negLog(vector<vector<float>*>* ratesTable){
    vector<vector<float>*>* transformedTable = new vector<vector<float>*>();
    for(int i = 0; i < ratesTable->size(); i++){
      vector<float>* row = ratesTable->at(i);
      vector<float>* newRow = new vector<float>();
      for(int j = 0; j < row->size(); j++){
        newRow->push_back(-log(row->at(j)));
      }
      transformedTable->push_back(newRow);
    }
    return transformedTable;
}

/**
 * Takes a rates table, determines if there exists arbitrage.
 */
bool existsArbitrage(vector<vector<float>*>* ratesTable){
  int n = ratesTable->size();
  vector<vector<float>*>* ratesTransformed = negLog(ratesTable);
  vector<float>* shortestPathTable = infTable(n); // shortest paths from 0 to j.

  shortestPathTable->at(0) = 0; // Start here.

  for(int i = 0; i < n-1; i++){ // Find all shortest paths of length i
    for(int j = 0; j < n; j++){
      float currShortest = shortestPathTable->at(j);
      for(int k = 0; k < n; k++){ // Try to reach j through k.
        float candidate = shortestPathTable->at(k) + ratesTransformed->at(k)->at(j);
        if(candidate < shortestPathTable->at(j)){
          // 0 -> k -> j is shorter than current 0 -> j.  Update.
          shortestPathTable->at(j) = candidate;
        }
      }
    }
  }

  /* Testing statements.
  cout << "Shortest Path Table:\n";
  cout << toString(shortestPathTable);
  cout << "Now checking for arbitrages...\n";
  */

  for(int j = 0; j < n; j++){
    float currShortest = shortestPathTable->at(j);
    for(int k = 0; k < n; k++){ // try to reach j through k.
      float candidate = shortestPathTable->at(k) + ratesTransformed->at(k)->at(j);
      if(candidate < currShortest){
        // We've just found a path of length n which is shorter than a path of
        // length n-1.  This can only be the case because of an arbitrage.
        return true;
      }
    }
  }
  return false; // no arbitrages found.  All paths of length n were not
                // improvements on paths of length n-1.
}



string toString(vector<vector<float>*>* ratesTable){
  stringstream s;
  s << fixed << setprecision(2);
  int n = ratesTable->size();
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      s << " ";
      s << ratesTable->at(i)->at(j);
    }
    s << "\n";
  }
  return s.str();
}

int main(int argc, char** argv){

  // exchangeRates[i][j] = a means
  // "One of currency i purchases a quantity of currency j."
  // Thus "large values are 'good'."
  const int n = 3;
  vector<vector<float>*>* exchangeRates1 = new vector<vector<float>*>();
  vector<vector<float>*>* exchangeRates2 = new vector<vector<float>*>();

  // NO ARBITRAGE
  exchangeRates1->push_back(new vector<float> {1.00,2.00,3.00});
  exchangeRates1->push_back(new vector<float> {0.45,1.00,1.40});
  exchangeRates1->push_back(new vector<float> {0.31,0.64,1.00});

  cout << "Analyzing the following exchange table (there should be no arbitrage here):\n" << toString(exchangeRates1);
  cout << "...";
  bool arbEx = existsArbitrage(exchangeRates1);
  cout << (arbEx ? "Arbitrage found!\n" : "No arbitrage found.\n");
  cout << '\n';

  // YES ARBITRAGE 1 -> 2 -> 3 -> 1
  exchangeRates2->push_back(new vector<float> {1.00, 2.00, 2.80});
  exchangeRates2->push_back(new vector<float> {0.30, 1.00, 1.50});
  exchangeRates2->push_back(new vector<float> {0.35, 0.66, 1.00});

  cout << "Analyzing the following exchange table (there SHOULD be an arbitrage here):\n" << toString(exchangeRates1);
  cout << "...";
  arbEx = existsArbitrage(exchangeRates2);
  cout << (arbEx ? "Arbitrage found!\n" : "No arbitrage found.\n");
  cout << '\n';

  return 0;
}
