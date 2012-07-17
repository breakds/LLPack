#include "../random.hpp"
#include <cstdio>



int main()
{
  srand( time( NULL ) );
  // std::vector<double> a( {1,2,3,4,5,6,7,8,9,10} );
  double a[10] = {1,2,3,4,5,6,7,8,9,10};
  std::vector<double> p = std::move( rndgen::randperm<double>( a, 3, 10 ) );
  for ( int i=0; i<3; i++ ) {
    printf( "%.2lf\n", p[i] );
  }
  return 0;
}
