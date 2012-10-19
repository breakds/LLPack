/*********************************************************************************
 * File: list.hpp
 * Description: UnitTest for circular list
 * by BreakDS, @ University of Wisconsin-Madison, Fri Oct 19 09:03:03 CDT 2012
 *********************************************************************************/

#include <cstdio>
#include "../list.hpp"

void print( Circular<int> &q ) 
{
  printf( "( " );
  for ( int i=0; i<q.size(); i++ ) {
    printf( "%d ", q(i) );
  }
  printf( ")\n" );
}

int main()
{
  Circular<int> q(4);
  print( q );
  q.push_back(1);
  print( q );
  q.push_back(2);
  print( q );
  q.pop_front();
  print( q );
  q.push_back(3);
  print( q );
  q.push_back(4);
  print( q );
  q.pop_back();
  print( q );
  for ( int i=5; i<=11; i++ ) {
    q.push_back(i);
    print( q );
  }
  
  
  return 0;
}

