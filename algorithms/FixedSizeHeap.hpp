/* by BreakDS
 * Jan 31 2012 @ University of Wisconsin-Madison
 * ----------------------------------------
 * A heap that well-maintained for K-Least element search
 */
#ifndef FIXED_SIZE_HEAP
#define FIXED_SIZE_HEAP

#include <cassert>

template<typename keyType, typename dataType>
struct HeapEle {
  dataType *data;
  keyType key;
  HeapEle() : data(NULL) {}
};
  

template<int size, typename keyType, typename dataType >
class FSHeap {
public:
  HeapEle< keyType, dataType> *h;
  int len;
    
  // The Constructor
  FSHeap() : len(0) {
    h = new HeapEle< keyType, dataType>[size+2];
  }


  // The Destructor
  ~FSHeap() {
    if ( NULL != h ) {
      for ( int i=0; i<size+2; i++ ) {
	if ( NULL != h[i].data ) {
	  delete h[i].data;
	}
      }
      delete[] h;
    }
  }

  // Add a new element into the heap
  inline void Push( keyType key, dataType &data ) {

    assert( len < size );
      
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
  
  inline void Add( keyType key, dataType &data ) {
    if ( len < size ) {
      Push( key, data );
    } else if ( key < h[1].key ) {
      dataType *d = Pop();
      delete d;
      Push( key, data );
    }
  }
  
  
  inline void MaxFix() {
    if ( len <= 0 ) return;
    int i = 1;
    int j = 0;
    int maxp = 0;
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
  
};

#endif
