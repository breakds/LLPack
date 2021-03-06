/*********************************************************************************
 * File: candy.hpp
 * Description: Some syntax sugar based on features up to c++11
 * by BreakDS, University of Wisconsin-Madison, Tue Jul  3 11:46:10 CDT 2012
 * ======================================================================
 * 
 *********************************************************************************/

#pragma once
#include <vector>
#include <type_traits>

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


// +--------------------------------------------------------------------------------
// | Fill a variable with the size of the vector, or do nothing
// +--------------------------------------------------------------------------------
// set the parameter to be the length of a vector or nothing
template <typename T, typename arrayType>
void get_size( const arrayType& a, int& len,
               typename std::enable_if<std::is_same<std::vector<T>,arrayType>::value>::type
               __attribute__((__unused__)) *padding = 0 )
{
  len = static_cast<int>(a.size());
}

template <typename T, typename arrayType>
void get_size( const arrayType __attribute__((__unused__)) &a, int __attribute__((__unused__)) &len,
               typename std::enable_if<!std::is_same<std::vector<T>,arrayType>::value>::type
               __attribute__((__unused__)) *padding = 0 )
{}



// +--------------------------------------------------------------------------------
// | Get the most general numeric type of the input type
// | i.e. floating point   -> double
// |      integral number  -> int
// | Example:
// |      Generalized<unsigned char>::type
// +--------------------------------------------------------------------------------
template <typename T, typename enabled = void>
class Generalized
{
public:
  typedef void type;
};

template <typename T>
class Generalized<T, typename std::enable_if<std::is_integral<T>::value>::type>
{
public:
  typedef int type;
};

template <typename T>
class Generalized<T, typename std::enable_if<std::is_floating_point<T>::value>::type>
{
public:
  typedef double type;
};



// +--------------------------------------------------------------------------------
// | Get the element type of an arrayType
// | Example:
// |      ElementOf<std::vector<double> >::type = double
// +--------------------------------------------------------------------------------
template <typename arrayType>
class ElementOf
{
  static arrayType a;
public:
  typedef typename std::remove_reference<decltype(a[0])>::type type;
};



// +--------------------------------------------------------------------------------
// | Superior (MAX)
// | Inferior (MIN)
// +--------------------------------------------------------------------------------
template <typename numeric>
inline numeric TEHMAX( const numeric& n, const numeric& m )
{
  return ( n > m ) ? n : m;
}

template <typename numeric>
inline numeric SUP( const numeric& n, const numeric& m )
{
  return ( n > m ) ? n : m;
}

template <typename Head, typename... Tail>
inline Head SUP( const Head& head, const Tail&... tail )
{
  return THEMAX( head, SUP(tail...) );
}

template <typename numeric>
inline numeric THEMIN( const numeric& n, const numeric& m )
{
  return ( n < m ) ? n : m;
}

template <typename numeric>
inline numeric INF( const numeric& n, const numeric& m )
{
  return ( n < m ) ? n : m;
}

template <typename Head, typename... Tail>
inline Head INF( const Head& head, const Tail&... tail )
{
  return THEMIN( head, INF(tail...) );
}


// +--------------------------------------------------------------------------------
// | Padding for static overloading
// +--------------------------------------------------------------------------------
#define ENABLE_IF(x) typename std::enable_if<x>::type __attribute__((__unused__)) *padding=nullptr







  



  













