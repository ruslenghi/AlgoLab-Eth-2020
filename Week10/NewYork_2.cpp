#include<iostream>
#include<vector>
#include<algorithm>

void testcase(){
  int n, m, k; std::cin >> n >> m >> k;
  std::vector<int> T;
  for(int i=0; i<n; i++){
    int h; std::cin >> h;
    T.push_back(h);
  }
  
  std::vector<int> routes(n,-1);
  std::vector<int> routes_2(n,-1);
  // This n-1 has to stay!
  for(int i=0; i<n-1; i++){
    int u, v; std::cin >> u >> v;
    routes[v] = u;
    routes_2[u] = v;
  }
  
  // The points with the -1 in routes_2 are those we want to start from to 
  // go back with the sliding windows fashion
  
  std::vector<int> feasible_points;
  for(int i=n-1; i>0; i--){
    if(routes_2[i] == -1){
      int my_head = i;
      int my_tail = i;
      int max_temp = T[i];
      int min_temp = T[i];
      bool reached = true;
      //Maybe this is j<m-1, be careful!!
      //Be also careful that you must not go back to 0 before you did m steps!
      //If you do, it means that all the points are to be thrown away
      for(int j=0; j<m-1; j++){
        my_tail = routes[my_tail];
        max_temp = std::max(max_temp,T[my_tail]);
        min_temp = std::min(min_temp,T[my_tail]);
        if(my_tail == 0 and j != m-2) {
          reached = false;
          break;}
      }
      
      if(reached == false) continue;
      if(max_temp-min_temp <= k) feasible_points.push_back(my_tail);
      
      while(my_tail != 0){
        my_tail = routes[my_tail];
        if(max_temp == T[my_head] or min_temp == T[my_head]){
          int search = routes[my_head];
          max_temp = T[search];
          min_temp = T[search];
          for(int j=0; j<m-1; j++){
            search = routes[search];
            max_temp = std::max(max_temp,T[search]);
            min_temp = std::min(min_temp,T[search]);
          }
        }
        
        max_temp = std::max(max_temp,T[my_tail]);
        min_temp = std::min(min_temp,T[my_tail]);
        
        my_head = routes[my_head];
        if(max_temp-min_temp <= k) feasible_points.push_back(my_tail);
      }
    }
  }
  
  int f_size = feasible_points.size();
  if(f_size == 0) {
    std::cout << "Abort mission" << "\n";
    return;}
    
  std::sort(feasible_points.begin(),feasible_points.end());

  std::vector<int> my_final_points;
  for(int i=0; i<f_size-1; i++){
    int a = feasible_points[i];
    int b = feasible_points[i+1];
    if(a != b) my_final_points.push_back(a);
  }
  
  int my_size = my_final_points.size();
  if(feasible_points[f_size-1] != my_final_points[my_size-1]){
    my_final_points.push_back(feasible_points[f_size-1]);
    my_size += 1;}

  for(int i=0; i < my_size; i++){
    std::cout << my_final_points[i] << " ";
  }
  
  std::cout << "\n";
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
