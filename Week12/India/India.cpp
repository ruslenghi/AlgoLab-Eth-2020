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

int max_cargo(graph& G, int&c, int& k, int& a){
  edge_adder adder(G);
  adder.add_edge(c, k, INT_MAX, 0);
  adder.add_edge(a, c+1, INT_MAX, 0);
  int max_cargo = boost::push_relabel_max_flow(G, c, c+1);
  boost::remove_edge(c,k,G);
  boost::remove_edge(a,c+1,G);
  return max_cargo;
}

bool can_buy(graph& G, int&c, int &b, int& k, int& a, int& i){
  edge_adder adder(G);
  auto c_map = boost::get(boost::edge_capacity, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  
  adder.add_edge(c, k, i, 0);
  adder.add_edge(a, c+1, i, 0);
  boost::successive_shortest_path_nonnegative_weights(G, c, c+1);
  int cost = boost::find_flow_cost(G);
  int flow = 0;
  out_edge_it e, eend;
  for(boost::tie(e, eend) = boost::out_edges(boost::vertex(c,G), G); e != eend; ++e) {
      flow += c_map[*e] - rc_map[*e];     
    }
  boost::remove_edge(c,k,G);
  boost::remove_edge(a,c+1,G);
  if(cost<=b and flow==i) return true;
  else return false;
}

void testcase(){
  int c, g, b, k, a; 
  std::cin >> c >> g >> b >> k >> a;
  graph G(c+2);
  edge_adder adder(G);  

  for(int i=0; i<g; i++){
    int p_x, p_y, d, e; 
    std::cin >> p_x >> p_y >> d >> e;
    adder.add_edge(p_x, p_y, e, d);
  }
  
  //I get the maximum number of suitcases that can travel from k to a
  //regardless of the budget. This is done to initialize the binary search
  int head = max_cargo(G,c,k,a);
  int tail = 0;
  
  //I do a binary search to find the maximum number of suitcases that I can
  //transport knowing that I have b as budget
  while(head>=tail){
    int q = (head+tail)/2;
    if(can_buy(G,c,b,k,a,q)) tail = q+1;
    else head = q-1;
  }
  std::cout << head << "\n";
  
}

int main(){
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
