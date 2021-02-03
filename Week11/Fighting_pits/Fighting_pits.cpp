//DISCLAIMER: I did not write this solution myself, i have found it on the internet

#include<iostream>
#include<vector>
#include<map>
#include<cmath>

using namespace std;

typedef pair<int,int> status;

//This function gets a number encoding the m fighters in the N/S entry
//end returns the variety that is among them
int variety(int v, int k){
  vector<int> vec(k+1, 0);
  
  while(v != 0){
    vec[v%10] = 1;
    v /= 10;
  }
  
  int sum = 0;
  for(int i=0; i<vec.size(); i++){
    sum += vec[i];
  }
  
  return sum;
  
}

int cut(int q, int m){
  int M = pow(10, m-1);
  return q % M;
} 

void testcase(){
  
  int n, k, m; std::cin >> n >> k >> m;
  
  vector<int> fighters;
  fighters.push_back(0);
  for(int i=0; i<n; i++){
    int type; std::cin >> type;
    type++;
    fighters.push_back(type);
  }
  
  //That is, we create a matrix that has n*23 element. One for each 
  //Possible configuration of the "fighters left -> n" and for the
  //"entries_in_left - entries_in_right + 11 -> 23". Now, for each of this couples (i,j)
  //we might have different statuses in the N/S entries, depending on
  //them 
  vector<vector<map<status, int>>> DP(n+1, vector<map<status,int>>(23));
  
  //Now we should proceed to fill the DP table in a bottom up manner!
  //I am not really comfortable doing that, but still...
  DP[0][11][make_pair(0,0)] = 0;
  
  //I will first work with the left entries
  
  //For every number of fighters left
  for(int i=0; i<n; i++){
    //For every possible difference in the r/l entries
    for(int j=0; j<23; j++){
      //for every possible pair in the map
      for(auto p : DP[i][j]){
        //This is one of the possible states in which I can find
        //the N hall, modulo hte i and j constraints
        int l = 10*p.first.first + fighters[i+1];;
        int inc = 1000*variety(l,k)-pow(2, abs(j-11+1));
        if(inc >= 0){
          int tmp = inc + p.second;
          if(tmp > DP[i+1][j+1][make_pair(cut(l,m),p.first.second)]){
            DP[i+1][j+1][make_pair(cut(l,m),p.first.second)] = tmp;
          }
        
        }
        
        int r = 10*p.first.second + fighters[i+1];;
        inc = 1000*variety(r,k)-pow(2, abs(j-11-1));
        if(inc >= 0){
          int tmp = inc + p.second;
          if(tmp > DP[i+1][j-1][make_pair(p.first.first, cut(r,m))]){
            DP[i+1][j-1][make_pair(p.first.first, cut(r,m))] = tmp;
          }
        
        }
      }
    }
  }
  
  int result = 0;
  for(int j=0; j<23; j++){
    for(auto p : DP[n][j]){
      if(p.second > result){
        result = p.second;
      }
    }
  }
  
  std::cout << result << "\n";
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t; 
  for(int i=0; i<t; i++){
    testcase();
  }
}
