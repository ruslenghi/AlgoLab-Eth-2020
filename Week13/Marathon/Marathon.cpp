#include <iostream>
#include<vector>
#include<algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::property_map<graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<graph>::edge_iterator edge_it;

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

// Custom edge adder class
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};

std::vector<int> dijkstra_dist(const graph &G, int s) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map;
}

void testcase(){
  int n, m, s, f; std::cin >> n >> m >> s >> f;
  
  graph dijkstra_g(n), g(n);
  weight_map weights = boost::get(boost::edge_weight, g);
  edge_adder adder(dijkstra_g);
  auto w_map = boost::get(boost::edge_weight, dijkstra_g);
  auto c_map = boost::get(boost::edge_capacity, dijkstra_g);
  for(int i=0; i<m; i++){
    int a, b, c, d; std::cin >> a >> b >> c >> d;
    if(a==b) continue;
    adder.add_edge(a, b, c, d);
    adder.add_edge(b, a, c, d);
    edge_desc e;
    e = boost::add_edge(a, b, g).first; weights[e]=d;
    e = boost::add_edge(b, a, g).first; weights[e]=d;
  }
  
  std::vector<int> distance_from_s = dijkstra_dist(g,s);
  std::vector<int> distance_from_f = dijkstra_dist(g,f);
  
  //Now I iterate over all the edges in the graph that has capacities.  
  //I set to 0 all the capacities that belong to non-shortest paths
  edge_it e_beg, e_end;
  for (boost::tie(e_beg, e_end) = boost::edges(dijkstra_g); e_beg != e_end; ++e_beg) {
        auto source_v = boost::source(*e_beg, dijkstra_g);
        auto target_v = boost::target(*e_beg, dijkstra_g);
        int tot_l = distance_from_s[source_v] + w_map[*e_beg] + distance_from_f[target_v];
        if(tot_l > distance_from_s[f]) {c_map[*e_beg] = 0;}
  }
  
  long flow = boost::push_relabel_max_flow(dijkstra_g, s, f);
  std::cout << flow << "\n";
  
}

int main(){
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
