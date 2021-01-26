#include <iostream>
#include <vector>
#include<climits>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

std::vector<edge_desc> kruskal(const weighted_graph &G) {
  std::vector<edge_desc> mst;    
  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
  return mst;
}

int dijkstra_dist(const weighted_graph &G, int s, int t) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map[t];
}


void testcase(){
  int n, e, s, a, b; std::cin >> n >> e >> s >> a >> b;
  
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  
  //std::vector<std::vector<int>> edges(e, std::vector<int>(s+2, 0));
  
  edge_desc E;
  for(int i=0; i<e; i++){
    int t_1, t_2; std::cin >> t_1 >> t_2;
    int minimum = INT_MAX;
    for(int j=0; j<s; j++){
      int w; std::cin >> w;
      minimum = std::min(minimum, w);
    }
    E = boost::add_edge(t_1, t_2, G).first; weights[E] = minimum;
  }
  
  for(int i=0; i<s; i++){
    int h; std::cin >> h;
  }

  std::vector<edge_desc> total_hive = kruskal(G);
  
  weighted_graph g(n);
  weight_map weights_ = boost::get(boost::edge_weight, g);
  
  edge_desc e_;
  for (std::vector<edge_desc>::iterator it = total_hive.begin(); it != total_hive.end(); ++it) {
    int x = boost::source(*it, G);
    int y = boost::target(*it, G);
    int w = weights[*it];
    e_ = boost::add_edge(x, y, g).first; weights_[e_]=w;
  }
  
  
  std::cout << dijkstra_dist(g, a, b) << "\n";

}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
