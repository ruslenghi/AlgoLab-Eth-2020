#include<iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose input type (input coefficients must fit)
typedef long IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int sign(IT x, IT y, IT a, IT b, IT c){
  long s = a*x+b*y+c;
  if(s >= 0) {return 1;}
  else {return -1;}
}

void testcase(){
  
  IT x_s, y_s, n; std::cin >> x_s >> y_s >> n;
  // create an LP with Ax <= b, no upper nor lower bounds
  Program lp (CGAL::SMALLER, false, 0, false, 0); 
  
  // set the coefficients of A and b
  const int t = 0;
  const int x_p = 1;
  const int y_p = 2;
  for(int i=0; i<n; i++){
    IT a, b, c, v; std::cin >> a >> b >> c >> v;
    int s_sign = sign(x_s,y_s,a,b,c);
    IT a_l = pow(a, 2), b_l = pow(b, 2), den = sqrt(a_l + b_l);
    
    //We want to ensure two conditions.
    
    //1) The optimum point must have the same sign as the starting point when we
    //   insert it in each of the roman lines equations. More formally:
    //   (a*x_p+b*y_p+c)*sign(a*x_s+b*y_s+c) >= 0 (A)
    
    //2) The time before Asterix is caught must be smaller than:
    //   t = abs(a*x_p+b*y_p+c)/(v*sqrt(a^2+b^2)) That is the same as asking:
    //   t*(v*sqrt(a^2+b^2)) <= abs(a*x_p+b*y_p+c) (B)
    
    //Now, to implement the r.h.s in eq (B) in the lp, we can multiply it for  
    //sign(a*x_s+b*y_s+c). This will both ensure eq (A), as the l.h.s in (B) is
    //positive, and implement the absolute value.
    
    lp.set_a(t, i, v*den); 
    lp.set_a(x_p, i, -a*s_sign); 
    lp.set_a(y_p, i, -b*s_sign); 
    lp.set_b(i, c*s_sign);
    
  }
  // objective function
  lp.set_l(t, true, 0);
  lp.set_c(t, -1);
  lp.set_c(x_p, 0);
  lp.set_c(y_p, 0);
  lp.set_c0(0);

  // solve the program, using ET as the exact type
  Solution s = CGAL::solve_linear_program(lp, ET());
  ET result = s.objective_value_numerator()/s.objective_value_denominator();
  // output solution
  std::cout << std::fixed << std::setprecision(0) << std::floor(CGAL::to_double(-1*result)) << "\n"; 
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
