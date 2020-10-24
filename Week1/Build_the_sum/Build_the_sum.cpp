#include <iostream>
#include <vector>

using namespace std;

void testcase(){
  int n = 0; cin >> n;
  int sum = 0;
  for(int i=0; i<n; i++){
    int b = 0; cin >> b;
    sum += b;
  }
  cout << sum << endl;
}

int main(){
  int t = 0; cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
  
}
