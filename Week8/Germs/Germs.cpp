#include<iostream> 
#include<vector>
#include<algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_vertex_base_with_info_2<double, K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;

void testcase(int n){
  
  int l, b, r, t;
  std::cin >> l >> b >> r >> t;
  
  std::vector<K::Point_2> pts;
  for(int i=0; i<n; i++){
    long long int x, y; 
    std::cin >> x >> y;
    pts.push_back(K::Point_2(x,y));
  }
  
  Triangulation T;
  T.insert(pts.begin(), pts.end());
  
  for(auto v = T.finite_vertices_begin(); v != T.finite_vertices_end(); ++v){
    K::Point_2 p = v->point(); double d = pow(2, 103);
    if( (p.x()-l)*(p.x()-l) < d) d = (p.x()-l)*(p.x()-l);
    if( (r-p.x())*(r-p.x()) < d) d = (r-p.x())*(r-p.x());
    if( (p.y()-b)*(p.y()-b) < d) d = (p.y()-b)*(p.y()-b);
    if( (t-p.y())*(t-p.y()) < d) d = (t-p.y())*(t-p.y());
    v->info() = d;
  }
  
  //I set every vertex to its length death
  for(auto e = T.finite_edges_begin(); e != T.finite_edges_end(); ++e){
    //I get the vertices of the edge
    Triangulation::Vertex_handle v1 = e->first->vertex((e->second + 1) % 3);
    Triangulation::Vertex_handle v2 = e->first->vertex((e->second + 2) % 3);
    // the /4 is there because the germs meet halfway 
    double d = CGAL::squared_distance(v1->point(), v2->point())/4;
    v1->info() = std::min(d, v1->info());
    v2->info() = std::min(d, v2->info());
  }
  
  std::vector<double> death_len;
  for(auto v = T.finite_vertices_begin(); v != T.finite_vertices_end(); ++v){
    death_len.push_back(v->info());
  }
  
  std::sort(death_len.begin(), death_len.end());
  
  int middle = n/2;
  
  double f_l = std::sqrt(death_len[0]);
  double m_l = std::sqrt(death_len[middle]);
  double l_l = std::sqrt(death_len[n-1]);
  
  double f_t = std::ceil(std::sqrt(f_l-0.5));
  double m_t = std::ceil(std::sqrt(m_l-0.5));
  double l_t = std::ceil(std::sqrt(l_l-0.5));
  
  std::cout << f_t <<" " <<  m_t << " " << l_t << "\n";
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  while(true){
    int n; std::cin >> n;
    if(n == 0) break;
    testcase(n); 
  }
}
