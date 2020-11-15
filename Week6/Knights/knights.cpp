#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <vector>
#include<algorithm>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS,
boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS,
  boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
      boost::property<boost::edge_residual_capacity_t, long,
          boost::property<boost::edge_reverse_t, 
            traits::edge_descriptor>>>> graph;
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

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

//The problem with this code is, I would say, that it does not work when c=1 
void testcase(){
  int m, n, k, c;
  std::cin >> m >> n >> k >> c;
  if(m==0 or n==0){
    std::cout<<0<<"\n";
    return;
  }
  //if(c==2) c = int(c/2);
  //n = n+2;
  //m = m+2;
  int vertices = n*m;
  graph G(vertices);
  edge_adder adder(G);
  
  for(int i=0; i<vertices; i++){
    adder.add_edge(2*i+1, 2*i, c);
    if(i < m*(n-1)){
      adder.add_edge(2*i, 2*(i+m)+1, 1);
      adder.add_edge(2*(i+m), 2*i+1, 1);}
    if(i%m != m-1){
      adder.add_edge(2*i, 2*(i+1)+1, 1);
      adder.add_edge(2*(i+1), 2*i+1, 1);}
  }
  
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  
  for(int i=0; i<k; i++){
    //x is the column and y the row
    int x, y; std::cin >> x >> y;
    adder.add_edge(v_source,2*(m*y+x)+1, 1);
  }
  
  for(int i=0; i<m; i++){
    adder.add_edge(2*i, v_sink, 1);
    adder.add_edge(2*(vertices -m +i), v_sink, 1);
  }
  
  // It looks like the error is in this for loop..
  for(int i=0; i<n; i++){
    adder.add_edge(2*i*m, v_sink, 1);
    int right_end = 2*(i*m+(m-1));
    adder.add_edge(right_end, v_sink, 1);
  }
  
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  std::cout << flow << "\n";
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t=0; std::cin >> t;
  while(t>0){
  testcase();
  t -=1;}
}
