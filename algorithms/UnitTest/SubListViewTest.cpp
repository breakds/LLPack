#include <cstdio>
#include <vector>
#include "../list.hpp"

int main()
{
  std::vector<int> a(100);
  for ( int i=0; i<100; i++ ) {
    a[i] = i;
  }
  std::vector<int> idx;
  idx.push_back(5);
  idx.push_back(93);
  idx.push_back(27);
  auto sbv = std::move( SubList::create( a, idx ) );
  printf( "size: %d\n", sbv.size() );
  for ( auto& ele : sbv ) {
    printf( "%d\n", ele );
  }
  return 0;
}
    


