#include <iostream>
#include <vector>
#include<climits>
#include<boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
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

void testcase(){
  int n, e, s, a, b; std::cin >> n >> e >> s >> a >> b;
  
  std::vector<std::vector<int>> edges(e, std::vector<int>(s+2, 0));

  for(int i=0; i<e; i++){
    int t_1, t_2; std::cin >> t_1 >> t_2;
    edges[i][0] = t_1; edges[i][1] = t_2;
    for(int j=0; j<s; j++){
      int w; std::cin >> w;
      edges[i][2+j] = w;
    }
  }
  
  weighted_graph g(n);
  weight_map weights_ = boost::get(boost::edge_weight, g);
  edge_desc e_;
  
  //For each species I build its mst and I store all of them. Then I merge them in
  //a full graph on which I run Dijkstra
  for(int i=0; i<s; i++){
    
    int h; std::cin >> h;
    weighted_graph G(n);
    weight_map weights = boost::get(boost::edge_weight, G);
    edge_desc E;
    
    for(int j=0; j<e; j++){
      E = boost::add_edge(edges[j][0], edges[j][1], G).first; weights[E]=edges[j][2+i];
    }
    
    std::vector<edge_desc> mst; 
    boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
    
    for(std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) {
      e_ = boost::add_edge(boost::source(*it, g), boost::target(*it, g), g).first; 
      weights_[e_] = weights[*it];
    }
    
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
