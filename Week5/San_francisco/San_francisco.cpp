#include<iostream>
#include<vector>

long long int dp(std::vector<std::vector<long long int>> &memo, std::vector<std::vector<std::pair<int,int>>> &table, int p, int k){
  
  if(memo[p][k] != -1) return memo[p][k];
  if(k == 0) return 0; //In case I have no more moves left I get zero points
  
  //In case I am at a node that has no offspring, 
  //I can move back to the start without any additional cost
  if(table[p].size() == 0){
    memo[p][k] = dp(memo, table, 0, k);
    return memo[p][k];}
    
  long long int result = 0;
  for(int i=0; i<(int)table[p].size(); i++){
    result = std::max(result, dp(memo, table, table[p][i].first, k-1) + table[p][i].second);
  }
  
  memo[p][k] = result;
  return memo[p][k];
  
}

void testcase(){
  
  int n, m; std::cin >> n >> m;
  long long int x; std::cin >> x;
  int k; std::cin >> k;
  
  //table[i][j] will tell me that the value of the j-th pair I can pick when starting from i
  std::vector<std::vector<std::pair<int,int>>> table(n, std::vector<std::pair<int,int>>());
  for(int i=0; i<m; i++){
    int u, v, p; std::cin >> u >> v >> p;
    table[u].push_back(std::make_pair(v,p));
  }
  
  //Now I make a memory. memo[i][j] will store how many points I can get if I start in i
  //and considering that I have j moves left 
  std::vector<std::vector<long long int>> memo(n, std::vector<long long int> (k+1, -1));
  for(int i=0; i<=k; i++){
    long long int result = dp(memo, table, 0, i);
    if(result >= x){
      std::cout << i << "\n";
      return;}
  }
  
  std::cout << "Impossible\n";
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
