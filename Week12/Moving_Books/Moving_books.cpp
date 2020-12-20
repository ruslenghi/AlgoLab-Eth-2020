#include<iostream>
#include<vector>
#include<algorithm>

//This one returns the index i of the largest weight w[i] that is smaller than s
//w is supposed to be ordered from largest to smallest
void print(std::vector<int>& w, std::vector<int>& s){
  std::cout << "These are my un-ordered streghts: " << "\n";
  for(int i=0; i<int(s.size()); i++){
    std::cout << s[i] << " ";
  }
  std::cout << "\n";
  
  std::cout << "These are my ordered weights: " << "\n";
  for(int i=0; i<int(w.size()); i++){
    std::cout << w[i] << " ";
  }
  std::cout << "\n";
}

int binary_search(std::vector<int>& w, int& s){
  int head; head = w.size()-1;
  int tail; tail = 0;
  if(w[head] > s){
    return -1;}
  while(head >= tail){
    int q = (head+tail)/2;
    if(s > w[q]) head = q-1;
    if(s < w[q]) tail = q+1;
    if(s == w[q]) return q;
  }
      return tail; 
}

void testcase(){
  int n, m; std::cin >> n >> m;
  
  std::vector<int> s;
  for(int i=0; i<n; i++){
    int s_i; std::cin >> s_i;
    s.push_back(s_i);
  }

  std::vector<int> w;
  for(int i=0; i<m; i++){
    int w_i; std::cin >> w_i;
    w.push_back(w_i);
  }
  
  int my_max = *std::max_element(s.begin(),s.end());
  std::sort(w.begin(),w.end(),std::greater<int>());
  
  if(my_max < w[0]){
    std::cout << "impossible" << "\n";
    return;
  }
  
  //print(w,s);
  int index_to_remove = 0;
  int my_time = 0;
  
  while(!w.empty()){
    int erased = 0;
    int size = s.size();
    for(int i=0; i<size; i++){
      index_to_remove = binary_search(w, s[i-erased]);
      if(index_to_remove != -1) w.erase(w.begin()+index_to_remove);
      if(index_to_remove == -1) {
        s.erase(s.begin()+i-erased);
        erased += 1;}
      if(s.size()==0 or w.size()==0) break;
    }
    my_time += 3;
  }
  
  std::cout << my_time-1 << "\n"; 
  
}

int main(){
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
