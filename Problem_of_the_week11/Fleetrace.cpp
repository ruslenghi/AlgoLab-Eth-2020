/* I solve the problem via min-cost/maax-flow, by creating a bond of null cost and unit capacity between each of the 
boat/sailor couples that are not linked according to the info provided by the test set. Then I run the algorithm 
with a small adjustment to ensure the positivity of the costs, while maximizing the cost instead of minimizing it*/

#include <iostream>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

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

void testcase(){
  int b, s, p; std::cin >> b >> s >> p;
  
  graph G(b*s+2);
  edge_adder adder(G);  
  auto c_map = boost::get(boost::edge_capacity, G);
  auto r_map = boost::get(boost::edge_reverse, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  
  for(int i=0; i<b; i++){
    for(int j=0; j<s; j++){
      adder.add_edge(i, b+j, 1, 50);
    }
  }
  
  for(int i=0; i<p; i++){
    int this_b, this_s, c; std::cin >> this_b >> this_s >> c;
    boost::remove_edge(this_b, b+this_s, G);
    adder.add_edge(this_b,b+this_s, 1, 50-c);
  }
  
  int v_source = b+s;
  int v_target = b+s+1;
  
  for(int i=0; i<b; i++){
    adder.add_edge(v_source, i, 1, 0);
  }
  
  for(int j=0; j<s; j++){
    adder.add_edge(b+j, v_target, 1, 0);
  }
  
  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_target);
  int cost = boost::find_flow_cost(G);
  int flow = 0;
  out_edge_it e, eend;
  for(boost::tie(e, eend) = boost::out_edges(boost::vertex(v_source,G), G); e != eend; ++e) {flow += c_map[*e] - rc_map[*e];}
  
  std::cout << flow*50-cost << "\n";
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t; 
  for(int i=0; i<t; i++){
    testcase();
  }
}
