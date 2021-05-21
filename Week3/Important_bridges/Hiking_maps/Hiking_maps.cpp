#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Line_2 L;
typedef K::Segment_2 S;
typedef K::Triangle_2 T;

bool Point_Is_In_Triangle(const vector<P>& Triangle, P& point){
  for(int k = 0; k<6; k+=2){
        if(CGAL::left_turn(Triangle[k],Triangle[k+1],point)) {
          return false;
        }
      }
  return true;
}

bool Path_Is_Covered(const vector<int>& covered){
  for(int i=0; i<covered.size(); ++i){
    if(covered[i] <= 0) return false;
  }
  return true;
}

int main(){
  ios_base::sync_with_stdio(false);
  int c; cin >> c;
  
  for(int i = 0; i<c; ++i){
    int m, n; cin >> m >> n;
    vector<P> Points;
    
  vector<vector<P>> Triangles(n);
  for(int k = 0 ; k < n ; k++ ){Triangles[k].resize(6);}

    // I build a vector of segments that describes the hiking path O(m)
    for(int j = 0; j<m; ++j){
      int x, y; cin >> x >> y;
      Points.push_back(P(x,y));
    }
    
    // I build a vector containing all the points representing triangles O(n)
    // I also make sure that the order of points on triangles is correct
    for(int j = 0; j<n; ++j){
      for(int k = 0; k<6; ++k){
        int x, y; cin >> x >> y ;
        Triangles[j][k] = P(x,y);
      }
      
      for(int k = 0; k<6; k+=2){
        if(!CGAL::right_turn(Triangles[j][k],Triangles[j][k+1],Triangles[j][(k+2)%6])){
          P a = Triangles[j][k];
          Triangles[j][k] = Triangles[j][k+1];
          Triangles[j][k+1] = a;
        }
      }
      
    }
   
    int b, e; b=0, e=0;
    int best = n;
    bool uncovered = true;
    vector<int> covered(m-1,0);
    
    // Rethink this part of the code on paper
    while(e != n or uncovered == false){
      
      if(uncovered == true){
        e +=1;
        for(int j=0; j<m-1; ++j){
          bool First_Point = Point_Is_In_Triangle(Triangles[e-1],Points[j]);
          bool Second_Point = Point_Is_In_Triangle(Triangles[e-1],Points[j+1]);
          if(First_Point and Second_Point){ covered[j] += 1; }
        }
      }
      
      if(uncovered == false){
        b +=1;
        for(int j=0; j<m-1; ++j){
          bool First_Point = Point_Is_In_Triangle(Triangles[b-1],Points[j]);
          bool Second_Point = Point_Is_In_Triangle(Triangles[b-1],Points[j+1]);
          if(First_Point and Second_Point){ covered[j] -= 1; }
        }
      }
      
      uncovered = !Path_Is_Covered(covered);
      if(uncovered == false) { best = min(best,e-b);}
      
    }
    
    cout << best << "\n";
    
  }
}
