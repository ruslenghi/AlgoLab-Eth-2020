/* The idea is to build two separate graphs that has the same geometry but 
different capacities. In the first one the capacities are set to 'infinity', as
we want the policemen to be freely able to move towards the best photographs. In
the second graph, however, we have to keep in mind the constraint that only 1 
policemen can traverse a specific edge, thus we set all capacities to 1. Finally,
we run max flow from source to target, where the source is connected to the stations 
of the first graph, while the target is conneced to the stations of the 2nd one */

#include<iostream>
#include<climits>

// BGL include
#include <boost/graph/adjacency_list.hpp>

// BGL flow include *NEW*
#include <boost/graph/push_relabel_max_flow.hpp>

// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

// Custom edge adder class, highly recommended
class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

void testcase(){
  int n, m, k, l; std::cin >> n >> m >> k >> l;
  
  //This singel graph will conceptually contain the two separate graphs 
  graph G(2*n);
  edge_adder adder(G);
  
  int v_source = 2*n;
  int v_target = 2*n+1;
  
  for(int i=0; i<k; i++){
    int my_station; std::cin >> my_station;
    //Connect source to each station
    adder.add_edge(v_source, my_station, 1);
    //Connect stations in 2nd graph to the target
    adder.add_edge(my_station + n, v_target, 1);
  }
  
  for(int i=0; i<l; i++){
    int my_photo; std::cin >> my_photo;
    //Connect photos in graph 1 to photos in graph 2
    adder.add_edge(my_photo, my_photo + n, 1);
  }
  
  //I create the edges in both the 1st and 2nd graphs
  for(int i=0; i<m; i++){
    int x, y; std::cin >> x >> y;
    //The edges in the first graph must have infinite capacity, as the policemen
    //are not carrying photographs yet
    adder.add_edge(x, y, INT_MAX);
    //The edges in the second graph must, instead, have unit capacity, as the 
    //policemen are now carrying the photographs
    adder.add_edge(x + n, y + n, 1);
  }
  
  long flow = boost::push_relabel_max_flow(G, v_source, v_target);
  std::cout << flow << "\n";
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
