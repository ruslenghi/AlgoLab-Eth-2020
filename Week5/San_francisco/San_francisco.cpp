#include<iostream>
#include<vector>
#include <boost/graph/adjacency_list.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;
typedef boost::graph_traits<weighted_graph>::out_edge_iterator out_edge_it;

//I believe that what I am doing here is right, the problem is that I am using
//the wrong data structures. The use of the graph probably slows down the code 
//Try using an stl adjacency list instead

long long int dp(std::vector<std::vector<long long int>> &memo, weighted_graph &G, int i, int k){
  
  if(memo[i][k] != -1) return memo[i][k];
  if(k==0) return 0;
  
  weight_map weights = boost::get(boost::edge_weight, G);
  std::vector<std::pair<int,int>> neighbours;
  
  //This is probably the part that slows down the code
  out_edge_it oe_beg, oe_end;
  for(boost::tie(oe_beg, oe_end) = boost::out_edges(i, G); oe_beg != oe_end; ++oe_beg) {
    int new_neighbour = boost::target(*oe_beg, G);
    int new_weight = weights[*oe_beg];
    neighbours.push_back(std::make_pair(new_neighbour, new_weight));
  }
  
  //In case I am at a dead end I can go back to 0 without any spending!
  if((int)neighbours.size() == 0){return dp(memo, G, 0, k);}
  
  long long int result = 0;
  for(int i = 0; i < (int)neighbours.size(); i++){
    result = std::max(result, dp(memo, G, neighbours[i].first, k-1) + neighbours[i].second);
  }
  
  memo[i][k] = result;
  return memo[i][k];
  
}

void testcase(){
  long long int n, m, x, k; std::cin >> n >> m >> x >> k;
  
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  edge_desc e;
  
  for(int i=0; i<m; i++){
    int u, v, p; std::cin >> u >> v >> p;
    e = boost::add_edge(u, v, G).first; weights[e]=p;
  }
  
  //memo[i][j] returns the maximum achievable score when starting from point i 
  //of the board and when we have j moves to make
  std::vector<std::vector<long long int>> memo(n+1 ,std::vector<long long int> (k+1, -1));

  int impossible = true;
  int tail = 1;
  int head = k;
  
  //The binary search does not speed up the code much
  //as the subproblems need to be solved in any case...
  while(head >= tail){
    int q = (head +tail)/2;
    if(dp(memo, G, 0, q) >= x) {
      head = q-1;
      impossible = false;}
    else tail = q+1;
  }
  
  if(impossible) std::cout << "Impossible\n";
  else std::cout << tail << "\n";
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
