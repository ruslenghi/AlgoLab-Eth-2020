#include<iostream>
#include<vector>
#include <algorithm>

using namespace std;

class Boat{
  public:
    int l, p;
    Boat(int length, int position) : l(length), p(position) {}
};

bool boats_order_relation(Boat& boat_1, Boat& boat_2){
  if(boat_1.p < boat_2.p) return true;
  else return false;
}

int compute_head(vector<Boat>& boats, int i, int latest_head){
  return max(latest_head,boats[i].p-boats[i].l) + boats[i].l;
}

void testcase(){
  int n; cin >> n;
  vector<Boat> boats;
  for(int i = 0; i < n; i++){
    int l, p; cin >> l >> p;
    boats.push_back(Boat(l,p));
  }
  
  sort(boats.begin(), boats.end(), boats_order_relation);

  int latest_head = boats[0].p-boats[0].l-1;
  int counter = 0;
  
  for(int i = 0; i < n; i++){
    bool check = true;
    int head = compute_head(boats, i, latest_head);
    if(latest_head > boats[i].p) continue;
    
    for(int j = i+1; j < n; j++){
      if(boats[j].p > head) break;
    int new_head = compute_head(boats, j, latest_head);
      if(new_head < head){
        check = false;
        break;}
    }
    
    if(check){
      latest_head = head;
      counter ++; 
    }
  }
  cout << counter << "\n";
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
  
}
