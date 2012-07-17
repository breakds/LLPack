/*********************************************************************************
 * File: random.hpp
 * Description: random number generating algorithms
 * by BreakDS, @ University of Wisconsin-Madison, Sun Jul 15 15:56:21 CDT 2012
 *********************************************************************************/

#pragma once
#include <type_traits>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "../utils/candy.hpp"
#include "../utils/extio.hpp"


namespace rndgen
{

  // Sample k elements from 0..n-1, with no replacement
  // an implementation of Reservoir Sampling Algorithm
  inline std::vector<int> randperm( const int n, const int k )
  {
    std::vector<int> result;
    if ( n <= k ) {
      result.resize(n);
      for ( int i=0; i<n; i++ ) {
        result[i] = i;
      }
    } else {
      result.resize( k );
      for ( int i=0; i<k; i++ ) {
        result[i] = i;
      }
      for ( int i=k; i<n; i++ ) {
        int rnd = rand() % (i+1);
        if ( rnd < k ) {
          rnd = rand() % k;
          result[rnd] = i;
        }
      }
    }
    return result;
  }

  
  // Sample k elements from an array / vector, with no replacement
  // an implementation of Reservoir Sampling Algorithm
  template <typename T, typename arrayType>
  inline std::vector<T> randperm( const arrayType& array,
                              const int k,
                              const int arrayLen=-1 )
  {

    static_assert( std::is_same<std::vector<T>,arrayType>::value ||
                   std::is_convertible<arrayType,T*>::value,
                   "Not a valid array type. Did you specify the wrong element type?" );
    int n = arrayLen;
    get_size<T>( array, n );

    if ( 0 >= n ) {
      Error( "Bad length of array. Did you forget to provide the length?" );
      exit( -1 );
    }
    
    std::vector<T> result;
    if ( n <= k ) {
      result.resize(n);
      for ( int i=0; i<n; i++ ) {
        result[i] = array[i];
      }
    } else {
      result.resize( k );
      for ( int i=0; i<k; i++ ) {
        result[i] = array[i];
      }
      for ( int i=k; i<n; i++ ) {
        int rnd = rand() % (i+1);
        if ( rnd < k ) {
          rnd = rand() % k;
          result[rnd] = array[i];
        }
      }
    }
    return result;
  }
  
};

