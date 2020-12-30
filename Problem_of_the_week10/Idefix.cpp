#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>  Triangulation;
typedef Triangulation::Vertex_iterator  Vertex_iterator;

long long int max_bones(std::vector<K::Point_2>& bones, Triangulation& t, long long int& q){
  
  for (Vertex_iterator v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v){v->info()=-1;}
  int component = -1;
  for (Vertex_iterator v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v){
    
    if(v->info() != -1) continue;
    
    component += 1;
    v->info() = component;
    std::queue<Triangulation::Vertex_handle> Q;
    Q.push(v);
    
    while(!Q.empty()){
      
      Triangulation::Vertex_handle handle_v = Q.front(); Q.pop();
      Triangulation::Vertex_circulator c = t.incident_vertices(handle_v);
      //The c!=0 is fundamental!! without it you get segfault!!!
      if(c!=0) do{
        //Here it might be the case that I have to pick <q and not <= q
        if(!t.is_infinite(c) && CGAL::squared_distance(c->point(),handle_v->point()) <= q) {
          if(c->info() == -1){
              Q.push(c->handle());
              c->info() = component;
            }
            
        }
        
      } while (++c != t.incident_vertices(handle_v));
    }
  }
  
  std::vector<int> bones_to_comp(component+1,0);
  int m = bones.size();
  
  for(int i=0; i<m; i++){

    K::Point_2 my_bone = bones[i];
    Triangulation::Vertex_handle v = t.nearest_vertex(my_bone);
    K::Point_2 nearest_tree = v->point();
    int index = v->info();
    if(CGAL::squared_distance(my_bone,nearest_tree) <= q/4){
      bones_to_comp[index] += 1;}
  }
  
  //Be careful! This max_element tool returns a pointer!
  int max = *std::max_element(bones_to_comp.begin(),bones_to_comp.end());
  return max;
  
}


void testcase(){
  long long int n, m, q, k; std::cin >> n >> m >> q >> k;
  
  //There might be a problem with the data types
  std::vector<K::Point_2> pts;
  for(int i=0; i<n; i++){
    int x, y; std::cin >> x >> y;
    pts.push_back(K::Point_2(x,y));
  }
  
  Triangulation t;
  t.insert(pts.begin(), pts.end());
  
  std::vector<K::Point_2> bones;
  
  for(int i=0; i<m; i++){
    int x, y; std::cin >> x >> y;
    K::Point_2 my_bone = K::Point_2(x,y);
    bones.push_back(my_bone);
  }
  
  long long int max = max_bones(bones,t,q);
  long long int head, tail;
  
  if(max >= k) {
    head = q;
    tail = 0;}
  else {
    head = LLONG_MAX;
    tail = q;}
  
  //I do a binary search for the result
  while(head>=tail){
    long long int s = (head+tail)/2;
    if(max_bones(bones,t,s)>=k) head = s-1;
    else tail = s+1;
  }
  
  std::cout << max << " " << tail << "\n";
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
