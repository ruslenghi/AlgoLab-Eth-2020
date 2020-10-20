#include <iostream>
#include <vector>

using namespace std;

int r(int pos, int n, vector<vector<int>> &matrix, vector<int> &memo){
  
  if(pos == n) return 0;
  if(memo[pos] != -1) return memo[pos];
  
  int res = n;
  int i = 0;
  
  while(matrix[pos][i] != 0){
    if(matrix[pos][i] == n){
      memo[matrix[pos][i]] = 1;
      return 1;
    }
    int j = 0;
    int temp = -1;
    while(matrix[matrix[pos][i]][j] != 0){
      temp = max(temp,2+r(matrix[matrix[pos][i]][j], n, matrix, memo));
      j ++;
    }
    res = min(res,temp);
    i++;
  }

  if(memo[pos] == -1) memo[pos] = res;
  return res;
    
  }

void testcase(){
  
  int n = 0; cin >> n;
  int m= 0; cin >> m;
  int R = 0; cin >> R;
  int B = 0; cin >> B;
  
  // I prepare a matrix to store information about the geometry of the board
  vector<vector<int>> matrix(n+1);
  for (int i = 0 ; i < n+1 ; i++ ){matrix[i].resize(n+1);}
  
  vector<int> v(n+1,0);
  
  // I fill the matrix O(n)
  // On row x of the matrix I will have all the bonds starting from point x
  for(int i = 0; i<m; i++){   
    int x = 0; cin >> x;
    int y = 0; cin >> y;
    matrix[x][v[x]]=y;
    v[x] += 1;}
    
  vector<int> memo(n+1,-1);
  
  int best_R = 0;
  int best_B = 0;
  
  // I divide the problem in determining the best strategy for B and for R
  // separately, as the two meeples do not interact. I then compare the lengths 
  // of the stategies and pick the smaller as the winner.
  
  best_B = r(B, n, matrix, memo);
  best_R = r(R, n, matrix, memo);
  
  if(best_B > best_R ) cout << 0 << "\n"; // If R arrives first Holmes wins
  if(best_B < best_R ) cout << 1 << "\n"; // If B arrives first Moriarty wins
  if(best_B == best_R and best_B%2==0) cout << 1 << "\n"; //Even draw M wins
  if(best_B == best_R and best_B%2==1) cout << 0 << "\n"; //Odd draw H wins

}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t = 0; cin >> t;
  for(int k=0; k<t; k++){
    testcase();
  }
}
