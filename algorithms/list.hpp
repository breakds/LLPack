/*********************************************************************************
 * File: list.hpp
 * Description: Implementation of list objects, including 
 *              1) circular list
 * by BreakDS, @ University of Wisconsin-Madison, Fri Oct 19 08:33:14 CDT 2012
 *********************************************************************************/

#pragma once


#include <vector>



template <typename valueType>
class Circular
{

private:
  std::vector<valueType> container; // container.len == capacity of Circular list
  int len;
  int head; // the first element
  int tail; // the position for the next back-incoming element


  inline void prev( int &pos ) 
  {
    pos--;
    if ( -1 == pos ) pos = static_cast<int>( container.size() ) - 1;
  }

  inline void succ( int &pos ) 
  {
    pos++;
    if ( static_cast<int>( container.size() ) == pos ) pos = 0;
  }

  Circular( const Circular<valueType> &other );

public:

  Circular( int n ) : len(n)
  {
    container.resize( n );
    head = 0;
    tail = 0;
    len = 0;
  }
  
  // move constructor
  Circular( Circular<valueType>&& other ) 
  {
    container.swap( other.container );
    len = other.len;
    head = other.len;
    tail = other.len;
  }


  void push_back( valueType val )
  {
    if ( len == static_cast<int>( container.size() ) ) {
      // resize if len exceeds capacity
      std::vector<valueType> vTmp;
      vTmp.resize( static_cast<int>( container.size() << 1 ) );
      int j = head;
      for ( int i=0; i<len; i++ ) {
        vTmp[i] = container[j];
        succ(j);
      }
      vTmp[len++] = val;
      head = 0;
      tail = len;
      container.swap( vTmp );
    } else {
      container[tail] = val;
      len++;
      succ(tail);
    }
  }

  void push_front( valueType val )
  {
    if ( len == static_cast<int>( container.size() ) ) {
      // resize if len exceeds capacity
      std::vector<valueType> vTmp;
      vTmp.resize( static_cast<int>( container.size() << 1 ) );
      len++;
      int j = head;
      for ( int i=1; i<len; i++ ) {
        vTmp[i] = container[j];
        succ(j);
      }
      vTmp[0] = val;
      head = 0;
      tail = len;
      container.swap( vTmp );
    } else {
      prev(head);
      container[head] = val;
      len++;
    }
  }

  bool pop_back()
  {
    if ( len > 0 ) {
      len--;
      prev(tail);
      return true;
    }
    return false;
  }

  bool pop_front()
  {
    if ( len > 0 ) {
      len--;
      succ(head);
      return true;
    }
    return false;
  }
  
  valueType& operator[]( int index )
  {
    if ( head + index >= static_cast<int>( container.size() ) ) {
      return container[head + index - static_cast<int>( container.size() )];
    }
    return container[head+index];
  }

  const valueType& operator()( int index )
  {
    if ( head + index >= static_cast<int>( container.size() ) ) {
      return container[head + index - static_cast<int>( container.size() )];
    }
    return container[head+index];
  }

  inline bool empty() const
  {
    return ( 0 == len );
  }

  inline int size() const
  {
    return len;
  }
};
