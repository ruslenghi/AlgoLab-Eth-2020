//DISCLAIMER: I DID NOT WRITE THIS SOLUTION MYSELF, I FOUND IT ON THE INTERNET

#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h> 
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K; 
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT,K> Fb; 
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds; 
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef Triangulation::Face_handle Face_handle;

std::istream & fp = std::cin;

K::FT MAX_DIST = pow(2, 103);

void testcase(){
  int n, m; fp >> n >> m;
  long r; fp >> r;
  
  std::vector<K::Point_2> pts; 
  pts.reserve(n);
  for (int i = 0; i < n; ++i) {
    long x, y;
    std::cin >> x >> y; 
    pts.push_back(K::Point_2(x, y));
  }
  
  Triangulation t; 
  t.insert(pts.begin(), pts.end());
  
  std::queue<Triangulation::Face_handle> Q;
  for(Triangulation::Face_handle f = t.all_faces_begin(); f != t.all_faces_end(); ++f){
    
    //I can escape from each and every one of the infinite faces
    if(t.is_infinite(f)){
      f->info() = MAX_DIST;
      Q.push(f);
    }
    
    //I can escape a face only if the distance of its center from the vertices is big enough
    else{
      //K::Point_2 P = t.circumcenter(f);
      //USE SQUARED RADIUS INSTEAD OF CIRCUMCENTER!!! IT IS MUCH FASTER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      f->info() = CGAL::squared_radius(f->vertex(0)->point(), f->vertex(1)->point(), f->vertex(2)->point());
      Q.push(f);}
    }
  
  /*while(!Q.empty()){
    //K::FT w = pq.top().first;
    Face_handle u = Q.front(); Q.pop();
    //if(w < u -> info()) continue;
    for(int i = 0; i < 3; ++i){
      Face_handle v = u -> neighbor(i);
      if(!t.is_infinite(v)){
        K::FT link = t.segment(u, i).squared_length();
        K::FT new_w = CGAL::min(link, u -> info());
        if(new_w > v -> info()){
          v -> info() = new_w;
          Q.push(v);
        }
      }
    }
  }*/
  
  while(!Q.empty()){
    auto f_h = Q.front(); Q.pop();
    for(int i=0; i<3; i++){
      Triangulation::Face_handle f_n = f_h->neighbor(i);
      if(t.is_infinite(f_n)) continue;
      K::FT l = CGAL::squared_distance(f_h->vertex((i+1)%3)->point(), f_h->vertex((i+2)%3)->point());
      K::FT new_w = std::min(f_h->info(), l);
      if(f_n->info() < new_w){
        f_n->info() = new_w;
        Q.push(f_n);
      }
      
    }
    
  }
  
  while(m--){
    long x, y, s; fp >> x >> y >> s;
    
    K::Point_2 p(x, y);
    K::FT distance = CGAL::squared_distance(t.nearest_vertex(p)->point(), p);
    K::FT radius = (s + r);
    
    if (distance < radius * radius){ 
      std::cout << "n";            
      continue;
    } 
    
    Triangulation::Face_handle start = t.locate(p);
    if (4*radius*radius <= start -> info()) std::cout << "y";
    else std::cout << "n";
    
  }
  
  std::cout << "\n";

}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
}
