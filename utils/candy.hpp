/*********************************************************************************
 * File: candy.hpp
 * Description: Some syntax sugar based on features up to c++11
 * by BreakDS, University of Wisconsin-Madison, Tue Jul  3 11:46:10 CDT 2012
 * ======================================================================
 * 
 *********************************************************************************/

#pragma once

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

