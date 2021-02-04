//DISCLAIMER: i DID NOT WRITE THIS SOLUTION

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <map>
#include <algorithm>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Edge_iterator Edge_iterator;
typedef K::Segment_2 Segment;
typedef K::Point_2 Point;
typedef std::map<Point, K::FT> Map;

// This map stores each point and the squared distance to the closest collision
void update_map(Map& my_map, Point& my_point, K::FT& dist){
  auto search = my_map.find(my_point);
  if(search == my_map.end()) my_map.insert(std::pair<Point, K::FT>(my_point, dist));
  else search->second = std::min(search->second, dist);
}

void testcase(int n){
  int left, bottom, right, top; 
  std::cin >> left >> bottom >> right >> top;
  std::vector<K::Point_2> pts;
  pts.reserve(n);
  for (std::size_t i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    pts.push_back(K::Point_2(x, y));
  }
  
  Triangulation t;
  t.insert(pts.begin(), pts.end());
  Map my_map;
  
  for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    Point p1 = e->first->vertex((e->second + 1) % 3)->point();  
    Point p2 = e->first->vertex((e->second + 2) % 3)->point();
    K::FT sqdist = CGAL::squared_distance(p1, p2) / 4;
    update_map(my_map, p1, sqdist);
    update_map(my_map, p2, sqdist);
  }
  
  //Here I check all the distances between the points and the box's borders
  Point lt(left,top), rt(right,top), rb(right,bottom), lb(left,bottom);
  std::vector<Segment> segments;
  segments.push_back({lt,rt});
  segments.push_back({rt,rb});
  segments.push_back({rb,lb});
  segments.push_back({lb,lt});
  for(Point& p : pts){
    for(Segment& s : segments){
      K::FT squared_dist = CGAL::squared_distance(p, s);
      update_map(my_map, p, squared_dist);
    }
  }
  
  //Now I have a map with its keys being the points and its values being the
  //squared distances from the closest objects when collision happens
  std::vector<int> my_times;
  for(Point& p : pts){
      auto search = my_map.find(p);
      double squared_distance = CGAL::to_double(search->second);
      double actual_time = std::sqrt(std::sqrt(squared_distance)-0.5);
      int my_time = int(actual_time);
      if (actual_time - my_time > 0) {my_time += 1;}
      my_times.push_back(my_time);
    }
    
    std::sort(my_times.begin(), my_times.end());
    int middle = 0;
    if(n != 1) middle = int(n/2); 
    std::cout << my_times[0] << " " << my_times[middle] << " " << my_times[n-1] << "\n";
  }

int main(){
  while(true){
    std::size_t n;
    std::cin >> n;
    if (n == 0) {
        return 0;
      }
    testcase(n);
  }
}
