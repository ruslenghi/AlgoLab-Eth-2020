#include <iostream>
#include <vector>
#include <bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

std::vector<edge_desc> kruskal(const weighted_graph &G) {
  std::vector<edge_desc> mst;
  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
  return mst;
}

void testcase_star(){
  int n, i; std::cin >> n >> i;
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  std::vector<std::vector<int>> A(n, std::vector<int>(n,0));
  edge_desc e;
  for(int j=0; j<n; j++){
    int j_th_guess = 0;
    for(int k=j+1; k<n; k++){
      int w; std::cin >> w;
      e = boost::add_edge(j, k, G).first; weights[e]=w;
      A[j][k] = w; A[k][j] = w; 
    }
  }
  
  int center = 0;
  bool double_min = false;
  int my_guess = INT_MAX;
  for(int j=0; j<n; j++){
    int j_th_guess = 0;
    for(int k=0; k<n; k++){
      j_th_guess += A[j][k];
    }
    if(j_th_guess <= my_guess) {
      if(j_th_guess == my_guess) double_min = true;
      else double_min = false;
      my_guess = j_th_guess;
      center = j;
    }
  }
  
  std::vector<edge_desc> mst = kruskal(G);
  int R2D2_cost = 0;
  for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) {
    R2D2_cost += weights[*it];
  }
  
  if(my_guess != R2D2_cost or double_min) {
    std::cout << R2D2_cost << "\n";
    return;}
  
  int minimum_change = INT_MAX;
  for(int j=0; j<n; j++){
    if(j != center){
      int first_bond = A[center][j];
      for(int k=0; k<n; k++){
        if(k != center and k!=j) {int second_bond = A[j][k];
        int total_change = second_bond - first_bond;
        if( total_change < minimum_change ) minimum_change = total_change;}
      }
    }
  }

  std::cout << R2D2_cost + minimum_change << "\n";
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase_star();
  }
}
