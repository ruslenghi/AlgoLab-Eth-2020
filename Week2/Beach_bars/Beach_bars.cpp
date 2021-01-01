#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include <climits>

void testcase(){

  int n; std::cin >> n;
  std::queue<int> Q;
  
  int covered_parasols = 0;
  int max_parasols = 0;
  std::vector<std::pair<int,int>> best_pairs;
  std::vector<int> parasols;
  
  for(int i=0; i<n; i++){
    int parasol; std::cin >> parasol;
    parasols.push_back(parasol);
  }
  
  //O(nlogn) This is the bottleneck
  std::sort(parasols.begin(),parasols.end());
  
  for(int i=0; i<n; i++){
    int parasol = parasols[i];
    int head = parasol;
    Q.push(parasol);
    covered_parasols += 1;
    while(abs(Q.front() -  head) > 200){
      Q.pop();
      covered_parasols -= 1;
    }

    //Since the parasols lay on a 1D line, the farthest parasols can only be
    //those at the extremes of the 1D line
    if(covered_parasols >= max_parasols){
      if(covered_parasols > max_parasols) best_pairs.clear();

      int mean_1 = (Q.front() + head - 1)/2;
      int mean_2 = (Q.front() + head + 1)/2;
      
      int max_dist_1 = std::max(abs(mean_1-Q.front()),abs(mean_1-head));
      int max_dist_2 = std::max(abs(mean_2-Q.front()),abs(mean_2-head));
      int mean, max_dist; 
      std::pair<int,int> my_pair;
      
      if(max_dist_1 > max_dist_2) {
        my_pair = std::make_pair(mean_2,max_dist_2);
        best_pairs.push_back(my_pair);
      }
      else if(max_dist_1 < max_dist_2) {
        my_pair = std::make_pair(mean_1,max_dist_1);
        best_pairs.push_back(my_pair);
      }
      else{
        my_pair = std::make_pair(mean_1,max_dist_1);
        best_pairs.push_back(my_pair);
        if(mean_1 != mean_2){
          my_pair = std::make_pair(mean_2,max_dist_2);
          best_pairs.push_back(my_pair);}
      }
      max_parasols = covered_parasols;
    }
  
  }
    
  int best_index;
  int min_dist = INT_MAX;
  for(int i=0; i<best_pairs.size(); i++){
    if(best_pairs[i].second < min_dist) {
      min_dist = best_pairs[i].second;
      best_index = i;
    }
  }
  
  std::cout << max_parasols << " " 
            << best_pairs[best_index].second << "\n";
  
  int minimum = INT_MAX;
  for(int i=0; i<best_pairs.size(); i++){
    minimum = std::min(best_pairs[i].second,minimum);
  }
  
  for(int i=0; i<best_pairs.size(); i++){
    if(best_pairs[i].second == minimum){
      std::cout << best_pairs[i].first << " ";}
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
