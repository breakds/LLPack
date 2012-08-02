//////////////////////////////////////////////////////////
// Filename: heap.hpp
// Author:   BreakDS
// Date:     Tue Nov  9 15:58:13 CST 2010
// Description: This file contains implementation of simp
//              -le max heap
//
//////////////////////////////////////////////////////////
#ifndef HEAP_HPP
#define HEAP_HPP

#include <string.h>
#include <valarray>
#include <cassert>
#include "../utils/SafeOP.hpp"

using std::valarray;

namespace SimpleTool{

  template<class T>
  class heap{
  private:

    inline void max_rectify( int x ){
      if ( x > p ) return;
      int i(x), m(x), t(0);
      while ( true ){
	m = i;
	if ( ( (i << 1) <= p ) && ( value[a[i<<1]] > value[a[m]] ) ) m = i << 1;
	if ( ( (i<<1)+1 <= p ) && ( value[a[(i<<1)+1]] > value[a[m]] ) ) m = ( i<< 1 ) + 1;
	if ( m == i ) break;
	t = a[i];
	a[i] = a[m];
	a[m] = t;
	i = m;
      }
    }


    void init(){
      int last = p >> 1;
      for ( int i=last; i>=1; i-- ){
	max_rectify( i );
      }
    }
  public:
    int size;
    int p;
    int *a;
    T *value;


    heap( int requiredSize ){
      size = requiredSize;
      p = -1;
      value = new T[size];
      a = new int[size];
    }

    heap(){
      size = 0;
      p = -1;
      a = NULL;
      value = NULL;
    }
    

    /// flag = true for min-heap
    heap( int requiredSize, int n, int *index, T *values, bool flag = false ){
      size = requiredSize;
      p = n;
      value = new T[requiredSize];
      memcpy( value, values, sizeof(T) * n );
      a = new int[requiredSize];
      memcpy( a+1, index, sizeof(int) * n );
      if ( flag ){

	for ( int i=0; i<n; i++ ){
	  value[i] = -value[i];
	}
      }
      init();
    }
    
    ~heap(){
      delete[] a;
      delete[] value;
    }

    bool isEmpty(){
      return p<1;
    }



    /// flag = true for min-heap
    /// provide requiredSize = -1 if you don't want to change the size
    void reassign( int requiredSize, int n, int *index, T *values, bool flag = false ){
      if ( requiredSize > size ){
	size = requiredSize;
	if ( a != NULL ) delete[] a;
	a = new int[size];
	if ( value != NULL ) delete value;
	value = new T[size];
      }
      p = n;
      memcpy( value, values, sizeof(T) * n );
      memcpy( a+1, index, sizeof(int) * n );
      if ( flag ){
	for ( int i=0; i<n; i++ ){
	  value[i] = -value[i];
	}
      }
      init();
    }
    



    inline int pop(){
      if ( p > 0 ){
	int i = a[1];
	a[1] = a[p];
	p--;
	max_rectify(1);
	return i;
      }
    }

    inline void insert(int x){
      p++;
      a[p] = x;
      int i(p);
      int t(0);
      while ( (i >> 1) > 0 && value[a[i>>1]] < value[a[i]]){
	t = a[i];
	a[i] = a[i>>1];
	a[i>>1] = t;
	i = i>>1;
      }
    }
  };
  
  template<typename keyType>
  struct IndexHeapEle {
    int index;
    keyType key;
  };


  // This is a min heap
  template<typename keyType>
  class IndexHeap {
  public:
    valarray< IndexHeapEle< keyType > > h;
    unsigned int p;
    // The Constructor
    IndexHeap( const uint size ) {
      p = 0;
      h.resize( size + 2 );
    }
    
    // Resize
    inline void Resize( const uint size ) {
      if ( size + 2 > h.size() ) {
	h.resize( size + 2 );
      }
    }
    // Reinitialize
    inline void Init() {
      p = 0;
    }
    
    // Add a new element into the heap
    inline void Push( const keyType key, const int index ) {
      p++;
      h[p].key = key;
      h[p].index = index;
      
      int i = p;
      int j = i >> 1;
      IndexHeapEle< keyType > heTmp;
      
      while ( j > 0 && h[i].key < h[j].key ) {
	heTmp = h[i];
	h[i] = h[j];
	h[j] = heTmp;
	i = j;
	j >>= 1;
      }
    }

    inline void MinFix() {
      if ( p <= 0 ) return;
      unsigned int i=1;
      unsigned int j=0;
      unsigned int minp = 0;
      IndexHeapEle< keyType > heTmp;
      do {
	minp = i;
	j = i << 1;
	if ( j <= p && h[j].key < h[minp].key ) minp = j;
	j++;
	if ( j <= p && h[j].key < h[minp].key ) minp = j;

	if ( minp != i ) {
	  heTmp = h[i];
	  h[i] = h[minp];
	  h[minp] = heTmp;
	  i = minp;
	} else {
	  break;
	}
      } while ( true );
    }
    
    inline IndexHeapEle< keyType > Pop() {
      if ( p > 0 ) { 
	IndexHeapEle< keyType > ele = h[1];
	h[1] = h[p--];
	MinFix();
	return ele;
      }
      IndexHeapEle< keyType > ele;
      ele.key = static_cast<keyType>( 0 );
      ele.index = -1;
      return ele;
    }



    inline bool Empty() const {
      return p < 1;
    }
  };






  // A heap that well-maintained for K-Least element search
  template<typename keyType, typename dataType>
  struct HeapEle {
    dataType *data;
    keyType key;
    HeapEle() : data(NULL) {}
  };

  template<typename keyType, typename dataType >
  class FixedSizeHeap {
  private:
    // Add a new element into the heap
    inline void Push( keyType key, const dataType &data ) {

      assert( len < capacity );
      
      if( 0 == len ) {
        h[1].key = key;
        h[1].data = new dataType( data );
        len = 1;
        return ;
      }

      len++;
      h[len].key = key;
      h[len].data = new dataType( data );
    
    
      int i = len;
      int j = i >> 1;
      HeapEle< keyType, dataType> heTmp;
      while ( j > 0 ) {
        if ( h[i].key > h[j].key ) {
          heTmp = h[i];
          h[i] = h[j];
          h[j] = heTmp;
          i = j;
          j >>= 1;
        } else {
          break;
        }
      }
    }

  public:
    HeapEle< keyType, dataType> *h;
    uint len;
    uint size;
    uint capacity; // The size of the container
    
    
    // The Constructor
    FixedSizeHeap( uint s ) : len(0) {
      size = s;
      capacity = s + 2;
      h = new HeapEle< keyType, dataType>[capacity];
    }

    inline void Clear() {
      if ( NULL != h ) {
        for ( uint i=0; i<capacity; i++ ) {
          DeleteToNullWithTest( h[i].data );
        }
      }
    }

    inline void ClearData() {
      if ( NULL != h ) {
        for ( uint i=0; i<capacity; i++ ) {
          DeleteToNullWithTest( h[i].data );
        }
        DeleteToNullWithTestArray(h);
      }
    }
    

    inline void Resize( uint s ) {
      size = s;
      len = 0;
      if ( s + 2 < capacity ) {
        return ;
      }
      
      ClearData();
      capacity = s + 2;
      h = new HeapEle< keyType, dataType>[capacity];
    }


    // The Destructor
    ~FixedSizeHeap() {
      ClearData();
    }

  
    inline void Add( keyType key, const dataType &data ) {
      if ( len < size ) {
        Push( key, data );
      } else if ( key < h[1].key ) {
        dataType *d = Pop();
        DeleteToNullWithTest( d );
        Push( key, data );
      }
    }
  
  
    inline void MaxFix() {
      if ( len <= 0 ) return;
      uint i = 1;
      uint j = 0;
      uint maxp = 0;
      HeapEle< keyType, dataType> heTmp;
      do {
        maxp = i;
        j = i << 1;
        if ( j <= len && h[j].key > h[maxp].key ) {
          maxp = j;
        }

        j++;
        if ( j <= len && h[j].key > h[maxp].key ) {
          maxp = j;
        }

        if ( maxp == i ) {
          break;
        } else {
          heTmp = h[i];
          h[i] = h[maxp];
          h[maxp] = heTmp;
          i = maxp;
        }
      } while ( true );
    }
    

    // Note: the acceptor is responsible to destroy the pointer
    inline dataType *Pop() {
      if ( len > 0 ) {
        dataType *re = h[1].data;
        h[1] = h[len];
        h[len--].data = NULL;
        MaxFix();
        return re;
      } 
      return NULL;
    }

    // The with-key version
    // Note: the acceptor is responsible to destroy the pointer
    inline dataType *Pop( keyType &key ) {
      if ( len > 0 ) {
        dataType *re = h[1].data;
        key = h[1].key;
        h[1] = h[len];
        h[len--].data = NULL;
        MaxFix();
        return re;
      } 
      return NULL;
    }

    inline bool Empty() const
    {
      return len == 0;
    }
  
  };
}




#endif
