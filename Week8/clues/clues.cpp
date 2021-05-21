#include<iostream>
#include<queue>
#include<vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<std::pair<int,bool>, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>  Triangulation;

bool interferences(Triangulation &t, long int rr) {
    for(auto e = t.finite_edges_begin(); e != t.finite_edges_end(); e++)
        if(t.segment(e).squared_length() <= rr) return false;
    return true;
}

bool can_color(Triangulation &t, long int rr){
  std::vector<K::Point_2> blues, reds;
  Triangulation t1, t2;
  int component = -1;
  for(auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v){
    
    if(v->info().first != -1) continue;
    v->info() = std::make_pair(++component, false);
    std::queue<Triangulation::Vertex_handle> my_queue;
    my_queue.push(v);
    do{
      Triangulation::Vertex_handle my_handle = my_queue.front();
      my_queue.pop();
      Triangulation::Vertex_circulator c = t.incident_vertices(my_handle);
      if(c!=0) do {
          if(!t.is_infinite(c) && CGAL::squared_distance(c->point(),my_handle->point()) <= rr){
            if(c->info() == my_handle->info()) return false;
            if(c->info().first == -1){
              my_queue.push(c->handle());
              c->info() = std::make_pair(component, !my_handle->info().second);
            }
          }
        } while (++c != t.incident_vertices(my_handle));
      if(my_handle->info().second) blues.push_back(my_handle->point());
      else reds.push_back(my_handle->point());
      }while(!my_queue.empty());
    }
    t1.insert(blues.begin(),blues.end()); 
    t2.insert(reds.begin(),reds.end());
    return interferences(t1,rr) && interferences(t2,rr);
  }

void testcase(){
  
  long int n, m, r; std::cin >> n >> m >> r;
  std::vector<K::Point_2> stations;
  for(int i=0; i<n; i++){
    int x, y; std::cin >> x >> y;
    stations.push_back(K::Point_2(x, y));
  }
  
  long int rr = r*r;
  Triangulation t;
  t.insert(stations.begin(), stations.end());
  for(auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); v++) v->info() = std::make_pair(-1, false);
  
  bool feasible_network = can_color(t,rr);

  for(int i=0; i<m; i++){
    long int h_x, h_y; std::cin >> h_x >> h_y;
    long int w_x, w_y; std::cin >> w_x >> w_y;
    K::Point_2 H = K::Point_2(h_x,h_y);
    K::Point_2 W = K::Point_2(w_x,w_y);
    if(!feasible_network) std::cout << "n";
    else {
          Triangulation::Vertex_handle v1 = t.nearest_vertex(H), v2 = t.nearest_vertex(W);
          if(CGAL::squared_distance(H, W) <= rr ||
              (v1->info().first == v2->info().first && 
              CGAL::squared_distance(v1->point(), H) <= rr &&
              CGAL::squared_distance(v2->point(), W) <= rr)) std::cout << "y";
          else std::cout << "n";
          }
  }
  std::cout << "\n";
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
