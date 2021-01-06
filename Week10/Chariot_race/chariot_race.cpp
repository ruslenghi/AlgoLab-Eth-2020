#include<iostream>
#include<vector>
#include <climits>

int buy_parent(std::vector<int> &memo_buy, std::vector<int> &memo_non_buy,
               std::vector<int> &cost, std::vector<std::vector<int>> &connections,
               int p);
               
int dont_buy_parent(std::vector<int> &memo_buy, std::vector<int> &memo_non_buy,
               std::vector<int> &cost, std::vector<std::vector<int>> &connections,
               int p);

void testcase(){
  int n; std::cin >> n;
  
  std::vector<std::vector<int>> connections(n, std::vector<int>());
  for(int i=0; i<n-1; i++){
    int x, y; std::cin >> x >> y;
    connections[x].push_back(y);}
  
  std::vector<int> cost;
  for(int i=0; i<n; i++){
    int my_cost; std::cin >> my_cost;
    cost.push_back(my_cost);}
  
  std::vector<int> memo_buy(n,-1);
  std::vector<int> memo_non_buy(n,-1);
    
  std::cout << dont_buy_parent(memo_buy, memo_non_buy, cost, connections, 0) << "\n";
    
}

//Returns the optimum price of a subtree, rooted in p, given that I buy the parent of its root
int buy_parent(std::vector<int> &memo_buy, std::vector<int> &memo_non_buy,
               std::vector<int> &cost, std::vector<std::vector<int>> &connections, int p){
  
  //If I am at a leaf of the tree and I buy its parent I can refrain from buying the leaf itself, as I bought its parent
  if(connections[p].size() == 0){
    memo_buy[p] = 0;
    return 0;}
  
  //If I have already computed this quantity I use the memory
  if(memo_buy[p] != -1){
    return memo_buy[p];}
    
  //result = min{(cost of buying p + sum [cost of children of p, modulo the fact that I bought their parent p]),
  //              (sum[children of p, modulo the fact that I did NOT buy their parent])}
  int result_1 = cost[p];
  int result_2 = 0;
  for(int i=0; i<(int)connections[p].size(); i++){
    int child = connections[p][i];
    result_1 += buy_parent(memo_buy, memo_non_buy, cost, connections, child);
    result_2 += dont_buy_parent(memo_buy, memo_non_buy, cost, connections, child);
  }
  
  int minimum = std::min(result_1,result_2);
  memo_buy[p] = minimum;
  return minimum;
}

//Returns the cost of a subtree, with root p, modulo the fact that I do NOT buy the parent node of p.
int dont_buy_parent(std::vector<int> &memo_buy, std::vector<int> &memo_non_buy,
               std::vector<int> &cost, std::vector<std::vector<int>> &connections, int p){
  
  //If I am at a leaf I must buy it, since I will not buy its parent
  if(connections[p].size() == 0){
    memo_non_buy[p] = cost[p];
    return cost[p];}
  
  //If I have already computed this quantity I use the memory
  if(memo_non_buy[p] != -1){
    return memo_non_buy[p];}
    
  //This is the case in which I buy p. If it do buy p I can refrain from buying its children
  //thus I used the buy_parent function
  int result_1 = cost[p];
  int appo = 0;
  for(int i=0; i<(int)connections[p].size(); i++){
    int child = connections[p][i];
    result_1 += buy_parent(memo_buy, memo_non_buy, cost, connections, child);
    appo += dont_buy_parent(memo_buy, memo_non_buy, cost, connections, child);
  }
  
  //What if I, instead, do not buy p. In this case I must buy at least one of its children!
  //Then I will not need to buy the children of this children, neither any of the other children of p
  //However I must cicle over the chidren of p to find the best one to buy.
  int result_2 = INT_MAX;
  for(int i=0; i<(int)connections[p].size(); i++){
    int special_child = connections[p][i];
    int candidate = appo - dont_buy_parent(memo_buy, memo_non_buy, cost, connections, special_child) + cost[special_child];
    for(int j=0; j<(int)connections[special_child].size(); j++){
      candidate += buy_parent(memo_buy, memo_non_buy, cost, connections, connections[special_child][j]);
    }
    result_2 = std::min(candidate,result_2);
  }
  
  int minimum = std::min(result_1,result_2);
  memo_non_buy[p] = minimum;
  return minimum;

}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
