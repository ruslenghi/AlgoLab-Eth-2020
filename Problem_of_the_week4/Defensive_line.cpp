#include<iostream>
#include<vector>

using namespace std;

std::vector<int> windows(std::vector<int> &v, int k, int n){
  
  std::vector<int> h(n, -1);
  int head = 0;
  int tail = 0;
  int sum = v[head];
  while(head != n){
    
    if(sum == k){
      //Just under this circumstance h can have a non -1 entry!
      h[head] = head-tail+1;//Be careful with this one!!
      sum -= v[tail];
      head++;
      tail++;
      sum += v[head]; 
    }
    
    else if(sum < k){
      head++;
      sum += v[head];
    }
    
    else if(sum > k){
      sum -= v[tail];
      tail++;
    }
      
  }
  
  return h;
  
}

void testcase(){
  
  int n, m, k; 
  cin >> n >> m >> k;
  
  std::vector<int> v;
  for(int i=0; i<n; i++){
    int value; cin >> value;
    v.push_back(value);
  }
  
  vector<int> h = windows(v, k, n);
  vector<vector<pair<int,int>>> DP(m+1, vector<pair<int,int>> (n+1, make_pair(0,0)));
  
  for(int i = 1; i <= m; i++)
      for(int j = 1; j <= n; j++) {
        if(h[j-1] == -1){DP[i][j] = DP[i][j-1]; continue;}
          if(DP[i-1][j-h[j-1]].first + h[j-1] > DP[i][j-1].first) 
              DP[i][j] = make_pair(DP[i-1][j-h[j-1]].first + h[j-1], DP[i-1][j-h[j-1]].second + 1);
          else DP[i][j] = DP[i][j-1];
      }

  if(DP[m][n].second != m) cout << "fail\n";
  else cout << DP[m][n].first << "\n";

}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
