#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

namespace boost
{
struct edge_component_t
{
    enum
    {
        num = 555
    };
    typedef edge_property_tag kind;
} edge_component;
}

using namespace boost;

typedef adjacency_list< vecS, vecS, undirectedS, no_property,
        property<edge_component_t, std::size_t >> Graph;
typedef boost::graph_traits<Graph>::edge_iterator EdgeIt;

void testcase(){
  int n, m;
  std::cin >> n >> m;
  Graph G(n);
  
  //I create the graph
  for(int i=0; i<m; i++){
    int a, b; std::cin >> a >> b;
    boost::add_edge(a, b, G);
  }
  
  property_map<Graph, edge_component_t >::type component = get(edge_component, G);
  int num_comps = biconnected_components(G, component);
  
  //I am going to use this for loop to assign each component with its number of edges
  std::vector<int> num_per_comp(num_comps, 0);
  
  graph_traits<Graph>::edge_iterator ei, ei_end;
  for (boost::tie(ei, ei_end) = edges(G); ei != ei_end; ++ei){
    num_per_comp[component[*ei]] += 1;
  } 
  
  int counter = 0;
  std::vector<std::pair<int,int>> important_bridges;
  for (boost::tie(ei, ei_end) = edges(G); ei != ei_end; ++ei){
    if(num_per_comp[component[*ei]] == 1){
      counter += 1;
      int a = source(*ei, G);
      int b = target(*ei, G);
      if(b < a) important_bridges.push_back(std::make_pair(b,a));
      else important_bridges.push_back(std::make_pair(a,b));
    } 
  }
  
  std::sort(important_bridges.begin(), important_bridges.end());
  
  std::cout << counter << "\n";
  
  for(int i=0; i<(int)important_bridges.size(); i++){
    std::cout << important_bridges[i].first << " " << important_bridges[i].second << "\n";
  }
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t=0; std::cin >> t;
  while(t>0){
  testcase();
  t -=1;}
}
