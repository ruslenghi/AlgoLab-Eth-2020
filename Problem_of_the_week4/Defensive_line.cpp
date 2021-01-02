#include<iostream>
#include<vector>
#include<queue>

int length(std::pair<int,int>& p){
  int l = (p.second-p.first) + 1;
  return l;
} 

bool conflict(std::pair<int,int>& p_1, std::pair<int,int>& p_2){
  bool c = true;
  if(p_1.first > p_2.second) c = false;
  if(p_2.first > p_1.second) c = false;
  return c;

}

void testcase(){
  int n, m, k; std::cin >> n >> m >> k;
  
  std::vector<int> defenders;
  for(int i=0; i<n; i++){
    int my_defender; std::cin >> my_defender;
    defenders.push_back(my_defender);
  }
  
  std::queue<int> Q;
  std::vector<std::pair<int,int>> segments;
  int total_defense = 0;
  int head = 0;
  int i = 0; 
  
  //I traverse the whole set of defenders in a sliding windows faschion
  //I think my implementation is quite ugly, but it works
  
  //Here I previously put head instead of i. Don't do that!!! It resulted in an 
  //error that took quite a but of time to debug!
  while(i < n){
    
    if(total_defense < k){
      Q.push(i);
      head = i;
      total_defense += defenders[i];
      i++;
    }
    
    if(total_defense > k){
      total_defense -= defenders[Q.front()];
      Q.pop();
    }
    
    if(total_defense == k){
      std::pair<int,int> my_pair = std::make_pair(Q.front(),head);
      segments.push_back(my_pair);
      head = i;
      if(i != n){
        total_defense += defenders[i];
        total_defense -= defenders[Q.front()];
        Q.pop(); Q.push(i); 
        i++;}
    }
    
  }
  
  /*std::cout << "these are the possible segments: " << "\n";
  for(int j=0; j<segments.size(); j++){
    std::cout << segments[j].first << " " << segments[j].second << " ";
    std::cout << "this segment covers " << length(segments[j]) << " players" << "\n";
  }*/
  
  //Be careful! This implementation of sliding windows worsk fine on the samples
  //however I am not 100% sure it works fine for all the test sets
  
  if(segments.size() < m) {
    std::cout<< "fail" << "\n";
    return;
  }
  
  int total_l = 0;
  
  //This is for the m = 2 case, with small n also
  if(m==2){
    for(int a=0; a<segments.size()-1; a++){
      for(int b=a+1; b<segments.size(); b++){
        if(!conflict(segments[a],segments[b])){
          total_l = std::max(total_l,length(segments[a])+length(segments[b]));
        }
      }
    }
  }
  
  if(m==1){
    for(int b=0; b<segments.size(); b++){
      total_l = std::max(total_l,length(segments[b]));
    }
  }
  
  if(total_l==0) {
    std::cout<< "fail" << "\n";
    return;
  }
  
  std::cout << total_l << "\n";
  
  //This code runs correctly on test 3 as well, but way too slowly (11s/0.5s)
  //You need to speed it up by implementing the right DP solution!
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
