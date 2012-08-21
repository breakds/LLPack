/*********************************************************************************
 * File: debug.hpp
 * Description: Debugging Tools
 * by BreakDS, @ University of Wisconsin-Madison, Tue Aug 21 11:53:53 CDT 2012
 *********************************************************************************/

#pragma once

#include <string>
#include <cstring>
#include <vector>
#include <type_traits>
#include <cmath>
#include "extio.hpp"
#include "candy.hpp"
#include "MacroTool.hpp"

namespace debugger
{
  // If proof = true, the Recorder will load the file for comaprison
  // otherwise, it simply record
  template <bool proof=false>
  class Recorder
  {
  public:
    FILE *file;
  public:
    Recorder( const char *filename )
    {
      if ( proof ) {
        file = fopen( filename, "r" );
      } else {
        file = fopen( filename, "w" );
      }
      if ( !file ) {
        Error( "Failed to open %s for debugger::Recorder.", filename );
        exit( -1 );
      }
    }

    ~Recorder()
    {
      fclose( file );
    }

    template <typename T, bool P=proof>
    void record( const char* name, const T& data,
                 typename std::enable_if<!P>::type __attribute__((__unused__)) *padding=nullptr ) const
    {
      int len = strlen(name);
      // write descriptive name for this item
      fwrite( &len, sizeof(int), 1, file );
      fwrite( name, sizeof(char), len+1, file );
      // write data
      fwrite( &data, sizeof(T), 1, file );
    }

    template <typename T, bool P=proof>
    void validate( const T& data,
                   typename std::enable_if<P>::type __attribute__((__unused__)) *padding=nullptr ) const
    {
      
      int len = 0;
      fread( &len, sizeof(int), 1, file );
      // read descriptive name for this item
      char descr[len+1];
      fread( descr, sizeof(char), len+1, file );
      // read data
      T d;
      fread( &d, sizeof(T), 1, file );
      equalCheck<T>( descr, d, data );
    }
  private:
    template <typename T>
    void equalCheck( const char* name, const T& d0, const T& d1,
                     typename std::enable_if<std::is_same<T,float>::value>::type __attribute__((__unused__))
                     *padding = nullptr ) const
    {
      if ( fabsf(d0 - d1) > 1e-5 ) {
        Error( "inconsistency on %s. Saved: %.5f  vs.  Generated: %.5f.", name, d0, d1 );
        Info( "Press [Enter] to Continue ..." );
        char ch;
        scanf( "%c", &ch );
      }
    }

    template <typename T>
    void equalCheck( const char* name, const T& d0, const T& d1,
                     typename std::enable_if<std::is_same<T,double>::value>::type __attribute__((__unused__))
                     *padding = nullptr ) const
    {
      if ( fabsf(d0 - d1) > 1e-5 ) {
        Error( "inconsistency on %s. Saved: %.5lf  vs.  Generated: %.5lf.", name, d0, d1 );
        Info( "Press [Enter] to Continue ..." );
        char ch;
        scanf( "%c", &ch );
      }
    }

    template <typename T>
    void equalCheck( const char* name, const T& d0, const T& d1,
                     typename std::enable_if<std::is_same<T,int>::value>::type __attribute__((__unused__))
                     *padding = nullptr ) const
    {
      if ( fabsf(d0 - d1) > 1e-5 ) {
        Error( "inconsistency on %s. Saved: %d  vs.  Generated: %d", name, d0, d1 );
        Info( "Press [Enter] to Continue ..." );
        char ch;
        scanf( "%c", &ch );
      }
    }

  };
  
};
