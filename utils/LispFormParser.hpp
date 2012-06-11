/*********************************************************************************
 * File: LispFormParser.hpp
 * Description: Utility for reading Lisp Forms as Options from files
 * by BreakDS, Wed Jun  6 14:06:00 CDT 2012
 *********************************************************************************/

#pragma once

#include <map>
#include <vector>
#include <string>
#include "extio.hpp"

using std::vector;
using std::map;
using std::string;


class LispFormParser
{
private:
  
  static bool isSpace( const char ch )
  {
    /* whether char ch is a space */
    return '\t' == ch || ' ' == ch || 10 == ch || 13 == ch;
  }

  
  class Lisp
  {
  public:
    // Note: non-leaf lisp object only has a name
    string name;
    vector< Lisp > lst;
    Lisp()
    {
      /* constructor for empty object */
      name = "";
      lst.clear();
    }
    
    Lisp( FILE* stream, bool& indicator )
    {
      
      name = "";
      lst.clear();
      
      // strip leading spaces
      char ch = static_cast<char>( getc( stream ) );
      while ( ch != EOF && isSpace( ch ) ) { 
	ch = static_cast<char>( getc( stream ) );
      }
      
      if ( EOF == ch ) {
	indicator = false;
	return ;
      } else if ( '(' == ch ) {
	// Lisp Object
	bool more;
	Lisp tmp( stream, more );
	name = std::move( tmp.name );
	if ( "" == name ) {
	  Error( "LispFormParser: nil object." );
	  exit( -1 );
	}
	
	do {
	  Lisp tmp( stream, more );
	  if ( "" != tmp.name ) {
	    lst.push_back( std::move( tmp ) );
	  }
	} while ( more );
	indicator = true;
      } else {
	// string object
	while ( ch != EOF && ch != ')' && (!isSpace(ch)) ) {
	  name += ch;
	  ch = static_cast<char>( getc( stream ) );
	}
	if ( EOF == ch || ')' == ch ) {
	  indicator = false;
	} else {
	  indicator = true;
	}
      }
    }

    Lisp( Lisp&& other ) 
    {
      /* Move Constructor */
      lst = std::move( other.lst );
      name = std::move( other.name );
    }
    
    
    const Lisp& operator[]( const string& query ) const
    {
      for ( auto& item : lst ) {
        if ( query == item.name ) {
          return item;
        }
      }
      // Exception: Not Found
      Error( "LispFormParser: item \"%s\" not found.", query.c_str() );
      exit(-1);
    }

    const Lisp& operator[]( const int ind ) const
    {
      if ( ind >= 0 && ind < static_cast<int>( lst.size() ) ) {
        return lst[ind];
      }
      // Exception: out of range
      Error( "LispFormParser: [%d] out of range.", ind );
      exit(-1);
    }

    const string& toString() const
    {
      if ( 1 == lst.size() ) {
        return lst[0].name;
      }
      // Exception: out of range
      Error( "LispFormParser: possibly accessing a composite form." );
      exit(-1);
    }

    const char* c_str() const
    {
      if ( 1 == lst.size() ) {
        return lst[0].name.c_str();
      }
      // Exception: out of range
      Error( "LispFormParser: possibly accessing a composite form." );
      exit(-1);
    }

    int toInt() const
    {
      /* explicit conversion to int */
      if ( 1 == lst.size() ) {
        return atoi( lst[0].name.c_str() );
      }
      // Exception: out of range
      Error( "LispFormParser: possibly accessing a composite form." );
      exit(-1);
    }

    operator const char*() const
    {
      /* implicit conversion to legacy string */
      if ( 1 == lst.size() ) {
        return lst[0].name.c_str();
      }
      // Exception: out of range
      Error( "LispFormParser: possibly accessing a composite form." );
      exit(-1);
    }

    double toDouble() const
    {
      /* explicit conversion to double */
      if ( 1 == lst.size() ) {
        return atof( lst[0].name.c_str() );
      }
      // Exception: out of range
      Error( "LispFormParser: possibly accessing a composite form." );
      exit(-1);
    }
  };
  
  vector< Lisp > options;
  bool loaded;
public:

  LispFormParser()
  {
    loaded = false;
    options.clear();
  }
  
  void parse( const string& filename )
  {
    WITH_OPEN( in, filename.c_str(), "r" );
    bool more = false;
    do {
      Lisp tmp( in, more );
      if ( "" != tmp.name ) {
        if ( "include" == tmp.name ) {
          parse( tmp[0].name );
        } else {
          options.push_back( std::move( tmp ) );
        }
      } 
    } while ( more );
    END_WITH( in );
    loaded = true;
  }

  const Lisp& operator[]( const string& query ) const
  {
    if ( !loaded ) {
      Error( "LispFormParser: please load a file first." );
      exit( -1 );
    }
    for ( auto& item : options ) {
      if ( query == item.name ) {
        return item;
      }
    }
    // Exception: Not Found
    Error( "LispFormParser: item \"%s\" not found.", query.c_str() );
    exit(-1);
  }
  
};
