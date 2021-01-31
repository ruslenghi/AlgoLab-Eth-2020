#include<iostream>
#include<vector>
#include<set>
#include<algorithm>

void testcase(){
  int n, m; std::cin >> n >> m;
  
  std::vector<int> s;
  for(int i=0; i<n; i++){
    int s_i; std::cin >> s_i;
    s.push_back(s_i);
  }

  std::vector<int> w;
  std::multiset<int, std::greater<int>> ws;
  for(int i=0; i<m; i++){
    int w_i; std::cin >> w_i;
    w.push_back(w_i);
    ws.insert(w_i);
  }
  
  int my_max_s = *std::max_element(s.begin(),s.end());
  int my_max_w = *std::max_element(w.begin(),w.end());
  
  if(my_max_s < my_max_w){
    std::cout << "impossible" << "\n";
    return;
  }

  std::sort(s.begin(), s.end(), std::greater<int>());
  
  int r = 0;
        while (!ws.empty()) {
            ++r;
            for (int i = 0; i < n; ++i) {
                auto b = ws.lower_bound(s[i]);
                if (b != ws.end()) {ws.erase(b);} 
                else { break; }
            }
        }
        
  std::cout << 3*r -1 << "\n";
  
}

int main(){
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
