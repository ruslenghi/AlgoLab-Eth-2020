#include<iostream>
#include<queue>
#include<vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>  Triangulation;

typedef Triangulation::Edge_iterator  Edge_iterator;
typedef Triangulation::Vertex_iterator  Vertex_iterator;

long long int longest_edge(Triangulation& t){
  long long int s = 0;
  for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e){
    long long int this_edge = t.segment(e).squared_length(); 
    if ( this_edge > s ) s = this_edge;}
  return s;
}

long long int test1(Triangulation& t){
  long long int s = LONG_LONG_MAX;
  for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e){
    long long int this_edge = t.segment(e).squared_length(); 
    if ( this_edge < s ) s = this_edge;}
  return s;
}

long long int test2(Triangulation& t,long long int& s_0){
  for(Vertex_iterator v = t.finite_vertices_begin(); v != t.finite_vertices_end(); v++){
    v->info() = 0;}
  
  long long int f = 0;
  for (Vertex_iterator v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v){
    if(v->info() != 0) continue;
    f += 1;
    v->info() = f;
    
    std::queue<Triangulation::Vertex_handle> my_queue;
    my_queue.push(v);
    
    do{
      
      Triangulation::Vertex_handle my_handle = my_queue.front();
      my_queue.pop();
      Triangulation::Vertex_circulator c = t.incident_vertices(my_handle);
      
      if(c!=0) do {
          if(!t.is_infinite(c) && CGAL::squared_distance(c->point(),my_handle->point()) < s_0){
            if(c->info() == 0){
              c->info()  = f;
              my_queue.push(c->handle());}
            }
          } while (++c != t.incident_vertices(my_handle));
        
    }while(!my_queue.empty());
  }
  return f;
}

void testcase(){
  int n, k, f_0; std::cin >> n >> k >> f_0;
  long long int s_0; std::cin >> s_0;
  
  std::vector<K::Point_2> pts;
  pts.reserve(n);
  
  for (int i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    pts.push_back(K::Point_2(x, y));
  }
  
  Triangulation t;
  t.insert(pts.begin(), pts.end());
  
  long long int s = test1(t); //This holds for the 2 1st test cases
  long long int f = test2(t,s_0); //This one holds for the 1st 3 test cases
  
  if(n == f_0){
    std::cout << s << " " << f << "\n";
    return;}
    
  s = longest_edge(t);
  long long int head = s;
  long long int tail = 0;
  int counter = 0;
  
  while(tail <= head){
    counter ++;
    long long int q = (tail + head)/2;
    long long int my_guess = test2(t,q);
    if(my_guess < f_0) {
      head = q-1;}
    else tail = q+1;
  } 
  
  s = head;
  std::cout << s << " " << f << "\n";
  
}

int main(){
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
