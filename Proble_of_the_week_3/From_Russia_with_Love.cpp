#include <iostream>
#include <vector>
#include <bits/stdc++.h>

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

int r(const VI& x, int i, int j, int m, VVI& memory){
  
  if(i > j) return 0;
  if(j-i < 1) return memory[i][j] = 0;
  if(memory[i][j] != -1) return memory[i][j];
  
  int left_choice, right_choice;
  left_choice = INT_MAX; right_choice = INT_MAX;
  for(int l=0; l<m; l++){
    left_choice = std::min(r(x, i+l+1, j-m+l+1, m, memory), left_choice);
    right_choice = std::min(r(x, i+l, j-m+l, m, memory), right_choice);
  }
  memory[i][j] = std::max(left_choice + x[i], right_choice + x[j-1]);
  return memory[i][j];
  
}

void testcase(){
  int n, m, k; std::cin >> n >> m >> k;
  std::vector<int> x;
  VVI memory(n+1, VI(n+1, -1));
  
  for(int i=0; i<n; i++){
    int this_coin; std::cin >> this_coin;
    x.push_back(this_coin);
  }
  
  int my_revenue = INT_MAX;
  for(int i=0; i<k+1; i++) {my_revenue = std::min(r(x, i, n-k+i, m, memory), my_revenue);}
  std::cout << my_revenue << "\n";
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t = 0; std::cin >> t;
  for(int k=0; k<t; k++){
    testcase();
  }
}
