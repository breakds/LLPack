#include "../heap.hpp"


using SimpleTool::FixedSizeHeap;

template <typename T>
inline void swap( T *a, uint x, uint y ) {
  static T t;
  t = a[x];
  a[x] = a[y];
  a[y] = t;
}

int main() {
  
  srand(time(NULL));
  uint n = 100;
  uint m = 10;
  int key[n];
  for ( uint i=0; i<n; i++ ) {
    key[i] = i;
  }
  for ( uint i=0; i<2*n; i++ ) {
    uint x = rand() % n;
    uint y = rand() % n;
    if ( x != y ) {
      swap( key, x, y );
    }
  }

  FixedSizeHeap< int, int > heap(2);

  
  heap.Resize( m );

  for ( uint i=0; i< n; i++ ) {
    heap.Add( key[i], key[i] );
  }

  for ( uint i=0; i<n; i++ ) {
    printf( "%d ", key[i] );
  }
  printf( "\n" );

  for ( uint i=0; i<m; i++ ) {
    int *ip = heap.Pop();
    printf( "%d\n", *ip );
    DeleteToNullWithTest( ip );
  }

  return 0;
}
