#include<iostream>
#include<vector>
#include<climits>

std::vector<int> dp(std::vector<std::vector<int>> &memo, std::vector<std::pair<int,int>> &beverages, int v, int n){
  
  if(v <= 0){
    std::vector<int> vec (n+1, 0);
    return vec;
  }
  
  if(memo[v][0] != -1) return memo[v];
  
  std::vector<int> result (n+1, INT_MAX);
  
  for(int i=1; i<n+1; i++){
    
    std::vector<int> dp_ = dp(memo, beverages, v - beverages[i].second, n);
    if(dp_[i] == 0) dp_[i] = 1;
    
    if(result[0] > beverages[i].first + dp_[0]){
      result = dp_;
      result[0] += beverages[i].first;
    }
    
    else if(result[0] == beverages[i].first + dp_[0]){
      int sum_1 = 0;
      int sum_2 = 0;
      for(int j = 1; j<n+1; j++){
        sum_1 += result[j];
        sum_2 += dp_[j]; }
      if(sum_2 > sum_1){
        result = dp_;
        result[0] += beverages[i].first;
      }
    }
    
  }
  
  memo[v] = result;
  return memo[v];
  
}

void testcase(){
  int n, k; std::cin >> n >> k;
  
  std::vector<std::pair<int,int>> beverages(n+1, std::make_pair(0,0));
  for(int i=1; i<n+1; i++){
    int c, v; std::cin >> c >> v;
    std::pair<int,int> my_pair = std::make_pair(c,v);
    beverages[i] = my_pair;
  }
  
  //memo[0]= costo di ottenere i litri
  //memo[1,...n] = numero massimo di bevande diverse che mi posso comprare con memo[i].first soldi
  std::vector<int> start(n, 0);
  std::vector<std::vector<int>> memo(k+1, std::vector<int> (n+1, -1));
  std::vector<int> result = dp(memo, beverages, k, n);
  int number_of_bev = 0;
  for(int i=1; i<n+1; i++){
    number_of_bev += result[i];
  }
  
  std::cout << result[0] << " " << number_of_bev << "\n";
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
