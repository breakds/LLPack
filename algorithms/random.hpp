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
#include <random>
#include "algebra.hpp"
#include "../utils/candy.hpp"
#include "../utils/extio.hpp"

using algebra::norm_l2;

namespace rndgen
{

  // Sample k elements from 0..n-1, with no replacement
  // an implementation of Reservoir Sampling Algorithm
  template <typename dataType>
  inline std::vector<dataType> randperm( const dataType n, const dataType k )
  {
    std::vector<dataType> result;
    if ( n <= k ) {
      result.resize(n);
      for ( dataType i=0; i<n; i++ ) {
        result[i] = i;
      }
    } else {
      result.resize( k );
      for ( dataType i=0; i<k; i++ ) {
        result[i] = i;
      }
      for ( dataType i=k; i<n; i++ ) {
        dataType rnd = rand() % (i+1);
        if ( rnd < k ) {
          rnd = rand() % k;
          result[rnd] = i;
        }
      }
    }
    return result;
  }
  

  inline int randperm( const int n, const int k, int* &result )
  {
    if ( n <= k ) {
      result = new int[n];
      for ( int i=0; i<n; i++ ) {
        result[i] = i;
      }
      return n;
    } else {
      result = new int[k];
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
      return k;
    }
  }


  
  // Sample k elements from an array / vector, with no replacement
  // an implementation of Reservoir Sampling Algorithm
  template <typename T, typename arrayType>
  inline std::vector<T> randperm( const arrayType& array,
                              const int k,
                              const int arrayLen=-1 )
  {

    static_assert( std::is_same<std::vector<T>,arrayType>::value ||
                   std::is_convertible<arrayType,T*>::value ||
                   std::is_convertible<arrayType,const T*>::value,
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

  // generate an index array from 0 to n
  inline std::vector<int> seq( int n )
  {
    std::vector<int> res( n );
    for ( int i=0; i<n; i++ ) {
      res[i] = i;
    }
    return res;
  }

  // random unit vector
  template <typename dataType, typename rngType = std::mt19937>
  inline std::vector<dataType> rnd_unit_vec( int dim, rngType& rng )
  {
    static std::normal_distribution<dataType> ndist( 0.0, 1.0 );
    std::vector<dataType> vec( dim );
    for ( auto& ele : vec ) {
      ele = ndist( rng );
    }
    double len = norm_l2( &vec[0], dim );
    for ( auto& ele : vec ) {
      ele /= len;
    }
    return vec;
  }

  template <typename dataType, typename rngType = std::mt19937>
  inline std::vector<dataType> rnd_uniform_real( int dim, dataType lower, dataType upper, rngType& rng )
  {
    std::uniform_real_distribution<dataType> udist( lower, upper );
    std::vector<dataType> vec( dim );
    for ( auto& ele : vec ) {
      ele = udist( rng );
    }
    return vec;
  }
  
};

