#include "LLPack/algorithms/DisjointSet.hpp"

int main()
{
  // Create an empty disjoint set (constructor)
  DisjointSet djset(10);

  // Do merge. 
  djset.merge( 0, 1 );
  djset.merge( 2, 3 );
  djset.merge( 4, 3 );
  djset.merge( 0, 4 ); 
  djset.merge( 7, 10 ); 
  // After this, 0, 1, 2, 3, 4 will be in the same set

  // Test whether 0 and 2 are in the same set
  if ( djset.find(0) == djset.find(1) ) {
    printf( "0 and 2 are in the same set.\n" );
  } else {
    printf( "0 and 2 are not in the same set.\n" );
  }

  // Test whether 4 and 8 are in the same set.
  if ( djset.find(4) == djset.find(8) ) {
    printf( "4 and 8 are in the same set.\n" );
  } else {
    printf( "4 and 8 are not in the same set.\n" );
  }
  
  printf( "====== Reisze() ======\n" );
  // Resize the disjoint set
  djset.Resize( 20 );
  
  // Test whether 0 and 2 are in the same set
  if ( djset.find(0) == djset.find(1) ) {
    printf( "0 and 2 are in the same set.\n" );
  } else {
    printf( "0 and 2 are not in the same set.\n" );
  }

  // Test whether 4 and 8 are in the same set.
  if ( djset.find(4) == djset.find(8) ) {
    printf( "4 and 8 are in the same set.\n" );
  } else {
    printf( "4 and 8 are not in the same set.\n" );
  }



  return 0;
}
