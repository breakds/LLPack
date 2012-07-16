/*********************************************************************************
 * File: random.hpp
 * Description: random number generating algorithms
 * by BreakDS, @ University of Wisconsin-Madison, Sun Jul 15 15:56:21 CDT 2012
 *********************************************************************************/

#pragma once
#include <type_traits>
#include <vector>
#include "../utils/candy.hpp"

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
  // template <typename T, typename arrayType>
  // inline std::vector<T> perm( const arrayType& array,
  //                             const int k,
  //                             const int arrayLen=-1,
  //                             typename std::enable_if<std::is_same<std::vector<T>,arrayType>::value ||
  //                             std::is_convertible<arrayType,T*>::value>::type
  //                             __attribute__((__unused__)) *padding=0 )
  // {

  //   int n = arrayLen;
  //   get_size( array, n );

  //   // if ( 0 >= arrayLen ) {
  //   //   n = static_cast<int>( array.size() );
  //   // } else {
  //   //   n = arrayLen;
  //   // }

  //   std::vector<T> result;
  //   if ( n <= k ) {
  //     result.resize(n);
  //     for ( int i=0; i<n; i++ ) {
  //       result[i] = array[i];
  //     }
  //   } else {
  //     result.resize( k );
  //     for ( int i=0; i<k; i++ ) {
  //       result[i] = array[i];
  //     }
  //     for ( int i=k; i<n; i++ ) {
  //       int rnd = rand() % (i+1);
  //       if ( rnd < k ) {
  //         rnd = rand() % k;
  //         result[rnd] = array[i];
  //       }
  //     }
  //   }
  //   return result;
  // }

};

