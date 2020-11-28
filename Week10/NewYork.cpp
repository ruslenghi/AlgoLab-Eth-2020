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
  for(int i=0; i<n-1; i++){
    int u, v; std::cin >> u >> v;
    routes[v] = u; 
  }
  
  std::vector<int> feasible_points;
  for(int i=n-1; i>0; i--){
    int steps = 0;
    int my_place = i;
    int max_temp = T[i];
    int min_temp = T[i];
    while(steps<m-1 and my_place != 0){
      my_place = routes[my_place];
      max_temp = std::max(T[my_place], max_temp);
      min_temp = std::min(T[my_place], min_temp);
      if(max_temp-min_temp > k) break;
      else steps++;
    }
    
    if(steps == m-1) feasible_points.push_back(my_place);
    
  }
  
  int f_size = feasible_points.size();
  if(f_size == 0) {
    std::cout << "Abort mission" << "\n";
    return;}
    
  if(f_size == 1) {
    std::cout << feasible_points[0] << "\n";
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
