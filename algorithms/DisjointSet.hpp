#ifndef DISJOINT_SET_HPP
#define DISJOINT_SET_HPP

#include <cstdio>
#include <cstring>
#include "../utils/SafeOP.hpp"


#define DISJOINT_SET_RECURSIVE_UPPER_BOUND 50

class DisjointSet {
  int *pre;
  int *num;
  int *tmp_stack;

  inline int find_rec( const int x ) {
    if ( -1 == pre[x] ) {
      return x;
    }
    int i = find( pre[x] );
    pre[x] = i;
    return i;
  }

  inline int find_stack( const int x ) {
    int top = -1;
    int i = x;
    while ( pre[i] != -1 ) {
      top++;
      tmp_stack[top] = i;
      i = pre[i];
    }

    for ( ; top >= 0 ; pre[tmp_stack[top--]] = i ) ;
    return i;
  }


public:
  int size;
  int capacity;

  DisjointSet() {
    size = 0;
    capacity = 0;
    pre = NULL;
    num = NULL;
    tmp_stack = NULL;
  }

  DisjointSet( const int s ) {
    capacity = s + 2;
    size = s;
    pre = new int[capacity];
    num = new int[capacity];
    tmp_stack = new int[capacity];
    for ( int i=0; i<size; i++ ) {
      pre[i] = -1;
      num[i] = 1;
    }
    memset( tmp_stack, 0, sizeof(int) * capacity );
  }
  
  inline void ClearData() {
    size = 0;
    capacity = 0;
    DeleteToNullWithTestArray( pre );
    DeleteToNullWithTestArray( num );
    DeleteToNullWithTestArray( tmp_stack );
  }
  
  ~DisjointSet() {
    ClearData();
  }

  inline void Resize ( const int s ) {
    if ( s < capacity ) {
      size = s;
    } else {
      capacity = s + 2;
      size = s;
      DeleteToNullWithTestArray( pre );
      pre = new int[capacity];
      DeleteToNullWithTestArray( num );
      num = new int[capacity];
      DeleteToNullWithTestArray( tmp_stack );
      tmp_stack = new int[capacity];
    }
    for ( int i=0; i<size; i++ ) {
      pre[i] = -1;
      num[i] = 1;
    }
    memset( tmp_stack, 0, sizeof(int) * capacity );
  }



  inline int find( const int x ) {
    if ( size < DISJOINT_SET_RECURSIVE_UPPER_BOUND ) {
      return find_rec( x ) ;
    } else {
      return find_stack( x );
    }
  }

  inline void merge( const int x, const int y ) {
    int x1 = find( x );
    int y1 = find( y );
    if ( x1 != y1 ) {
      if ( num[x1] > num[y1] ) {
        pre[y1] = x1;
        num[x1] += num[y1];
      } else {
        pre[x1] = y1;
        num[y1] += num[x1];
      }
    }
  }
};


#endif
