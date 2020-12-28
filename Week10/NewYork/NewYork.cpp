#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<queue>

void testcase(){
  int n, m, k; std::cin >> n >> m >> k;
  
  if(n<m) {
    std::cout << "Abort mission" << "\n";
    return;}
  
  std::vector<int> T;
  std::vector<int> routes(n,-1);
  std::vector<bool> is_parent(n,false);
  std::vector<bool> visited(n,false);
  
  for(int i=0; i<n; i++){
    int my_t; std::cin >> my_t;
    T.push_back(my_t);
  }
  
  for(int i=0; i<n-1; i++){
    int parent, child; std::cin >> parent >> child;
    routes[child] = parent;
    is_parent[parent] = true;
  }
  
  std::queue<int> Q;
  for(int i=0; i<n; i++){
    if(!is_parent[i]) Q.push(i);
  }

  std::vector<int> feasible_points;
  while(!Q.empty()){
    
    std::multiset<long> window;
    int tail = Q.front(); Q.pop();
    
    window.insert(T[tail]);
    
    int head = tail;
    //As I already inserted one Temperature I add m-1 terms
    for(int i=0; i<m-1; i++){
      head = routes[head];
      window.insert(T[head]);
    }
    
    while(head != -1 and !visited[tail]){
      
      int mini = *window.begin();
      int maxi = *window.rbegin();
      if(maxi-mini<=k){feasible_points.push_back(head);}
      
      //The fact that I do it here should ensure that the !visited[tail] 
      //condition is not automatically satisfied 
      visited[tail] = true;
      window.erase(window.find(T[tail]));
      
      head = routes[head];
      window.insert(T[head]);
      tail = routes[tail];
      
    }
    
  }
  
  if(feasible_points.empty()){
    std::cout << "Abort mission" << "\n";
    return;}
  
  std::sort(feasible_points.begin(),feasible_points.end());
  std::cout << feasible_points[0] << " ";
  for(int i=1; i<feasible_points.size(); i++){
      if(feasible_points[i] != feasible_points[i-1])
      std::cout << feasible_points[i] << " ";
  }
  
  
  std::cout << "\n";
  
}

int main(){
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
