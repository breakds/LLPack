#include <cstdlib>
#include <cstdio>
#include "../heap.hpp"


int main() {
  
  srand(103);

  heap<int,int> h(10);

  for ( int i=0; i<800; i++ ) {
    h.add( rand() % 1000, i );
  }
  
  while ( !h.empty() ) {
    printf( "%d\n", h(0) );
    h.pop();
  }
  
  return 0;
}
