#include<iostream>
#include<vector>

int dp(std::vector<std::vector<int>> &memo, std::vector<int> &coins, int head, int tail){
  
  if(memo[head][tail] != -1) return memo[head][tail];
  if(head == tail) return coins[head];
  if(tail < head) return 0;
  
  if(head == (int)coins.size()-1) return coins[head];
  if(head == (int)coins.size()-2) return std::max(coins[head],coins[head+1]);
  
  if(tail == 0) return coins[tail];
  if(tail == 1) return std::max(coins[tail],coins[tail-1]);
  
  int a = coins[head] + std::min( dp(memo, coins, head + 2, tail), dp(memo, coins, head + 1, tail - 1));
  
  int b = coins[tail] + std::min( dp(memo, coins, head, tail - 2), dp(memo, coins, head + 1, tail - 1));
                                  
  memo[head][tail] = std::max(a,b);
  return memo[head][tail];
  
}

void testcase(){
  int n; std::cin >> n;
  
  std::vector<int> coins;
  for(int i=0; i<n; i++){
    int v; std::cin >> v;
    coins.push_back(v);
  }
  
  std::vector<std::vector<int>> memo(n, std::vector<int>(n, -1));
  int result = dp(memo, coins, 0, n-1);
  
  std::cout << result << "\n";
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
