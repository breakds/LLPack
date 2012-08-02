/*********************************************************************************
 * File: heap.hpp
 * Description: Priority Queue/Heap related data structures and operations
 * by BreakDS, @ University of Wisconsin-Madison, Thu Aug  2 10:21:49 CDT 2012
 *********************************************************************************/

#pragma once

#include <type_traits>
#include <memory>
#include <vector>
#include "../utils/candy.hpp"



// Note that heap will have its own data copy
template <typename keyType, typename dataType, bool fixed = true>
class heap
{
private:
  std::vector<keyType> keys;
  std::vector<std::unique_ptr<dataType> > data;
  int len, size, capacity;
  // len: the current # of elements in the heap
  // size: the up-limit (if any) for the heap. will be ignored if fixed = false
  // capacity: the number of elements that the internal data structure (vector) can hold
  //           will be ignored if fixed = false

private: // ========== For Commom part ==========

  inline void maxfix()
  {
    if ( len <= ) return;
    uint i = 1;
    uint j = 0;
    uint maxp = 0;


    do {
      maxp = i;
      j = i << 1;
      if ( j <= len && keys[j] > keys[maxp] ) maxp = j;
      j++;
      if ( j <= len && keys[j] > keys[maxp] ) maxp = j;

      if ( maxp == i ) {
        break;
      } else {
        keyType kTmp = keys[i];
      }
    }
  }

  inline void push( const keyType &key, dataType &&datum )
  {
    len++;
    keys[len] = key;
    data[len].reset( new dataType(datum) );
  }

  inline void pop()
  {
    
  }

public: // ========== For fixed size heap ==========
  
  // Constructor for fixed size heap
  template <bool T = fixed>
  heap( int s, ENABLE_IF(T) ) : len(0), size(s), capacity(s+2)
  {
    keys.resize( capacity );
    data.resize( capacity );
  }

  // resize the capacity for fixed size heap
  template <bool T = fixed>
  inline void resize( int s, ENABLE_IF(T) )
  {
    capacity = s + 2;
    size = s;
    len = 0;
    keys.resize( capacity );
    data.resize( capacity );
  }

  // Add a key/datum pair to the heap
  // the datum has to give up its content
  template <bool T = fixed>
  inline void add( const keyType &key, dataType &&datum )
  {
    if ( len < size ) {
      push( key, datum );
    } else if ( key < keys[1] ) {
      
    }
  }
  
public: // ========== For non-fixed size heap ==========

  // Constructor for non-fixed size heap
  template <bool T = fixed>
  heap( ENABLE_IF(!T) ) : len(0), capacity(0)
  {
    keys.clear();
    data.clear();
  }





  
};
