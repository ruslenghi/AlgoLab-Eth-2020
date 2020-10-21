//This code does not work, adjust it

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Jedi{
  public:
    int a, b;
    Jedi(int a, int b) : a(a), b(b) {};
};

bool compare_jedies(Jedi& j_1, Jedi& j_2){
  if(j_1.a<j_2.a) return true;
  else return false;
}

void testcase(){
  int n, m; cin >> n >> m;
  vector<Jedi> Jedies_regular;
  vector<Jedi> Jedies_periodic;
  for(int i = 0 ; i < n; i++){
    int a, b; cin >> a >> b;
    if(a<=b) Jedies_regular.push_back(Jedi(a,b));
    else Jedies_periodic.push_back(Jedi(a,b));
  }
  
  sort(Jedies_regular.begin(), Jedies_regular.end(), compare_jedies);
  int counter = 0;
  int latest_head = 0;
  int tail = m;
  int jr_size = Jedies_regular.size();
  int jp_size = Jedies_periodic.size();
  
  for(int i = 0; i < jr_size; i++){
    if(Jedies_regular[i].a <= latest_head ) continue;
    int head_candidate = Jedies_regular[i].b;
    bool check = false;
    
    for(int j = i+1; j < jr_size; j++){
      int other_head_candidate = Jedies_regular[j].b;
      if(other_head_candidate <= head_candidate) break;
      if(Jedies_regular[j].a > head_candidate){
       check = true;
       break;}
    }
    
    if(check == true){
      latest_head = head_candidate;
      ++ counter;
      if(counter == 2) tail = Jedies_regular[i].a;
    }
  }
  
  int true_tail = 0;
  
  for(int i = 0; i < jr_size; i++){
    if(Jedies_regular[i].b < tail){
      true_tail = Jedies_regular[i].a;
    }
    else break;
  }

  for(int i = 0; i < jr_size; i++){
    int b = m; 
    if(Jedies_regular[i].b < b and Jedies_regular[i].a > latest_head){
      b=Jedies_regular[i].b;
      latest_head = b;
    }
  }
  
  counter ++;
  for(int i = 0; i < jp_size; i++){
    if(Jedies_periodic[i].a > latest_head and Jedies_periodic[i].b < true_tail){
      counter ++;
      break;
    }
  }
  
  cout << counter << "\n";
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++){
    testcase();
  }
}
