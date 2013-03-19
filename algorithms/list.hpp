/*********************************************************************************
 * File: list.hpp
 * Description: Implementation of list objects, including 
 *              1) circular list
 *              2) sub-list wrapper
 * by BreakDS, @ University of Wisconsin-Madison, Fri Oct 19 08:33:14 CDT 2012
 *********************************************************************************/

#pragma once

#include "../utils/candy.hpp"
#include <cassert>
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

  void clear()
  {
    len = 0;
    head = 0;
    tail = 0;
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
  
  inline valueType& operator[]( int index )
  {
    if ( head + index >= static_cast<int>( container.size() ) ) {
      return container[head + index - static_cast<int>( container.size() )];
    }
    return container[head+index];
  }

  inline const valueType& operator()( int index )
  {
    if ( head + index >= static_cast<int>( container.size() ) ) {
      return container[head + index - static_cast<int>( container.size() )];
    }
    return container[head+index];
  }

  inline const valueType& back()
  {
    assert( size > 0 );
    int t = tail;
    prev(t);
    return container[t];
  }

  inline const valueType& front()
  {
    assert( size > 0 );
    return container[head];
  }
  
  inline bool empty() const
  {
    return ( 0 == len );
  }

  inline bool full() const
  {
    if ( static_cast<int>( container.size() ) == len ) {
      return true;
    }
    return false;
  }

  inline int size() const
  {
    return len;
  }
};


template <typename arrayType=std::vector<int> >
class SubListView
{
public:
  typedef typename ElementOf<arrayType>::type dataType;
private:
  const arrayType& parent;
  const std::vector<int>& idx;
  
public:

  SubListView( const arrayType& array, const std::vector<int>& subidx ) : parent(array), idx(subidx)
  {}

  /* ---------- accessors ---------- */
  inline const dataType operator[]( int index )
  {
    return parent[idx[index]];
  }

  inline int size() const
  {
    return static_cast<int>( idx.size() );
  }

  /* ---------- iterator ---------- */
  class iterator
  {
  private:
    const arrayType& parent;
    std::vector<int>::const_iterator iter;
  public:
    iterator( const arrayType& _parent, std::vector<int>::const_iterator _iter )
      : parent(_parent), iter(_iter) {}

    bool operator!=( const iterator& other ) const
    {
      return iter != other.iter;
    }

    const dataType& operator*() const
    {
      return parent[*iter];
    }

    const iterator& operator++()
    {
      iter++;
      return (*this);
    }
  };

  iterator begin() const
  {
    return iterator( parent, idx.begin() );
  }

  iterator end() const
  {
    return iterator( parent, idx.end() );
  }

};

class SubList
{
public:
  template <typename T>
  static SubListView<T> create( const T& array, const std::vector<int>& subidx )
  {
    return SubListView<T>( array, subidx );
  }
};




