#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <iostream>
#include <vector>
#include <queue>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<long long,K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>  Triangulation;
typedef Triangulation::Finite_faces_iterator  Face_iterator;


void testcase(int n){
  std::vector<K::Point_2> pts;
  pts.reserve(n);
  for (std::size_t i = 0; i < std::size_t(n); ++i) {
    int x, y; std::cin >> x >> y;
    pts.push_back(K::Point_2(x, y));
  }
  
  Triangulation t;
  t.insert(pts.begin(), pts.end());
  
  std::priority_queue<std::pair<long long,Triangulation::Face_handle>> Q;
  for (auto f = t.all_faces_begin(); f != t.all_faces_end(); ++f){
    if(t.is_infinite(f)){  
      Triangulation::Vertex_handle v1;
      Triangulation::Vertex_handle v2;
      if(!t.is_infinite(f,0)) {v1 = f->vertex(1), v2 = f->vertex(2);}
      if(!t.is_infinite(f,1)) {v1 = f->vertex(2), v2 = f->vertex(0);}
      if(!t.is_infinite(f,2)) {v1 = f->vertex(0), v2 = f->vertex(1);}
      long long d = CGAL::squared_distance(v1->point(),v2->point());
      f->info() = d;
      Q.push(std::make_pair(d,f));}
    else f->info() = 0;
  }
  
  while(!Q.empty()){
    std::pair<long long,Triangulation::Face_handle> p = Q.top();  Q.pop();
    //It runs also without this following line of code. I would erase it
    //if(p.first != p.second->info()) continue;
    for(int i = 0; i<3; i++){
      Triangulation::Face_handle fh = p.second->neighbor(i);
      if(!t.is_infinite(fh)){
        long long w = CGAL::squared_distance(p.second->vertex((i+1)%3)->point(), p.second->vertex((i+2)%3)->point());
        w = std::min(w,p.second->info());
      if(w > fh->info()){
        fh->info() = w;
        Q.push(std::make_pair(w,fh));
        }
      }
    }
  }
  
  int m;
    std::cin >> m;
    for(int i=0;i<m;++i){
      K::Point_2 p;
      long long d;
      std::cin >> p >> d;
      
      Triangulation::Locate_type lt;
      int x;
      Triangulation::Face_handle f = t.locate(p,lt,x);
      if(CGAL::squared_distance(p,t.nearest_vertex(p)->point())<d){
        std::cout << 'n';
      }
      else if(t.is_infinite(f) || f->info()>=4*d){
        std::cout << 'y';
      }
      else {
        std::cout << 'n';
      }
    }
    std::cout << std::endl;
  
}

int main(){
  
  std::ios_base::sync_with_stdio(false);
  
  while(true){
    std::size_t n;
    std::cin >> n;
    if(n == 0) {
        return 0;
      }
    testcase(n);
  }
}
