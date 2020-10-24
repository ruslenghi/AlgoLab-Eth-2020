#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void testcase(){
  
  int n = 0; cin >> n;
  vector<int> h;
  
  for(int i=0; i<n; i++){
    int b = 0; cin >> b;
    h.push_back(b);
  }
  
  int max = 0; int head = 0;
  int vis = 0; bool finish = false;
  while(h[max]!=1 && finish==false){
    head=h[max]+max-1;
    if(head>=n){
      head = n-1;
      finish = true;
    }
    int d = head - max;
    int index = 0; int c = 0;
    for(int i=0; i<d+1; i++){
      int a = h[max+i] - d + i;
      if(a>=c){
        c=a;
        index = i;
      }
    }
    max=max+index;
  }
  cout << head+1 << endl;
}

int main(){
  int t = 0; cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
