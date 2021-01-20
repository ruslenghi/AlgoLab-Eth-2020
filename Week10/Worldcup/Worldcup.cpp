#include<map>
#include<vector>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 P;

typedef CGAL::Gmpq IT;
typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

struct warehouse{
  int x, y, s, a;
  warehouse(int x, int y, int s, int a): x(x), y(y), s(s), a(a) {}
};

struct stadium{
  int x, y, d, u;
  stadium(int x, int y, int d, int u): x(x), y(y), d(d), u(u) {}
};

struct circle{
  int x, y, r;
  circle(int x, int y, int r): x(x), y(y), r(r) {}
};

double floor_to_double(const ET& x)
{
  double a = std::floor(CGAL::to_double(x));
  return a;
}


void testcase(){
  int n, m, c; std::cin >> n >> m >> c;
  
  std::vector<P> relevant_points;
  
  std::vector<warehouse> warehouses;
  for(int i=0; i<n; i++){
    int x, y, s, a; std::cin >> x >> y >> s >> a;
    P my_point = P(x,y);
    relevant_points.push_back(my_point);
    warehouse my_warehouse = warehouse(x,y,s,a);
    warehouses.push_back(my_warehouse);
  }
  
  std::vector<stadium> stadiums;
  for(int i=0; i<m; i++){
    int x, y, d, u; std::cin >> x >> y >> d >> u;
    P my_point = P(x,y);
    relevant_points.push_back(my_point);
    stadium my_stadium = stadium(x,y,d,u);
    stadiums.push_back(my_stadium);
  }
  
  std::vector<std::vector<double>> revenues(n, std::vector<double> (m, 0));
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      std::cin >> revenues[i][j];
    }
  }
  
  Program lp (CGAL::SMALLER, true, 0, false, 0);
  
  
  for(int i=0; i<n; i++){
      for(int j=0; j<m; j++){
      
          lp.set_a(i*m+j, j, 1);
          lp.set_a(i*m+j, m+j, -1);
          lp.set_a(i*m+j, 2*m+j, warehouses[i].a);
          lp.set_a(i*m+j, 3*m+i, 1);
      
    }
    
  }
  
  for(int j=0; j<m; j++){
    
    lp.set_b(j, stadiums[j].d);
    lp.set_b(m+j, -stadiums[j].d);
    lp.set_b(2*m+j, stadiums[j].u*100);
    
  }
  
  for(int i=0; i<n; i++){
    lp.set_b(3*m+i, warehouses[i].s);
  }
  
  Triangulation t;
  t.insert(relevant_points.begin(), relevant_points.end());
  
  //std::vector<circle> circles;
  for(int i=0; i<c; i++){
    long x, y, r; std::cin >> x >> y >> r;
    r *= r; //Be careful with this one! Maybe you would prefer to use pow!!
    
    P my_center = P(x,y);
    P nn = t.nearest_vertex(my_center)->point();
    if(CGAL::squared_distance(nn,my_center) <= r){
      //In case the circle contains the nn relevant point, check all the relevant points
      for(int j=0; j<n; j++){   
        bool one = (CGAL::squared_distance(relevant_points[j],my_center) <= r);
        for(int k=n; k<n+m; k++){   
          bool two = (CGAL::squared_distance(relevant_points[k],my_center) <= r);
          if(one != two){revenues[j][k-n] -= 0.01;}
        }
      }
    }
    
  }
  
  for(int i=0; i<n; i++){
      for(int j=0; j<m; j++){
          lp.set_c(i*m+j, -revenues[i][j]);
      }
    }
  
  Solution s = CGAL::solve_linear_program(lp, ET());
        if(s.is_infeasible()) std::cout << "RIOT!\n";
        else std::cout << std::fixed << std::setprecision(0) << 
             floor_to_double((-1*ET(s.objective_value_numerator()/s.objective_value_denominator()))) << "\n";
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
