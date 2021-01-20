#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

using namespace std;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,  
    boost::no_property,  
    boost::property<boost::edge_weight_t, int>> Graph;
typedef boost::graph_traits<Graph>::edge_iterator EdgeIt;
typedef boost::property_map<Graph, boost::edge_weight_t>::type  WeightMap;
  
typedef pair<int,int> E;

void testcase(){
  int n, m;
  cin >> n >> m;
  Graph G(n);
  
  //I define this variable, because I need a property map to store the 
  //bicconnected components
  WeightMap componentmap = get(boost::edge_weight, G);
  for(int i=0; i<m; i++){
    int e_1, e_2; std::cin >> e_1 >> e_2;
    add_edge(e_1,e_2,G);
  }
  
  int numcomp = boost::biconnected_components(G, componentmap);
  std::vector<int> component_counter(numcomp,0);
  std::vector<E> critical_edges;
  EdgeIt ebeg, eend;
  for(boost::tie(ebeg,eend) = edges(G); ebeg!= eend; ++ebeg){
    int index = componentmap[*ebeg];
    component_counter[index] += 1;
  }
  
  for(boost::tie(ebeg,eend) = edges(G); ebeg!= eend; ++ebeg){
    int index = componentmap[*ebeg];
    if(component_counter[index] == 1){
      int a = boost::source(*ebeg,G);
      int b = boost::target(*ebeg,G);
      E couple {min(a,b),max(a,b)};
      critical_edges.push_back(couple);
    }
  }
  
  std::sort(critical_edges.begin(), critical_edges.end());
  std::cout << critical_edges.size() << "\n";
  for(int i =0; i < critical_edges.size(); i++){
    std::cout << critical_edges[i].first << " " <<
                 critical_edges[i].second << "\n";
  }
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t=0; std::cin >> t;
  while(t>0){
  testcase();
  t -=1;}
}
