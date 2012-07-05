/*********************************************************************************
 * File: extio.hpp
 * Description: Extension of standard I/O for C++/C
 * by BreakDS, @ University of Wisconsin-Madison, Mar 7 2012
 * ======================================================================
 * - Mar 26 2012, Modified by BreakDS : strf() added
 * - Mar 30 2012, Modified by BreakDS : WITH_OPEN / END_WITH
 *********************************************************************************/

#ifndef LLPACK_EXTIO_HPP
#define LLPACK_EXTIO_HPP

#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <string>
#include <string.h>
#include "MacroTool.hpp"


// Formatted String, which is thread-safe
inline std::string strf( const char* format, ... )
{
  char tmp[200];
  
  va_list argptr;
  va_start( argptr, format );
  vsprintf( tmp, format, argptr );
  va_end( argptr );
  return std::string( tmp );
}

#define Error( format, ... ) ( Signal_Error( __LINE__, __FILE__, format, ##__VA_ARGS__) )

inline void Signal_Error( int line, const char* file, const char* format, ... ) 
{
  fprintf( stderr, "%c[%dm\n", 27, 0  );
  va_list argptr;
  fprintf( stderr, "%c[%d;%dm[ERROR] %c[%dm", 27,1,31,27,0 );
  fprintf( stderr, "%c[%d;%dm", 27,0,31 );
  va_start( argptr, format );
  vfprintf( stderr, format, argptr );
  va_end( argptr );
  fprintf( stderr, "%c[%dm\nat %s:%d\n", 27, 0, file, line );
}

inline int Warning( const char* format, ... ) 
{
#if 1 == DISABLE_LLPACK_WARNING
  va_list argptr;
  fprintf( stderr, "%c[%d;%dm[ Warning ] %c[%dm", 27,0,33,27,0 );
  va_start( argptr, format );
  vfprintf( stderr, format, argptr );
  va_end( argptr );
  fprintf( stderr, "\n" );
#else
  return strlen(format);
#endif
}


inline void Done( const char* format, ... ) 
{
  va_list argptr;
  fprintf( stderr, "%c[%d;%dm[ ok ] %c[%dm", 27,0,32,27,0 );
  va_start( argptr, format );
  vfprintf( stderr, format, argptr );
  va_end( argptr );
  fprintf( stderr, "\n" );
}


inline void Info( const char* format, ... ) 
{
  va_list argptr;
  fprintf( stderr, "%c[%d;%dm[Info] %c[%dm", 27,0,36,27,0 );
  va_start( argptr, format );
  vfprintf( stderr, format, argptr );
  va_end( argptr );
  fprintf( stderr, "\n" );
}



inline int CountSpecifiers( const char* format ) {
  const char *cp = format;
  char pre = 0;
  int n = 0;
  do {
    if ( '%' == *cp ) {
      if ( '%' == pre ) {
        n --;
      } else {
        n ++;
      }
    }
  } while ( 0 != *(++cp) );
  return n;
}

inline void ScanfCheck( int line, const char *file, const char* format, ... )
{
  int r = 0;
  int n = CountSpecifiers( format );
  va_list argptr;
  va_start( argptr, format );
  r = vfscanf( stdin, format, argptr );
  va_end( argptr );
  if ( n > r ) {
    Error( "ScanfCheck() failed.  -- %s:%d", file, line );
    exit( -1 );
  }
}


inline void FscanfCheck( int line, const char *file, FILE *in, const char* format, ... )
{
  int r = 0;
  int n = CountSpecifiers( format );
  va_list argptr;
  va_start( argptr, format );
  r = vfscanf( in, format, argptr );
  va_end( argptr );
  if ( n > r ) {
    Error( "ScanfCheck() failed.  -- %s:%d", file, line );
    exit( -1 );
  }
}



#define SCANF_CHECK(format, ... ) ( ScanfCheck( __LINE__, __FILE__, format, ##__VA_ARGS__ ) )
#define FSCANF_CHECK(format, ... ) ( FscanfCheck( __LINE__, __FILE__, format, ##__VA_ARGS__ ) )




#define WITH_OPEN(fp,filename,mode) WITH_OPEN_(fp,filename,mode,__FILE__,__LINE__)
#define WITH_OPEN_(fp,filename,mode,file,line)                       \
  {                                                                  \
  FILE *fp = fopen( filename, mode );                                \
  if ( ! fp ) {                                                      \
    Error( "Failed to open %s at %s:%d.", filename, file, line );    \
    exit(-1);                                                        \
  }                                                                  
  

#define END_WITH(fp)                            \
  fclose(fp);                                   \
  }
                                                
  






#endif
