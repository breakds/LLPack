#include <string>
#include <cstdio>
#include "LLPack/algorithms/heap.hpp"


int main() {
  
  // Create the heap, non-fixed
  heap<int,std::string,false> gradeRanker;

  // Check whether the heap is empty.
  if ( gradeRanker.empty() ) {
    printf( "empty\n" );
  } else {
    printf( "not empty\n" );
  }

  // Add grade/name pairs into the heap
  gradeRanker.add( 65, "Tom" );

  // Check whether the heap is empty.
  if ( gradeRanker.empty() ) {
    printf( "empty\n" );
  } else {
    printf( "not empty\n" );
  }
  
  // reset the heap
  gradeRanker.reset();

  // Check whether the heap is empty.
  if ( gradeRanker.empty() ) {
    printf( "empty\n" );
  } else {
    printf( "not empty\n" );
  }

  return 0;
}
