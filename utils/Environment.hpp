/*********************************************************************************
 * File: enviroment.hpp
 * Description: wrapper for lisp form parser
 * by BreakDS, University of Wisconsin-Madison, Tue Jul  3 12:38:02 CDT 2012
 * ======================================================================
 * 
 *********************************************************************************/

#pragma once

#include <string>
#include "extio.hpp"
#include "candy.hpp"
#include "LispFormParser.hpp"

namespace EnvironmentVariable
{
  LispFormParser env;


  // signature injection
  
  namespace {
    inline void seal_iter( FILE *out, const char* name )
    {
      // write value
      int val = env[name];
      fwrite( &val,sizeof(int), 1, out );
    }

    template <typename... T>
      inline void seal_iter( FILE *out, const char* name, const T... t ) 
    {
      seal_iter( out, name );
      seal_iter( out, t... );
    }

    inline void unseal_iter( FILE *in, const char *name )
    {
      // read value
      int val = 0;
      fread( &val, sizeof(int), 1, in );
      if ( val != env[name] ) {
        Error( "unseal() falied due to mismatch on %s. current: %d, load: %d.", name, env[name].toInt(), val );
        exit( -1 );
      }
    }

    template <typename... T>
      inline void unseal_iter( FILE *in, const char *name, const T... t )
    {
      unseal_iter( in, name );
      unseal_iter( in, t... );
    }

  }

  template <typename... T>
  inline void seal( FILE *out, const T... t )
  {
    if ( !out ) {
      Error( "seal() failed due to corrupted file descriptor pointer." );
      exit( -1 );
    }
    int s = 880518; // indicator of a signature
    fwrite( &s, sizeof(int), 1, out );
    int num = num_args( t... );
    fwrite( &num, sizeof(uint), 1, out );
    seal_iter( out, t... );
  }


  template <typename... T>
  inline void unseal( FILE *in, const T... t )
  {
    if ( !in ) {
      Error( "unseal() failed due to corrupted file descriptor pointer." );
      exit( -1 );
    }

    int s = 0;
    fread( &s, sizeof(int), 1, in );
    if ( 880518 != s ) {
      Error( "unseal() failed due to wrong signature indicator. Are you sure you want to call unseal() here?" );
      exit( -1 );
    }

    int num = num_args( t... );
    fread( &s, sizeof(int), 1, in );
    if ( num != s ) {
      Error( "unseal() failed due to wrong number of signature entries. need: %d, but load: %d.", num, s );
      exit( -1 );
    }

    unseal_iter( in, t... );
  }
    
}
