#ifndef LLPACK_SAFE_OP
#define LLPACK_SAFE_OP

#include <string>
#include <cstdio>

template < typename T > void DeleteToNull( T* &pointer )
{
  delete pointer;
  pointer = NULL;
}
template < typename T > void DeleteToNullWithTest( T* &pointer )
{
  if ( NULL != pointer ) {
    delete pointer;
    pointer = NULL;
  }
}
template < typename T > void DeleteToNullArray( T* &array_pointer )
{
  delete[] array_pointer;
  array_pointer = NULL;
}
template < typename T > void DeleteToNullWithTestArray( T* &array_pointer )
{
  if ( NULL != array_pointer ) {
    delete[] array_pointer;
    array_pointer = NULL;
  }
}
#endif
