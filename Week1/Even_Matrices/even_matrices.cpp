#include <iostream>
#include <vector>

using namespace std;

void testcase(){
  
  int n = 0; cin >> n;
  
  // I create the matrix
  vector<vector<int>> matrix(n);
  for ( int i = 0 ; i < n ; i++ ){matrix[i].resize(n);}
  
  for(int i = 0; i<n; i++)
  {   for(int j = 0; j<n; j++) {cin>>matrix[i][j];}
    }
  
  int even=0;
  
  // I create a 3D matrix to store all the "volumes" of the boxes i am gonna need
  vector<vector<vector<int>>> Box(n, vector<vector<int> > (n, vector<int>(n,0)));
  
  for(int i_2=0; i_2<n; i_2++){
    for(int i_1=0; i_1<=i_2; i_1++){
      for(int j=0; j<n; j++){
        int sum=0;
           for(int a=i_1; a<=i_2; a++){
             for(int b=0; b<=j; b++){
              sum += matrix[a][b];
          }
        }
        Box[i_1][i_2][j] = sum;
        // I perform the 1) step: I evaluate the boxes
        //The "i_1<=i_2" condition is guaranteed to hold by the 2nd for's shape
        if(sum%2==0){even++;}
      }
    }
  }
  
  //I perform the 2) step: I evaluate the complementaries of boxes 
  //that start and end on the same rows
  for(int b=0; b<n; b++){
    for(int a=0; a<=b; a++){
      for(int c_2=0; c_2<n; c_2++){
        for(int c_1=0; c_1<c_2; c_1++){
            int elem = Box[a][b][c_2]-Box[a][b][c_1];
           if(elem%2==0){even++;}
        }
      }
    }
  }

 cout << even << endl; 
}

int main(){
  int t = 0; cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}
