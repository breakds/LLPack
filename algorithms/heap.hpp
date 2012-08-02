/*********************************************************************************
 * File: heap.hpp
 * Description: Priority Queue/Heap related data structures and operations
 * by BreakDS, @ University of Wisconsin-Madison, Thu Aug  2 10:21:49 CDT 2012
 *********************************************************************************/

#pragma once

#include <type_traits>
#include <memory>
#include <vector>
#include <cassert>
#include "../utils/candy.hpp"



// Note that heap will have its own data copy
template <typename keyType, typename dataType, bool fixed = true>
class heap
{
public:
  int len, size, capacity;
  // len: the current # of elements in the heap
  // size: the up-limit (if any) for the heap. will be ignored if fixed = false
  // capacity: the number of elements that the internal data structure (vector) can hold
  //           will be ignored if fixed = false
private:
  std::vector<keyType> keys;
  std::vector<std::unique_ptr<dataType> > data;
private: // ========== For Commom part ==========

  inline void maxfix()
  {
    if ( len <= 1 ) return;
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
	keys[i] = keys[maxp];
	keys[maxp] = kTmp;
	std::unique_ptr<dataType> dTmp = std::move( data[i] );
	data[i] = std::move( data[maxp] );
	data[maxp] = std::move( dTmp );
	i = maxp;
      }
    } while ( true );
  }
  
  inline void push( const keyType &key, dataType &&datum )
  {
    len++;
    keys[len] = key;
    data[len].reset( new dataType(datum) );
    
    int i = len;
    int j = i >> 1;
    while ( j > 0 ) {
      if ( keys[i] > keys[j] ) {
	keyType kTmp = keys[i];
	keys[i] = keys[j];
	keys[j] = kTmp;
	std::unique_ptr<dataType> dTmp = std::move( data[i] );
	data[i] = std::move( data[j] );
	data[j] = std::move( dTmp );
	i = j;
	j >>= 1;
      } else {
	break;
      }
    }
  }


public: // ========== For Commom part ==========

  inline const keyType operator()( int index )
  {
    assert( index < len );
    return keys[index+1];
  }

  inline const dataType& operator[]( int index )
  {
    assert( index < len );
    return *data[index+1];
  }


  inline bool empty()
  {
    return 0 == len;
  }
  
  inline void pop()
  {
    if ( len > 0 ) {
      keys[1] = keys[len];
      data[1] = std::move( data[len] );
      data[len].reset( nullptr );
      len--;
      maxfix();
    }
  }

  inline void reset()
  {
    len = 0;
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
    if ( s >= capacity ) {
      capacity = s + 2;
      keys.resize( capacity );
      data.resize( capacity );
    }
    size = s;
    len = 0;
  }

  // Add a key/datum pair to the heap
  // the datum has to give up its content
  template <bool T = fixed>
  inline void add( const keyType &key, dataType &datum, ENABLE_IF(T) )
  {
    if ( len < size ) {
      push( key, std::move( datum ) );
    } else if ( key < keys[1] ) {
      pop();
      push( key, std::move( datum ) );
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

  template <bool T = fixed>
  inline void add( const keyType &key, dataType &datum, ENABLE_IF(!T) )
  {
    if ( 0 == len ) {
      if ( keys.size() < 2 ) {
	keys.resize(2);
      }
      if ( data.size() < 2 ) {
	data.resize(2);
      }
    } else {
      if ( static_cast<int>( key.size() ) < len + 2 ) {
	data.push_back( key );
	data.push_back( std::move( std::unique_ptr<dataType>( nullptr ) ) );
      }
    }
    push( key, std::move( datum ) );
  }

};
