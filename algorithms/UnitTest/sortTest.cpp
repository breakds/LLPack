/*********************************************************************************
 * File: sortTest.cpp
 * Description: Test facility for sort.hpp in LLPack
 * by BreakDS, @ University of Wisconsin-Madison, Wed Jun  6 12:10:19 CDT 2012
 *********************************************************************************/
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <functional>
#include "../sort.hpp"


using std::vector;

int main() 
{
  int n = 100;
  srand( time( NULL ) );
  vector<int> vals;
  vals.resize(n);
  for ( int& item : vals ) item = rand() % 1000;
  function<bool(const int&, const int&)> compare = [](const int& a, const int& b) -> bool {
    return a > b;
  };
  vector<int> ind = std::move( sorting::index_sort( vals, compare ) );
  for ( int& item : ind ) {
    printf( "%d\n", vals[item] );
  }
  return 0;
}
