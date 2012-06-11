/* 
 * by BreakDS
 * Feb 17 2012 @ University of Wisconsin-Madison
 * ------------------------------------------------------------
 * A Class for Undirected Graph
 * implemented Edge List
 */
#ifndef MESH_HPP
#define MESH_HPP


#include <vector>
#include <valarray>
#include <cassert>

using std::vector;
using std::valarray;

class Mesh {
  uint size;
  valarray< vector<unsigned int> > m;

public:
  Mesh() 
  {
    size = 0;
  }
  
  Mesh( const uint s ) : size(s) 
  {
    m.resize(s);
    for ( unsigned int i=0; i<s; i++ ) {
      m[i].clear();
    }
  }

  inline void resize( const uint s ) 
  {
    size = s;
    m.resize( s );
    for ( unsigned int i=0; i<s; i++ ) {
      m[i].clear();
    }
  }
  
  inline bool connected( const unsigned int x, const unsigned int y ) const {
    assert( x < size );
    assert( y < size );
    
    if ( x == y ) {
      return true;
    }
    for ( unsigned int i=0; i<m[x].size(); i++ ) {
      if ( y == m[x][i] ) {
	return true;
      }
    }
    return false;
  }
  
  inline void connect( unsigned int x, unsigned int y ) {
    assert( x < size );
    assert( y < size );
    m[x].push_back(y);
    m[y].push_back(x);
  }

  inline void safe_connect( unsigned int x, unsigned int y ) {
    assert( x < size );
    assert( y < size );
    if ( ! connected ( x, y ) ) {  
      m[x].push_back(y);
      m[y].push_back(x);
    }
  }
  
  inline const vector<unsigned int> &operator[] ( const unsigned int i ) const {
    assert( i < size );
    return m[i];
  }

};

#endif
