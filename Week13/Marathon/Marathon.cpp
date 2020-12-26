// STL includes
#include <iostream>
#include <vector>
#include<map>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int>>      weighted_graph;

typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

int dijkstra_dist(const weighted_graph &G, int s, int t) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map[t];
}

int dijkstra_path(const weighted_graph &G, int s, int t, std::vector<vertex_desc> &path) {
  int n = boost::num_vertices(G);
  std::vector<int>         dist_map(n);
  std::vector<vertex_desc> pred_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G)))
    .predecessor_map(boost::make_iterator_property_map(
      pred_map.begin(), boost::get(boost::vertex_index, G))));

  int cur = t;
  path.clear(); path.push_back(cur);
  while (s != cur) {
    cur = pred_map[cur];
    path.push_back(cur);
  }
  std::reverse(path.begin(), path.end());
  return dist_map[t];
}

void testcase(){
  
  int n, m, s, f; std::cin >> n >> m >> s >> f;
  std::cout << n <<" " << m << " " << s << " " << f << "\n";
  if(n == 0 or m == 0){
    std::cout << 0;
  } 
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  edge_desc e;
  
  
  std::map<std::pair<int,int>,int> capacities;
  for(int i=0; i<m; i++){
    int a, b, c, d; std::cin >> a >> b >> c >> d;
    e = boost::add_edge(a, b, G).first; weights[e]=d;
    e = boost::add_edge(b, a, G).first; weights[e]=d;
    std::pair<int,int> my_pair_1 = std::make_pair(a,b);
    std::pair<int,int> my_pair_2 = std::make_pair(b,a);
    capacities.insert(std::make_pair(my_pair_1,c));
    capacities.insert(std::make_pair(my_pair_2,c));
  }

  std::vector<vertex_desc> path;
  dijkstra_path(G, s, f, path);
  
  int prev = path[0]; int next = path[0];
  int bottleneck = INT_MAX;
  for (int i = 1; i < (int)path.size(); i++){ 
    prev = next;
    next = path[i];
    std::cout << prev << " " << next << "\n"; 
    std::pair<int,int> my_edge = std::make_pair(prev,next);
    int this_cap = capacities.at(my_edge);
    bottleneck = std::min(bottleneck,this_cap);
  }
  
  std::cout << bottleneck << "\n";
  
}

int main(){
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();}
}
