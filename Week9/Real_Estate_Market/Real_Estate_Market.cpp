#include<iostream>
#include<vector>
#include<algorithm>
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

typedef boost::graph_traits<graph>::edge_descriptor  edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator  out_edge_it; // Iterator

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
  
  int N, M, S; std::cin >> N >> M >> S;
  
  //limits contains the maximum sellable houses per state
  //limits[i] contains the limit for the i-th state
  std::vector<int> limits;
  for(int i=0; i<S; i++){
    int this_limit; std::cin >> this_limit;
    limits.push_back(this_limit);
  }
  
  //home_to_state contains the list of all homes and the state they are in
  //home_to_state[i] contains the state it belongs to
  std::cout << "Homes to states: " << "\n";
  std::vector<int> home_to_state;
  for(int i=0; i<M; i++){
    int this_home; std::cin >> this_home;
    home_to_state.push_back(this_home);
    std::cout << home_to_state[i] << "\n";
  }
  
  std::vector<std::vector<int>> bids;
  bids.resize(N, std::vector<int>(M, 0));
  
  //For every buyer
  std::cout << "Bids: " << "\n";
  for(int i=0; i<N; i++){
    //For every house
    for(int j=0; j<M; j++){
      int this_offer; std::cin >> this_offer;
      //bids[i][j] = the price that client i is willing to pay for home j
      bids[i][j] = this_offer;
      std::cout << bids[i][j] << " ";
    }
    std::cout << "\n";
  }
  
  graph G(N+M+S+2);
  edge_adder adder(G);  
  auto c_map = boost::get(boost::edge_capacity, G);
  auto r_map = boost::get(boost::edge_reverse, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  
  const int v_source = N+M+S;
  const int v_target = N+M+S+1;
  
  for(int i=0; i<N; i++){
      //I connect the source to the clients
      adder.add_edge(v_source, i, 1, 0);
    for(int j=0; j<M; j++){
      //I connect the clients to the homes
      adder.add_edge(i, N+j, 1, -bids[i][j]);
    }
  }
  
  for(int j=0; j<M; j++){
      //I connect the homes to the states
      int state = home_to_state[j];
      adder.add_edge(N+j, N+M+state, 1, 0);
    }
  
  //I connect the states to the target
  for(int i=0; i<S; i++) {adder.add_edge(N+M+i, v_target, limits[i], 0);}
  int my_flow = boost::push_relabel_max_flow(G, v_source, v_target);
  boost::cycle_canceling(G);
  int my_cost = -boost::find_flow_cost(G);
  
  std::cout << my_flow << " " << my_cost << "\n";
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
  
}
