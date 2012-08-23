/*********************************************************************************
 * File: sortTest.cpp
 * Description: Test facility for sort.hpp in LLPack
 * by BreakDS, @ University of Wisconsin-Madison, Wed Jun  6 12:10:19 CDT 2012
 *********************************************************************************/
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <functional>
#include "../sort.hpp"
#include "../../utils/time.hpp"


using std::vector;

int main() 
{
  int n = 10000;
  srand( time( NULL ) );
  vector<int> vals;
  vals.resize(n);


  double elapsed = 0.00;
  vector<int> ind;
  ind.resize(n);

  for ( int iter=0; iter<2000; iter++ ) {
  
    for ( int i=0; i<n; i++ ) {
      vals[i] = rand() % 7778881;
    }

    timer::tic();
    ind = std::move( sorting::index_sort( vals ) );
    elapsed += timer::utoc();
  }
  
  printf( "time consumption: %.3lf\n", elapsed );

  /*
  for ( int i=0; i<n; i++ ) {
    printf( "%d\n", vals[ind[i]] );
  }
  */
  
  /*
  vector<int> c( {5,6,3,4,7,8,1,9,2} );
  printf( "median is %d\n", sorting::median( c ) );
  */
  
  return 0;
}
