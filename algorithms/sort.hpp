/*********************************************************************************
 * File: sort.hpp
 * Description: More Stable Sorting Utilities
 * by BreakDS, @ University of Wisconsin-Madison, Tue Jun  5 15:53:07 CDT 2012
 *********************************************************************************/

#pragma once

#include <functional>
#include <utility>
#include <cstdlib>
#include <cassert>
#include <vector>


using std::vector;
using std::pair;
using std::make_pair;
using std::function;

namespace sorting {


  // unnamed namespace for private functions
  namespace {
    template <typename T>
    // This function will REVERSE a vector
    inline void nreverse( vector<T> &vec )
    {
      int last = static_cast<int>( vec.size() ) - 1;
      for ( int i=0, end=static_cast<int>(vec.size()>>1); i<end; i++ ) {
	T tmp( std::move( vec[i] ) );
	vec[i] = std::move( vec[last-i] );
	vec[last-i] = std::move( tmp );
      }
    }
  };

  
  template<typename valueType>
  inline vector<int> index_sort( const vector<valueType>& values, bool ascending=false )
  {
    /* This is an implementation of quick sort
     * that will report sorting result as an index vector.
     */
       

    // Initialize Index
    vector< int > index;
    index.resize( values.size() );
    for ( int i=0, end=static_cast<int>( values.size() ); i<end; i++ ) {
      index[i] = i;
    }
    
    // Initialize Stack
    vector< pair< int, int > > stack;
    stack.clear();
    stack.push_back( make_pair( 0, static_cast<int>( values.size() ) - 1 ) );
		     
    while ( ! stack.empty() ) {
      int p = stack.back().first;
      int q = stack.back().second;
      stack.pop_back();
      
      int r = rand()%(q-p+1) + p;
      int tmp = index[r];
      index[r] = index[q];
      index[q] = tmp;
      
      r = p-1;
      for ( int i=p; i<q; i++ ){
	if ( values[index[i]] > values[index[q]] ){
	  r++;
	  tmp = index[r];
	  index[r] = index[i];
	  index[i] = tmp;
	}
      }
      
      r++;

      tmp = index[r];
      index[r] = index[q];
      index[q] = tmp;

      if ( q-r>1 ) stack.push_back( make_pair( r+1, q ) );
      if ( r-p>1 ) stack.push_back( make_pair( p, r-1 ) );
    }

    // if ascending then do reverse
    if ( ascending ) {
      nreverse( index );
    }
    
    return index;
  }


  template<typename valueType>
  inline vector<int> index_sort( const vector<valueType>& values,
				 std::function<bool(const valueType&, const valueType&)> compare)
  {
    /* This is an implementation of quick sort
     * that will report sorting result as an index vector.
     * This function takes an extra lambda function parameter.
     */
       

    // Initialize Index
    vector< int > index;
    index.resize( values.size() );
    for ( int i=0, end=static_cast<int>( values.size() ); i<end; i++ ) {
      index[i] = i;
    }
    
    // Initialize Stack
    vector< pair< int, int > > stack;
    stack.clear();
    stack.push_back( make_pair( 0, static_cast<int>( values.size() ) - 1 ) );
		     
    while ( ! stack.empty() ) {
      int p = stack.back().first;
      int q = stack.back().second;
      stack.pop_back();
      
      int r = rand()%(q-p+1) + p;
      int tmp = index[r];
      index[r] = index[q];
      index[q] = tmp;
      
      r = p-1;
      for ( int i=p; i<q; i++ ){
	if ( compare( values[index[i]], values[index[q]] ) ){
	  r++;
	  tmp = index[r];
	  index[r] = index[i];
	  index[i] = tmp;
	}
      }
      
      r++;

      tmp = index[r];
      index[r] = index[q];
      index[q] = tmp;

      if ( q-r>1 ) stack.push_back( make_pair( r+1, q ) );
      if ( r-p>1 ) stack.push_back( make_pair( p, r-1 ) );
    }

    // if ascending then do reverse
    return index;
  }

  // Find the kth smallest element
  template <typename valueType>
  inline valueType kth( const vector<valueType>& values, const int k )
  {

    int p = 0;
    int q = static_cast<int>( values.size() ) - 1;

    if ( p == q && 0 == k ) return values[0];
    
    vector<int> index;
    index.resize( values.size() );
    for ( int i=0, end=static_cast<int>( values.size() ); i<end; i++ ) {
      index[i] = i;
    }
    
    int target = k;
    while ( p < q ) {
      
      int r = rand()%(q-p+1) + p;
      int tmp = index[r];
      index[r] = index[q];
      index[q] = tmp;

      r = p-1;
      for ( int i=p; i<q; i++ ) {
        if ( values[index[i]] < values[index[q]] ) {
          r++;
          tmp = index[r];
          index[r] = index[i];
          index[i] = tmp;
        }
      }

      r++;
      tmp = index[r];
      index[r] = index[q];
      index[q] = tmp;


      if ( target < r - p ) {
        q = r - 1;
      } else if ( target > r-p ) {
        target = target - r + p -1;
        p = r + 1;
      } else {
        return values[index[r]];
      }
      
    }

    // Should not reach here
    if ( p==q ) return values[index[p]];
    
    assert( false );
    
    return values[0];
  }

  template <typename valueType>
  inline valueType median( const vector<valueType>& values )
  {
    return kth( values, static_cast<int>( values.size() ) >> 1 );
  }
}




