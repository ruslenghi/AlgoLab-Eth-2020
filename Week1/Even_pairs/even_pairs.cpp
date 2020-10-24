#include <iostream>
#include <vector>

using namespace std;

void testcase(){
  
  int n = 0; cin >> n;
  
  vector<int> v;
  for(int i=0; i<n; i++){
    int b = 0; cin >> b;
    v.push_back(b);
  }
  
  vector<int> sum;
  
  for(int i=0; i<n; i++){
    int b = 0;
    for(int j=0; j<=i; j++){
      b += v[j];
    }
    sum.push_back(b);
  }
  
  int even = 0;
  
  // O(n^2) solution
  for(int j=0; j<n; j++){
    for(int k=0; k<=j; k++){
      if(j>=k){
        int diff = 0;
        // I don't get why it works with the "-1"
        diff = sum[j]-sum[k-1];
        if(diff%2 == 0){even ++;}
      }
    }
  }
  
  // O(n^3) solution
  /*for(int j=0; j<n; j++){
    for(int k=0; k<n; k++){
      if(k>=j){
        int check = 0;
        for(int l=j; l<k+1; l++){
          check += v[l];}
        if(check%2 == 0){even++;}
      }
    }
  }*/
  cout << even << endl;
}

int main(){
  int t;
  cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
