#include <iostream>
#include <vector>

using namespace std;

int r(vector<int> v, vector<vector<int>> &memo, int i, int j){

    int sum = 0;
    for(int k = i; k<=j; k++) sum += v[k];

    if(i==j) {
      return v[i];
      memo[i][j]=v[i];
    }
      
    if(memo[i][j] != -1) return memo[i][j];

    memo[i][j] = max(memo[i][j], sum-r(v,memo,i+1,j));
    memo[i][j] = max(memo[i][j], sum-r(v,memo,i,j-1));

    return memo[i][j];
  }

void testcase(){
  
  int n = 0; cin >> n;
  vector<int> v(n,0);
  for(int i=0; i<n; i++){cin >> v[i];}
  
  // I create the memory matrix
  vector<vector<int>> memo(n);
  for ( int i = 0 ; i < n ; i++ ){memo[i].resize(n);}
  
  // I initialize the memory matrix to -1 in each entry O(n^2)
  for ( int i = 0 ; i < n ; i++ ){
    for ( int j = 0 ; j < n ; j++ ){memo[i][j]=-1;}
  }
  cout << r(v, memo, 0, n-1) << "\n";
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t = 0; cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
