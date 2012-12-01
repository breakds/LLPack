/// Filename: llvm-aux/bitset.hpp
/// Description: a simple bit set
/// Author: BreakDS <breakds@cs.wisc.edu>
/// Created: Sun Oct  7 15:57:01 CDT 2012

#pragma once

#include <inttypes.h>
#include <vector>
#include <bitset>
#include <iostream>
#include <cstdio>
#include <string>


namespace {
  // constant array represent number with an "1" at corresponding position 
  // in their binary representation
  const uint64_t allone = 18446744073709551615ULL;
    
  const uint64_t setbit[64] = { 1,2,4,8,16,32,64,128,256,512,1024,
                                2048,4096,8192,16384,32768,65536,131072,
                                262144,524288,1048576,2097152,4194304,8388608,
                                16777216,33554432,67108864,134217728,268435456,
                                536870912,1073741824,2147483648,4294967296,8589934592,
                                17179869184,34359738368,
                                68719476736,
                                137438953472ULL,
                                274877906944ULL,
                                549755813888ULL,
                                1099511627776ULL,
                                2199023255552ULL,
                                4398046511104ULL,
                                8796093022208ULL,
                                17592186044416ULL,
                                35184372088832ULL,
                                70368744177664ULL,
                                140737488355328ULL,
                                281474976710656ULL,
                                562949953421312ULL,
                                1125899906842624ULL,
                                2251799813685248ULL,
                                4503599627370496ULL,
                                9007199254740992ULL,
                                18014398509481984ULL,
                                36028797018963968ULL,
                                72057594037927936ULL,
                                144115188075855872ULL,
                                288230376151711744ULL,
                                576460752303423488ULL,
                                1152921504606846976ULL,
                                2305843009213693952ULL,
                                4611686018427387904ULL,
                                9223372036854775808ULL };

  const uint64_t unsetbit[64] = { 18446744073709551614ULL,
                                  18446744073709551613ULL,
                                  18446744073709551611ULL,
                                  18446744073709551607ULL,
                                  18446744073709551599ULL,
                                  18446744073709551583ULL,
                                  18446744073709551551ULL,
                                  18446744073709551487ULL,
                                  18446744073709551359ULL,
                                  18446744073709551103ULL,
                                  18446744073709550591ULL,
                                  18446744073709549567ULL,
                                  18446744073709547519ULL,
                                  18446744073709543423ULL,
                                  18446744073709535231ULL,
                                  18446744073709518847ULL,
                                  18446744073709486079ULL,
                                  18446744073709420543ULL,
                                  18446744073709289471ULL,
                                  18446744073709027327ULL,
                                  18446744073708503039ULL,
                                  18446744073707454463ULL,
                                  18446744073705357311ULL,
                                  18446744073701163007ULL,
                                  18446744073692774399ULL,
                                  18446744073675997183ULL,
                                  18446744073642442751ULL,
                                  18446744073575333887ULL,
                                  18446744073441116159ULL,
                                  18446744073172680703ULL,
                                  18446744072635809791ULL,
                                  18446744071562067967ULL,
                                  18446744069414584319ULL,
                                  18446744065119617023ULL,
                                  18446744056529682431ULL,
                                  18446744039349813247ULL,
                                  18446744004990074879ULL,
                                  18446743936270598143ULL,
                                  18446743798831644671ULL,
                                  18446743523953737727ULL,
                                  18446742974197923839ULL,
                                  18446741874686296063ULL,
                                  18446739675663040511ULL,
                                  18446735277616529407ULL,
                                  18446726481523507199ULL,
                                  18446708889337462783ULL,
                                  18446673704965373951ULL,
                                  18446603336221196287ULL,
                                  18446462598732840959ULL,
                                  18446181123756130303ULL,
                                  18445618173802708991ULL,
                                  18444492273895866367ULL,
                                  18442240474082181119ULL,
                                  18437736874454810623ULL,
                                  18428729675200069631ULL,
                                  18410715276690587647ULL,
                                  18374686479671623679ULL,
                                  18302628885633695743ULL,
                                  18158513697557839871ULL,
                                  17870283321406128127ULL,
                                  17293822569102704639ULL,
                                  16140901064495857663ULL,
                                  13835058055282163711ULL,
                                  9223372036854775807ULL };
    
};
  
class bitset
{
private:
  int n;
  std::vector<uint64_t> masks;

public:
    
  bitset() : n(0) {}
    
  // create an empty set with _n possible elements
  bitset( int _n ) : n(_n) 
  {
    masks.resize( ( n >> 6 ) + 1 );
    for ( int i=0, end = static_cast<int>( masks.size() ); i<end; i++ ) {
      masks[i] = 0;
    }
  }

  // copy constructor
  bitset( const bitset& other ) : n(other.n)
  {
    n = other.n;
    masks = other.masks;
  }

  // move constructor
  bitset( bitset&& other ) : n(other.n)
  {
    n = other.n;
    masks.swap( other.masks );
  }

    
  inline void resize( int _n = -1 ) 
  {
    if ( 0 < _n ) {
      n = _n;
    }
    masks.resize( ( n >> 6 ) + 1 );
    for ( int i=0, end = static_cast<int>( masks.size() ); i<end; i++ ) {
      masks[i] = 0;
    }
  }
    
  inline void set( int i ) 
  {
    int idx = i >> 6;
    int pos = i & 0x3f;
    masks[idx] |= setbit[pos];
  }

  inline void setAll()
  {
    for ( int i=0, end=static_cast<int>( masks.size() ); i<end; i++ ) {
      masks[i] = allone;
    }
  }

  inline void unset( int i ) 
  {
    int idx = i >> 6;
    int pos = i & 0x3f;
    masks[idx] &= unsetbit[pos];
  }

  inline bool member( int i ) const
  {
    int idx = i >> 6;
    int pos = i & 0x3f;
    return static_cast<bool>( masks[idx] & setbit[pos] );
  }


  inline void list( std::string prefix, int offset = 0 )
  {
    std::cerr << "{ ";
    for ( int i=0; i<n; i++ ) {
      if ( member(i) ) {
        std::cerr << prefix << i + offset << " ";
      }
    }
    std::cerr << "} ";
  }


  inline void list( char prefix, int offset = 0 )
  {
    fprintf( stderr, "{ " );
    for ( int i=0; i<n; i++ ) {
      if ( member(i) ) {
        fprintf( stderr, "%c%d ", prefix, i + offset );
      }
    }
    fprintf( stderr, "} " );
  }

  // set union
  inline const bitset& operator+=( const bitset& other )
  {
    // if ( masks.size() != other.masks.size() ) {
    //   std::cerr << masks.size() << " : " << other.masks.size() << "\n";
    // }
    for ( int i=0, end=static_cast<int>( masks.size() ); i<end; i++ ) {
      masks[i] |= other.masks[i];
    }
    return (*this);
  }
    
  // set intersection
  inline const bitset& operator*=( const bitset& other ) 
  {

    for ( int i=0, end=static_cast<int>( masks.size() ); i<end; i++ ) {
      masks[i] &= other.masks[i];
    }
    return (*this);
  }
    
  // copy assignment
  inline const bitset& operator=( const bitset& other )
  {
    n = other.n;
    masks = other.masks;
    return (*this);
  }

  // copy assignment
  inline const bitset& operator=( bitset&& other )
  {
    n = other.n;
    masks.swap( other.masks );
    return (*this);
  }

  inline bool operator==( const bitset& other ) const
  {
    for ( int i=0, end=static_cast<int>( masks.size() ); i<end; i++ ) {
      if ( masks[i] != other.masks[i] ) {
        return false;
      }
    }
    return true;
  }



  inline bool operator!=( const bitset& other ) const
  {
    for ( int i=0, end=static_cast<int>( masks.size() ); i<end; i++ ) {
      if ( masks[i]  != other.masks[i] ) {
        return true;
      }
    }
    return false;
  }

  static bool validate( const bitset &a, const bitset &b ) {
    if ( a.masks.size() != b.masks.size() ) {
      std::cerr << "size: " << a.masks.size() << " vs " << b.masks.size() << "\n";
      std::cerr << "n: " << a.n << " vs " << b.n << "\n";
      return false;
    }
    return true;
  }

};


