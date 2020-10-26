#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>

bool sortbysecincr(const std::pair<int,int> &a,
                   const std::pair<int,int> &b)
{return a.second<b.second;}

int top(int& x, int& k){
  int to_add = 0;
  for(int i=1; i<k+1; i++){ to_add += pow(2,i);}
  return pow(2,k)*x+to_add;
}

int bottom(int& x, int& k){
  int to_add = 0;
  for(int i=0; i<k; i++){ to_add += pow(2,i);}
  return pow(2,k)*x+to_add;
}

void testcase(){
  int n; std::cin >> n;
  std::vector<int> dismissed(n,0);
  std::vector<std::pair<int,int>> timetable;
  
  for(int i=0; i<n; i++){
    int t; std::cin >> t;
    std::pair<int,int> this_pair;
    this_pair.first = i;
    this_pair.second = t;
    timetable.push_back(this_pair);
  }
  
  std::sort(timetable.begin(), timetable.end(), sortbysecincr);
  
  int count_dismissed = 0;
  int my_time = 0;
  int index = 0;
  
  while(count_dismissed < n){
    bool ok = false;
    int x = timetable[index].first;
    int t_x = timetable[index].second;
    if(dismissed[x]==1){
      index += 1;
      continue;}
    if(x >= int((n-1)/2) and my_time + 1 <= t_x){
      dismissed[x]=1;
      count_dismissed += 1;
      my_time += 1;
      ok = true;
      index += 1;
    }

    int counter = 0;
    if(x <= int((n-3)/2)){
      dismissed[x]=1;
      counter += 1;
      int k = 0;
      
      while(top(x,k) < n){
        for(int i = 0; i < top(x,k)-bottom(x,k) + 1; i++){
            int bot = bottom(x,k);
            if(dismissed[bot+i]==0){
              counter += 1;
              dismissed[bot+i] = 1;
            }
        }
          k ++;
      }
    
      if(my_time + counter <= t_x){
        ok = true;
        index += 1;
        my_time += counter;
        count_dismissed += counter;
      }
    }
    
    if(ok == false) {
      std::cout << "no" <<"\n";
      return;
    }
    
  }
  
  std::cout << "yes" <<"\n";
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
