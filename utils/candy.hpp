/*********************************************************************************
 * File: candy.hpp
 * Description: Some syntax sugar based on features up to c++11
 * by BreakDS, University of Wisconsin-Madison, Tue Jul  3 11:46:10 CDT 2012
 * ======================================================================
 * 
 *********************************************************************************/

#pragma once
#include <vector>

// +--------------------------------------------------------------------------------
// | Get number of variadic function parameters
// +--------------------------------------------------------------------------------
// credit given to JophannesD from stackoverflow.com
int num_args()
{
  return 0;
}

template <typename H, typename... T>
int num_args( H __attribute__((__unused__)) h, T... t )
{
  return 1 + num_args( t... );
}


// +--------------------------------------------------------------------------------
// | Count variadic template parameters
// +--------------------------------------------------------------------------------
// credit given to www.jot.fm/issues/issue_2008_02/article2/
// count the number of variadic template arguments
template <typename... Args> struct count;

// explicit specialization of no argument
template <> struct count<> {
  static const int value = 0;
};

// explicit specialization of unpacking
template <typename T, typename... Rest> 
struct count<T, Rest...> {
  static const int value = 1 + count<Rest...>::value;
};


// set the parameter to be the length of a vector or nothing
// template <typename T, typename arrayType>
// void get_size( const arrayType& a, int& len,
//                std::enable_if<std::is_same<std::vector<T>,arrayType>::value>::type
//                __attribute__((__unused__)) *padding = 0 )
// {
//   len = static_cast<int>(a);
// }

// template <typename T, typename arrayType>
// void get_size( const arrayType& a, int& len,
//                std::enable_if<!std::is_same<std::vector<T>,arrayType>::value>::type
//                __attribute__((__unused__)) *padding = 0 )
// {}











