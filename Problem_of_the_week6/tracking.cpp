#include<iostream>
#include<vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      graph;
  
typedef boost::property_map<graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor          vertex_desc;

void testcase(){
  int n, m, k, x, y; std::cin >> n >> m >> k >> x >> y;
  
  //I need k+1 "graphs", because I need, first to pass thorugh k rivers, and thus k graphs,
  //after that I have to reach y though, thus the +1
  graph G(n*(k+1));
  weight_map weights = boost::get(boost::edge_weight, G);
  
  //This struct represent a weighted edge, I will need it later, to store the 
  //edges that are parallel to the river
  struct My_edge{
    int a, b, c; 
    My_edge(int a, int b, int c): a(a), b(b), c(c) {}
  };
  
  //This is a vector storing all the edges that are parallel to a river
  std::vector<My_edge> river_edges;
  edge_desc e;
  
  for(int i=0; i<m; i++){
    int a, b, c, d; std::cin >> a >> b >> c >> d;
    if(d==1){
      struct My_edge my_edge(a,b,c);
      river_edges.push_back(my_edge);
    }
    for(int j=0; j<=k; j++){
      //I create the connections among each of the k+1 "graphs"
      e = boost::add_edge(a+j*n, b+j*n, G).first; weights[e]=c;
    }
  }
  
  //Now I create the connections among the different "graphs" via the river edges
  for(int i=0; i<(int)river_edges.size(); i++){
    
    int a = river_edges[i].a;
    int b = river_edges[i].b;
    int c = river_edges[i].c;
    
    for(int j=0; j<k; j++){
      //I create the connections among each of the k+1 "graphs"
      e = boost::add_edge(a+j*n, b+(j+1)*n, G).first; weights[e]=c;
      e = boost::add_edge(b+j*n, a+(j+1)*n, G).first; weights[e]=c;
    }
  }
  
  //I transport y to the last "graph", as I want the x->y path to traverse each 
  //of the (k+1) graphs, to ensure the "pass thorugh k rivers" condition
  y += n*k;
  
  int N = boost::num_vertices(G);
  std::vector<int> dist_map(N);

  boost::dijkstra_shortest_paths(G, x,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));
      
  std::cout << dist_map[y] << "\n";
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
