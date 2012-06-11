#ifndef DISJOINT_SET_HPP
#define DISJOINT_SET_HPP

#include "../utils/SafeOP.hpp"

#define DISJOINT_SET_RECURSIVE_UPPER_BOUND 50

class DisjointSet {
  int *pre;
  uint *num;
  uint *tmp_stack;

  inline uint find_rec( const uint x ) {
    if ( -1 == pre[x] ) {
      return x;
    }
    uint i = find( pre[x] );
    pre[x] = i;
    return i;
  }

  inline uint find_stack( const uint x ) {
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
  uint size;
  uint capacity;

  DisjointSet() {
    size = 0;
    capacity = 0;
    pre = NULL;
    num = NULL;
    tmp_stack = NULL;
  }

  DisjointSet( const uint s ) {
    capacity = s + 2;
    size = s;
    pre = new int[capacity];
    num = new uint[capacity];
    tmp_stack = new uint[capacity];
    for ( uint i=0; i<size; i++ ) {
      pre[i] = -1;
      num[i] = 1;
    }
    memset( tmp_stack, 0, sizeof(uint) * capacity );
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

  inline void Resize ( const uint s ) {
    if ( s < capacity ) {
      size = s;
    } else {
      capacity = s + 2;
      size = s;
      DeleteToNullWithTestArray( pre );
      pre = new int[capacity];
      DeleteToNullWithTestArray( num );
      num = new uint[capacity];
      DeleteToNullWithTestArray( tmp_stack );
      tmp_stack = new uint[capacity];
    }
    for ( uint i=0; i<size; i++ ) {
      pre[i] = -1;
      num[i] = 1;
    }
    memset( tmp_stack, 0, sizeof(uint) * capacity );
  }



  inline uint find( const uint x ) {
    if ( size < DISJOINT_SET_RECURSIVE_UPPER_BOUND ) {
      return find_rec( x ) ;
    } else {
      return find_stack( x );
    }
  }

  inline void merge( const uint x, const uint y ) {
    uint x1 = find( x );
    uint y1 = find( y );
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
