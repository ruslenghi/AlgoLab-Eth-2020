#include<iostream>
#include<queue>
#include<map>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS,
                              boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor    vertex_desc;    
typedef boost::graph_traits<graph>::edge_iterator edge_it;
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it;

long int d(std::pair<int,int> p1, std::pair<int,int> p2){
  long int d_x = p1.first - p2.first;
  long int d_y = p1.second - p2.second;
  return pow(d_x,2)+pow(d_y,2);
}

int custom_BFS(std::map<int,bool>& visited_planets, graph& G, const int& k, const int& this_planet){
  
  int counter = 0;
  std::queue<int> Q;
  Q.push(this_planet);
  counter +=1;
  visited_planets.at(this_planet) = true;
  
  while(!Q.empty()){
    int planet = Q.front(); Q.pop();
    out_edge_it oe_beg, oe_end;
    for (boost::tie(oe_beg, oe_end) = boost::out_edges(planet, G);oe_beg != oe_end; ++oe_beg) 
    { int neighbour = boost::target(*oe_beg, G);
      if(neighbour >= k and !visited_planets.at(neighbour)){
        counter +=1;
        visited_planets.at(neighbour) = true;
        Q.push(neighbour);}
    }
  }
  
  return counter;
  
}
  
bool can_get_k(const int& k, const int& n, graph& G){
  std::map<int,bool> visited_planets;
  for(int i=k; i<n; i++) {
    visited_planets.insert(std::pair<int,bool>(i,false));
  }
  
  for(int i=k; i<n; i++) {
    if(visited_planets.at(i) == true) continue;
    else{
      if(custom_BFS(visited_planets,G,k,i)>=k) return true;
    }
  }
  
  return false;
  
}

void testcase(){
  int n, r; std::cin >> n >> r;
  long int r_2 = pow(r,2);
  
  std::vector<std::pair<int,int>> planets;
  for(int i=0; i<n; i++){
    int x, y; std::cin >> x >> y;
    std::pair<int,int> my_planet;
    my_planet = std::make_pair(x,y);
    planets.push_back(my_planet);
  }
  
  //Secondo me ci siamo, ma il modo di determinare le distanze non è buono, 
  //devo trovare un modo di farlo con la Delaunay triangulation penso
  graph G(n);
  for(int i=0; i<n; i++){
    std::pair<int,int> first_planet = planets[i];
    for(int j=i+1; j<n; j++){
      std::pair<int,int> second_planet = planets[j];
      if(d(first_planet,second_planet) <= r_2) {boost::add_edge(i,j,G);}
    }
  }
  
  /*edge_it e_beg, e_end;
  for (boost::tie(e_beg, e_end) = boost::edges(G); e_beg != e_end; ++e_beg) {
        std::cout << boost::source(*e_beg, G) << " "
                  << boost::target(*e_beg, G) << "\n";}*/
  
  //Put the function can_get_k function here and do a binary search with it
  
  int head = n;
  int tail = 0;
  while(head >= tail){
    int q = (head+tail)/2;
    if(can_get_k(q, n, G)) tail = q+1;
    else head = q-1;
  }
  std::cout << head << "\n";
  //if(test) std::cout << "YES!" << "\n";
  //else std::cout << "NO!" << "\n";
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
